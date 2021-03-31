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
#ifndef StackingActionMessenger_h
#define StackingActionMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class StackingAction;
class G4UIdirectory;
class G4UIcmdWithABool;
class G4UIcmdWithoutParameter;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class StackingActionMessenger : public G4UImessenger {
public:
    StackingActionMessenger(StackingAction*);
    ~StackingActionMessenger();

    void SetNewValue(G4UIcommand*, G4String);

private:
    StackingAction* CaTSAction;
    G4UIdirectory* StackingActionDir;
    G4UIcmdWithABool* killPi0Cmd;
    G4UIcmdWithABool* killetaCmd;
    G4UIcmdWithABool* killGammafromnCaptureCmd;
    G4UIcmdWithoutParameter* listCmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

