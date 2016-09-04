//######################################################################
//
// GraspIt!
// Copyright (C) 2002-2009  Columbia University in the City of New York.
// All rights reserved.
//
// GraspIt! is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// GraspIt! is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with GraspIt!.  If not, see <http://www.gnu.org/licenses/>.
//
// Author(s): Matei T. Ciocarlie
//
// $Id: simAnnPlanner.cpp,v 1.16 2009/05/07 19:57:26 cmatei Exp $
//
//######################################################################

#include "simAnnPlanner.h"

#include "searchState.h"
#include "searchEnergy.h"
#include "simAnn.h"

//#define GRASPITDBG
#include "debug.h"

//! How many of the best states are buffered. Should be a parameter
#define BEST_LIST_SIZE 20
//! Two states within this distance of each other are considered to be in the same neighborhood
#define DISTANCE_THRESHOLD 0.3

SimAnnPlanner::SimAnnPlanner()
{
	mHand = NULL;
	init();
    mEnergyCalculator = SearchEnergy::getSearchEnergy(ENERGY_CONTACT);
	mSimAnn = new SimAnn();
	DBGA("SimAnnPlanner Constructor no hand")
}

SimAnnPlanner::SimAnnPlanner(Hand *h)
{
	mHand = h;
	init();
    mEnergyCalculator = SearchEnergy::getSearchEnergy(ENERGY_CONTACT);
	mSimAnn = new SimAnn();
	DBGA("SimAnnPlanner Constructor with hand")
}

SimAnnPlanner::~SimAnnPlanner() 
{
	if (mSimAnn) delete mSimAnn;
}

// void SimAnnPlanner::setHand(Hand *h)
// {
// 	mHand = h;
// }
void
SimAnnPlanner::setAnnealingParameters(AnnealingType y) {
	if (isActive()) {
		DBGA("Stop planner before setting ann parameters");
		return;
	}
	mSimAnn->setParameters(y);
}

void SimAnnPlanner::useAnnealingParameters(AnnealingType y, std::vector<float> p) {
	if (isActive()) {
		DBGA("Stop planner before setting ann parameters");
		return;
	}
	DBGA("Setting SimAnn parameters")
	mSimAnn->useParameters(y, p);
	
}
void
SimAnnPlanner::resetParameters()
{
	EGPlanner::resetParameters();
	mSimAnn->reset();
	mCurrentStep = mSimAnn->getCurrentStep();
	mCurrentState->setEnergy(1.0e8);
}

bool
SimAnnPlanner::initialized()
{
	if (!mCurrentState) return false;
	return true;
}

void
SimAnnPlanner::setModelState(const GraspPlanningState *modelState)
{
	DBGA("Setting model state...");
	if (isActive()) {
		DBGA("Can not change model state while planner is running");
		return;
	}

	if (mCurrentState) delete mCurrentState;
	DBGA("Setting current state...");
	mCurrentState = new GraspPlanningState(modelState);
	//removed for testing purposes -> mCurrentState->setEnergy(1.0e5);
	//my hand might be a clone
	DBGA("Setting to current state to that of the given hand");
	mCurrentState->changeHand(mHand, true);
	DBGA("Done setting current state!");

	if (mTargetState && (mTargetState->readPosition()->getType() != mCurrentState->readPosition()->getType() ||
						 mTargetState->readPosture()->getType() != mCurrentState->readPosture()->getType() ) ) {
		DBGA("Target state is not of correct type with regards to the current state...setting to null");
		delete mTargetState; mTargetState = NULL;
    }
	if (!mTargetState) {
		DBGA("No target state initialized, copying from current state...");
		mTargetState = new GraspPlanningState(mCurrentState);
		//removed for testing purposes -> mTargetState->reset();
		mInputType = INPUT_NONE;
	}
	DBGA("Done setting target state!")
	invalidateReset();
}

void SimAnnPlanner::configPlanner(std::map<std::string, double>& params)
{
	if (isActive()) {
		DBGA("Stop planner before setting ann parameters");
		return;
	}
	mSimAnn->configParams(params);
}

void SimAnnPlanner::configPlanner(SimAnnParams *params)
{
	if (isActive()) {
		DBGA("Stop planner before setting ann parameters");
		return;
	}
	DBGA("Checking Planner type")
	PlannerType pt = params->getPlannerType();
	if(this->getType() == pt)
	{
		DBGA("Configuring SimAnnPlanner");
		std::map<std::string, double> p;
		p = params->getPlannerParams();
		if(mSimAnn) delete mSimAnn;
		mSimAnn = new SimAnn(p);
		DBGA("Configured SimAnnPlanner");
		mSimAnn->listParams();
	}
	else
	{
		DBGA("Cannot configure this planner with these parameters");
	}	
}

void SimAnnPlanner::printPlanner()
{
	DBGA("This is a SimAnnPlanner with the parameters:");
	mSimAnn->listParams();
}
void
SimAnnPlanner::mainLoop()
{

	GraspPlanningState *input = NULL;
	
	if ( processInput() ) {
		//DBGA("Target state is set to current state");
		input = mTargetState;
	}
	else
	{
		//DBGA("Target state is set to null state");
	}
	//call sim ann
	SimAnn::Result result = mSimAnn->iterate(mCurrentState, mEnergyCalculator, input);
	if ( result == SimAnn::FAIL) {
		DBGP("Sim ann failed");
		return;
	}
	DBGP("Sim Ann success");

	//put result in list if there's room or it's better than the worst solution so far
	double worstEnergy;
	if ((int)mBestList.size() < BEST_LIST_SIZE) worstEnergy = 1.0e5;
	else worstEnergy = mBestList.back()->getEnergy();
	if (result == SimAnn::JUMP && mCurrentState->getEnergy() < worstEnergy) {
		GraspPlanningState *insertState = new GraspPlanningState(mCurrentState);
		//but check if a similar solution is already in there
		if (!addToListOfUniqueSolutions(insertState,&mBestList,0.2)) {
			delete insertState;
		} else {
			mBestList.sort(GraspPlanningState::compareStates);
			while ((int)mBestList.size() > BEST_LIST_SIZE) {
				delete(mBestList.back());
				mBestList.pop_back();
			}
		}
	}
	render();
	mCurrentStep = mSimAnn->getCurrentStep();
	if (mCurrentStep % 100 == 0 && !mMultiThread) Q_EMIT update();
	if (mMaxSteps == 200) {DBGP("Child at " << mCurrentStep << " steps");}
}
