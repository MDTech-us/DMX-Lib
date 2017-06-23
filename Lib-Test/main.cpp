/*
  Demo of usage of QLC+ plugins through DMX-Lib.
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

//#include <qlcioplugin.h> - Not needed since it is already included in dmxlib.h.
#include <dmxlib.h>

#include <QCoreApplication>
#include <QDebug>
#include <QTime>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DMXLib writerLib;
    qDebug() << writerLib.plugins();
    
    QLCIOPlugin *FTDIOut = writerLib.plugins().value("DMX USB");

    FTDIOut->openOutput(0, 0);

    QByteArray data;
    data[0] = (uchar)255;
    data[1] = (uchar)255;
    data[2] = (uchar)255;
    data[3] = (uchar)255;
    FTDIOut->writeUniverse(0, 0, data);

    int origBrightness = 255;
    double brightness = 255;
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
            data[0] = (uchar)brightness;

            FTDIOut->writeUniverse(0, 0, data);
            usleep(250);
            //qDebug() << data;
        }
        origBrightness = 255;
        changePerMs = changePerMs * -1;
        timer.restart();

        while (brightness > 0) {
            brightness = origBrightness + changePerMs * timer.elapsed();
            //qDebug() << brightness << changePerMs * timer.elapsed();
            if (brightness < 0)
                brightness = 0;
            data[0] = (uchar)brightness;

            FTDIOut->writeUniverse(0, 0, data);
            usleep(250);
            //qDebug() << data;
        }
        origBrightness = 0;
        changePerMs = changePerMs * -1;
        timer.restart();
    }

    return a.exec();
}
