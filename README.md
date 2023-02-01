# Ann-Medics System

This repo is for university graduation project

## What is Ann-Medics ?

Ann-Medics is a enhanced Remote Medical Device that store the 
human vitalities and monitor it for doctors,nurses and other medical stuff ,
it also  management system that works to organize the doctors’ hours, especially the anesthesiologists, given that their number is few in the world. Instead of waiting for the anesthesiologist for the patient to prepare for anesthesia, he can do anything else until this humble system summons him and sends a message to the doctor, and thus we will be as much as possible to save the treating doctor’s time.
 
![review!][review.mp4] 
![review2!][MCU_uiux.png] 

## General setup  
**Host machine:** Ubuntu 18.04.4 LTS or later   
**Target machine:** Raspberry Pi 3B  , AD8232 ecg module , Max30102 ,buzzer 
 




## Setting up the environment for Raspberry pi
---

1. Download the raspbian image and 
```
  sudo apt install rpi-imager
``` 
note:select any raspbian lite image because we don't 
need to have x11 or wayland gui 

2. install the package dependencies
```
 sudo apt-get install libboost-all-dev libudev-dev libinput-dev libts-dev libmtdev-dev libjpeg-dev libfontconfig1-dev libssl-dev libdbus-1-dev libglib2.0-dev libxkbcommon-dev libegl1-mesa-dev libgbm-dev libgles2-mesa-dev mesa-common-dev libasound2-dev libpulse-dev gstreamer1.0-omx libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev  gstreamer1.0-alsa libvpx-dev libsrtp2-dev libsnappy-dev libnss3-dev "^libxcb.*" flex bison libxslt-dev ruby gperf libbz2-dev libcups2-dev libatkmm-1.6-dev libxi6 libxcomposite1 libfreetype6-dev libicu-dev libsqlite3-dev libxslt1-dev
``` 
``` 
 sudo apt-get install libavcodec-dev libavformat-dev libswscale-dev libx11-dev freetds-dev libsqlite3-dev libpq-dev libiodbc2-dev firebird-dev libgst-dev libxext-dev libxcb1 libxcb1-dev libx11-xcb1 libx11-xcb-dev libxcb-keysyms1 libxcb-keysyms1-dev libxcb-image0 libxcb-image0-dev libxcb-shm0 libxcb-shm0-dev libxcb-icccm4 libxcb-icccm4-dev libxcb-sync1 libxcb-sync-dev libxcb-render-util0 libxcb-render-util0-dev libxcb-xfixes0-dev libxrender-dev libxcb-shape0-dev libxcb-randr0-dev libxcb-glx0-dev libxi-dev libdrm-dev libxcb-xinerama0 libxcb-xinerama0-dev libatspi2.0-dev libxcursor-dev libxcomposite-dev libxdamage-dev libxss-dev libxtst-dev libpci-dev libcap-dev libxrandr-dev libdirectfb-dev libaudio-dev libxkbcommon-x11-dev

``` 
This will install a bunch of libraries from the Debian repository that Qt needed to deploy various kinds of applications on Raspberry Pi.

We also will make a directory that will hold the Qt installation targeting Raspberry Pi, as specified in the previous section. Actually, this can be done at every time before sending Qt 6 build from host machine to the Raspberry Pi, but in this guide we will create it now:
```
 sudo mkdir /usr/local/qt6
```
this is all for raspberry pi


## Setting up the environment for HOST Machine 
---

1. Install Cross Compiler
```
sudo apt install gcc-aarch64-linux-gnu g++-aarch64-linux-gnu
```
2. Setting up SSH Connection

We also want to setup an SSH connection between Raspberry Pi and a host machine. This is needed to transfer data between both devices. The official Raspberry Pi documentation page provided a very detailed and thorough instruction on how to setup SSH between Raspberry Pi and other device, so you can refer this step into that https://www.raspberrypi.com/documentation/computers/remote-access.html#ssh.

