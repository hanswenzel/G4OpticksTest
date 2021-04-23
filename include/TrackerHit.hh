#ifndef TRACKERHIT_HH
#define TRACKERHIT_HH
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class TrackerHit : public G4VHit {
    // Default constructor
public:
    TrackerHit();
    ~TrackerHit();
    TrackerHit(const TrackerHit&);
    const TrackerHit& operator=(const TrackerHit&);
    G4bool operator==(const TrackerHit&) const;

    inline void* operator new(size_t);
    inline void operator delete(void*);

    virtual void Draw();
    virtual void Print();

    TrackerHit(G4double edep, G4ThreeVector position, G4double time);

    G4double GetEdep() {
        return Edep;
    }
private:

    G4double Edep;
    G4ThreeVector position;
    G4double time;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

using TrackerHitsCollection = G4THitsCollection<TrackerHit>;
extern G4ThreadLocal G4Allocator<TrackerHit>* TrackerHitAllocator;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* TrackerHit::operator new(size_t){
    if (!TrackerHitAllocator) {
        TrackerHitAllocator = new G4Allocator<TrackerHit>;
    }
    return (void *) TrackerHitAllocator->MallocSingle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void TrackerHit::operator delete(void *aHit) {
    TrackerHitAllocator->FreeSingle((TrackerHit*) aHit);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
