#ifndef DRCalorimeterHit_h
#define DRCalorimeterHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DRCalorimeterHit : public G4VHit {
public:
    DRCalorimeterHit();
    ~DRCalorimeterHit();
    DRCalorimeterHit(const DRCalorimeterHit&);
    const DRCalorimeterHit& operator=(const DRCalorimeterHit&);
    G4bool operator==(const DRCalorimeterHit&) const;

    inline void* operator new(size_t);
    inline void operator delete(void*);

    virtual void Draw();
    virtual void Print();

    DRCalorimeterHit(unsigned int i,
            double e,
            double em,
            unsigned int nc,
            double t,
            G4ThreeVector p);

    inline void SetPosition(G4ThreeVector position) {
        this->position = position;
    };

    inline G4ThreeVector GetPosition() const {
        return position;
    };

    inline void SetTime(double time) {
        this->time = time;
    };

    inline double GetTime() const {
        return time;
    };

   inline  void SetId(unsigned int id) {
        this->id = id;
    };

  inline   unsigned int GetId() const {
        return id;
    };

   inline  void SetEdep(double Edep) {
        this->Edep = Edep;
    };

   inline  double GetEdep() const {
        return Edep;
    };


     void SetNceren(unsigned int Nceren);
     unsigned int GetNceren() const;
     void SetEm_Edep(double em_Edep);
     double GetEm_Edep() const;;

private:
    unsigned int id;
    double Edep;
    double em_Edep;
    unsigned int Nceren;
    double time;
    G4ThreeVector position;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

using DRCalorimeterHitsCollection = G4THitsCollection<DRCalorimeterHit>;
extern G4ThreadLocal G4Allocator<DRCalorimeterHit>* DRCalorimeterHitAllocator;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* DRCalorimeterHit::operator new(size_t){
    if (!DRCalorimeterHitAllocator) {
        DRCalorimeterHitAllocator = new G4Allocator<DRCalorimeterHit>;
    }
    return (void *) DRCalorimeterHitAllocator->MallocSingle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void DRCalorimeterHit::operator delete(void *aHit) {
    DRCalorimeterHitAllocator->FreeSingle((DRCalorimeterHit*) aHit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
