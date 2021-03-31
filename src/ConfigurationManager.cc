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
#include "G4SystemOfUnits.hh"
// project headers
#include "ConfigurationManager.hh"
#include "ConfigurationManagerMessenger.hh"

using namespace std;

ConfigurationManager* ConfigurationManager::instance = 0;

ConfigurationManager::ConfigurationManager() {
  confMessenger = new ConfigurationManagerMessenger(this);
  #ifdef WITH_ROOT
  FileName="hits.root";
  writeHits = true;       // by default we write hits
  #endif
  #ifdef WITH_G4OPTICKS 
  enable_opticks = true;  // by default we use opticks
  #endif 
  enable_verbose = false; // by default we run quiet 
  SDNames = new std::vector<G4String>();
/*
  ReferencePhysicsList="FTFP_BERT";
  EmOption="";
  enableOpticalConstructor=true;
  enableNeutronKiller=true;
  enableStepLimiter=true;
 */
}

ConfigurationManager* ConfigurationManager::getInstance() {
    if (instance == 0) instance = new ConfigurationManager;
    return instance;
}
