#
#  DMX-Lib - A library that simplifies usage of QLC+ plugins separately from the main program.
#  DMX-Lib.pro
#
#  Copyright (C) Maxwell Dreytser
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0.txt
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.


include(../variables.pri)

QT       -= gui

TARGET = DMXLib
TEMPLATE = lib

win32:QMAKE_LFLAGS += -shared

DEFINES += DMXLIB_LIBRARY

INCLUDEPATH += ../plugins/interfaces

SOURCES += dmxlib.cpp 

HEADERS += dmxlib.h
        
HEADERS += ../plugins/interfaces/qlcioplugin.h
SOURCES += ../plugins/interfaces/qlcioplugin.cpp


DEFINES += "PLUGINSPATH=\\\"$$INSTALLROOT/$$PLUGINDIR\\\""

target.path = $$INSTALLROOT/$$LIBSDIR
INSTALLS += target

includeHeader.files = ../plugins/interfaces/qlcioplugin.h dmxlib.h
includeHeader.path = $$INSTALLROOT/$$INCLUDESDIR
INSTALLS += includeHeader
