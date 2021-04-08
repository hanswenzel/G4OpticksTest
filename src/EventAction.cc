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
//
// Project headers:
//
#include "EventAction.hh"
#include "Ctx.hh"
#include "ConfigurationManager.hh"
#include "RunAction.hh"
#include "Event.hh"
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
//EventAction* EventAction::instance = 0;

EventAction::EventAction(Ctx* ctx_)
:
ctx(ctx_) {
#ifdef WITH_ROOT
    enable_IO = ConfigurationManager::getInstance()->isWriteHits();
    if (enable_IO) {
        CaTSEvt = Event::getInstance();
    }
#endif
}

EventAction::~EventAction() {
}

void EventAction::BeginOfEventAction(const G4Event* anEvent) {
#ifdef WITH_ROOT
    enable_IO = ConfigurationManager::getInstance()->isWriteHits();
    if (enable_IO) {
        CaTSEvt->SetEventNr(anEvent->GetEventID());
    }
#endif  
    ctx->setEvent(anEvent);
}

void EventAction::EndOfEventAction(const G4Event* event) {

    bool verbose = ConfigurationManager::getInstance()->isEnable_verbose();
    if (verbose) G4cout << "Event:   " << event->GetEventID() << G4endl;
    G4HCofThisEvent* HCE = event->GetHCofThisEvent();
    assert(HCE);
#ifdef WITH_ROOT
    //    if (enable_IO) {
    RunAction::getInstance()->getIOTimer()->resume();
    //hjw  std::vector<G4VHit*>* hitsVector = new std::vector<G4VHit*>();
    //hjwstd::map<G4String, std::vector<G4VHit* >* >* hcmap = CaTSEvt->GetHCMap();
    RunAction::getInstance()->getIOTimer()->stop();
    //}
#endif  
#ifdef WITH_G4OPTICKS
    if (ConfigurationManager::getInstance()->isEnable_opticks()) {
        RunAction::getInstance()->getOpticksTimer()->resume();
        G4Opticks* g4ok = G4Opticks::Get();
        G4int eventid = event->GetEventID();
        g4ok->propagateOpticalPhotons(eventid);
        G4OpticksHit hit;
        G4OpticksHitExtra hit_extra;
        unsigned num_gensteps = g4ok->getNumGensteps();
        unsigned num_photons = g4ok->getNumPhotons();
        unsigned num_hits = g4ok->getNumHit();
        bool way_enabled = g4ok->isWayEnabled();
        G4OpticksHitExtra* hit_extra_ptr = way_enabled ? &hit_extra : NULL;
        std::map<G4String, std::vector<G4VHit*> >* hcmap = Event::getInstance()->GetHCMap();
//        std::vector<G4VHit*> hitsVector = hcmap->at("Det_Photondetector");
        std::vector<G4VHit*>* hitsVector = &(hcmap->at("Det_Photondetector"));
        //        if (verbose) {
        G4cout << "EventAction::final Hits "
                << " eventid " << eventid
                << " num_gensteps " << num_gensteps
                << " num_photons " << num_photons
                << " num_hits " << num_hits
                << " way_enabled " << way_enabled
                << " hitsVector-.size():  " << hitsVector->size()
                << G4endl;

        //        } 
        for (unsigned i = 0; i < num_hits; i++) {
            g4ok->getHit(i, &hit, hit_extra_ptr);
#ifdef WITH_ROOT
            if (ConfigurationManager::getInstance()->isWriteHits()) {
                //RunAction::getInstance()->getIOTimer()->resume();
                hitsVector->push_back(new PhotonHit(i,
                        0,
                        hit.wavelength,
                        hit.time,
                        hit.global_position,
                        hit.global_direction,
                        hit.global_polarization));
                //   RunAction::getInstance()->getIOTimer()->stop();
            }
#endif
        }
               G4cout << "EventAction::final Hits "
                << " hitsVector-.size():  " << hitsVector->size()
                << G4endl;
        g4ok->reset();

        RootIO::GetInstance()->Write(CaTSEvt);
        CaTSEvt->Reset();
        RunAction::getInstance()->getIOTimer()->stop();





















        RunAction::getInstance()->getOpticksTimer()->stop();
    }
#endif  //end   WITH_G4OPTICKS
    //
    // Now we deal with the Geant4 Hit collections. 
    //
    if (verbose) {
        G4cout << "Number of collections:  " << HCE->GetNumberOfCollections() << G4endl;
    }
#ifdef WITH_ROOT
    /*
    if (enable_IO) {
        RunAction::getInstance()->getIOTimer()->resume();
        for (int i = 0; i < HCE->GetNumberOfCollections(); i++) {
          //hitsVector->clear();
          G4VHitsCollection* hc = HCE->GetHC(i);
          G4String hcname = hc->GetName();
          std::vector<std::string> y = split(hcname, '_');
          std::string Classname = y[1];
          if (verbose) {
            G4cout << "Classname: " << Classname << G4endl;
          }
          if (Classname == "lArTPC") {
            G4int NbHits = hc->GetSize();
            for (G4int ii = 0; ii < NbHits; ii++) {
              G4VHit* hit = hc->GetHit(ii);
              lArTPCHit* tpcHit = dynamic_cast<lArTPCHit*> (hit);
              hitsVector->push_back(tpcHit);
            }
            hcmap->insert(std::make_pair(hcname, hitsVector));
          } else if (Classname == "Photondetector") {
            G4int NbHits = hc->GetSize();
            if (verbose) G4cout << "Photondetector size: " << hc->GetSize() << G4endl;
            for (G4int ii = 0; ii < NbHits; ii++) {
              G4VHit* hit = hc->GetHit(ii);
              PhotonHit* pHit = dynamic_cast<PhotonHit*> (hit);
              hitsVector->push_back(pHit);
            }
            hcmap->insert(std::make_pair(hcname, hitsVector));
          } else if (Classname == "Tracker") {
            G4int NbHits = hc->GetSize();
            if (verbose) G4cout << "Tracker size: " << hc->GetSize() << G4endl;
            for (G4int ii = 0; ii < NbHits; ii++) {
              G4VHit* hit = hc->GetHit(ii);
              TrackerHit* tHit = dynamic_cast<TrackerHit*> (hit);
              hitsVector->push_back(tHit);
            }
            hcmap->insert(std::make_pair(hcname, hitsVector));
          } else if (Classname == "Calorimeter") {
            G4int NbHits = hc->GetSize();
            if (verbose) G4cout << "Calorimeter size: " << hc->GetSize() << G4endl;
            for (G4int ii = 0; ii < NbHits; ii++) {
              G4VHit* hit = hc->GetHit(ii);
              CalorimeterHit* cHit = dynamic_cast<CalorimeterHit*> (hit);
              hitsVector->push_back(cHit);
            }
            hcmap->insert(std::make_pair(hcname, hitsVector));
          } else if (Classname == "DRCalorimeter") {
            G4int NbHits = hc->GetSize();
            if (verbose) G4cout << "DRCalorimeter size: " << hc->GetSize() << G4endl;
            for (G4int ii = 0; ii < NbHits; ii++) {
              G4VHit* hit = hc->GetHit(ii);
              DRCalorimeterHit* drHit = dynamic_cast<DRCalorimeterHit*> (hit);
              hitsVector->push_back(drHit);
            }
            hcmap->insert(std::make_pair(hcname, hitsVector));
          } else {
            G4cout << "SD type: " << Classname << " unknown" << G4endl;
          }
        }
          RootIO::GetInstance()->Write(CaTSEvt);
          CaTSEvt->Reset();
          RunAction::getInstance()->getIOTimer()->stop();
      } // end enable_IO
     */
#endif
}

//EventAction* EventAction::getInstance() {
//    if (instance == 0) instance = new EventAction;
//    return instance;
//}