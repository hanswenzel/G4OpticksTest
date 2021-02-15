/*
 * Copyright (c) 2019 Opticks Team. All Rights Reserved.
 *
 * This file is part of Opticks
 * (see https://bitbucket.org/simoncblyth/opticks).
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); 
 * you may not use this file except in compliance with the License.  
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" BASIS, 
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  
 * See the License for the specific language governing permissions and 
 * limitations under the License.
 */
#ifdef WITH_G4OPTICKS
#include "OPTICKS_LOG.hh"
#endif

#include "G4.hh"
#include "ConfigurationManager.hh"

#include "G4UImanager.hh"
#include "G4Timer.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"


#include <boost/timer/timer.hpp>
//#include <iostream>
//using namespace boost::timer;

int main(int argc, char** argv) {
    boost::timer::auto_cpu_timer t;
    bool interactive = false;
    G4UIExecutive* ui = nullptr;
    if (argc < 2) {
        G4cout << "Error! Mandatory input file is not specified!" << G4endl;
        G4cout << G4endl;
        G4cout << G4endl;
        G4cout << "Usage: lArTest <intput_gdml_file:mandatory>" << G4endl;
        G4cout << G4endl;
        return -1;
    }

    if (argc == 2) {
        interactive = true;
        ui = new G4UIExecutive(argc, argv);
    }
    if (ConfigurationManager::getInstance()->isEnable_verbose()) {
        G4cout << " gdml file: " << argv[1] << G4endl;
    }
    //start time
    G4Timer *eventTimer = new G4Timer;
    eventTimer->Start();
    //cpu_timer timer;
    //    timer.start();

    OPTICKS_LOG(argc, argv);
    G4 g(argv[1]);

    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    if (interactive) {
        G4VisManager* visManager = new G4VisExecutive;
        visManager->Initialize();
        //get the pointer to the User Interface manager
        UImanager->ApplyCommand("/control/execute init_vis.mac");
        ui->SessionStart();
        delete ui;
        delete visManager;
    } else {
        // batch mode
        G4String command = "/control/execute ";
        G4String fileName = argv[2];
        UImanager->ApplyCommand(command + fileName);
    }

    eventTimer->Stop();
    //   timer.stop();

    double totalCPUTime = eventTimer->GetUserElapsed() + eventTimer->GetSystemElapsed();
    G4int precision_t = G4cout.precision(3);
    std::ios::fmtflags flags_t = G4cout.flags();
    G4cout.setf(std::ios::fixed, std::ios::floatfield);
    G4cout << "TimeTotal> " << eventTimer->GetRealElapsed() << " " << totalCPUTime << G4endl;
    G4cout.setf(flags_t);
    G4cout.precision(precision_t);
    delete eventTimer;
    //    std::cout << timer.format() << '\n';
    return 0;
}


