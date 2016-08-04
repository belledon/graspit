//PlanningParams.cpp

#include "EGPlanner/PlanningParams.h"

PlanningParams::PlanningParams(PlannerType type) :pType(type){}


PlannerType PlanningParams::getPlannerType()
{
	return pType;
}

