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
class G4UIcmdWithAString;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class ConfigurationManagerMessenger : public G4UImessenger {
public:
    ConfigurationManagerMessenger(ConfigurationManager*);
    virtual ~ConfigurationManagerMessenger();
    void SetNewValue(G4UIcommand*, G4String);
private:
    ConfigurationManager* mgr;
    G4UIdirectory* testDir;
#ifdef WITH_ROOT
    G4UIcmdWithABool* writeHitsCmd;
    G4UIcmdWithABool* doAnalysisCmd; 
    G4UIcmdWithAString* FileNameCmd;
    G4UIcmdWithAString* HistoFileNameCmd;
#endif
#ifdef WITH_G4OPTICKS
    G4UIcmdWithABool* enable_opticksCmd;
#endif  
    G4UIcmdWithABool* enable_verboseCmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif

