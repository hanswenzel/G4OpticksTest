#include "lArTPCHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

G4ThreadLocal G4Allocator<lArTPCHit>* lArTPCHitAllocator = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

lArTPCHit::lArTPCHit()
: G4VHit(), fElectrons(0), fPosX(0), fPosY(0), fPosZ(0) {
}

lArTPCHit::lArTPCHit(G4double fe, G4double fx, G4double fy, G4double fz) {
    fElectrons = fe;
    fPosX = fx;
    fPosY = fy;
    fPosZ = fz;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

lArTPCHit::~lArTPCHit() {
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

lArTPCHit::lArTPCHit(const lArTPCHit& right)
: G4VHit() {
    fElectrons = right.fElectrons;
    fPosX = right.fPosX;
    fPosY = right.fPosY;
    fPosZ = right.fPosZ;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const lArTPCHit& lArTPCHit::operator=(const lArTPCHit& right) {
    fElectrons = right.fElectrons;
    fPosX = right.fPosX;
    fPosY = right.fPosY;
    fPosZ = right.fPosZ;
    return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool lArTPCHit::operator==(const lArTPCHit& right) const {
    return (this == &right) ? true : false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void lArTPCHit::Draw() {
    /*
    G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
    if (pVVisManager) {
        G4Circle circle(fPos);
        circle.SetScreenSize(2.);
        circle.SetFillStyle(G4Circle::filled);
        G4Colour colour(1., 0., 0.);
        G4VisAttributes attribs(colour);
        circle.SetVisAttributes(attribs);
        pVVisManager->Draw(circle);
    }
     */
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void lArTPCHit::Print() {
    G4cout << "Nr. of electrons: " << fElectrons
            << "  x position [mm]: " << fPosX
            << "  y position [mm]: " << fPosY
            << "  z position [mm]: " << fPosZ
            << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

