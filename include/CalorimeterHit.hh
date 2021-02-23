#ifndef CalorimeterHit_h
#define CalorimeterHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class CalorimeterHit : public G4VHit {
public:
    CalorimeterHit();
    ~CalorimeterHit();
    CalorimeterHit(const CalorimeterHit&);
    const CalorimeterHit& operator=(const CalorimeterHit&);
    G4bool operator==(const CalorimeterHit&) const;

    inline void* operator new(size_t);
    inline void operator delete(void*);

    virtual void Draw();
    virtual void Print();

    CalorimeterHit(unsigned int i,
            double e,
            double em,
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

   inline  void Setem_Edep(double em_Edep) {
        this->em_Edep = em_Edep;
    };

     double Getem_Edep() const {
        return em_Edep;
    };

private:
    unsigned int id;
    double Edep;
    double em_Edep;
    double time;
    G4ThreeVector position;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

using CalorimeterHitsCollection = G4THitsCollection<CalorimeterHit>;
extern G4ThreadLocal G4Allocator<CalorimeterHit>* CalorimeterHitAllocator;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* CalorimeterHit::operator new(size_t){
    if (!CalorimeterHitAllocator) {
        CalorimeterHitAllocator = new G4Allocator<CalorimeterHit>;
    }
    return (void *) CalorimeterHitAllocator->MallocSingle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void CalorimeterHit::operator delete(void *aHit) {
    CalorimeterHitAllocator->FreeSingle((CalorimeterHit*) aHit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
