/* ------------------------------------------------------------------------
            |\___/|       
            )     (    
           =\     /=
             )===(
            /     \         CaTS: Calorimeter and Tracker Simulation
            |     |         Author: Hans Wenzel (Fermilab)
           /       \        Created on June 23, 2014
           \       /
            \__  _/
              ( (
               ) )
              (_(
-------------------------------------------------------------------------*/
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#include "InteractionHit.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

G4Allocator<InteractionHit> InteractionHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

InteractionHit::InteractionHit() {
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

InteractionHit::InteractionHit(G4String pn, G4double p, G4double e,G4double t) {
    pname = pn; // name of secondary particle
    pmom = p;   // momentum of secondary particle
    Ekin = e;   // kinetic energy of secondary particle
    theta = t;  // theta of secondary particle 
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

InteractionHit::~InteractionHit() {
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

InteractionHit::InteractionHit(const InteractionHit& right)
: G4VHit() {

    pname = right.pname;
    pmom = right.pmom;
    Ekin = right.Ekin;
    theta = right.theta;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const InteractionHit& InteractionHit::operator=(const InteractionHit& right) {
    pname = right.pname;
    pmom = right.pmom;
    Ekin = right.Ekin;
    theta = right.theta;
    return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4int InteractionHit::operator==(const InteractionHit& right) const {
    return (this == &right) ? 1 : 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void InteractionHit::Print() {

    G4cout << "Particle name : " << pname
            << "  momentum [GeV]: " << pmom
            << "kinetic Energy [GeV]"<<Ekin
            << "  theta: " << theta
            << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


