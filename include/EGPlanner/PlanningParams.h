//PlanningParams.h

#ifndef _planningparams_h_
#define _planningparams_h_

#include "EGPlanner/search.h"
//#include "EGPlanner/egPlanner.h"

 
class PlanningParams{


protected:
	
	PlannerType pType;

public:
	PlanningParams(PlannerType type);
	PlannerType getPlannerType();

	// virtual void configPlanner(EGPlanner * planner) = 0;
};

#endif