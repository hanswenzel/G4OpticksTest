#ifndef CalorimeterSD_h
#define CalorimeterSD_h 1

#include "G4VSensitiveDetector.hh"
#include "CalorimeterHit.hh"

class G4Step;
class G4HCofThisEvent;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class CalorimeterSD : public G4VSensitiveDetector {
public:
    CalorimeterSD(G4String);
    ~CalorimeterSD();

    void Initialize(G4HCofThisEvent*);
    G4bool ProcessHits(G4Step*, G4TouchableHistory*);
    virtual void EndOfEvent(G4HCofThisEvent* hitCollection);

private:
    CalorimeterHitsCollection* fCalorimeterHitsCollection;
    G4int fHCID;
    bool verbose;
};
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

