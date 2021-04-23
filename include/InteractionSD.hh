/* ------------------------------------------------------------------------
            |\___/|       
            )     (    
           =\     /=
             )===(
            /     \         CaTS: Calorimeter and Tracker Simulation
            |     |         Author: Hans Wenzel (Fermilab)
           /       \        Created on June 23, 2014
           \       /
            \__  _/
              ( (
               ) )
              (_(
-------------------------------------------------------------------------*/
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef INTERACTIONSD_HH
#define	INTERACTIONSD_HH

#include "G4VSensitiveDetector.hh"
#include "ParticleChange.hh"
#include "InteractionHit.hh"

class G4Step;
class G4HCofThisEvent;


class InteractionSD : public G4VSensitiveDetector {
public:
    InteractionSD(G4String);
    ~InteractionSD();

    void Initialize(G4HCofThisEvent*);
    G4bool ProcessHits(G4Step*, G4TouchableHistory*);

private:
    InteractionHitsCollection* interactionCollection;
    G4int HCID;
    ParticleChange* fFirstInter;
    ParticleChange* fOtherInter;

};


#endif	/* INTERACTIONSD_HH */

