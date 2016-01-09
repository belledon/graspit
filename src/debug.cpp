#include "debug.h"
#include <QString>

std::ostream& operator<<(std::ostream& o, const QString& q){
    o<<q.toStdString();
    return o;
}