3. Building Sysroot from Device

We need to build a Sysroot from our own Raspberry Pi device in the host machine. To do this, we will copy and paste a few directories from Raspberry Pi using rsync through SSH. If rsync is not installed yet in your host machine, simply install it by executing sudo apt install rsync.

After the host machine and Raspberry Pi is connected,
```
 rsync -avz --rsync-path="sudo rsync" --delete <pi_username>@<pi_ip_address>:/lib rpi-sysroot
 rsync -avz --rsync-path="sudo rsync" --delete <pi_username>@<pi_ip_address>:/usr/include rpi-sysroot/usr
 rsync -avz --rsync-path="sudo rsync" --delete <pi_username>@<pi_ip_address>:/usr/lib rpi-sysroot/usr
 rsync -avz --rsync-path="sudo rsync" --delete <pi_username>@<pi_ip_address>:/opt/vc rpi-sysroot/opt
```
Change <pi_username> and <pi_ip_address> with your Raspberry Pi username and IP Address, respectively.

Note: Your Raspberry Pi might not have a directory named /opt/vc, and it is fine. Usually this directory contains proprietary Broadcom libraries, but during the testing the author did not find any issue with the lack of this directory.

After building our own sysroot, we need to fix absolute symbolic links that were broken during the syncing process by converting them to relative symlinks. The easiest, fastest way to do this is to use a command-line tool called symlinks, which is available from the Ubuntu official repository.
```
 sudo apt install symlinks
 cd ~
 symlinks -rc rpi-sysroot
```


<a name="Cross Compiling QT5"></a>
---
1. downloading qt source codes 
```
cd $HOME
git clone "https://codereview.qt-project.org/qt/qt5"
cd qt5/
git checkout 6.4.0
perl init-repository -f
cd ..
mkdir $HOME/qt-hostbuild
cd $HOME/qt-hostbuild/
cmake ../qt5/ -GNinja -DCMAKE_BUILD_TYPE=Release -DQT_BUILD_EXAMPLES=OFF -DQT_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=$HOME/qt-host
cmake --build . --parallel 8
cmake --install .
```

2. Create a Toolchain File

