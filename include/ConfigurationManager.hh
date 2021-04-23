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
    bool doAnalysis; // variable determines if we are doing analysis
    G4String HistoFileName; // File name for histos and  ntuples
    bool writeHits; // variable determines if hits are written out into Root File
    G4String FileName; // File name for root io
    G4String fname; // full File name for root io
#endif
#ifdef WITH_G4OPTICKS  
    bool enable_opticks; // use opticks if available
    unsigned int MaxPhotons;
#endif
    bool enable_verbose; // switch on/off diagnostic printouts
    ConfigurationManagerMessenger* confMessenger;
    ConfigurationManager();
public:

    ~ConfigurationManager();
    static ConfigurationManager* getInstance();

#ifdef WITH_ROOT

    inline void setHistoFileName(G4String HistoFileName) {
        this->HistoFileName = HistoFileName;
    }

    inline G4String getHistoFileName() const {
        return HistoFileName;
    }

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

    inline void setfname(G4String fname) {
        this->fname = fname;
    }

    inline G4String getfname() const {
        return fname;
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
    void setMaxPhotons(unsigned int MaxPhotons);
    unsigned int getMaxPhotons() const;
#endif
};
#endif /* /CONFIGURATIONMANAGER */

