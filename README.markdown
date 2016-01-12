# graspit

Forks off the original graspit repository which contains the original GraspIt source and adds some changes, specifically:

* Removing some issues with the Locale settings which become apparent when you try to read contact files on a system which does not use the *US Locale*.
  This was resolved by manually setting the US Locale where relevant *scanf* and *fwritef* calls are made in the original source (see also notes below).
* Adding support for compiling with catkin_make/cmake.
* Minimal changes to the original source which allow to run GraspIt without the GUI. Specific changes are described [in this README](ChangesToOriginalSource.md). 

This package will compile:
* A C++ library for the original GraspIt code 
* The original simulator executable (with graphical interface)

# Prerequisites

You will need the following libraries in order to compile GraspIt!:
* Qt 4 (ubuntu packages *libqt4-dev, libqt4-opengl-dev* and *libqt4-sql-psql*)
* Coin 3 (ubuntu package *libcoin40-dev* or higher version)
* SoQt (ubuntu package *libsoqt4-dev*)
* Blas and Lapack (ubuntu packages *libblas-dev* and *libblas-dev*)

# Installation

Simply add this package to your catkin workspace and then you can compile it with 

``catkin_make``

In order to run the original simulator (with GUI), you will need to set an environment variable called *GRASPIT* to point to the main source directory *Graspit*. 
This is needed for GraspIt to run properly, not for compiling.         

``echo "export GRASPIT=<path to graspit_ros>/Graspit" >> ~/.bashrc``    

``source ~/.bashrc``

All your GraspIt robot, model and world files must be located in the *models* and *world* directories which you can find in the *$GRASPIT* directory. It is enough if you create soft links to your robot directory (containing the GraspIt robot description) in the folder *$GRASPIT/models/robots* (same for your objects which belong into *$GRASPIT/models/objects*).

``cd $GRASPIT/models/robots``

``ls -s <path-to-YOUR_ROBOT-folder>``


You may then run the original simulator with

``rosrun graspit_ros graspit_simulator``

# Planning with GraspIt

Before you can start planning with the GraspIt simulator, you will need the GraspIt world and model files. You can generate a GraspIt format for your robot with the 
[urdf2graspit](https://github.com/JenniferBuehler/jb-ros-packs/urdf2graspit) package using your robot's URDF description.
 
You can try the jaco example delivered in [this package](https://github.com/JenniferBuehler/jb-ros-packs/jaco_arm), but keep in mind that this is not an ideal hand to grasp, as the joints in the middle of the fingers are not actuated (the way they work cannot be simulated). It is planned to provide other example hands.

You can also try the hands which come in the ``$GRASPIT/models`` directory. 

Here's how you use the GraspIt EigenGrasp planner:

* To load up your robot, open the world file which includes the object. 

* To start planning, go to ``Grasp --> EigenGrasp Planner`` and change any options, or leave them on default.

* If the hand contact points are not loaded yet (checkbox "preset contact" on the top right unchecked), you need to load them first, otherwise the planning results are not going to be very good.

* Click on ``Init`` to initialize the algorihm (I usually use Axis-angle). Then, click on the ``>`` symbol to start planning and watch the hand try different positions.

* Each time you run the planning, you may get different results.

For more information on how to plan with GraspIt, please refer to the [official documentation](http://www.cs.columbia.edu/~cmatei/graspit/). A more detailed tutorial is planned to be added here at a later time.


### Note about the Locale conflicts in the original source

If your system is not set to default US Locale (in particular, where floating points are specified with dots (.) and not commas (,)), there will be a conflict with reading the GraspIt files. The problem becomes apparent as soon as you try to load the GraspIt contact file for your robot, and the contact's won't load. The reason for this is that QApplication (in the QT4 library) changes the Locale, and afterwards some *fscanf* calls fail to read the proper values.

Unfortunately, it is not enough to just change the Locale after QApplication (or GraspItApp) is created. It must be reset again later on somewhere, probably in Qt or other invoced functions. So I spread setting the Locale to all points in the code where it seemed apparent to me that it is necessary. Maybe there is a cleaner solution for this, but for now this should work.
