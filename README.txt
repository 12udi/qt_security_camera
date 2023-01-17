##############################################################################################################
# Tutorial How to use this repo for cross build of Qt App with OpenCV!
##############################################################################################################

Build a Webcam application which will take a screenshot when a motion was detected and save it to local drive
Run a Telegram Server which can provide those screenshots to a bot on smartphone

##############################################################################################################
# Version Infos:
##############################################################################################################

Host: Ubuntu 20.04 (GCC 9.4)
Target Raspberry OS Bullseye  (aarch64-linux-gnu-gcc-9)
Qt: 6.4.2
OpenCV: 4.7.0
CMake: 3.25.1

##############################################################################################################
# Steps:
##############################################################################################################

1. Install Raspberry Pi OS (https://www.raspberrypi.com/software/operating-systems/#raspberry-pi-os-64-bit)

2. Cross Compile Qt6 (https://wiki.qt.io/Cross-Compile_Qt_6_for_Raspberry_Pi)

3. Install OpenCV4 on target machine (https://singleboardbytes.com/647/install-opencv-raspberry-pi-4.htm)

    cmake -D CMAKE_BUILD_TYPE=RELEASE \
        -D CMAKE_INSTALL_PREFIX=/usr/local \
        -D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib/modules \
        -D BUILD_TESTS=OFF \
        -D INSTALL_PYTHON_EXAMPLES=OFF \
        -D OPENCV_ENABLE_NONFREE=ON \
        -D CMAKE_SHARED_LINKER_FLAGS=-latomic \
        -D BUILD_EXAMPLES=OFF ..

    not: removed options due to issues with build-test:
        -D ENABLE_NEON=ON \
        -D ENABLE_VFPV3=ON \

4. Build Qt App with OpenCV support

    a. Configure Kit
        Sysroot:            /home/user/rpi-sysroot
        Qt Versions:        Qt 6.4.2 (/home/user/qt-raspi/bin/qmake)
        Compiler:           GCC (/usr/bin/aarch64-linux-gnu-gcc-9)
                            G++ (/usr/bin/aarch64-linux-gnu-g++-9)
        CMake Tool:         System CMake
        CMake generator:    CMAKE_TOOLCHAIN_FILE:INTERNAL=/home/user/qt-raspi/lib/cmake/Qt6/qt.toolchain.cmake

    b. update -rpi-sysroot because step 3 ("Install OpenCV4") added some more libs

    $ rsync -avz --rsync-path="sudo rsync" --delete <pi_username>@<pi_ip_address>:/lib rpi-sysroot
    $ rsync -avz --rsync-path="sudo rsync" --delete <pi_username>@<pi_ip_address>:/usr/include rpi-sysroot/usr
    $ rsync -avz --rsync-path="sudo rsync" --delete <pi_username>@<pi_ip_address>:/usr/lib rpi-sysroot/usr


    c. copy /etc/alternatives/libs* because they are linked to some opencv dependencies like liblapack.*

    $ rsync -avz --rsync-path="sudo rsync" --delete <pi_username>@<pi_ip_address>:/etc/alternatives/libs* /etc/alternatives

    d. update CMakeLists.txt so it can find the RPI OpenCV4 libs/header

    CMakeLists.txt

    ...

    # copied from prebuild RPi4 OpenCV install folder (usr/local/lib/aarch64-linux-gnu/cmake/opencv4)
    set(OpenCV_DIR ${CMAKE_SOURCE_DIR}/etc/lib/aarch64-linux-gnu/cmake/opencv4)

    ...

    # copied from prebuild RPi4 OpenCV install folder (usr/local/include/opencv4)
    set(OpenCV_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/etc/include/opencv4)
    include_directories(${OpenCV_INCLUDE_DIRS})

    ...

5. copy and test binary on target

    a. connect USB Webcam
    b. check availability --> ls /dev/video*
    c. execute runApp.sh
        --> open: /dev/video0
        --> stream of webcam should be visible









