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
//
// Geant4 headers:
//
#include "G4Event.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
//
// Project headers:
//
#include "EventAction.hh"
#include "Ctx.hh"
#include "ConfigurationManager.hh"
#include "RunAction.hh"
#include "Event.hh"
#include "PhotonSD.hh"
#ifdef WITH_ROOT
#include "RootIO.hh"
#endif
//
// stl headers:
//
#include <cassert>
#include <string>
#include <vector>

#ifdef WITH_G4OPTICKS
#include "OpticksFlags.hh"
#include "G4Opticks.hh"
#include "G4OpticksHit.hh"
#endif

#include <boost/timer/timer.hpp>
using namespace boost::timer;

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    return split(s, delim, elems);
}

EventAction::EventAction(Ctx* ctx_)
:
ctx(ctx_) {
#ifdef WITH_ROOT
    enable_IO = ConfigurationManager::getInstance()->isWriteHits();
#endif 
}

EventAction::~EventAction() {
}

void EventAction::BeginOfEventAction(const G4Event* anEvent) {
    ctx->setEvent(anEvent);
}

void EventAction::EndOfEventAction(const G4Event* event) {
    bool verbose = ConfigurationManager::getInstance()->isEnable_verbose();
    if (verbose)    G4cout << "end of Event:   " << event->GetEventID() << G4endl;
    G4HCofThisEvent* HCE = event->GetHCofThisEvent();
    assert(HCE);
#ifdef WITH_ROOT
    Event* CaTSEvt = new Event();
    CaTSEvt->SetEventNr(event->GetEventID());
    std::map<G4String, std::vector<G4VHit*> >* hcmap = CaTSEvt->GetHCMap();
#endif  //end WITH_ROOT    
#ifdef WITH_G4OPTICKS
    if (ConfigurationManager::getInstance()->isEnable_opticks()) {
        RunAction::getInstance()->getOpticksTimer()->resume();
        G4Opticks* g4ok = G4Opticks::Get();
        G4int eventid = event->GetEventID();
        g4ok->propagateOpticalPhotons(eventid);
        G4HCtable* hctable = G4SDManager::GetSDMpointer()->GetHCtable();
        for (G4int i = 0; i < hctable->entries(); ++i) {
            std::string sdn = hctable->GetSDname(i);
            std::size_t found = sdn.find("Photondetector");
            if (found != std::string::npos) {
                PhotonSD* aSD = (PhotonSD*) G4SDManager::GetSDMpointer()->FindSensitiveDetector(sdn);
                aSD->AddOpticksHits();
            }
        }
        g4ok->reset();
    }// end isEnable_opticks
#endif  //end   WITH_G4OPTICKS
    //
    // Now we deal with the Geant4 Hit collections. 
    //
    if (verbose) G4cout << "Number of collections:  " << HCE->GetNumberOfCollections() << G4endl;
#ifdef WITH_ROOT
    if (enable_IO) {
        //RunAction::getInstance()->getIOTimer()->resume();
        for (int i = 0; i < HCE->GetNumberOfCollections(); i++) {
            G4VHitsCollection* hc = HCE->GetHC(i);
            G4String hcname = hc->GetName();
            std::vector<std::string> y = split(hcname, '_');
            std::string Classname = y[1];
            if (verbose) G4cout << "Classname: " << Classname << G4endl;
            if (Classname == "lArTPC") {
                std::vector<G4VHit*> hitsVector;
                G4int NbHits = hc->GetSize();
                for (G4int ii = 0; ii < NbHits; ii++) {
                    G4VHit* hit = hc->GetHit(ii);
                    lArTPCHit* tpcHit = dynamic_cast<lArTPCHit*> (hit);
                    hitsVector.push_back(tpcHit);
                }
                hcmap->insert(std::make_pair(hcname, hitsVector));
            } else if (Classname == "Photondetector") {
                std::vector<G4VHit*> hitsVector;
                G4int NbHits = hc->GetSize();
                if (verbose) G4cout << "Photondetector size: " << hc->GetSize() << G4endl;
                for (G4int ii = 0; ii < NbHits; ii++) {
                    G4VHit* hit = hc->GetHit(ii);
                    PhotonHit* pHit = dynamic_cast<PhotonHit*> (hit);
                    hitsVector.push_back(pHit);
                }
                hcmap->insert(std::make_pair(hcname, hitsVector));
            } else if (Classname == "Target") {
                std::vector<G4VHit*> hitsVector;
                G4int NbHits = hc->GetSize();
                if (verbose) G4cout << "Interaction size: " << hc->GetSize() << G4endl;
                for (G4int ii = 0; ii < NbHits; ii++) {
                    G4VHit* hit = hc->GetHit(ii);
                    InteractionHit* iaHit = dynamic_cast<InteractionHit*> (hit);
                    hitsVector.push_back(iaHit);
                }
                hcmap->insert(std::make_pair(hcname, hitsVector));
            } else if (Classname == "Tracker") {
                std::vector<G4VHit*> hitsVector;
                G4int NbHits = hc->GetSize();
                if (verbose) G4cout << "Tracker size: " << hc->GetSize() << G4endl;
                for (G4int ii = 0; ii < NbHits; ii++) {
                    G4VHit* hit = hc->GetHit(ii);
                    TrackerHit* tHit = dynamic_cast<TrackerHit*> (hit);
                    hitsVector.push_back(tHit);
                }
                hcmap->insert(std::make_pair(hcname, hitsVector));
            } else if (Classname == "Calorimeter") {
                std::vector<G4VHit*> hitsVector;
                G4int NbHits = hc->GetSize();
                if (verbose) G4cout << "Calorimeter size: " << hc->GetSize() << G4endl;
                for (G4int ii = 0; ii < NbHits; ii++) {
                    G4VHit* hit = hc->GetHit(ii);
                    CalorimeterHit* cHit = dynamic_cast<CalorimeterHit*> (hit);
                    hitsVector.push_back(cHit);
                }
                hcmap->insert(std::make_pair(hcname, hitsVector));
            } else if (Classname == "DRCalorimeter") {
                std::vector<G4VHit*> hitsVector;
                G4int NbHits = hc->GetSize();
                if (verbose) G4cout << "DRCalorimeter size: " << hc->GetSize() << G4endl;
                std::vector<G4VHit*> myVec;
                hcmap->insert(std::make_pair(hcname, myVec));
                for (G4int ii = 0; ii < NbHits; ii++) {
                    G4VHit* hit = hc->GetHit(ii);
                    DRCalorimeterHit* drHit = dynamic_cast<DRCalorimeterHit*> (hit);
                    hitsVector.push_back(drHit);
                }
            } else {
                G4cout << "SD type: " << Classname << " unknown" << G4endl;
            }
        }
        RootIO::GetInstance()->Write(CaTSEvt);
        CaTSEvt->Reset();
        delete CaTSEvt;
        // RunAction::getInstance()->getIOTimer()->stop();
    } // end ConfigurationManager::getInstance()->isWriteHits()
#endif
}

