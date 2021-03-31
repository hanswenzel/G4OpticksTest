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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "StackingActionMessenger.hh"
#include "StackingAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithoutParameter.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

StackingActionMessenger::StackingActionMessenger(
        StackingAction* CaTSAction)
: CaTSAction(CaTSAction) {
    StackingActionDir = new G4UIdirectory("/CaTS/StackingAction/");
    StackingActionDir->SetGuidance("CaTS StackingAction control commands.");

    killPi0Cmd = new G4UIcmdWithABool("/CaTS/StackingAction/killPi0", this);
    killPi0Cmd->SetGuidance("true for killing Pi0 at creation");
    killPi0Cmd->SetGuidance("Default is false");
    killPi0Cmd->SetParameterName("killPi0", false);
    killPi0Cmd->SetDefaultValue(false);
    killPi0Cmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    killetaCmd = new G4UIcmdWithABool("/CaTS/StackingAction/killeta", this);
    killetaCmd->SetGuidance("true for killing eta at creation");
    killetaCmd->SetGuidance("Default is false");
    killetaCmd->SetParameterName("killeta", false);
    killetaCmd->SetDefaultValue(false);
    killetaCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    killGammafromnCaptureCmd = new G4UIcmdWithABool("/CaTS/StackingAction/killGammafromnCapture", this);
    killGammafromnCaptureCmd->SetGuidance("true for killing gammas from nCapture at creation");
    killGammafromnCaptureCmd->SetGuidance("Default is false");
    killGammafromnCaptureCmd->SetParameterName("killGammafromnCapture", false);
    killGammafromnCaptureCmd->SetDefaultValue(false);
    killGammafromnCaptureCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    listCmd = new G4UIcmdWithoutParameter("/CaTS/StackingAction/List", this);
    listCmd->SetGuidance("List the status of control flags of the StackingAction.");

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

StackingActionMessenger::~StackingActionMessenger() {
    delete killPi0Cmd;
    delete killetaCmd;
    delete killGammafromnCaptureCmd;
    delete StackingActionDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void StackingActionMessenger::SetNewValue(G4UIcommand* command, G4String newValues) {
    if (command == killPi0Cmd) {
        CaTSAction->SetkillPi0(killPi0Cmd->GetNewBoolValue(newValues));
    } else if (command == killetaCmd) {
        CaTSAction->Setkilleta(killetaCmd->GetNewBoolValue(newValues));
    } else if (command == killGammafromnCaptureCmd) {
        CaTSAction->SetkillGammafromnCapture(killGammafromnCaptureCmd->GetNewBoolValue(newValues));
    } else if (command == listCmd) {
        CaTSAction->Print();
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

