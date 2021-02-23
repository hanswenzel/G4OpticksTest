#include "CalorimeterSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "ConfigurationManager.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CalorimeterSD::CalorimeterSD(G4String name)
: G4VSensitiveDetector(name), fCalorimeterHitsCollection(0), fHCID(0) {
    G4String HCname = name + "_HC";
    collectionName.insert(HCname);
    G4cout << collectionName.size() << "   CalorimeterSD name:  " << name << " collection Name: "
            << HCname << G4endl;
    fHCID = -1;
    verbose = ConfigurationManager::getInstance()->isEnable_verbose();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CalorimeterSD::~CalorimeterSD() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CalorimeterSD::Initialize(G4HCofThisEvent* hce) {
    fCalorimeterHitsCollection = new CalorimeterHitsCollection(SensitiveDetectorName, collectionName[0]);
    if (fHCID < 0) {
        if (verbose) G4cout << "CalorimeterSD::Initialize:  " << SensitiveDetectorName << "   "
                << collectionName[0] << G4endl;
        fHCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    }
    hce->AddHitsCollection(fHCID, fCalorimeterHitsCollection);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool CalorimeterSD::ProcessHits(G4Step* aStep, G4TouchableHistory*) {
    double edep = aStep->GetTotalEnergyDeposit() / CLHEP::MeV;
    if (edep == 0.) return false;
    double time = aStep->GetPreStepPoint()->GetGlobalTime() / CLHEP::ns;
    const G4VTouchable* touch = aStep->GetPreStepPoint()->GetTouchable();
    G4ThreeVector cellpos = touch->GetTranslation();
    unsigned int ID = aStep->GetPreStepPoint()->GetPhysicalVolume()->GetCopyNo();
    //std::cout<<"ID:  "<<ID<<"  Edep:  "<< edep<<std::endl;
    G4Track* theTrack = aStep->GetTrack();
    G4String particleType = theTrack->GetDefinition()->GetParticleName();
    // 
    //  check if this cell has been hit before
    //fCalorimeterHitsCollection
    for (unsigned int j = 0; j < fCalorimeterHitsCollection->entries(); j++) {
        CalorimeterHit* aPreviousHit = (*fCalorimeterHitsCollection)[j];
        if (ID == aPreviousHit->GetId()) {
            aPreviousHit->SetEdep(aStep->GetTotalEnergyDeposit() + aPreviousHit->GetEdep());
            if ((particleType == "e+") || (particleType == "gamma") || (particleType == "e-")) {
                aPreviousHit->Setem_Edep(edep + aPreviousHit->Getem_Edep());
            }
            return true;
        }
    }
    //
    // otherwise create a new hit:
    //
    CalorimeterHit* newHit;
    if ((particleType == "e+") || (particleType == "gamma") || (particleType == "e-")) {
        newHit = new CalorimeterHit(ID, edep, edep, time, cellpos);
    } else {
        newHit = new CalorimeterHit(ID, edep, 0.0, time, cellpos);
    }
    fCalorimeterHitsCollection->insert(newHit);
    return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void CalorimeterSD::EndOfEvent(G4HCofThisEvent*) {
    G4int NbHits = fCalorimeterHitsCollection->entries();
    if (verbose) G4cout << " Number of CalorimeterHits:  " << NbHits << G4endl;
}

