#include "CalorimeterSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4VVisManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CalorimeterSD::CalorimeterSD(G4String name)
: G4VSensitiveDetector(name) {
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CalorimeterSD::~CalorimeterSD() {

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CalorimeterSD::Initialize(G4HCofThisEvent* HCE) {
  calorimeterCollection.clear();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool CalorimeterSD::ProcessHits(G4Step* aStep, G4TouchableHistory*) {
    G4double edep = aStep->GetTotalEnergyDeposit() / CLHEP::MeV;
    if (edep == 0.) return false;
    const G4double time = aStep->GetPreStepPoint()->GetGlobalTime() / CLHEP::ns;
    const G4VTouchable* touch = aStep->GetPreStepPoint()->GetTouchable();
    const G4ThreeVector cellpos = touch->GetTranslation();
    int ID = aStep->GetPreStepPoint()->GetPhysicalVolume()->GetCopyNo();
    //std::cout<<"ID:  "<<ID<<"  Edep:  "<< edep<<std::endl;
    G4Track* theTrack = aStep->GetTrack();
    G4String particleType = theTrack->GetDefinition()->GetParticleName();
    // 
    //  check if this cell has been hit before
    //

    for (unsigned int j = 0; j < calorimeterCollection.size(); j++) {
        CalorimeterHit aPreviousHit = calorimeterCollection[j];
        if (ID == aPreviousHit.GetID()) {
            aPreviousHit.SetEdep(aStep->GetTotalEnergyDeposit() + aPreviousHit.GetEdep());
            if ((particleType == "e+") || (particleType == "gamma") || (particleType == "e-")) {
                aPreviousHit.Setem_Edep(edep + aPreviousHit.GetEdepEM());
            } else {
                aPreviousHit.Setnonem_Edep(edep + aPreviousHit.GetEdepnonEM());
            }
            return true;
        }
    }
    //
    // otherwise create a new hit:
    //
    CalorimeterHit newHit;
    if ((particleType == "e+") || (particleType == "gamma") || (particleType == "e-")) {
      newHit= CalorimeterHit(ID,edep,edep,0.0,cellpos.x(),cellpos.y(),cellpos.z(),time);
    } else {
      newHit= CalorimeterHit(ID,edep,0.0,edep,cellpos.x(),cellpos.y(),cellpos.z(),time);
    }
    calorimeterCollection.push_back(newHit);
    return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

