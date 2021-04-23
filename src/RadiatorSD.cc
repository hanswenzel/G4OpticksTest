// -----------------------------------------------------
//  _    _        _____         _   
// | |  / \   _ _|_   _|__  ___| |_ 
// | | / _ \ | '__|| |/ _ \/ __| __|
// | |/ ___ \| |   | |  __/\__ \ |_ 
// |_/_/   \_\_|   |_|\___||___/\__|
//                                  
// lArTest: A Geant4 application to study and profile  
//          simulation of physics processes relevant 
//          to liquid Ar TPC
//
// Author: Hans Wenzel, Fermilab
// -----------------------------------------------------
// Geant4 headers
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4VProcess.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4EventManager.hh"
#include "G4Event.hh"
#include "G4Cerenkov.hh"
#include "G4SteppingManager.hh"
#include "G4Track.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4VRestDiscreteProcess.hh"
#include "G4RunManager.hh"
#ifdef WITH_G4OPTICKS
#include "G4Opticks.hh"
#include "TrackInfo.hh"
#include "OpticksGenstep.h"
#include "OpticksFlags.hh"
#include "G4OpticksHit.hh"
#endif
// project headers
#include "RadiatorSD.hh"
#include "PhotonSD.hh"
#include "ConfigurationManager.hh"
#include "Event.hh"
#include <string>
using namespace std;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RadiatorSD::RadiatorSD(G4String name)
: G4VSensitiveDetector(name) {
    first = true;
    verbose = ConfigurationManager::getInstance()->isEnable_verbose();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RadiatorSD::~RadiatorSD() {
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RadiatorSD::Initialize(G4HCofThisEvent*) {

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool RadiatorSD::ProcessHits(G4Step* aStep, G4TouchableHistory*) {
    G4double edep = aStep->GetTotalEnergyDeposit();
    if (edep == 0.) return false;
    // only deal with charged particles
    G4Track* aTrack = aStep->GetTrack();
    G4double charge = aTrack->GetDynamicParticle()->GetCharge();
    if (charge == 0) return false;
#ifdef WITH_G4OPTICKS
    if (ConfigurationManager::getInstance()->isEnable_opticks()) {
        if (first) {
            aMaterial = aTrack->GetMaterial();
            materialIndex = aMaterial->GetIndex();
            if (verbose) {
                G4cout << "RadiatorSD::ProcessHits initializing Material:  "
                        << aMaterial->GetName() << " "
                        << G4endl;
                G4cout << "RadiatorSD::ProcessHits: Name " << aStep->GetPreStepPoint()->GetPhysicalVolume()->GetLogicalVolume()->GetName() << G4endl;
            }
            aMaterialPropertiesTable = aMaterial->GetMaterialPropertiesTable();
            if (verbose) {
                aMaterialPropertiesTable->DumpTable();
            }
            // 
            // properties related to Scintillation
            //
            //            Fast_Intensity = aMaterialPropertiesTable->GetProperty(kFASTCOMPONENT);
            //            Slow_Intensity = aMaterialPropertiesTable->GetProperty(kSLOWCOMPONENT);
            YieldRatio = aMaterialPropertiesTable->GetConstProperty(kYIELDRATIO); // slowerRatio,
            FastTimeConstant = aMaterialPropertiesTable->GetConstProperty(kFASTTIMECONSTANT); // TimeConstant,
            SlowTimeConstant = aMaterialPropertiesTable->GetConstProperty(kSLOWTIMECONSTANT); //slowerTimeConstant,
            ScintillationType = Slow;
            //          if (!aMaterialPropertiesTable) return false;
            // 
            // properties related to Cerenkov
            //
            Rindex = aMaterialPropertiesTable->GetProperty("RINDEX");
            //        thePhysicsTable    G4PhysicsTable * GetPhysicsTable() const;
            //        CerenkovAngleIntegrals = (G4PhysicsOrderedFreeVector*) ((*thePhysicsTable)(materialIndex));
            //G4PhysicsTable * GetPhysicsTable() const;
            Pmin = Rindex->GetMinLowEdgeEnergy();
            Pmax = Rindex->GetMaxLowEdgeEnergy();
            dp = Pmax - Pmin;
            if (verbose) {
                G4cout << "nMax: " << nMax
                        << "Pmin: " << Pmin
                        << "Pmax: " << Pmax
                        << "dp: " << dp << G4endl;
                Rindex->DumpValues();
            }
            //
            first = false;
        } // end if first
        G4int Sphotons = 0; // number of scintillation photons this step 
        G4int Cphotons = 0; // number of Cerenkov photons this step 
        //
        // info needed for generating Cerenkov photons on the GPU;
        //
        G4double maxCos = 0.0;
        G4double maxSin2 = 0.0;
        G4double beta = 0.0;
        G4double beta1 = 0.0;
        G4double beta2 = 0.0;
        G4double BetaInverse = 0.0;
        G4double MeanNumberOfPhotons1 = 0.0;
        G4double MeanNumberOfPhotons2 = 0.0;

        G4SteppingManager* fpSteppingManager = G4EventManager::GetEventManager()->GetTrackingManager()->GetSteppingManager();
        G4StepStatus stepStatus = fpSteppingManager->GetfStepStatus();
        if (stepStatus != fAtRestDoItProc) {
            G4ProcessVector* procPost = fpSteppingManager->GetfPostStepDoItVector();
            size_t MAXofPostStepLoops = fpSteppingManager->GetMAXofPostStepLoops();
            for (size_t i3 = 0; i3 < MAXofPostStepLoops; i3++) {
                if ((*procPost)[i3]->GetProcessName() == "Cerenkov") {
                    G4Cerenkov* proc = (G4Cerenkov*) (*procPost)[i3];
                    thePhysicsTable = proc->GetPhysicsTable();
                    CerenkovAngleIntegrals = (G4PhysicsOrderedFreeVector*) ((*thePhysicsTable)(materialIndex));
                    Cphotons = proc->GetNumPhotons();
                    if (Cphotons > 0) {
                        beta1 = aStep->GetPreStepPoint()->GetBeta();
                        beta2 = aStep->GetPostStepPoint()->GetBeta();
                        beta = (beta1 + beta2) *0.5;
                        BetaInverse = 1. / beta;
                        maxCos = BetaInverse / nMax;
                        maxSin2 = (1.0 - maxCos) * (1.0 + maxCos);
                        MeanNumberOfPhotons1 = proc-> GetAverageNumberOfPhotons(charge, beta1, aMaterial, Rindex);
                        MeanNumberOfPhotons2 = proc-> GetAverageNumberOfPhotons(charge, beta2, aMaterial, Rindex);
                    }
                }
                if ((*procPost)[i3]->GetProcessName() == "Scintillation") {
                    G4Scintillation* proc1 = (G4Scintillation*) (*procPost)[i3];
                    Sphotons = proc1->GetNumPhotons();
                }
            }
        }
        tSphotons += Sphotons;
        tCphotons += Cphotons;

        //   unsigned opticks_photon_offset = 0;
        const G4DynamicParticle* aParticle = aTrack->GetDynamicParticle();
        const G4ParticleDefinition* definition = aParticle->GetDefinition();
        G4ThreeVector deltaPosition = aStep->GetDeltaPosition();
        G4double ScintillationTime = 0. * ns;
        //    G4double ScintillationRiseTime = 0. * ns;
        G4int scntId = 1;
        // total number of photons for all gensteps collected before this one
        // within this OpticksEvent (potentially crossing multiple G4Event)
        G4StepPoint* pPreStepPoint = aStep->GetPreStepPoint();
        //   G4StepPoint* pPostStepPoint = aStep->GetPostStepPoint();
        G4ThreeVector x0 = pPreStepPoint->GetPosition();
        G4ThreeVector p0 = aStep->GetDeltaPosition().unit();
        G4double t0 = pPreStepPoint->GetGlobalTime();
        //
        // harvest the Scintillation photon gensteps:
        //
        if (Sphotons > 0) {
            // total number of photons for all gensteps collected before this one
            // within this OpticksEvent (potentially crossing multiple G4Event)
            //           int opticks_photon_offset = G4Opticks::Get()->getNumPhotons();
            //            G4cout << "RadiatorSD::ProcessHits: offset " << opticks_photon_offset << G4endl;
            //            G4cout << "RadiatorSD::ProcessHits:  Scint. photons " << Sphotons << G4endl;
            G4Opticks::Get()->collectScintillationStep(
                    //1, // 0    id:zero means use scintillation step count
                    OpticksGenstep_G4Scintillation_1042,
                    aTrack->GetTrackID(),
                    materialIndex,
                    Sphotons,
                    x0.x(), // 1
                    x0.y(),
                    x0.z(),
                    t0,
                    deltaPosition.x(), // 2
                    deltaPosition.y(),
                    deltaPosition.z(),
                    aStep->GetStepLength(),
                    definition->GetPDGEncoding(), // 3
                    definition->GetPDGCharge(),
                    aTrack->GetWeight(),
                    pPreStepPoint->GetVelocity(),
                    scntId,
                    YieldRatio, // slowerRatio,
                    FastTimeConstant, // TimeConstant,
                    SlowTimeConstant, //slowerTimeConstant,
                    ScintillationTime, //scintillationTime,
                    0.0, //not used scintillationIntegrationMax,
                    0, //spare1
                    0 // spare2
                    );
        }
        //
        // harvest the Cerenkov photon gensteps:
        //
        if (Cphotons > 0) {

            // total number of photons for all gensteps collected before this one
            // within this OpticksEvent (potentially crossing multiple G4Event)
            //        opticks_photon_offset = G4Opticks::Get()->getNumPhotons();
            //        G4cout << "RadiatorSD::ProcessHits: offset " << opticks_photon_offset << G4endl;
            //        G4cout << "RadiatorSD::ProcessHits:  Cerenkov photons " << Cphotons << G4endl;
            G4Opticks::Get()->collectGenstep_G4Cerenkov_1042(
                    aTrack,
                    aStep,
                    Cphotons,

                    BetaInverse,
                    Pmin,
                    Pmax,
                    maxCos,

                    maxSin2,
                    MeanNumberOfPhotons1,
                    MeanNumberOfPhotons2
                    );
        }
        G4Opticks* g4ok = G4Opticks::Get();
        G4RunManager* rm = G4RunManager::GetRunManager();
        const G4Event*event = rm->GetCurrentEvent();
        G4int eventid = event->GetEventID();
        G4OpticksHit hit;
        unsigned num_photons = g4ok->getNumPhotons();
        if (num_photons > ConfigurationManager::getInstance()->getMaxPhotons()) {
            g4ok->propagateOpticalPhotons(eventid);
            G4HCtable* hctable = G4SDManager::GetSDMpointer()->GetHCtable();
            for (G4int  i = 0; i < hctable->entries(); ++i) {
                std::string sdn= hctable->GetSDname(i);
                std::size_t found = sdn.find("Photondetector");
                if (found != std::string::npos) {
                    PhotonSD* aSD = (PhotonSD*) G4SDManager::GetSDMpointer()->FindSensitiveDetector(sdn);
                    aSD->AddOpticksHits();
                }
            }
            g4ok->reset();
        }
    }
#endif 
    return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RadiatorSD::EndOfEvent(G4HCofThisEvent*) {
    tSphotons = 0;
    tCphotons = 0;
}

