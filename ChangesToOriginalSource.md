All changes applied to this fork which have not been merged in with the original yet:

- Catkin-stuff in the CMakeLists.txt, and the graspitConfig.cmake in cmake/

- class World:
    * world.cpp:
        - method destoryElement(): Removing only registered bodies from collision interface: in the old version, if a body is removed, it is *always* removed from the collision interface as well, even if it is *not* registered in the world. This prints an error from collision interface if the body was not in the world. So I moved this line into the loop. 
 I noticed this issue when I removed a robot and all its links from the scene and kept the pointer (deleteElement=false) to maintain it in the the database, so I could add it again later. destroyElement() is called from the Robot destructor. If the robot is destroyed but not part of the world, it will still remove its links from the collision interface... is this supposed to happen?

- class Body:
    * body.cpp:
        - *axesTranToCOG / axesScale* is NULL if *graspItCore* is NULL. Added check for NULL pointer in following functions:
            - setCoG()
            - setMaxRadius()

- class EGPlanner:
    * egPlanner.cpp
        - added method *runPlannerLoop()* which essentially does the same as *startThread()* (without starting a thread) and then calling *run()*.
          this was needed because all QObjects have to be created by the same thread which also runs the planning. So we cannot run the planning
          as originally with *EGPlanner* (out of the method *EGPlanner::sensorCB*). 
    * egPlanner.h
        - added method *runPlannerLoop()* (see description in source file)

