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
#include "G4SystemOfUnits.hh"
#include "G4ParticleGun.hh"
// Project headers:
#include "PrimaryGeneratorAction.hh"
//#include "Analysis.hh"
#include "ConfigurationManager.hh"
//
#include "Randomize.hh"
#include <time.h>
// Geant4 headers:

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
    ConfigurationManager* cfMgr=ConfigurationManager::getInstance();
    if (cfMgr->GetdoAnalysis()) {
        /*
        Analysis* analysis = Analysis::getInstance();
        Double_t ener = particleGun->GetParticleEnergy();
        G4ParticleDefinition* part = particleGun->GetParticleDefinition();
        analysis->SetPrimGenInfo(ener, part);
         */
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
