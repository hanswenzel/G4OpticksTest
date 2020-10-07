#ifndef PhotonHit_h
#define PhotonHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
//#include "G4ThreeVector.hh"

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

    PhotonHit(float xp,
            float yp,
            float zp,
            float en,
            float ti);
    
    void SetTime(float t) {
        this->time = t;
    }

    float GetTime() const {
        return time;
    }

    void SetEnergy(float e) {
        this->energy = e;
    }

    float GetEnergy() const {
        return energy;
    }

    void SetZpos(float z) {
        this->zpos = z;
    }

    float GetZpos() const {
        return zpos;
    }

    void SetYpos(float y) {
        this->ypos = y;
    }

    float GetYpos() const {
        return ypos;
    }

    void SetXpos(float x) {
        this->xpos = x;
    }

    float GetXpos() const {
        return xpos;
    }

private:

    float xpos;
    float ypos;
    float zpos;
    float energy;
    float time;
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
