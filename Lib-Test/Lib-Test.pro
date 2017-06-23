#
#  Demo of usage of QLC+ plugins through DMX-Lib.
#  Lib-Test.pro
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


QT += core
QT -= gui

CONFIG += c++11

TARGET = Lib-Test
CONFIG += console
CONFIG -= app_bundle

# Just for the build to work:
#INCLUDEPATH += ../DMX-Lib
LIBS += -lDMXLib

TEMPLATE = app

SOURCES += main.cpp