First, we want to create our own CMake toolchain file. This file is important to link the right compilers and libraries so that CMake can produces the suitable Qt build for Raspberry Pi. For this guide, we will use the following CMake code and save it as toolchain.cmake.
```
cmake_minimum_required(VERSION 3.18)
include_guard(GLOBAL)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(TARGET_SYSROOT /path/to/your/sysroot)
set(CMAKE_SYSROOT ${TARGET_SYSROOT})

set(ENV{PKG_CONFIG_PATH} $PKG_CONFIG_PATH:/usr/lib/aarch64-linux-gnu/pkgconfig)
set(ENV{PKG_CONFIG_LIBDIR} /usr/lib/pkgconfig:/usr/share/pkgconfig/:${TARGET_SYSROOT}/usr/lib/aarch64-linux-gnu/pkgconfig:${TARGET_SYSROOT}/usr/lib/pkgconfig)
set(ENV{PKG_CONFIG_SYSROOT_DIR} ${CMAKE_SYSROOT})

# if you use other version of gcc and g++ than gcc/g++ 9, you must change the following variables
set(CMAKE_C_COMPILER /usr/bin/aarch64-linux-gnu-gcc-9)
set(CMAKE_CXX_COMPILER /usr/bin/aarch64-linux-gnu-g++-9)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I${TARGET_SYSROOT}/usr/include")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS}")

set(QT_COMPILER_FLAGS "-march=armv8-a")
set(QT_COMPILER_FLAGS_RELEASE "-O2 -pipe")
set(QT_LINKER_FLAGS "-Wl,-O1 -Wl,--hash-style=gnu -Wl,--as-needed")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_BUILD_RPATH ${TARGET_SYSROOT})


include(CMakeInitializeConfigs)

function(cmake_initialize_per_config_variable _PREFIX _DOCSTRING)
  if (_PREFIX MATCHES "CMAKE_(C|CXX|ASM)_FLAGS")
    set(CMAKE_${CMAKE_MATCH_1}_FLAGS_INIT "${QT_COMPILER_FLAGS}")
        
    foreach (config DEBUG RELEASE MINSIZEREL RELWITHDEBINFO)
      if (DEFINED QT_COMPILER_FLAGS_${config})
        set(CMAKE_${CMAKE_MATCH_1}_FLAGS_${config}_INIT "${QT_COMPILER_FLAGS_${config}}")
      endif()
    endforeach()
  endif()


  if (_PREFIX MATCHES "CMAKE_(SHARED|MODULE|EXE)_LINKER_FLAGS")
    foreach (config SHARED MODULE EXE)
      set(CMAKE_${config}_LINKER_FLAGS_INIT "${QT_LINKER_FLAGS}")
    endforeach()
  endif()

  _cmake_initialize_per_config_variable(${ARGV})
endfunction()

set(XCB_PATH_VARIABLE ${TARGET_SYSROOT})

set(GL_INC_DIR ${TARGET_SYSROOT}/usr/include)
set(GL_LIB_DIR ${TARGET_SYSROOT}:${TARGET_SYSROOT}/usr/lib/aarch64-linux-gnu/:${TARGET_SYSROOT}/usr:${TARGET_SYSROOT}/usr/lib)

set(EGL_INCLUDE_DIR ${GL_INC_DIR})
set(EGL_LIBRARY ${XCB_PATH_VARIABLE}/usr/lib/aarch64-linux-gnu/libEGL.so)

set(OPENGL_INCLUDE_DIR ${GL_INC_DIR})
set(OPENGL_opengl_LIBRARY ${XCB_PATH_VARIABLE}/usr/lib/aarch64-linux-gnu/libOpenGL.so)

set(GLESv2_INCLUDE_DIR ${GL_INC_DIR})
set(GLIB_LIBRARY ${XCB_PATH_VARIABLE}/usr/lib/aarch64-linux-gnu/libGLESv2.so)

set(GLESv2_INCLUDE_DIR ${GL_INC_DIR})
set(GLESv2_LIBRARY ${XCB_PATH_VARIABLE}/usr/lib/aarch64-linux-gnu/libGLESv2.so)

set(gbm_INCLUDE_DIR ${GL_INC_DIR})
set(gbm_LIBRARY ${XCB_PATH_VARIABLE}/usr/lib/aarch64-linux-gnu/libgbm.so)

set(Libdrm_INCLUDE_DIR ${GL_INC_DIR})
set(Libdrm_LIBRARY ${XCB_PATH_VARIABLE}/usr/lib/aarch64-linux-gnu/libdrm.so)

set(XCB_XCB_INCLUDE_DIR ${GL_INC_DIR})
set(XCB_XCB_LIBRARY ${XCB_PATH_VARIABLE}/usr/lib/aarch64-linux-gnu/libxcb.so)
```
Now that we have our toolchain, as well as the cross compiler and sysroot, we can continue with configuring and building Qt for our Raspberry Pi!

As decided in the planning process, we will put all build configuration files on qtpi-build, so let's cd into that directory:
```
 cd ~/qtpi-build
```
Now inside this directory, we can run this configuration command:
```
 ../qt5/configure -release -opengl es2 -nomake examples -nomake tests -qt-host-path $HOME/qt-host -extprefix $HOME/qt-raspi -prefix /usr/local/qt6 -device linux-rasp-pi4-aarch64 -device-option CROSS_COMPILE=aarch64-linux-gnu- -- -DCMAKE_TOOLCHAIN_FILE=$HOME/toolchain.cmake -DQT_FEATURE_xcb=ON -DFEATURE_xcb_xlib=ON -DQT_FEATURE_xlib=ON
The command above will run a configuration script that came with the Qt source code and complementing it with the CMake toolchain that we just created. It is equivalent to this CMake command:
```
```
 cmake ../qt5/ -GNinja -DCMAKE_BUILD_TYPE=Release -DINPUT_opengl=es2 -DQT_BUILD_EXAMPLES=OFF -DQT_BUILD_TESTS=OFF -DQT_HOST_PATH=$HOME/qt-host -DCMAKE_STAGING_PREFIX=$HOME/qt-raspi -DCMAKE_INSTALL_PREFIX=/usr/local/qt6 -DCMAKE_TOOLCHAIN_FILE=$HOME/toolchain.cmake -DQT_QMAKE_TARGET_MKSPEC=devices/linux-rasp-pi4-aarch64 -DQT_FEATURE_xcb=ON -DFEATURE_xcb_xlib=ON -DQT_FEATURE_xlib=ON
```
Note: Both commands will do exactly the same thing: configuring Qt to be installed in folder qt-raspi on the host machine, with expectation that it will populate usr/local/qt6 on the Raspberry Pi. If you already run the first command, then there is no need to run the second command.

The Qt installation from this build will be suitable to run Qt ARM64 applications using X11 as the windowing system. You can check this page from Qt Docs to learn more about xcb plugins.

In more advanced cases, check this page from Qt Documentation if you want to use other windowing systems such as Wayland or EGLFS.

We can then proceed with building and installing.
```
 cmake --build . --parallel 4
 cmake --install .
```
After Qt is successfully installed on ~/qt-raspi, we will then send this Qt installation back to the Raspberry Pi.

To do this, we can use rsync as we did when building sysroot, or scp. Both will accomplish the same thing, and there should be no significant difference between both of them.

To use rsync:
```
rsync -avz --rsync-path="sudo rsync" /path/to/qt-raspi/* <pi_username>@<pi_ip_address>:/usr/local/qt6
```
To use scp:
```
 cd ~/qt-raspi
 scp -r * <pi_username>@<pi_ip_address>:/usr/local/qt6
```

3. Final Configuration on Raspberry Pi
To ensure our Qt 5 installation can be run on Raspberry Pi, we need to setup a few environment variables. All of this can be done on the host device via SSH.
```
ssh pi@169.254.187.77
```
## enter your raspberry pi user password, if prompted
```
 export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/qt6/lib/
```

4. Compiling and Running Qt Project
```
 cd ~/qt5/qtbase/examples/gui/analogclock/
 ls ## make sure there is a CMakeLists.txt file
 ~/qt-raspi/bin/qt-cmake CMakeLists.txt
```
### CMake is configuring here. After it is done without any error, we can proceed to build and install it
```
 cmake --build . --parallel 4
 cmake --install .
```
We now have the binary of our application ready to be run on the Raspberry Pi. We can then send the binary to our Raspberry Pi using either scp or rsync and run the application (either through SSH or directly on the Raspberry Pi with keyboard and mouse connected).
```
 scp -r gui_analogclock <pi_username>@<pi_ip_address>:/home/pi
 ssh <pi_username>@<pi_ip_address>
 cd ~ ## or cd to the directory where you send the binary
 ./gui_analogclock
```


now you are ready download our repo and go to device directory and build it
for your device .


# References 

1. [Qt Documentation](https://doc.qt.io/qt-5/index.html)  
2. [Using Qt Creator to cross-compile and debug Raspberry Pi Qt5 apps ](https://jumpnowtek.com/rpi/Qt-Creator-Setup-for-RPi-cross-development.html) 
3. [Qt C++ GUI Tutorial for Beginners](https://www.youtube.com/playlist?list=PLS1QulWo1RIZiBcTr5urECberTITj7gjA)  
4. [Intel Edison audio output to Bluetooth speaker](https://tl00.wordpress.com/2015/01/28/11/)

![logo!][logo.png]
![team!][team.png]  