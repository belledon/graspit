### Install instructions with MinGW/MSYS

**Set up MinGW and Qt**

1. Download MinGW toolchain (from MinGW-w64 project) already set up for Qt from [here](http://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/4.8.2/threads-posix/dwarf/i686-4.8.2-release-posix-dwarf-rt_v3-rev3.7z/download) and extract it, e.g. to C:/MinGW. See also [this link on qt.io](https://wiki.qt.io/MinGW).

2. Download Qt 4 and run the installer (default destination is D:/Qt). I used the file [from qt.io](https://download.qt.io/archive/qt/4.8/4.8.6/) 
You have to locate the MinGW files previously extracted (see also [this useful resource](https://github.com/iat-cener/tonatiuh/wiki/Installing%20Qt%20For%20Windows))

3. Add MinGW *bin* directory to your PATH

4. Download and install [cmake](https://cmake.org/download/) for windows.

**Install MSYS2**

* Download Msys2 [from here](https://msys2.github.io/) and execute installer.
* Open MSYS shell and add the MinGW *bin* directory to PATH (either export or .bashrc)
- *(optional)*: Install vim in from MSYS shell with ``pacman -S vim``


**General notes for compiling with cmake**

CMake and MSYS do not get along that well. When you use cmake from within
the MSYS command line, it will complain about sh.exe being in your PATH.
So in general, the best is to use the cmake graphical interface on Windows
to generate the makefiles, and then use the MSYS shell to compile.

If you do run cmake from within MSYS, you should set it to generate MinGW makefiles:
``cmake -G "MinGW Makefiles" ..``    
For the error about sh.exe: it will go away after re-runnign cmake. Careful though because
this may lead to the wrong compilers being chosen (you could set them with
explicitly with CMAKE_CXX_COMPILER and CMAKE_C_COMPILER, though I have not tried this).

    
You may have to soft-link *ming32-make.exe* to *make.exe*, or just run make explicitly:
``
mingw32-make
``
    
*Hint:* Pass -DCMAKE_PREFIX_PATH with a custom install directory for any dependencies installed in custom paths


**Install basic dependencies**

1. lapack/blas: Install from source (see also [this link](http://icl.cs.utk.edu/lapack-for-windows/lapack/)), can be done [with this source](http://netlib.org/lapack/lapack.tgz) and cmake.
2. qhull : Compile from source [from github](https://github.com/qhull/qhull)

Alternatively, try pacman to install the libraries:
``pacman -Ss lapack`` will list the specific name of the package (something with openblas) 
Then install with ``pacman -S <name>``
And for qhull: find out package name with ``pacman -Ss qhull`` and install with ``-S``

**Install Coin and SoQt**

A good set of instructions can be found on [this link](https://github.com/iat-cener/tonatiuh/wiki/Installing-SoQt-For-Windows).
Please refer to these instructions for installation.

There are binaries as well, but they are not the most recent version any more (found on [this link](http://ascend4.org/Building_Coin3d_and_SoQt_on_MinGW) which may be useful)).

A few general notes:

*Coin*    
- use the extra configure flag  ``--build=x86_64-w64-mingw32`` (you could try to use output of ``gcc -dumpmachine`` but this may refer to the MSYS gcc (not the MinGW gcc)).
- As of May 2016, the source code had to be edited as suggested in the instructions, except the change in freetype.cpp which was not necessary
- You also may need to install diffutils: ``pacman -S diffutils``
- The Coin *bin* directory has to be in the PATH environment variable

*SoQt*    
- Hint: variable QTDIR has to be the directory where all the Qt includes are in

**Install bullet**

This was straight forward with cmake right [out of repository](https://github.com/bulletphysics/bullet3)

**Compile graspit**

For compiling with cmake, the path to the MSYS bash.exe is required for being able to call soqt-config, which is not provided as Windows .exe file and needs to be run via bash. 
You need to pass the path to bash.exe (probably this is ``<your-msys-install>/usr/bin``) in the CMAKE_PREFIX_PATH.

Use the cmake GUI to generate make files, and explicitly choose the native compilers and set them to the MinGW gcc.exe/g++exe you installed in the first step:

1. Select source and build directory, then click "Configure"
2. Select "MinGW Makefiles", and you may first try to stick to the default compilers. If it does not compile or have other issues, try to re-run cmake and this time select "Specify native compilers", choosing the fortran.exe/gcc.exe/g++.exe from your MinGW install (the one built for Qt in the first step above).
3. The first configuration process may be unsuccessful because not all directories are included. Add the path to bash.exe, the path to the Qt files (QTDIR), and any other dependency directories in a "New Entry" named CMAKE_PREFIX_PATH.
4. Click "Configure" again. It should be printing something like "Result of soqt_config: " followed by a list of libraries. If it does not, it did not find bash.exe.
5. After configuration was successful, click on "Generate".

After the cmake files were generated in the GUI,
go to the MSYS shell, change to the build directory, and type

``mingw32-make`` 

*Notes*

I also installed ``pacman -S mingw-w64-86_64-dlfcn`` (also the i686 version of the package) while I was testing, it may be that it is not actually necessary, or it may be that it was required after all.
