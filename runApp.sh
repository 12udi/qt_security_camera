#!/bin/sh
export LD_LIBRARY_PATH=`pwd`/lib
export QT_PLUGIN_PATH=`pwd`/plugins
export QML2_IMPORT_PATH=`pwd`/qml
./qt-conan
