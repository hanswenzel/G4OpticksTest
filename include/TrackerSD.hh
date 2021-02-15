#ifndef TrackerSD_h
#define TrackerSD_h 1

#include "G4VSensitiveDetector.hh"
#include "TrackerHit.hh"
class G4Step;
class G4HCofThisEvent;
class TrackerHitCollection;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TrackerSD : public G4VSensitiveDetector {
public:
    TrackerSD(G4String);
    ~TrackerSD();

    void Initialize(G4HCofThisEvent*);
    G4bool ProcessHits(G4Step*, G4TouchableHistory*);
    virtual void EndOfEvent(G4HCofThisEvent* hitCollection);

private:
    TrackerHitsCollection* fTrackerHitsCollection;
    G4int fHCID;
    bool verbose;
};
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif

