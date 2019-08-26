// -*- C++ -*-
/*!
 * @file AutoGainControlComp.cpp
 * @brief Standalone component
 * @date $Date$
 *
 * $Id$
 */

#include "AutoGainControl.h"


void MyModuleInit(RTC::Manager* manager)
{
  AutoGainControlInit(manager);
  RTC::RtcBase* comp;

  // Create a component
  comp = manager->createComponent("AutoGainControl");

  if (comp==NULL)
  {
    std::cerr << "Component create failed." << std::endl;
    abort();
  }

  return;
}

/*
    M A I N
 */
int main (int argc, char** argv)
{
  RTC::Manager* manager;

  manager = RTC::Manager::init(argc, argv);

  // Initialize manager
  manager->init(argc, argv);

  // Set module initialization proceduer
  // This procedure will be invoked in activateManager() function.
  manager->setModuleInitProc(MyModuleInit);

  // Activate manager and register to naming service
  manager->activateManager();

  // run the manager in blocking mode
  // runManager(false) is the default.
  manager->runManager();

  // If you want to run the manager in non-blocking mode, do like this
  // manager->runManager(true);

  return 0;
}
