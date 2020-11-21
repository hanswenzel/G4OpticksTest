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
    writeHits = true; // by default we write hits
    SDNames = new std::vector<G4String>();
}

void ConfigurationManager::setFileName(G4String FileName) {
    this->FileName = FileName;
}

G4String ConfigurationManager::getFileName() const {
    return FileName;
}

void ConfigurationManager::setEnable_verbose(bool enable_verbose) {
    this->enable_verbose = enable_verbose;
}

bool ConfigurationManager::isEnable_verbose() const {
    return enable_verbose;
}

void ConfigurationManager::setEnable_opticks(bool enable_opticks) {
    this->enable_opticks = enable_opticks;
}

bool ConfigurationManager::isEnable_opticks() const {
    return enable_opticks;
}

void ConfigurationManager::setWriteHits(bool writeHits) {
    this->writeHits = writeHits;
}

bool ConfigurationManager::isWriteHits() const {
    return writeHits;
}



ConfigurationManager* ConfigurationManager::getInstance() {
    if (instance == 0) instance = new ConfigurationManager;
    return instance;
}
