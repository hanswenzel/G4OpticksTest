/* ------------------------------------------------------------------------
            |\___/|       
            )     (    
           =\     /=
             )===(
            /     \         CaTS: Calorimeter and Tracker Simulation
            |     |         Author: Hans Wenzel (Fermilab)
           /       \
           \       /
            \__  _/
              ( (
               ) )
              (_(
 Created on May 2, 2012, 8:44 AM
-------------------------------------------------------------------------*/
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef Event_HH
#define Event_HH
#include <vector>
#include <map>

#include "G4Types.hh"
#include "G4VHit.hh"

class Event {
private:

    G4int fEvtNum;
    // Hit Map:
    std::map<G4String, std::vector<G4VHit*> > hcmap; // map of Hit Collections
  //  static Event* instance;
public:

    Event() : fEvtNum(0) {
    }
  //  static Event* getInstance();

    virtual ~Event() {
    }

    void SetEventNr(G4int i) {
        fEvtNum = i;
    }

    G4int GetEventNumber() const {
        return fEvtNum;
    }


    std::map<G4String, std::vector<G4VHit*> >* GetHCMap() {
        return &hcmap;
    }
    void Reset();
};
#endif /* Event_HH */

