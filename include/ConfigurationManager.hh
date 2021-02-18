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
#ifdef WITH_ROOT 
    bool writeHits; // variable determines if hits are written out into Root File
    G4String FileName; // File name for root io
#endif
#ifdef WITH_G4OPTICKS  
    bool enable_opticks; // use opticks if available
#endif
    bool enable_verbose; // switch on/off diagnostic printouts
    G4String ReferencePhysicsList;
    G4String EmOption;
    bool enableOpticalConstructor;
    bool enableNeutronKiller;
    bool enableStepLimiter;
    std::vector<G4String> *SDNames;
    ConfigurationManagerMessenger* confMessenger;
public:
    ConfigurationManager();
    ~ConfigurationManager();
    static ConfigurationManager* getInstance();

    std::vector<G4String>* getSDNames() {
        return SDNames;
    }
#ifdef WITH_ROOT

    inline void setWriteHits(bool writeHits) {
        this->writeHits = writeHits;
    }

    inline bool isWriteHits() const {
        return writeHits;
    }

    inline void setFileName(G4String FileName) {
        this->FileName = FileName;
    }

    inline G4String getFileName() const {
        return FileName;
    }
#endif  

    inline void setEnable_verbose(bool enable_verbose) {
        this->enable_verbose = enable_verbose;
    };

    inline bool isEnable_verbose() const {
        return enable_verbose;
    };

    inline void setEnable_OpticalConstructor(bool enableOpticalConstructor) {
        this->enableOpticalConstructor = enableOpticalConstructor;
    };

    inline bool isEnable_OpticalConstructor() const {
        return enableOpticalConstructor;
    };

    inline void setEnable_NeutronKiller(bool enableNeutronKiller) {
        this->enableNeutronKiller = enableNeutronKiller;
    };

    inline bool isEnable_NeutronKiller() const {
        return enableNeutronKiller;
    };

    inline void setEnable_StepLimiter(bool enableStepLimiter) {
        this->enableStepLimiter = enableStepLimiter;
    };

    inline bool isEnable_StepLimiter() const {
        return enableStepLimiter;
    };

    inline void setReferencePhysicsList(G4String ReferencePhysicsList) {
        this->ReferencePhysicsList = ReferencePhysicsList;
    };

    inline G4String getReferencePhysicsList() const {
        return ReferencePhysicsList;
    };

    inline void setEmOption(G4String EmOption) {
        this->EmOption = EmOption;
    };

    inline G4String getEmOption() const {
        return EmOption;
    };
#ifdef WITH_G4OPTICKS 

    inline void setEnable_opticks(bool enable_opticks) {
        this->enable_opticks = enable_opticks;
    };

    inline bool isEnable_opticks() const {
        return enable_opticks;
    };
#endif
};
#endif /* /CONFIGURATIONMANAGER */

