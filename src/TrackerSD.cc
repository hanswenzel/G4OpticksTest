#include "TrackerSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4VVisManager.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4VSolid.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "ConfigurationManager.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackerSD::TrackerSD(G4String name)
: G4VSensitiveDetector(name), fTrackerHitsCollection(0), fHCID(0) {
    G4String HCname = name + "_HC";
    collectionName.insert(HCname);
    G4cout << collectionName.size() << "   TrackerSD name:  " << name << " collection Name: "
            << HCname << G4endl;
    fHCID = -1;
    verbose = ConfigurationManager::getInstance()->isEnable_verbose();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackerSD::Initialize(G4HCofThisEvent* hce) {
    fTrackerHitsCollection = new TrackerHitsCollection(SensitiveDetectorName, collectionName[0]);
    if (fHCID < 0) {
        if (verbose) G4cout << "TrackerSD::Initialize:  " << SensitiveDetectorName << "   "
                << collectionName[0] << G4endl;
        fHCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    }
    hce->AddHitsCollection(fHCID, fTrackerHitsCollection);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackerSD::~TrackerSD() {
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool TrackerSD::ProcessHits(G4Step* aStep, G4TouchableHistory*) {
    G4double edep = aStep->GetTotalEnergyDeposit();
    if (edep == 0.) return false;
    if (aStep->GetTrack()->GetDynamicParticle()->GetCharge() == 0) return false;
    TrackerHit* newHit = new TrackerHit(
            edep,
            aStep->GetPostStepPoint()->GetPosition(),
            aStep->GetPostStepPoint()->GetGlobalTime() / ns
            );
    fTrackerHitsCollection->insert(newHit);
    return true;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackerSD::EndOfEvent(G4HCofThisEvent*) {
    G4int NbHits = fTrackerHitsCollection->entries();
    if (verbose) G4cout << " Number of TrackerHits:  " << NbHits << G4endl;
}

