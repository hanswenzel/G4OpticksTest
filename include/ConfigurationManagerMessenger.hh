// -----------------------------------------------------
//  _    _        _____         _   
// | |  / \   _ _|_   _|__  ___| |_ 
// | | / _ \ | '__|| |/ _ \/ __| __|
// | |/ ___ \| |   | |  __/\__ \ |_ 
// |_/_/   \_\_|   |_|\___||___/\__|
//                                  
// lArTest: A Geant4 application to study and profile  
//          simulation of physics processes relevant 
//          to liquid Ar TPCs
//
// Author: Hans Wenzel, Fermilab
// -----------------------------------------------------


#ifndef ConfigurationManagerMessenger_h
#define ConfigurationManagerMessenger_h 1

#include "G4UImessenger.hh"

class ConfigurationManager;
class G4UIdirectory;
class G4UIcmdWithABool;
class G4UIcmdWithADoubleAndUnit;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class ConfigurationManagerMessenger : public G4UImessenger {
public:

    ConfigurationManagerMessenger(ConfigurationManager*);
    virtual ~ConfigurationManagerMessenger();

    void SetNewValue(G4UIcommand*, G4String);

private:

    ConfigurationManager* mgr;

    G4UIdirectory* testDir;
    G4UIcmdWithABool* writeHitsCmd;
    G4UIcmdWithABool* anaCmd;
    G4UIcmdWithABool* steplimitCmd;
    G4UIcmdWithABool* debugEventCmd;
    G4UIcmdWithABool* profileCmd;
    G4UIcmdWithADoubleAndUnit* slengthCmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

