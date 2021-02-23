#ifndef PhotonHit_h
#define PhotonHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class PhotonHit : public G4VHit {
public:
    PhotonHit();
    ~PhotonHit();
    PhotonHit(const PhotonHit&);
    const PhotonHit& operator=(const PhotonHit&);
    G4bool operator==(const PhotonHit&) const;

    inline void* operator new(size_t);
    inline void operator delete(void*);

    virtual void Draw();
    virtual void Print();

    PhotonHit(unsigned id,
            unsigned pid,
            G4double wavelength,
            G4double time,
            G4ThreeVector position,
            G4ThreeVector direction,
            G4ThreeVector polarization);

    G4double GetWavelength() {
        return wavelength;
    }
    void SetPolarization(G4ThreeVector polarization);
    G4ThreeVector GetPolarization() const;
    void SetDirection(G4ThreeVector direction);
    G4ThreeVector GetDirection() const;
    void SetPosition(G4ThreeVector position);
    G4ThreeVector GetPosition() const;
    void SetTime(G4double time);
    G4double GetTime() const;
    void SetWavelength(G4double wavelength);
    void SetPid(unsigned pid);
    unsigned GetPid() const;
    void SetId(unsigned id);
    unsigned GetId() const;

private:
    unsigned id;
    unsigned pid;
    G4double wavelength;
    G4double time;
    G4ThreeVector position;
    G4ThreeVector direction;
    G4ThreeVector polarization;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

using PhotonHitsCollection = G4THitsCollection<PhotonHit>;
extern G4ThreadLocal G4Allocator<PhotonHit>* PhotonHitAllocator;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* PhotonHit::operator new(size_t){
    if (!PhotonHitAllocator) {
        PhotonHitAllocator = new G4Allocator<PhotonHit>;
    }
    return (void *) PhotonHitAllocator->MallocSingle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void PhotonHit::operator delete(void *aHit) {
    PhotonHitAllocator->FreeSingle((PhotonHit*) aHit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
