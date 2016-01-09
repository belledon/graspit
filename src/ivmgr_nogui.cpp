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
// Author(s): Jennifer Buehler 
//
//
//######################################################################

/*! \file
  \brief Implements the IVmgrNoGui class which acts like the original IVmgr class but bypasses all GUI actions.
*/

#include "ivmgr_nogui.h"
#include "world.h"
#include <Inventor/Qt/SoQt.h>
#include <Inventor/nodes/SoSeparator.h>

#include "SoComplexShape.h"
#include "SoArrow.h"
#include "SoTorquePointer.h"

//#define GRASPITDBG
#include "debug.h"

#ifdef USE_DMALLOC
include "dmalloc.h"
#endif 

#define FORCE_SCALE 5.0

#ifdef GRASPITDBG
extern FILE *debugfile;
#endif


IVmgrNoGui::IVmgrNoGui(const char * _name):
    qapp(NULL) 
{

#ifdef GRASPITDBG
  printf("Starting Inventor...\n");
#endif
  
  initSoQt();

  // Initialize the main world
  world = new World(NULL,_name, this);

  sceneRoot = new SoSeparator;
  sceneRoot->ref();

//  mDBMgr = NULL;
}


/*!
  Deselects all elements, and deletes the main world.  Deletes the remaining
  Inventor scene graph and deletes the Inventor viewer.
*/
IVmgrNoGui::~IVmgrNoGui()
{
  //std::cout << "deleting IVmgrNoGui" << std::endl;
  
  exitMainLoop();

  delete world;
  sceneRoot->unref();

  if (qapp) {
    delete qapp;
  }

}

/*!
  Deselects all world elements, deletes the world, and creates a new world.
*/
void
IVmgrNoGui::emptyWorld()
{
  delete world;
  world = new World(NULL, "MainWorld", this);
  //comment out here and where another world is created to stop using mutexes
  //world->setRenderMutex(&mRenderMutex);
}

void
IVmgrNoGui::createNewWorld(const char* name)
{

  delete world;
  sceneRoot->unref();

  world = new World(NULL, name, this);
  //world->setRenderMutex(&mRenderMutex);
  
  sceneRoot=world->getIVRoot();
  sceneRoot->ref();
}



void
IVmgrNoGui::initSoQt()
{
    qapp = SoQt::init("Test");   

    // initialize GraspIt Inventor additions
    SoComplexShape::initClass();
    SoArrow::initClass();
//    SoTorquePointer::initClass();
}

/*!
  Starts the main event loop.
*/
void
IVmgrNoGui::beginMainLoop()
{
  SoQt::mainLoop();
}

void
IVmgrNoGui::exitMainLoop()
{
  SoQt::exitMainLoop();
}



