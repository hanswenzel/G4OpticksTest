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
#ifndef ConfigurationManager_h
#define ConfigurationManager_h 1
#include <vector>
#include "G4String.hh"
class ConfigurationManagerMessenger;

class ConfigurationManager {
private:

    static ConfigurationManager* instance;
    bool writeHits; // variable determines if hits are written out into Root File
    bool enable_opticks; // use opticks if available 
    bool enable_verbose; // switch on/off diagnostic printouts
    G4String FileName;   // File name for root io
    std::vector<G4String> *SDNames;
    ConfigurationManagerMessenger* confMessenger;

public:
    ConfigurationManager();
    ~ConfigurationManager();
    static ConfigurationManager* getInstance();
    std::vector<G4String>* getSDNames() {
        return SDNames;
    }
    void setFileName(G4String FileName);
    G4String getFileName() const;
    void setEnable_verbose(bool enable_verbose);
    bool isEnable_verbose() const;
    void setEnable_opticks(bool enable_opticks);
    bool isEnable_opticks() const;
    void setWriteHits(bool writeHits);
    bool isWriteHits() const;

};

#endif /* /CONFIGURATIONMANAGER */

