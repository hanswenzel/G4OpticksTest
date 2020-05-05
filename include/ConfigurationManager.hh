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
#include <map>
#include "G4String.hh"
class ConfigurationManagerMessenger;

class ConfigurationManager {
private:

    static ConfigurationManager* instance;
    bool writeHits; // variable determines if hits are written
    //bool stepLimit;  // variable determines if step limits are applied
    bool doAnalysis; // variable determines if analysis is done and root file written out
    bool debugEvent; // variable determines if debugging is done
    bool doProfile; // variable determines if computing profiling is done
    std::vector<G4String> *SDNames;
    std::map<G4String, G4int> *mapOfntIDs;
    //double limitval; // value of the step limit in mm
    ConfigurationManagerMessenger* confMessenger;

public:
    ConfigurationManager();
    ~ConfigurationManager();
    static ConfigurationManager* getInstance();
    /*
        bool GetstepLimit() {
            return stepLimit;
        }
     */

    /*
    void SetstepLimit(bool value) {
        stepLimit = value;
    }
     */
    void SetwriteHits(bool value) {
        writeHits = value;
    }

    bool GetwriteHits() {
        return writeHits;
    }

    bool GetdoAnalysis() {
        return doAnalysis;
    }

    void SetdoAnalysis(bool value) {
        doAnalysis = value;
    }

    bool GetdebugEvent() {
        return debugEvent;
    }

    void SetdebugEvent(bool value) {
        debugEvent = value;
    }

    bool GetdoProfile() {
        return doProfile;
    }

    void SetdoProfile(bool value) {
        doProfile = value;
    }

    std::vector<G4String>* getSDNames() {
        return SDNames;
    }

    std::map<G4String, int>* getMapOfntIDs() {
        return mapOfntIDs;
    }


    /*
        double Getlimitval() {
            return limitval;
        }

        void Setlimitval(double value) {
            limitval = value;
        }
     */
};

#endif /* /CONFIGURATIONMANAGER */

