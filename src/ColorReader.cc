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

#include "ColorReader.hh"

#include "G4LogicalVolume.hh"
#include "G4VisAttributes.hh"
//#define VERBOSE 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ColorReader::ColorReader()
: G4GDMLReadStructure() {
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ColorReader::~ColorReader() {
    std::map<G4String, G4VisAttributes*>::iterator pos;
    for (pos = fAttribs.begin(); pos != fAttribs.end(); pos++) {
        delete pos->second;
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ColorReader::ExtensionRead(const xercesc::DOMElement * const extElement) {
#ifdef VERBOSE
    G4cout << " ColorReaderReading GDML extension..." << G4endl;
    G4cout << "ColorReader: Reading new GDML extension..." << G4endl;
#endif
    for (xercesc::DOMNode* iter = extElement->getFirstChild();
            iter != 0; iter = iter->getNextSibling()) {
        if (iter->getNodeType() != xercesc::DOMNode::ELEMENT_NODE) {
            continue;
        }

        const xercesc::DOMElement * const child
                = dynamic_cast<xercesc::DOMElement*> (iter);
        const G4String tag = Transcode(child->getTagName());
#ifdef VERBOSE
        G4cout << "G4GDML:" << tag << G4endl;
#endif
        if (tag == "color") {
            ColorRead(child);
        } else {
            G4String error_msg = "Unknown tag in structure: " + tag;
            G4Exception("ColorReader::ExtensionRead()",
                    "ReadError", FatalException, error_msg);
        }
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ColorReader::VolumeRead(const xercesc::DOMElement * const volumeElement) {
#ifdef VERBOSE    
    G4cout << "G4GDML: VolumeRead" << G4endl;
#endif    
    G4VSolid* solidPtr = 0;
    G4Material* materialPtr = 0;
    G4VisAttributes* attrPtr = 0;
    G4GDMLAuxListType auxList;

    XMLCh *name_attr = xercesc::XMLString::transcode("name");
    const G4String name = Transcode(volumeElement->getAttribute(name_attr));
    xercesc::XMLString::release(&name_attr);

    for (xercesc::DOMNode* iter = volumeElement->getFirstChild();
            iter != 0; iter = iter->getNextSibling()) {
        if (iter->getNodeType() != xercesc::DOMNode::ELEMENT_NODE) {
            continue;
        }

        const xercesc::DOMElement * const child
                = dynamic_cast<xercesc::DOMElement*> (iter);
        const G4String tag = Transcode(child->getTagName());

        if (tag == "auxiliary") {
            auxList.push_back(AuxiliaryRead(child));
        } else
            if (tag == "materialref") {
            materialPtr = GetMaterial(GenerateName(RefRead(child), true));
        } else
            if (tag == "solidref") {
            solidPtr = GetSolid(GenerateName(RefRead(child)));
        } else
            if (tag == "colorref") {
#ifdef VERBOSE      
            G4cout << "G4GDML: found visual attribute ..." << G4endl;
#endif 
            attrPtr = GetVisAttribute(GenerateName(RefRead(child)));
        }
    }

    pMotherLogical = new G4LogicalVolume(solidPtr, materialPtr,
            GenerateName(name), 0, 0, 0);
#ifdef VERBOSE    
    G4cout << "G4GDML: attaching visual attribute ..." << G4endl;
#endif   
    pMotherLogical->SetVisAttributes(attrPtr);

    if (!auxList.empty()) {
        auxMap[pMotherLogical] = auxList;
    }

    Volume_contentRead(volumeElement);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ColorReader::ColorRead(const xercesc::DOMElement * const colorElement) {
#ifdef VERBOSE
    G4cout << "G4GDML: ColorRead" << G4endl;
#endif 
    G4String name;
    G4VisAttributes* color = 0;
    G4double r = 0., g = 0., b = 0., a = 0.;

    const xercesc::DOMNamedNodeMap * const attributes
            = colorElement->getAttributes();
    XMLSize_t attributeCount = attributes->getLength();

    for (XMLSize_t attribute_index = 0;
            attribute_index < attributeCount; attribute_index++) {
        xercesc::DOMNode* attribute_node = attributes->item(attribute_index);

        if (attribute_node->getNodeType() != xercesc::DOMNode::ATTRIBUTE_NODE) {
            continue;
        }

        const xercesc::DOMAttr * const attribute
                = dynamic_cast<xercesc::DOMAttr*> (attribute_node);
        const G4String attName = Transcode(attribute->getName());
        const G4String attValue = Transcode(attribute->getValue());

        if (attName == "name") {
            name = GenerateName(attValue);
        } else
            if (attName == "R") {
            r = eval.Evaluate(attValue);
        } else
            if (attName == "G") {
            g = eval.Evaluate(attValue);
        } else
            if (attName == "B") {
            b = eval.Evaluate(attValue);
        } else
            if (attName == "A") {
            a = eval.Evaluate(attValue);
        }
    }
#ifdef VERBOSE
    G4cout << "Color attribute (R,G,B,A) is: "
            << r << ", " << g << ", " << b << ", " << a << " !" << G4endl;
#endif 
    color = new G4VisAttributes(G4Color(r, g, b, a));
    fAttribs.insert(std::make_pair(name, color));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VisAttributes* ColorReader::GetVisAttribute(const G4String& ref) {
#ifdef VERBOSE
    G4cout << "G4GDML: GetVisAttribute" << G4endl;
#endif 
    G4VisAttributes* col = 0;
    std::map<G4String, G4VisAttributes*>::iterator pos = fAttribs.find(ref);

    if (pos != fAttribs.end()) {
        col = pos->second;
    } else {
        G4String err_mess = "Attribute: " + ref + " NOT found !";
        G4Exception("ColorReader::GetVisAttribute()",
                "ReadError", FatalException, err_mess);
    }
    return col;
}
