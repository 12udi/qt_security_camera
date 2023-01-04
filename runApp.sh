#!/bin/sh
export LD_LIBRARY_PATH=${PWD}/etc/lib
#export QT_PLUGIN_PATH=${PWD}/etc/plugins
#export QML2_IMPORT_PATH=${PWD}/etc/qml
./build/qt-conan
