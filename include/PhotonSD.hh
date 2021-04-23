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

#ifndef PhotonSD_h
#define PhotonSD_h 1

#include "G4VSensitiveDetector.hh"
#include "PhotonHit.hh"

class G4Step;
class G4HCofThisEvent;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class PhotonSD : public G4VSensitiveDetector {
public:

    PhotonSD(G4String);
    ~PhotonSD();

    void Initialize(G4HCofThisEvent*);
    G4bool ProcessHits(G4Step*, G4TouchableHistory*);
#ifdef WITH_G4OPTICKS
    void AddOpticksHits();
#endif
    virtual void EndOfEvent(G4HCofThisEvent* hitCollection);

private:
    PhotonHitsCollection* fPhotonHitsCollection;
    double etolambda(double);
    G4int fHCID;
    const double c = 299792458.; // speed of light in m/sec
    const double h = 4.13566743E-15; // Planck constant in eVsec
    bool verbose;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
