### graspit

Forks off the original graspit repository which contains the original GraspIt source and adds some changes, specifically:

* Removing some issues with the Locale settings which become apparent when you try to read contact files on a system which does not use the *US Locale*.
  This was resolved by manually setting the US Locale where relevant *scanf* and *fwritef* calls are made in the original source (see also notes below).
* Adding support for compiling with catkin_make/cmake.
* Minimal changes to the original source which allow to run GraspIt without the GUI. Specific changes are described [in this README](ChangesToOriginalSource.md). 

This package will compile:
* A C++ library for the original GraspIt code 
* The original simulator executable (with graphical interface)

### Installation

You will need the following libraries in order to compile GraspIt!:
* Qt 4 (ubuntu packages *libqt4-dev, libqt4-opengl-dev* and *libqt4-sql-psql*)
* Coin 3 (ubuntu package *libcoin40-dev* or higher version)
* SoQt (ubuntu package *libsoqt4-dev*)
* Blas and Lapack (ubuntu packages *libblas-dev* and *libblas-dev*)

For example, if you are on Ubuntu/Debian, install them with:

``sudo apt-get install libsoqt4-dev libcoin80-dev libqt4-dev libblas-dev liblapack-dev``

Then, simply add this package to your catkin workspace and then you can compile it with 

``catkin_make``

Or, to compile without catkin, you may also use cmake:

```
cd <graspit-dir>
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=<graspit-install-location> ..
make
make install
```

### Setting up GraspIt!

You will need to set up the graspit folders before you can load world files.

**1. Create environment variable**

You will need to create an environment variable called GRASPIT to point to the root folder of the [graspit](https://github.com/JenniferBuehler/graspit) repository.

```
echo "export GRASPIT=<path to graspit>" >> ~/.bashrc    
source ~/.bashrc
```

**2. Soft-link your robot files**

You will also need to add a soft link to your robot's graspit files in the $GRASPIT directory.
Your robots graspit files should be organised in the same directory structure as the models/ and worlds/ directories in the $GRASPIT directory:

- models/robots/YOUR\_ROBOT
   - eigen: contains eigen.xml    
   - iv: contains all inventor geometry folders    
   - YOUR\_ROBOT.xml    
   - virtual: contains contacts.vgr      
- worlds: 
    - YOUR\_ROBOT\_world.xml

All your GraspIt robot, model and world files must be located in the *models* and *world* directories in the *$GRASPIT* directory. It is enough if you create soft links to your robot directory models/robots/YOUR\_ROBOT in the folder *$GRASPIT/models/robots* (same for your objects which belong into *$GRASPIT/models/objects*).

```
cd $GRASPIT/models/robots
ls -s <path-to: models/robots/YOUR\_ROBOT>
```

### Running the simulator

You may then run the original simulator with

``rosrun graspit_ros graspit_simulator``

### Planning with GraspIt

Please also refer to [this wiki](https://github.com/JenniferBuehler/jb-ros-packs/wiki/The-Graspit-simulator) for instruction on how to use the simulator.


### Note about the Locale conflicts in the original source

If your system is not set to default US Locale (in particular, where floating points are specified with dots (.) and not commas (,)), there will be a conflict with reading the GraspIt files. The problem becomes apparent as soon as you try to load the GraspIt contact file for your robot, and the contact's won't load. The reason for this is that QApplication (in the QT4 library) changes the Locale, and afterwards some *fscanf* calls fail to read the proper values.

Unfortunately, it is not enough to just change the Locale after QApplication (or GraspItApp) is created. It must be reset again later on somewhere, probably in Qt or other invoced functions. So I spread setting the Locale to all points in the code where it seemed apparent to me that it is necessary. Maybe there is a cleaner solution for this, but for now this should work.
