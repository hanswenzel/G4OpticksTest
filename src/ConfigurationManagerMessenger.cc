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
// Geant4 headers
#include "G4UIdirectory.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAString.hh"
// project headers
#include "ConfigurationManagerMessenger.hh"
#include "ConfigurationManager.hh"
using namespace std;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ConfigurationManagerMessenger::ConfigurationManagerMessenger(ConfigurationManager * mgr1)
: mgr(mgr1) {
    testDir = new G4UIdirectory("/testConfig/");
    testDir->SetGuidance("Examining stepping in geant 4.");
    //
    writeHitsCmd = new G4UIcmdWithABool("/testConfig/writeHits", this);
    writeHitsCmd->SetGuidance("Set flag for writing hits");
    writeHitsCmd->SetParameterName("writeHits", true);
    writeHitsCmd->SetDefaultValue(true);
    writeHitsCmd->AvailableForStates(G4State_Idle);
    //    
    enable_opticksCmd = new G4UIcmdWithABool("/testConfig/enable_opticks", this);
    enable_opticksCmd->SetGuidance("Set flag for enabling opticks");
    enable_opticksCmd->SetParameterName("enable_opticks", true);
    enable_opticksCmd->SetDefaultValue(true);
    enable_opticksCmd->AvailableForStates(G4State_Idle);
    //
    enable_verboseCmd = new G4UIcmdWithABool("/testConfig/enable_verbose", this);
    enable_verboseCmd->SetGuidance("Set flag for enabling verbose diagnostic printout");
    enable_verboseCmd->SetParameterName("enable_verbose", true);
    enable_verboseCmd->SetDefaultValue(true);
    enable_verboseCmd->AvailableForStates(G4State_PreInit,G4State_Init,G4State_Idle);
    //
    FileNameCmd = new G4UIcmdWithAString("/testConfig/FileName", this);
    FileNameCmd->SetGuidance("Enter file name for Hits collections ");
    FileNameCmd->SetParameterName("FileName", true);
    FileNameCmd->SetDefaultValue("hist.root");
    FileNameCmd->AvailableForStates(G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ConfigurationManagerMessenger::~ConfigurationManagerMessenger() {
    delete testDir;
    delete writeHitsCmd;
    delete enable_opticksCmd;
    delete enable_verboseCmd;
    delete FileNameCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ConfigurationManagerMessenger::SetNewValue(G4UIcommand* command, G4String newValue) {
    if (command == writeHitsCmd) mgr->setWriteHits(writeHitsCmd->GetNewBoolValue(newValue));
    if (command == enable_opticksCmd) mgr->setEnable_opticks(enable_opticksCmd->GetNewBoolValue(newValue));
    if (command == enable_verboseCmd) mgr->setEnable_verbose(enable_verboseCmd->GetNewBoolValue(newValue));
    if (command == FileNameCmd) mgr->setFileName(newValue);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

