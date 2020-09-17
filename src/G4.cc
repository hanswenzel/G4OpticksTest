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

#include "G4RunManager.hh"
#include "G4GeometryManager.hh"


#include "G4.hh"
#include "Ctx.hh"


#include "SensitiveDetector.hh"
#include "DetectorConstruction.hh"
#include "DetConOrg.hh"
//#include "L4Cerenkov.hh"
//#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"

#include "RunAction.hh"
#include "EventAction.hh"
#include "TrackingAction.hh"
#include "SteppingAction.hh"
//

// process
#include "G4VUserPhysicsList.hh"

#include "G4Version.hh"
//#include "G4Scintillation.hh"
#include "G4OpAbsorption.hh"
#include "G4OpRayleigh.hh"
#include "G4OpBoundaryProcess.hh"
//#include "L4Cerenkov.hh"
//#include "L4Scintillation.hh"

//

#include "G4PhysListFactoryAlt.hh" 
#include "G4PhysicsConstructorRegistry.hh"
#include "G4PhysListRegistry.hh"
#include "G4OpticalPhysics.hh"
#include "G4NeutronTrackingCut.hh"
#include "G4VModularPhysicsList.hh"
#include "G4StepLimiter.hh"
#include "G4StepLimiterPhysics.hh"
#include "G4SystemOfUnits.hh"




G4::G4(G4String fname)
:
ctx(new Ctx),
rm(new G4RunManager),

sdn("SD0"),
//sd(new SensitiveDetector(sdn)),
dc(new DetectorConstruction(fname)),

  
pl(NULL),
ga(NULL),
ra(NULL),
ea(NULL),
ta(NULL),
sa(NULL) {
  //dc(new DetConOrg(sdn)),
//
    // Access to registries and factories
    //
    G4PhysicsConstructorRegistry* g4pcr = G4PhysicsConstructorRegistry::Instance();
    G4PhysListRegistry* g4plr = G4PhysListRegistry::Instance();
    // print state of the factory after loading 2nd library
    
    G4cout<< "Available Physics Constructors:  "<< g4pcr->AvailablePhysicsConstructors().size()<<G4endl;
    G4cout<< "Available Physics Lists:         "<< g4plr->AvailablePhysLists().size()<<G4endl;
    G4cout<< "Available Physics Extensions:    "<< g4plr->AvailablePhysicsExtensions().size()<<G4endl;
    G4cout<< "Available Physics Lists Em:      "<< g4plr->AvailablePhysListsEM().size()<<G4endl;
     

    g4plr->AddPhysicsExtension("OPTICAL", "G4OpticalPhysics");
    g4plr->AddPhysicsExtension("STEPLIMIT", "G4StepLimiterPhysics");
    g4plr->AddPhysicsExtension("NEUTRONLIMIT", "G4NeutronTrackingCut");

    g4pcr->PrintAvailablePhysicsConstructors();
    g4plr->PrintAvailablePhysLists();
    g4alt::G4PhysListFactory factory;
    G4VModularPhysicsList* phys = nullptr;
    G4String physName = "FTFP_BERT+OPTICAL+STEPLIMIT+NEUTRONLIMIT";
    //
    // currently using the Constructor names doesn't work otherwise it would be:
    // G4String physName = "FTFP_BERT+G4OpticalPhysics+G4StepLimiterPhysics";
    // using the name doesn't work either
    //G4String physName = "FTFP_BERT+Optical+stepLimiter";
    // reference PhysicsList via its name
    if (factory.IsReferencePhysList(physName)) {
        phys = factory.GetReferencePhysList(physName);
    }
    /*
        // now add optical physics constructor:
        G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
        phys->RegisterPhysics(opticalPhysics);
        // Cerenkov off by default
     */

    G4cout << phys->GetPhysicsTableDirectory() << G4endl;
    G4OpticalPhysics* opticalPhysics = (G4OpticalPhysics*) phys->GetPhysics("Optical");
    //G4OpticalPhysics* opticalPhysics = (G4OpticalPhysics*) phys->GetPhysics("G4OpticalPhysics");
    opticalPhysics->Configure(kCerenkov, true);
    opticalPhysics->SetCerenkovStackPhotons(false);
    opticalPhysics->Configure(kWLS, false);
    opticalPhysics->Configure(kScintillation, true);
//    opticalPhysics->SetScintillationYieldFactor(1.0);
//    opticalPhysics->SetScintillationExcitationRatio(0.0);
    opticalPhysics->Configure(kRayleigh, true);
    opticalPhysics->Configure(kBoundary, true);
    opticalPhysics->Configure(kAbsorption, true);
    opticalPhysics->SetScintillationStackPhotons(false);
    opticalPhysics->SetTrackSecondariesFirst(kCerenkov, true); // only relevant if we actually stack and trace the optical photons
    opticalPhysics->SetTrackSecondariesFirst(kScintillation, false); // only relevant if we actually stack and trace the optical photons
    opticalPhysics->SetMaxNumPhotonsPerStep(100);
    opticalPhysics->SetMaxBetaChangePerStep(10.0);


    /*
    G4NeutronTrackingCut * neutrcut = (G4NeutronTrackingCut*) phys->GetPhysics("neutronTrackingCut");
    //    G4NeutronTrackingCut * neutrcut = (G4NeutronTrackingCut*) phys->GetPhysics("G4NeutronTrackingCut");
    neutrcut->SetTimeLimit(10000);
    //G4cout << "step limiter enabled limit: " << ConfigurationManager::getInstance()->Getlimitval() * cm << " cm" << G4endl;
    //
     */
    phys->DumpList();
    
    rm->SetUserInitialization(dc);
    rm->SetUserInitialization(phys);
    ga = new PrimaryGeneratorAction();
    ra = new RunAction();
    ea = new EventAction(ctx);
    ta = new TrackingAction(ctx);
    sa = new SteppingAction(ctx);

    rm->SetUserAction(ga);
    rm->SetUserAction(ra);
    rm->SetUserAction(ea);
    rm->SetUserAction(ta);
    rm->SetUserAction(sa);

    rm->Initialize();
    // beamOn(nev);
}

G4::~G4() {
    G4GeometryManager::GetInstance()->OpenGeometry();
}

//id G4::beamOn(int nev) {
//  rm->BeamOn(nev);
//


