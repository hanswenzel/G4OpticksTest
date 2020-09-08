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
#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"

class G4ParticleGun;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  PrimaryGeneratorAction();
  virtual ~PrimaryGeneratorAction();

  void GeneratePrimaries(G4Event*);
  G4ParticleGun* GetParticleGun() {return particleGun;};

private:

  PrimaryGeneratorAction & operator=(const PrimaryGeneratorAction &right);
  PrimaryGeneratorAction(const PrimaryGeneratorAction&);

  G4ParticleGun*   particleGun;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


