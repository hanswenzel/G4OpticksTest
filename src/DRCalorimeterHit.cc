
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "DRCalorimeterHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

G4ThreadLocal G4Allocator<DRCalorimeterHit>* DRCalorimeterHitAllocator = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DRCalorimeterHit::DRCalorimeterHit()
: G4VHit(),
Edep(0),
em_Edep(0),
Nceren(0),
time(0),
position(0) {
}

void DRCalorimeterHit::SetNceren(unsigned int Nceren) {
    this->Nceren = Nceren;
}

unsigned int DRCalorimeterHit::GetNceren() const {
    return Nceren;
}

void DRCalorimeterHit::SetEm_Edep(double em_Edep) {
    this->em_Edep = em_Edep;
}

double DRCalorimeterHit::GetEm_Edep() const {
    return em_Edep;
}

DRCalorimeterHit::DRCalorimeterHit(unsigned int i,
        G4double e,
        G4double em,
        unsigned int nc,
        G4double t,
        G4ThreeVector p) : G4VHit() {
    id = i;
    Edep = e;
    em_Edep = em;
    Nceren = nc;
    time = t;
    position = p;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DRCalorimeterHit::~DRCalorimeterHit() {
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DRCalorimeterHit::DRCalorimeterHit(const DRCalorimeterHit& right)
: G4VHit() {
    this->id = right.id;
    this->Edep = right.Edep;
    this->em_Edep = right.em_Edep;
    this->Nceren = right.Nceren;
    this->time = right.time;
    this->position = right.position;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const DRCalorimeterHit& DRCalorimeterHit::operator=(const DRCalorimeterHit& right) {
    this->id = right.id;
    this->Edep = right.Edep;
    this->em_Edep = right.em_Edep;
    this->Nceren = right.Nceren;
    this->time = right.time;
    this->position = right.position;
    return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool DRCalorimeterHit::operator==(const DRCalorimeterHit& right) const {
    return (this == &right) ? true : false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DRCalorimeterHit::Draw() {
    G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();

    if (pVVisManager) {
        G4Circle circle(position);
        circle.SetScreenSize(2.);
        circle.SetFillStyle(G4Circle::filled);
        G4Colour colour(1., 0., 0.);
        G4VisAttributes attribs(colour);
        circle.SetVisAttributes(attribs);
        pVVisManager->Draw(circle);
    }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DRCalorimeterHit::Print() {

    //    position.
    //    G4ThreeVector position;
    //    G4ThreeVector direction;
    //    G4ThreeVector polarization;
    //  G4cout << "  trackID: " << fTrackID << "  chamberNb: " << fChamberNb
    //          << "  wavelength deposit[MeV]: " << fEdep
    //          << "  position[mm]: " << fPos << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

