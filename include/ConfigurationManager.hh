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
    bool doAnalysis; // variable determines if we are doing analysis
    G4String HistoFileName; // File name for histos and  ntuples
#ifdef WITH_ROOT 
    bool writeHits; // variable determines if hits are written out into Root File
    G4String FileName; // File name for root io
#endif
#ifdef WITH_G4OPTICKS  
    bool enable_opticks; // use opticks if available
#endif
    bool enable_verbose; // switch on/off diagnostic printouts
    std::vector<G4String> *SDNames;
    ConfigurationManagerMessenger* confMessenger;
public:
    ConfigurationManager();
    ~ConfigurationManager();
    static ConfigurationManager* getInstance();

    std::vector<G4String>* getSDNames() {
        return SDNames;
    }

    inline void setHistoFileName(G4String HistoFileName) {
        this->HistoFileName = HistoFileName;
    }

    inline G4String getHistoFileName() const {
        return HistoFileName;
    }
#ifdef WITH_ROOT

    inline void setWriteHits(bool writeHits) {
        this->writeHits = writeHits;
    }

    inline bool isWriteHits() const {
        return writeHits;
    }

    inline void setdoAnalysis(bool writeHits) {
        this->doAnalysis = doAnalysis;
    }

    inline bool isdoAnalysis() const {
        return doAnalysis;
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

