// -----------------------------------------------------
//  _    _        _____         _   
// | |  / \   _ _|_   _|__  ___| |_ 
// | | / _ \ | '__|| |/ _ \/ __| __|
// | |/ ___ \| |   | |  __/\__ \ |_ 
// |_/_/   \_\_|   |_|\___||___/\__|
//                                  
// lArTest: A Geant4 application to study and profile  
//          simulation of physics processes relevant 
//          to liquid Ar TPCs
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
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4Cerenkov.hh"
#include "G4Scintillation.hh"
#include "G4SteppingManager.hh"
#include "G4Track.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4VRestDiscreteProcess.hh"
#include "G4ScintillationTrackInformation.hh"
//#ifdef WITH_OPTICKS
#include "G4Opticks.hh"
#include "TrackInfo.hh"    
// TrackInfo is a simple struct holding the photon_record_id integer
//#endif
#include "OpticksGenstep.h"
// project headers
#include "lArTPCSD.hh"
//#include "Analysis.hh"
#include "ConfigurationManager.hh"
using namespace std;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
int tphotons;
lArTPCSD::lArTPCSD(G4String name)
: G4VSensitiveDetector(name) {
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

lArTPCSD::~lArTPCSD() {

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void lArTPCSD::Initialize(G4HCofThisEvent* hce) {

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool lArTPCSD::ProcessHits(G4Step* aStep,
        G4TouchableHistory*) {
    G4double edep = aStep->GetTotalEnergyDeposit();
    if (edep == 0.) return false;
    // only deal with charged particles
    G4Track* aTrack = aStep->GetTrack();
    if (aTrack->GetDynamicParticle()->GetCharge() == 0) return false;
    const G4Material* aMaterial = aTrack->GetMaterial();
    G4cout
            << "lArTPCSD::ProcessHits Material:  "
            << aMaterial->GetName() << " "
            << G4endl
            ;
    G4MaterialPropertiesTable* aMaterialPropertiesTable =
            aMaterial->GetMaterialPropertiesTable();
    G4cout << "lArTPCSD::ProcessHits:  predump:   " << aMaterial->GetName() << G4endl;
    aMaterialPropertiesTable->DumpTable();
    G4cout << "lArTPCSD::ProcessHits:  postdump " << G4endl;

    if (!aMaterialPropertiesTable) return false;
    //        return G4VRestDiscreteProcess::PostStepDoIt(aTrack, *aStep);
    G4cout << "lArTPCSD::ProcessHits:  Hi Hi " << G4endl;
    G4MaterialPropertyVector* Fast_Intensity =
            aMaterialPropertiesTable->GetProperty(kFASTCOMPONENT);
    G4MaterialPropertyVector* Slow_Intensity =
            aMaterialPropertiesTable->GetProperty(kSLOWCOMPONENT);

    G4int photons = 0;
    G4SteppingManager* fpSteppingManager = G4EventManager::GetEventManager()->GetTrackingManager()->GetSteppingManager();
    G4StepStatus stepStatus = fpSteppingManager->GetfStepStatus();
    if (stepStatus != fAtRestDoItProc) {
        G4ProcessVector* procPost = fpSteppingManager->GetfPostStepDoItVector();
        size_t MAXofPostStepLoops = fpSteppingManager->GetMAXofPostStepLoops();
        for (size_t i3 = 0; i3 < MAXofPostStepLoops; i3++) {

            if ((*procPost)[i3]->GetProcessName() == "Cerenkov") {
                G4Cerenkov* proc = (G4Cerenkov*) (*procPost)[i3];
                photons += proc->GetNumPhotons();
            }
            if ((*procPost)[i3]->GetProcessName() == "Scintillation") {
                G4Scintillation* proc1 = (G4Scintillation*) (*procPost)[i3];
                photons += proc1->GetNumPhotons();
            }
        }
    }
    tphotons=tphotons+photons;
    //#ifdef WITH_OPTICKS
    unsigned opticks_photon_offset = 0;
    const G4DynamicParticle* aParticle = aTrack->GetDynamicParticle();
    const G4ParticleDefinition* definition = aParticle->GetDefinition();
    G4ThreeVector deltaPosition = aStep->GetDeltaPosition();
    G4cout << "G4Scintillation::PostStepDoIt"
            //               << " dp (Pmax-Pmin) " << dp
            << G4endl
            ;
    G4double ScintillationTime = 0. * ns;
    G4double ScintillationRiseTime = 0. * ns;
//    G4PhysicsOrderedFreeVector* ScintillationIntegral = nullptr;
    G4ScintillationType ScintillationType = Slow;
    opticks_photon_offset = G4Opticks::GetOpticks()->getNumPhotons();
    G4cout << "lArTPCSD::ProcessHits: offset " << opticks_photon_offset << G4endl;
    G4cout << "lArTPCSD::ProcessHits:  photons " << photons << G4endl;
    G4int scntId = 1;
    // total number of photons for all gensteps collected before this one
    // within this OpticksEvent (potentially crossing multiple G4Event)
    G4StepPoint* pPreStepPoint = aStep->GetPreStepPoint();
    G4StepPoint* pPostStepPoint = aStep->GetPostStepPoint();
    G4ThreeVector x0 = pPreStepPoint->GetPosition();
    G4ThreeVector p0 = aStep->GetDeltaPosition().unit();
    G4double t0 = pPreStepPoint->GetGlobalTime();
    
    G4int materialIndex = aMaterial->GetIndex();

    // Max Scintillation Integral

//    G4double CIImax = ScintillationIntegral->GetMaxValue();
//    G4cout << " CIImax:  " << CIImax << G4endl;
//    G4cout << " ScintillationTime:  " << ScintillationTime << G4endl;
    if (photons>0){
    G4Opticks::GetOpticks()->collectScintillationStep(
            //1, // 0    id:zero means use scintillation step count
            OpticksGenstep_G4Scintillation_1042,
            aTrack->GetTrackID(),
            materialIndex,
            photons,
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
            aMaterialPropertiesTable->GetConstProperty(kYIELDRATIO), // slowerRatio,
            aMaterialPropertiesTable->GetConstProperty(kFASTTIMECONSTANT), // TimeConstant,
            aMaterialPropertiesTable->GetConstProperty(kSLOWTIMECONSTANT), //slowerTimeConstant,
            ScintillationTime, //scintillationTime,
            0.0,//wrong but not used scintillationIntegrationMax,
            0, //spare1
            0 // spare2
            );
    }
    //#endif 





    //ConfigurationManager* cfMgr = ConfigurationManager::getInstance();
    //std::map<G4String, int> *mapOfntIDs = cfMgr->getMapOfntIDs();
    //const G4String name = aStep->GetPostStepPoint()->GetPhysicalVolume()->GetLogicalVolume()->GetName() + "_Tracker";
     std::cout << "lArTPCSD::ProcessHits: Name " << aStep->GetPreStepPoint()->GetPhysicalVolume()->GetLogicalVolume()->GetName()<<std::endl;
    //const G4String name = aStep->GetPreStepPoint()->GetPhysicalVolume()->GetLogicalVolume()->GetName() + "_Tracker";
    //G4int ID = 0;
    //std::map<G4String, int>::iterator iter = mapOfntIDs->find(name);
    //G4int ID = (*mapOfntIDs)[name];
    //std::cout <<"ID:  "<<ID<<std::endl;
    //for (std::map<G4String, int>::iterator ii = mapOfntIDs->begin(); ii != mapOfntIDs->end(); ++ii) {
    //    std::cout << (*ii).first << ": " << (*ii).second << std::endl;
    //}
    //mapOfntIDs[name];
    /*
    if (cfMgr->GetdoAnalysis()) {
        // get analysis manager
        auto analysisManager = G4AnalysisManager::Instance();
        // fill ntuple
        analysisManager->FillNtupleDColumn(ID, 0, edep / MeV);
        analysisManager->FillNtupleDColumn(ID, 1, aStep->GetTrack()->GetPosition().x() / cm);
        analysisManager->FillNtupleDColumn(ID, 2, aStep->GetTrack()->GetPosition().y() / cm);
        analysisManager->FillNtupleDColumn(ID, 3, aStep->GetTrack()->GetPosition().z() / cm);
        analysisManager->FillNtupleDColumn(ID, 4, aStep->GetTrack()->GetGlobalTime() / ns);
        analysisManager->FillNtupleDColumn(ID, 5, aStep->GetStepLength() / cm);
        analysisManager->FillNtupleIColumn(ID, 6, photons);
        analysisManager->FillNtupleIColumn(ID, 7, G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID());
        analysisManager->AddNtupleRow(ID);
    }
     */
    return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void lArTPCSD::EndOfEvent(G4HCofThisEvent*) {
    G4cout<<" tphotons:  "<<tphotons<<G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
