/*
  DMX-Lib - A library that simplifies usage of QLC+ plugins separately from the main program.
  dmxlib.h

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

#ifndef DMXLIB_H
#define DMXLIB_H

#include <qlcioplugin.h>
#include <QMap>
#include <QtCore/qglobal.h>

#if defined(DMXLIB_LIBRARY)
#  define DMXLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define DMXLIBSHARED_EXPORT Q_DECL_IMPORT
#endif

class DMXLIBSHARED_EXPORT DMXLib
{

public:
    DMXLib();

    QMap<QString, QLCIOPlugin *> plugins();

private:
    QMap<QString, QLCIOPlugin *> m_plugins;
};

#endif // DMXLIB_H
