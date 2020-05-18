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

#include <string>

#include "G4Event.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4HCtable.hh"

#include "EventAction.hh"
#include "SensitiveDetector.hh"
#include "OpHit.hh"

#ifdef WITH_OPTICKS
#include "G4Opticks.hh"
#include "NPY.hpp"
#endif

#include "Ctx.hh"

EventAction::EventAction(Ctx* ctx_)
:
ctx(ctx_) {
}

void EventAction::BeginOfEventAction(const G4Event* anEvent) {
    ctx->setEvent(anEvent);
}

void EventAction::EndOfEventAction(const G4Event* event) {
    G4HCofThisEvent* HCE = event->GetHCofThisEvent();
    assert(HCE);

#ifdef WITH_OPTICKS
    G4cout << "\n###[ EventAction::EndOfEventAction G4Opticks.propagateOpticalPhotons\n" << G4endl;

    G4Opticks* ok = G4Opticks::GetOpticks();
    int num_hits = ok->propagateOpticalPhotons();
    NPY<float>* hits = ok->getHits();
    hits->save(".","hittie.npy");
 //   hits->save("/home/wenzel/tt2/G4OpticksTest-install/bin/hits.npy");
    //hits->save("hits.npy");
    assert(hits == NULL || hits->getNumItems() == unsigned(num_hits));
    G4cout
            << "EventAction::EndOfEventAction"
            << " num_hits " << num_hits
            << " hits " << hits
            << G4endl
            ;

    // TODO: feed the hits into the Hit collection 

    G4cout << "\n###] EventAction::EndOfEventAction G4Opticks.propagateOpticalPhotons\n" << G4endl;
#endif

    //addDummyHits(HCE);
    G4cout
            << "EventAction::EndOfEventAction"
            << " DumpHitCollections "
            << G4endl
            ;
    SensitiveDetector::DumpHitCollections(HCE);

    // A possible alternative location to invoke the GPU propagation
    // and add hits in bulk to hit collections would be SensitiveDetector::EndOfEvent  
}
/*
void EventAction::addDummyHits(G4HCofThisEvent* HCE)
{
    OpHitCollection* A = SensitiveDetector::GetHitCollection(HCE, "SD0/OpHitCollectionA");
    OpHitCollection* B = SensitiveDetector::GetHitCollection(HCE, "SD0/OpHitCollectionB");
    for(unsigned i=0 ; i < 10 ; i++) 
    {
        OpHitCollection* HC = i % 2 == 0 ? A : B ; 
        HC->insert( OpHit::MakeDummyHit() ) ;
    }
}
 */


