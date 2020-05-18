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
#ifndef ColorReader_H
#define ColorReader_H 1

#include <map>
#include "G4GDMLReadStructure.hh"

class G4VisAttributes;

/// GDML reader for the color attributes

class ColorReader : public G4GDMLReadStructure {
public:

    ColorReader();
    ~ColorReader();

    void ExtensionRead(const xercesc::DOMElement * const element);
    void ColorRead(const xercesc::DOMElement * const element);

    G4VisAttributes* GetVisAttribute(const G4String& ref);

protected:

    virtual void VolumeRead(const xercesc::DOMElement * const);

private:

    std::map<G4String, G4VisAttributes*> fAttribs;
};

#endif
