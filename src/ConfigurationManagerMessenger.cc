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
    testDir = new G4UIdirectory("/G4OpticksTest/");
    testDir->SetGuidance("Configuring G4OpticksTest");
#ifdef WITH_ROOT
    //
    FileNameCmd = new G4UIcmdWithAString("/G4OpticksTest/FileName", this);
    FileNameCmd->SetGuidance("Enter file name for Hits collections ");
    FileNameCmd->SetParameterName("FileName", true);
    FileNameCmd->SetDefaultValue("hist.root");
    FileNameCmd->AvailableForStates(G4State_Idle);
    //
    writeHitsCmd = new G4UIcmdWithABool("/G4OpticksTest/writeHits", this);
    writeHitsCmd->SetGuidance("Set flag for writing hits");
    writeHitsCmd->SetParameterName("writeHits", true);
    writeHitsCmd->SetDefaultValue(true);
    writeHitsCmd->AvailableForStates(G4State_Idle);
        //
    HistoFileNameCmd = new G4UIcmdWithAString("/G4OpticksTest/FileName", this);
    HistoFileNameCmd->SetGuidance("Enter file name for Hits collections ");
    HistoFileNameCmd->SetParameterName("FileName", true);
    HistoFileNameCmd->SetDefaultValue("hist.root");
    HistoFileNameCmd->AvailableForStates(G4State_Idle);
    //
    doAnalysisCmd = new G4UIcmdWithABool("/G4OpticksTest/doAnalysis", this);
    doAnalysisCmd->SetGuidance("Set flag for writing hits");
    doAnalysisCmd->SetParameterName("doAnalysis", true);
    doAnalysisCmd->SetDefaultValue(true);
    doAnalysisCmd->AvailableForStates(G4State_Idle);
#endif   

#ifdef WITH_G4OPTICKS
    //
    enable_opticksCmd = new G4UIcmdWithABool("/G4OpticksTest/enable_opticks", this);
    enable_opticksCmd->SetGuidance("Set flag for enabling opticks");
    enable_opticksCmd->SetParameterName("enable_opticks", true);
    enable_opticksCmd->SetDefaultValue(true);
    enable_opticksCmd->AvailableForStates(G4State_Idle);
#endif
    //
    enable_verboseCmd = new G4UIcmdWithABool("/G4OpticksTest/enable_verbose", this);
    enable_verboseCmd->SetGuidance("Set flag for enabling verbose diagnostic printout");
    enable_verboseCmd->SetParameterName("enable_verbose", false);
    enable_verboseCmd->SetDefaultValue(false);
    enable_verboseCmd->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle);
/*
    ReferencePhysicsListCmd = new G4UIcmdWithAString("/G4OpticksTest/ReferencePhysicsList", this);
    ReferencePhysicsListCmd->SetGuidance("Enter name of Reference Physics List");
    ReferencePhysicsListCmd->SetParameterName("ReferencePhysicsList", true);
    ReferencePhysicsListCmd->SetDefaultValue("FTFP_BERT");
    ReferencePhysicsListCmd->AvailableForStates(G4State_Idle);

    EmOptionCmd = new G4UIcmdWithAString("/G4OpticksTest/EmOption", this);
    EmOptionCmd->SetGuidance("Enter name of em option");
    EmOptionCmd->SetParameterName("EmOption", true);
    EmOptionCmd->SetDefaultValue("");
    EmOptionCmd->AvailableForStates(G4State_Idle);
    
    enableOpticalConstructorCmd = new G4UIcmdWithABool("/G4OpticksTest/enableOpticalConstructor", this);
    enableOpticalConstructorCmd->SetGuidance("Set flag for enabling optical constructor");
    enableOpticalConstructorCmd->SetParameterName("enableOpticalConstructor", true);
    enableOpticalConstructorCmd->SetDefaultValue(true);
    enableOpticalConstructorCmd->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle);
    
    enableNeutronKillerCmd = new G4UIcmdWithABool("/G4OpticksTest/enableNeutronKiller", this);
    enableNeutronKillerCmd->SetGuidance("Set flag for enabling verbose diagnostic printout");
    enableNeutronKillerCmd->SetParameterName("enableNeutronKiller", true);
    enableNeutronKillerCmd->SetDefaultValue(true);
    enableNeutronKillerCmd->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle);
    
    enableStepLimiterCmd = new G4UIcmdWithABool("/G4OpticksTest/enableStepLimiter", this);
    enableStepLimiterCmd->SetGuidance("Set flag for enabling verbose diagnostic printout");
    enableStepLimiterCmd->SetParameterName("enableStepLimiter", true);
    enableStepLimiterCmd->SetDefaultValue(true);
    enableStepLimiterCmd->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle);
*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ConfigurationManagerMessenger::~ConfigurationManagerMessenger() {
    delete testDir;
#ifdef WITH_ROOT
    delete writeHitsCmd;
    delete doAnalysisCmd;
    delete FileNameCmd;
    delete HistoFileNameCmd;
    
#endif
#ifdef WITH_G4OPTICKS
    delete enable_opticksCmd;
#endif
    delete enable_verboseCmd;
    /*
    delete ReferencePhysicsListCmd;
    delete EmOptionCmd;
    delete enableOpticalConstructorCmd;
    delete enableNeutronKillerCmd;
    delete enableStepLimiterCmd;
     */
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ConfigurationManagerMessenger::SetNewValue(G4UIcommand* command, G4String newValue) {
#ifdef WITH_ROOT
    if (command == writeHitsCmd) mgr->setWriteHits(writeHitsCmd->GetNewBoolValue(newValue));
    if (command == FileNameCmd) mgr->setFileName(newValue);
    if (command == doAnalysisCmd) mgr->setWriteHits(doAnalysisCmd->GetNewBoolValue(newValue));
    if (command == HistoFileNameCmd) mgr->setFileName(newValue);
#endif
#ifdef WITH_G4OPTICKS
    if (command == enable_opticksCmd) mgr->setEnable_opticks(enable_opticksCmd->GetNewBoolValue(newValue));
#endif
    if (command == enable_verboseCmd) mgr->setEnable_verbose(enable_verboseCmd->GetNewBoolValue(newValue));
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

