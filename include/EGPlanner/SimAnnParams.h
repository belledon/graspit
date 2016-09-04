//SimAnnParams.h
#ifndef _simannparams_h_
#define _simannparams_h_
 

#include "EGPlanner/PlanningParams.h"

#include <vector>
#include <map>
#include <string> 

class SimAnnParams : public PlanningParams
{

private:
	//! The instance passed to the SimAnnPlanner
	std::map<std::string, double> parameters;


public:
	SimAnnParams(std::map<std::string, double> params);
	//! Getter for annealing parameters
	std::map<std::string, double> getPlannerParams();
	/*! Only applies the parameters if the planner is of
		the type PLANNER_SIM_ANN
	*/
	// void configPlanner(EGPlanner * planner);
};

#endif
 