# GRASPITDBG error fixes 

It still needs to be verified whether the following changes (done in my old version of the fork) have been fixed in Graspit now.


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
 
