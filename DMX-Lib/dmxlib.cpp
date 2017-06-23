/*
  DMX-Lib - A library that simplifies usage of QLC+ plugins separately from the main program.
  dmxlib.cpp

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

#include "dmxlib.h"
#include <QDebug>
#include <QPluginLoader>
#include <QDir>
#include <QDirIterator>

#if defined(WIN32) || defined(Q_OS_WIN)
#   define PluginExt    "*.dll" // Dynamic-Link Library
#elif defined(__APPLE__) || defined(Q_OS_MAC)
#   define PluginExt  "*.dylib" // DYnamic LIBrary
#else
#   define PluginExt    "*.so"  // Shared Object
#endif

DMXLib::DMXLib()
{
    QDirIterator it(PLUGINSPATH, QStringList() << PluginExt, QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString pluginFile = it.next();
        QPluginLoader loader(pluginFile);
        QLCIOPlugin *ptr = qobject_cast<QLCIOPlugin*>(loader.instance());
        if (!m_plugins.keys().contains(ptr->name())) {
            ptr->init();
            m_plugins.insert(ptr->name(), ptr);
        }
    }
}

QMap<QString, QLCIOPlugin *> DMXLib::plugins()
{
    return m_plugins;
}
