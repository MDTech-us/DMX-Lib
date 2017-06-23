TEMPLATE = subdirs

!android:!ios {

 SUBDIRS              += dmxusb
 SUBDIRS              += peperoni
 SUBDIRS              += udmx

# MIDI needs to much QLC stuff, so may as well just cut it out for now.
# TODO: It would be nice to actually fix this...
# SUBDIRS              += midi

 unix {
   system(pkg-config --exists libola) {
     system(pkg-config --exists libolaserver) {
       SUBDIRS        += ola
     }
   }
 }
 !macx:!win32:SUBDIRS += dmx4linux
 SUBDIRS              += velleman
 SUBDIRS              += enttecwing

# There is a problem with this plugin during runtime.
# TODO: symbol lookup error: /usr/lib/DMXLib-Plugins/libhidplugin.so: undefined symbol: udev_new
# SUBDIRS              += hid

 !macx:!win32:SUBDIRS += spi

 greaterThan(QT_MAJOR_VERSION, 4) {
    #!macx:!win32:SUBDIRS += uart
    #!macx:!win32:SUBDIRS += gpio
 }
}

SUBDIRS              += artnet
SUBDIRS              += E1.31
SUBDIRS              += loopback
SUBDIRS              += osc
