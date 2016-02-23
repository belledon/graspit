### graspit

Forks off the original graspit repository which contains the original GraspIt source and adds some changes, specifically:

* Removing some issues with the Locale settings which become apparent when you try to read contact files on a system which does not use the *US Locale*.
  This was resolved by manually setting the US Locale where relevant *scanf* and *fwritef* calls are made in the original source (see also notes below).
* Adding support for compiling with catkin_make/cmake.
* Minimal changes to the original source which allow to run GraspIt without the GUI. Specific changes are described [in this README](ChangesToOriginalSource.md). 

This package will compile:
* A C++ library for the original GraspIt code 
* The original simulator executable (with graphical interface)



###Installation

```
cd <graspit-dir>
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=<graspit-install-location> -DBUILD_TESTS:BOOL=false ..
make
make install
```

*Note*: If you decide to build the GraspIt! tests as well (using cmake
argument ``-DBUILD_TESTS:BOOL=true``) you may need to compile gtest libraries as well.
See the Appendix of this page for instructions.



### Planning with GraspIt

Please also refer to [this wiki](https://github.com/JenniferBuehler/jb-ros-packs/wiki/The-Graspit-simulator) for instruction on how to use the simulator.


### Note about the Locale conflicts in the original source

If your system is not set to default US Locale (in particular, where floating points are specified with dots (.) and not commas (,)), there will be a conflict with reading the GraspIt files. The problem becomes apparent as soon as you try to load the GraspIt contact file for your robot, and the contact's won't load. The reason for this is that QApplication (in the QT4 library) changes the Locale, and afterwards some *fscanf* calls fail to read the proper values.

Unfortunately, it is not enough to just change the Locale after QApplication (or GraspItApp) is created. It must be reset again later on somewhere, probably in Qt or other invoced functions. So I spread setting the Locale to all points in the code where it seemed apparent to me that it is necessary. Maybe there is a cleaner solution for this, but for now this should work.

### Appendix: Compiling gtest library

```
sudo apt-get install libgtest-dev
cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make
```

Then, you will still need to copy or symlink libgtest.a
and libgtest_main.a to your /usr/lib folder

``sudo cp *.a /usr/lib``


