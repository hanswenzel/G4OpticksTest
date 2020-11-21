// Geant4 headers
#include "G4SystemOfUnits.hh"
#include "G4ParticleGun.hh"
// Project headers:
#include "PrimaryGeneratorAction.hh"
#include "Randomize.hh"
#include <time.h>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
using namespace std;

PrimaryGeneratorAction::PrimaryGeneratorAction() {
    particleGun = new G4ParticleGun(1);
    particleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
    G4double zVertex = -4.55 * m;
    particleGun->SetParticlePosition(G4ThreeVector(0., 0., zVertex));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction() {
    delete particleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
    particleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
