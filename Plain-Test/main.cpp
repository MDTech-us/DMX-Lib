/*
  Demo of direct usage of QLC+ plugins.
  main.cpp

  Copyright (C) Maxwell Dreytser

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0.txt

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#include <qlcioplugin.h>
#include <QCoreApplication>
#include <QDebug>
#include <QDirIterator>
#include <QPluginLoader>
#include <QMap>
#include <QTime>

#if defined(WIN32) || defined(Q_OS_WIN)
#   define PluginExt    "*.dll" // Dynamic-Link Library
#elif defined(__APPLE__) || defined(Q_OS_MAC)
#   define PluginExt  "*.dylib" // DYnamic LIBrary
#else
#   define PluginExt    "*.so"  // Shared Object
#endif

int main(int argc, char **argv) {
    QCoreApplication a(argc, argv);

    QMap<QString, QLCIOPlugin *> plugins;

    QDirIterator it(PLUGINSPATH, QStringList() << PluginExt, QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString pluginFile = it.next();
        qDebug() << pluginFile;
        QPluginLoader loader(pluginFile);
        QLCIOPlugin *ptr = qobject_cast<QLCIOPlugin*>(loader.instance());
        if (!plugins.keys().contains(ptr->name())) {
            ptr->init();
            plugins.insert(ptr->name(), ptr);
            qDebug() << ptr->name() << ptr->outputs();
        }
    }

    // I am using and FTDI (DMX USB) adapter for testing. (replace with another plugin if needed)
    QLCIOPlugin *FTDIOut = plugins.value("DMX USB");
    FTDIOut->openOutput(0, 0);

    QByteArray data;
    data[0] = (uchar)255;
    data[1] = (uchar)0;
    data[2] = (uchar)255;
    data[3] = (uchar)100;
    FTDIOut->writeUniverse(0, 0, data);

    int origBrightness = 10;
    double brightness = 10;
    double changePerMs = 0.1;

    QTime timer;
    timer.start();

    while (true)
    {
        while (brightness < 255) {
            brightness = origBrightness + changePerMs * timer.elapsed();
            //qDebug() << brightness << changePerMs * timer.elapsed();
            if (brightness > 255)
                brightness = 255;
            data[1] = (uchar)brightness;

            FTDIOut->writeUniverse(0, 0, data);
            //usleep(100);
            //qDebug() << data;
        }
        origBrightness = 255;
        changePerMs = changePerMs * -1;
        timer.restart();

        while (brightness > 10) {
            brightness = origBrightness + changePerMs * timer.elapsed();
            //qDebug() << brightness << changePerMs * timer.elapsed();
            if (brightness < 10)
                brightness = 10;
            data[1] = (uchar)brightness;

            FTDIOut->writeUniverse(0, 0, data);
            //usleep(100);
            //qDebug() << data;
        }
        origBrightness = 0;
        changePerMs = changePerMs * -1;
        timer.restart();
    }
    qDebug() << plugins;

    return a.exec();
}
