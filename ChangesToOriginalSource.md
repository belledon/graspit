Details about the changes applied to the original source:

- Created *IVmgrAbstract* class, of which the classes *IVmgrNoGui* (new class) and *IVmgr* (existing class) are derived. This allows to use IVmgr without the GUI.

- class *IVmgr* has remained untouched, except:
    * ivmgr.h:
        - the abstract class inheritance
        - made the following functions virtual:
            - setCamera()
            - getCamera()
        - added implementation of:
            - virtual void viewAll()
        - removed *#define MAX_COLLISIONS* and *#define MAX_POLYTOPES* statements and moved them to *IVmgrAbstract*

- class World:
    * world.h:
        - All references to *IVmgr* has been changed to *IVmgrAbstract* (3 changes)
    * world.cpp:
        - All references to *IVmgr* has been changed to *IVmgrAbstract* (1 change in constuctor)
        - including *ivmgr_abstract.h* instead of *ivmgr.h*
        - calling *IVmgrAbstract::viewAll()* instead of *ivmgr->getViewer()->viewAll()*.

- class Body:
    * body.cpp:
        - *axesTranToCOG / axesScale* is NULL if *graspItGUI* is NULL. Added check for NULL pointer in following functions:
            - setCoG()
            - setMaxRadius()


- class EGPlanner:
    * egPlanner.cpp
        - added method *runPlannerLoop()* which essentially does the same as *startThread()* (without starting a thread) and then calling *run()*.
          this was needed because all QObjects have to be created by the same thread which also runs the planning. So we cannot run the planning
          as originally with *EGPlanner* (out of the method *EGPlanner::sensorCB*). 
    * egPlanner.h
        - added method *runPlannerLoop()* (see description in source file)




# GRASPITDBG error fixes 

While compiling with -DGRASPITDGB, a few new compiler errors appeared with Macro DBGP, specifically to printing QString objects. 

So I added following lines to *debug.h*:

```
#include <QString>    
extern std::ostream& operator<<(std::ostream& o, const QString& q);
```


and added a file *debug.cpp* with contents:

```
std::ostream& operator<<(std::ostream& o, const QString& q){    
    o<<q.toStdString();    
    return o;    
}
```

Furthermore, I also had to change:

- world.cpp
    * line 1946:    
        ORIG: ``numCols = getCollisionReport(colReport);``    
        NEW : ``numCols = getCollisionReport(&colReport);``
    * line 1124:    
        ORIG: ``if (e->inherits("Body")) {DBGP(" with collision id " << ((Body*)e)->getId());}``    
        NEW : ``if (e->inherits("Body")) {DBGP(" with collision id " << ((Body*)e)->getName());}``

- graspitServer.cpp
    * line 193:    
        ORIG: ``std::cout <<"Command parser line: "<<line << std::endl;``    
        NEW : ``std::cout <<"Command parser line: "<<line.toStdString() << std::endl;``
 
