//SimAnnParams.cpp

#include "EGPlanner/SimAnnParams.h"
#include "debug.h"


SimAnnParams::SimAnnParams(std::map<std::string, double> params):
	PlanningParams(PLANNER_SIM_ANN),
	parameters(params)
{}

std::map<std::string, double> SimAnnParams::getPlannerParams()
{
	return parameters;
}

// void SimAnnParams::configPlanner(EGPlanner * planner)
// {
// 	PlannerType pt = planner->getType();
// 	if(this->getPlannerType() == pt)
// 	{
		
// 		PlanningParams * ptr;
// 		ptr = this;
// 		planner->configPlanner(ptr);
// 	}
// 	else
// 	{
// 		DGBA("Cannot configure this planner with these parameters");
// 	}
// }