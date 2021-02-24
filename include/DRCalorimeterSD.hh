#ifndef DRCalorimeterSD_h
#define DRCalorimeterSD_h 1

#include "G4VSensitiveDetector.hh"
#include "DRCalorimeterHit.hh"

class G4Step;
class G4HCofThisEvent;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DRCalorimeterSD : public G4VSensitiveDetector {
public:
    DRCalorimeterSD(G4String);
    ~DRCalorimeterSD();

    void Initialize(G4HCofThisEvent*);
    G4bool ProcessHits(G4Step*, G4TouchableHistory*);
    virtual void EndOfEvent(G4HCofThisEvent* hitCollection);

private:
    DRCalorimeterHitsCollection* fDRCalorimeterHitsCollection;
    G4int fHCID;
    bool verbose;
};
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

