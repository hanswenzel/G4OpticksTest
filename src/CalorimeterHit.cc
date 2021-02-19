
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "CalorimeterHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

G4ThreadLocal G4Allocator<CalorimeterHit>* CalorimeterHitAllocator = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CalorimeterHit::CalorimeterHit()
: G4VHit(),
Edep(0),
em_Edep(0),
time(0),
position(0) {
}

CalorimeterHit::CalorimeterHit(unsigned i,
        G4double e,
        G4double em,
        G4double t,
        G4ThreeVector p) : G4VHit() {
    id = i;
    Edep = e;
    em_Edep = em;
    time = t;
    position = p;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CalorimeterHit::~CalorimeterHit() {
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CalorimeterHit::CalorimeterHit(const CalorimeterHit& right)
: G4VHit() {
    this->id = right.id;
    this->Edep = right.Edep;
    this->em_Edep = right.em_Edep;
    this->time = right.time;
    this->position = right.position;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const CalorimeterHit& CalorimeterHit::operator=(const CalorimeterHit& right) {
    this->id = right.id;
    this->Edep = right.Edep;
    this->em_Edep = right.em_Edep;
    this->time = right.time;
    this->position = right.position;
    return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool CalorimeterHit::operator==(const CalorimeterHit& right) const {
    return (this == &right) ? true : false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CalorimeterHit::Draw() {
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

void CalorimeterHit::Print() {

    //    position.
    //    G4ThreeVector position;
    //    G4ThreeVector direction;
    //    G4ThreeVector polarization;
    //  G4cout << "  trackID: " << fTrackID << "  chamberNb: " << fChamberNb
    //          << "  wavelength deposit[MeV]: " << fEdep
    //          << "  position[mm]: " << fPos << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

