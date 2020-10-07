/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   lArTPCHit.hh
 * Author: wenzel
 *
 * Created on October 6, 2020, 2:54 PM
 */

#ifndef LARTPCHIT_HH
#define LARTPCHIT_HH

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/// Hit implementation for the persistency example

class lArTPCHit : public G4VHit {
public:

    lArTPCHit();
    ~lArTPCHit();
    lArTPCHit(G4double fe, G4double fx, G4double fy, G4double fz);
    lArTPCHit(const lArTPCHit&);
    const lArTPCHit& operator=(const lArTPCHit&);
    G4bool operator==(const lArTPCHit&) const;

    inline void* operator new(size_t);
    inline void operator delete(void*);

    virtual void Draw();
    virtual void Print();

public:

    void SetElectrons(G4double de) {
        fElectrons = de;
    };

    void SetPosX(G4double x) {
        fPosX = x;
    };

    void SetPosY(G4double y) {
        fPosY = y;
    };

    void SetPosZ(G4double z) {
        fPosZ = z;
    };

    G4double GetEdep() {
        return fElectrons;
    };

    G4double GetPosX() {
        return fPosX;
    };

    G4double GetPosY() {
        return fPosY;
    };

    G4double GetPosZ() {
        return fPosZ;
    };
private:

    G4double fElectrons;
    G4double fPosX;
    G4double fPosY;
    G4double fPosZ;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

using lArTPCHitsCollection = G4THitsCollection<lArTPCHit>;

extern G4ThreadLocal G4Allocator<lArTPCHit>* lArTPCHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* lArTPCHit::operator new(size_t){
    if (!lArTPCHitAllocator) {
        lArTPCHitAllocator = new G4Allocator<lArTPCHit>;
    }
    return (void *) lArTPCHitAllocator->MallocSingle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void lArTPCHit::operator delete(void *aHit) {
    lArTPCHitAllocator->FreeSingle((lArTPCHit*) aHit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


#endif /* LARTPCHIT_HH */

