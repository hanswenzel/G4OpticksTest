/* ------------------------------------------------------------------------
            |\___/|       
            )     (    
           =\     /=
             )===(
            /     \         CaTS: Calorimeter and Tracker Simulation
            |     |         Author: Hans Wenzel (Fermilab)
           /       \        Created on June 23, 2014, 11:21 AM
           \       /
            \__  _/
              ( (
               ) )
              (_(
-------------------------------------------------------------------------*/
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



#ifndef PARTICLECHANGE_HH
#define	PARTICLECHANGE_HH
#include "G4VParticleChange.hh"

class ParticleChange : public G4VParticleChange
{

   public:
   
      ParticleChange() : fIsFirstInter(false) {}
      ParticleChange( bool isFirst ) : fIsFirstInter( isFirst ) {}
      virtual ~ParticleChange() {}
      
      bool IsFisrtInteraction() const { return fIsFirstInter; }

   private:
   
      bool fIsFirstInter;

};


#endif	/* PARTICLECHANGE_HH */

