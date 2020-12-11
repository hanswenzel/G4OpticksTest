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
#ifndef lArTPCSD_h
#define lArTPCSD_h 1
#include "G4Scintillation.hh"
#include "G4VSensitiveDetector.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4PhysicsOrderedFreeVector.hh" 
#include "G4ScintillationTrackInformation.hh"
#include "lArTPCHit.hh"
class G4Step;
class G4HCofThisEvent;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class lArTPCSD : public G4VSensitiveDetector {
public:
    lArTPCSD(G4String name);
    virtual ~lArTPCSD();

    // methods from base class
    virtual void Initialize(G4HCofThisEvent* hitCollection);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
    virtual void EndOfEvent(G4HCofThisEvent* hitCollection);

private:
    G4int materialIndex;
    const G4Material* aMaterial;
    G4MaterialPropertiesTable* aMaterialPropertiesTable;
    //
    // properties related to Scintillation
    //
    G4MaterialPropertyVector* Fast_Intensity;
    G4MaterialPropertyVector* Slow_Intensity;
    G4double YieldRatio; // slowerRatio,
    G4double FastTimeConstant; // TimeConstant,
    G4double SlowTimeConstant; //slowerTimeConstant,
    G4ScintillationType ScintillationType;
    //
    // properties related to Cerenkov
    //
    G4MaterialPropertyVector* Rindex;
    G4PhysicsOrderedFreeVector* CerenkovAngleIntegrals;
    const G4PhysicsTable* thePhysicsTable;
    G4double Pmin;
    G4double Pmax;
    G4double dp;
    G4double nMax;
    bool first;
    bool verbose;
    int tCphotons;
    int tSphotons;

    double NumElectrons(double e, double ds);
    lArTPCHitsCollection* flArTPCHitsCollection;
    G4int fHCID;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
