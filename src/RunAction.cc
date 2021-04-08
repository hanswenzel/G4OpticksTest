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
// Geant4 headers
#include <cassert>
#include "G4Run.hh"
#include "G4SDManager.hh"
#include "g4analysis.hh"
//#define G4ANALYSIS_USE TRUE
//#ifdef G4ANALYSIS_USE
//#include "CaTS_Analysis.hh"
//#endif
#include "StackingAction.hh"
#ifdef WITH_G4OPTICKS
#include "G4TransportationManager.hh"
#include "G4Opticks.hh"
#endif
//
// Project headers:
//
#ifdef WITH_ROOT
#include "RootIO.hh"
#endif 
// project headers
#include "RadiatorSD.hh"
#include "PhotonSD.hh"
#include "RunAction.hh"
#include "ConfigurationManager.hh"
#include "Event.hh"
// C++ headers 
#include <vector>
RunAction* RunAction::instance = 0;

RunAction::RunAction()
: G4UserRunAction() {
    OpticksTimer = new cpu_timer();
    OpticksTimer->stop();
    IOTimer = new cpu_timer();
    IOTimer->stop();
}

void RunAction::BeginOfRunAction(const G4Run* aRun) {

#ifdef WITH_ROOT
    std::map<G4String, std::vector<G4VHit*> >* hcmap = Event::getInstance()->GetHCMap();
    std::vector<G4VHit*> hitsVector;
    //#ifdef G4ANALYSIS_USE
    // Create the analysis manager using a new factory method.
    // The choice of analysis technology is done via the function argument.

    std::vector<G4String>* SDNames = ConfigurationManager::getInstance()->getSDNames();
    std::size_t found;
    for (std::size_t i = 0; i < SDNames->size(); ++i) {
        std::cout << SDNames->at(i) << "\n";
        G4String sdn = SDNames->at(i);
        found = sdn.find("Photondetector");
        if (found != std::string::npos) {
            std::cout << "************** Photondetector found at: " << found << '\n';
           hcmap->insert(std::make_pair(sdn, hitsVector));
           // hcmap->insert(std::make_pair(sdn, new std::vector<G4VHit*>()));
        }
        //hjw        PhotonSD* aSD = (PhotonSD*) G4SDManager::GetSDMpointer()->FindSensitiveDetector(sdn);
        found = sdn.find("Radiator");
        if (found != std::string::npos) {
            std::cout << "************ Radiator found at: " << found << '\n';
        }
    }
    //hjw     std::map<G4String, std::vector<G4VHit*>* >* hcmap=Event::getInstance()->GetHCMap();
    std::cout << "***********size of hitvector map:  " << hcmap->size() << std::endl;
    auto analysisManager = G4Analysis::ManagerInstance("root");
    G4cout << "Using " << analysisManager->GetType() << G4endl;
    // Default settings
    //analysisManager->SetNtupleMerging(true);
    // Note: merging ntuples is available only with Root output
    analysisManager->SetVerboseLevel(1);
    G4String HistoFileName = ConfigurationManager::getInstance()->getHistoFileName();
    G4cout << "Opening Analysis output File: " << HistoFileName << G4endl;
    analysisManager->SetFileName(HistoFileName);
    analysisManager->OpenFile();
    //
    // Book histograms, ntuple
    //
    // Creating 1D histograms
    analysisManager->CreateH1("ENeutron", "Energy of created Neutrons", 200, 0, 100);
    analysisManager->CreateH1("EProton", "Energy of created Protons", 200, 0, 100);
    //   G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
    //   Analysis* analysis = Analysis::getInstance();
    //   analysis->BeginOfRun(aRun->GetRunID());
    //   StackingAction::getInstance()->BeginRun();
    //#endif
#endif   
#ifdef WITH_G4OPTICKS
    if (ConfigurationManager::getInstance()->isEnable_opticks()) {
        G4cout << "\n\n###[ RunAction::BeginOfRunAction G4Opticks.setGeometry\n\n" << G4endl;
        OpticksTimer->resume();
        G4VPhysicalVolume* world = G4TransportationManager::GetTransportationManager()->GetNavigatorForTracking()->GetWorldVolume();
        assert(world);
        bool standardize_geant4_materials = false; // required for alignment
        G4Opticks* g4ok = G4Opticks::Get();
        g4ok->setGeometry(world, standardize_geant4_materials);
        const std::vector<G4PVPlacement*>& sensor_placements = g4ok->getSensorPlacements();
        G4cout << "sensor_placements.size():  " << sensor_placements.size() << G4endl;
        for (unsigned i = 0; i < sensor_placements.size(); i++) {
            float efficiency_1 = 0.5f;
            float efficiency_2 = 1.0f;
            int sensor_cat = -1; // -1:means no angular info
            int sensor_identifier = 0xc0ffee + i; // mockup a detector specific identifier
            unsigned sensorIndex = 1 + i; // 1-based
            g4ok->setSensorData(sensorIndex, efficiency_1, efficiency_2, sensor_cat, sensor_identifier);
        }
        OpticksTimer->stop();
        G4cout << "\n\n###] RunAction::BeginOfRunAction G4Opticks.setGeometry\n\n" << G4endl;
    }
#endif 
}

void RunAction::EndOfRunAction(const G4Run*) {

#ifdef WITH_G4OPTICKS
    if (ConfigurationManager::getInstance()->isEnable_opticks()) {
        G4cout << "\n\n###[ RunAction::EndOfRunAction G4Opticks.Finalize\n\n" << G4endl;
        OpticksTimer->resume();
        G4Opticks::Finalize();
        OpticksTimer->stop();
        std::cout << "Opticks Timer: " << OpticksTimer->format() << '\n';
        std::cout << "IO Timer:      " << IOTimer->format() << '\n';
        G4cout << "\n\n###] RunAction::EndOfRunAction G4Opticks.Finalize\n\n" << G4endl;
    }
#endif
#ifdef WITH_ROOT
    if (ConfigurationManager::getInstance()->isWriteHits()) {
        IOTimer->resume();
        RootIO::GetInstance()->Close();
        IOTimer->stop();
    }
    if (ConfigurationManager::getInstance()->isdoAnalysis()) {
        auto analysisManager = G4AnalysisManager::Instance();
        analysisManager->Write();
        analysisManager->CloseFile();
    }
#endif    
}

RunAction* RunAction::getInstance() {
    if (instance == 0) instance = new RunAction;
    return instance;
}
