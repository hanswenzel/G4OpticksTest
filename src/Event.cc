
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
-------------------------------------------------------------------------*/
#include "Event.hh"
//Event* Event::instance = 0;
void Event::Reset() {
      std::map<G4String, std::vector<G4VHit*>>::iterator it; 
       for (it = hcmap.begin(); it != hcmap.end(); it++)
       {
            (it->second).clear();
       }
}

//Event* Event::getInstance() {
//    if (instance == 0) instance = new Event;
//    return instance;
//}