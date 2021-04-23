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
// project headers:
#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "PhysicsConfigurator.hh"
#include "ConfigurationManager.hh"
// Geant4 headers:
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4Timer.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "G4VModularPhysicsList.hh"
#include "G4Version.hh"
// boost headers: 
#include <boost/timer/timer.hpp>

int main(int argc, char** argv) {
    boost::timer::auto_cpu_timer t;
    bool interactive = false;
    G4String physicsconf = "";
    G4String gdmlfile = "";
    G4String macrofile = "";
    G4UIExecutive* ui = nullptr;
    for (G4int i = 1; i < argc; i = i + 2) {
        if (G4String(argv[i]) == "-gdml") {
            gdmlfile = argv[i + 1];
        } else if (G4String(argv[i]) == "-pl") {
            physicsconf = G4String(argv[i + 1]);
        } else if (G4String(argv[i]) == "-macro") {
            macrofile = G4String(argv[i + 1]);
        }
    }
    if (gdmlfile == "") {
        G4cout << "Error! Mandatory input file is not specified!" << G4endl;
        G4cout << G4endl;
        G4cout << G4endl;
        G4cout << "Usage:  G4OpticksTest -gdml intput_gdml_file:mandatory" << G4endl;
        G4cout << G4endl;
        return -1;
    }
    if (physicsconf == "") {
        G4cout << "Warning! no physics configuration specified!" << G4endl;
        G4cout << "Using default FTFP_BERT" << G4endl;
        physicsconf = "FTFP_BERT";
        G4cout << G4endl;
        G4cout << G4endl;
        G4cout << "Usage:  G4OpticksTest -pl physicsconfiguration" << G4endl;
        G4cout << G4endl;
    }
    if (macrofile == "") {
        G4cout << "Warning! no macro specified!" << G4endl;
        G4cout << "assume interactive mode" << G4endl;
        interactive = true;
        ui = new G4UIExecutive(argc, argv);
        G4cout << G4endl;
        G4cout << G4endl;
        G4cout << "Usage:  G4OpticksTest -pl physicsconfiguration" << G4endl;
        G4cout << G4endl;
    }
//    G4cout << G4VERSION_TAG << G4endl;
//    G4cout << G4VERSION_NUMBER << G4endl;
    G4Timer *eventTimer = new G4Timer;
    eventTimer->Start();

    OPTICKS_LOG(argc, argv);
    G4VModularPhysicsList* phys = PhysicsConfigurator::getInstance()->Construct(physicsconf);
    DetectorConstruction* dc = new DetectorConstruction(gdmlfile);
    G4RunManager* rm = new G4RunManager();
    rm->SetUserInitialization(dc);
    rm->SetUserInitialization(phys);
    ActionInitialization* actionInitialization = new ActionInitialization();
    rm->SetUserInitialization(actionInitialization);
    //
    //   rm->Initialize();
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
        //        G4String fileName = argv[2];
        UImanager->ApplyCommand(command + macrofile);
        delete ui;
    }

    eventTimer->Stop();

    double totalCPUTime = eventTimer->GetUserElapsed() + eventTimer->GetSystemElapsed();
    G4int precision_t = G4cout.precision(3);
    std::ios::fmtflags flags_t = G4cout.flags();
    G4cout.setf(std::ios::fixed, std::ios::floatfield);
    G4cout << "TimeTotal> " << eventTimer->GetRealElapsed() << " " << totalCPUTime << G4endl;
    G4cout.setf(flags_t);
    G4cout.precision(precision_t);
    delete eventTimer;
    //delete rm;
    return 0;
}


