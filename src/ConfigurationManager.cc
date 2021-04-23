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
    HistoFileName = "histograms.root";
    doAnalysis = true; // by default do analysis
    FileName = "hits";    
    writeHits = true; // by default we write hits
#endif
#ifdef WITH_G4OPTICKS 
    enable_opticks = true; // by default we use opticks
    MaxPhotons = 1000000;
#endif 
    enable_verbose = false; // by default we run quiet 
}
ConfigurationManager* ConfigurationManager::getInstance() {
    if (instance == 0) instance = new ConfigurationManager;
    return instance;
}
#ifdef WITH_G4OPTICKS 
    void ConfigurationManager::setMaxPhotons(unsigned int MaxPhotons) {
        this->MaxPhotons = MaxPhotons;
    }

    unsigned int ConfigurationManager::getMaxPhotons() const {
        return MaxPhotons;
    }


 #endif  
    