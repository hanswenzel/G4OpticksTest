// Geant4 headers
#include "G4RunManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4StepLimiter.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4UserLimits.hh"
#include "G4UnitsTable.hh"
#include "G4ios.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4SDManager.hh"
#include "globals.hh"
#include "G4ElectricField.hh"
#include "G4UniformElectricField.hh"
#include "G4FieldManager.hh"
#include "G4EqMagElectricField.hh"
#include "ColorReader.hh"
#include "G4GDMLParser.hh"
// project headers
#include "ConfigurationManager.hh"
#include "DetectorConstruction.hh"
#include "TrackerSD.hh"
#include "lArTPCSD.hh"
#include "CalorimeterSD.hh"
#include "DRCalorimeterSD.hh"
#include "RadiatorSD.hh"
#include "PhotonSD.hh"
#include "InteractionSD.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
using namespace std;

DetectorConstruction::DetectorConstruction(G4String fname) {
    gdmlFile = fname;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction() {
}

G4VPhysicalVolume* DetectorConstruction::Construct() {
    verbose = ConfigurationManager::getInstance()->isEnable_verbose();
    ReadGDML();
    const G4GDMLAuxMapType* auxmap = parser->GetAuxMap();
    if (verbose) {
        std::cout << "Found " << auxmap->size()
                << " volume(s) with auxiliary information."
                << std::endl << std::endl;
    }
    for (G4GDMLAuxMapType::const_iterator iter = auxmap->begin();
            iter != auxmap->end(); iter++) {
        if (verbose) {
            std::cout << "Volume " << ((*iter).first)->GetName()
                    << " has the following list of auxiliary information: "
                    << std::endl;
        }
        for (G4GDMLAuxListType::const_iterator vit = (*iter).second.begin();
                vit != (*iter).second.end(); vit++) {
            if (verbose) {
                std::cout << "--> Type: " << (*vit).type
                        << " Value: " << (*vit).value << std::endl;
            }
            if ((*vit).type == "StepLimit") {
                G4UserLimits *fStepLimit = new G4UserLimits(atof((*vit).value));
                ((*iter).first)->SetUserLimits(fStepLimit);
            }
        }
    }
    G4VPhysicalVolume* worldPhysVol = parser->GetWorldVolume();
    return worldPhysVol;
}

void DetectorConstruction::ConstructSDandField() {
    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    const G4GDMLAuxMapType* auxmap = parser->GetAuxMap();
    if (verbose) {
        std::cout << "Found " << auxmap->size()
                << " volume(s) with auxiliary information."
                << std::endl << std::endl;
    }
    for (G4GDMLAuxMapType::const_iterator iter = auxmap->begin();
            iter != auxmap->end(); iter++) {
        if (verbose) {
            std::cout << "Volume " << ((*iter).first)->GetName()
                    << " has the following list of auxiliary information: "
                    << std::endl;
        }
        for (G4GDMLAuxListType::const_iterator vit = (*iter).second.begin();
                vit != (*iter).second.end(); vit++) {
            if (verbose) {
                std::cout << "--> Type: " << (*vit).type
                        << " Value: " << (*vit).value << std::endl;
            }
            if ((*vit).type == "SensDet") {
                if (verbose) {
                    std::cout << "Found sensitive Detector: " << (*vit).value << std::endl;
                }
                if ((*vit).value == "PhotonDetector") {
                    G4String name = ((*iter).first)->GetName() + "_Photondetector";
                    PhotonSD* aPhotonSD = new PhotonSD(name);
                    SDman->AddNewDetector(aPhotonSD);
                    ((*iter).first)->SetSensitiveDetector(aPhotonSD);
                    if (verbose) {
                        std::cout << "Attaching sensitive Detector: " << (*vit).value
                                << " to Volume:  " << ((*iter).first)->GetName() << std::endl;
                    }
                } else if ((*vit).value == "Target") {
                    G4String name = ((*iter).first)->GetName() + "_Target";
                    InteractionSD* aInteractionSD = new InteractionSD(name);
                    SDman->AddNewDetector(aInteractionSD);
                    ((*iter).first)->SetSensitiveDetector(aInteractionSD);
                    if (verbose) {
                        std::cout << "Attaching sensitive Detector: " << (*vit).value
                                << " to Volume:  " << ((*iter).first)->GetName() << std::endl;
                    }
                } else if ((*vit).value == "Tracker") {
                    G4String name = ((*iter).first)->GetName() + "_Tracker";
                    TrackerSD* aTrackerSD = new TrackerSD(name);
                    SDman->AddNewDetector(aTrackerSD);
                    ((*iter).first)->SetSensitiveDetector(aTrackerSD);
                    if (verbose) {
                        std::cout << "Attaching sensitive Detector: " << (*vit).value
                                << " to Volume:  " << ((*iter).first)->GetName() << std::endl;
                    }
                } else if ((*vit).value == "lArTPC") {
                    G4String name = ((*iter).first)->GetName() + "_lArTPC";
                    lArTPCSD* alArTPCSD = new lArTPCSD(name);
                    SDman->AddNewDetector(alArTPCSD);
                    ((*iter).first)->SetSensitiveDetector(alArTPCSD);
                    if (verbose) {
                        std::cout << "Attaching sensitive Detector: " << (*vit).value
                                << " to Volume:  " << ((*iter).first)->GetName() << std::endl;
                    }
                } else if ((*vit).value == "Radiator") {
                    G4String name = ((*iter).first)->GetName() + "_Radiator";
                    RadiatorSD* aRadiatorSD = new RadiatorSD(name);
                    SDman->AddNewDetector(aRadiatorSD);
                    ((*iter).first)->SetSensitiveDetector(aRadiatorSD);
                    if (verbose) {
                        std::cout << "Attaching sensitive Detector: " << (*vit).value
                                << " to Volume:  " << ((*iter).first)->GetName() << std::endl;
                    }
                } else if ((*vit).value == "Calorimeter") {
                    G4String name = ((*iter).first)->GetName() + "_Calorimeter";
                    CalorimeterSD* aCalorimeterSD = new CalorimeterSD(name);
                    SDman->AddNewDetector(aCalorimeterSD);
                    ((*iter).first)->SetSensitiveDetector(aCalorimeterSD);
                    if (verbose) {
                        std::cout << "Attaching sensitive Detector: " << (*vit).value
                                << " to Volume:  " << ((*iter).first)->GetName() << std::endl;
                    }
                } else if ((*vit).value == "DRCalorimeter") {
                    G4String name = ((*iter).first)->GetName() + "_DRCalorimeter";
                    DRCalorimeterSD* aDRCalorimeterSD = new DRCalorimeterSD(name);
                    SDman->AddNewDetector(aDRCalorimeterSD);
                    ((*iter).first)->SetSensitiveDetector(aDRCalorimeterSD);
                    if (verbose) {
                        std::cout << "Attaching sensitive Detector: " << (*vit).value
                                << " to Volume:  " << ((*iter).first)->GetName() << std::endl;
                    }
                }
            } else if ((*vit).type == "Solid") {
                if ((*vit).value == "True") {
                    G4VisAttributes * visibility = new G4VisAttributes();
                    visibility->SetForceSolid(true);
                    G4VisAttributes * visatt = new G4VisAttributes(((*iter).first)->GetVisAttributes()->GetColour());
                    visatt->SetVisibility(true);
                    visatt->SetForceSolid(true);
                    visatt->SetForceAuxEdgeVisible(true);
                    ((*iter).first)->SetVisAttributes(visatt);
                }
            } else if ((*vit).type == "Efield") {
                //                std::cout << "Setting E-Field of " << ((*iter).first)->GetName() << " to " << (*vit).value << " V/cm" << std::endl;
                //                double E = atof((*vit).value.c_str());
                //                G4ElectricField* fEMfield = new G4UniformElectricField(
                //                       G4ThreeVector(0.0, E * volt / cm, 0.0));
                //G4EqMagElectricField* fEquation = new G4EqMagElectricField(fEMfield);
                //              G4FieldManager* fFieldManager = G4TransportationManager::GetTransportationManager()->GetFieldManager();
                //               G4bool allLocal = true;
                //               ((*iter).first)->SetFieldManager(fFieldManager, allLocal);
            } //else if ((*vit).type == "Spline") {
            //  if ((*vit).value == "True") {
            //      ((*iter).first)->GetMaterial()->GetMaterialPropertiesTable()->GetProperty("FASTCOMPONENT")->SetSpline(true);
            //      ((*iter).first)->GetMaterial()->GetMaterialPropertiesTable()->GetProperty("SLOWCOMPONENT")->SetSpline(true);
            //  }
            // }
        }
    }
}

void DetectorConstruction::ReadGDML() {
    fReader = new ColorReader;
    parser = new G4GDMLParser(fReader);
    parser->Read(gdmlFile, false);
    G4VPhysicalVolume *World = parser->GetWorldVolume();
    //----- GDML parser makes world invisible, this is a hack to make it
    //visible again...
    G4LogicalVolume* pWorldLogical = World->GetLogicalVolume();
    pWorldLogical->SetVisAttributes(0);
    std::cout << World->GetTranslation() << std::endl << std::endl;
    if (verbose) {
        std::cout << "Found World:  " << World-> GetName() << std::endl;
        std::cout << "World LV:  " << World->GetLogicalVolume()->GetName() << std::endl;
    }
    G4LogicalVolumeStore *pLVStore = G4LogicalVolumeStore::GetInstance();
    if (verbose) {
        std::cout << "Found " << pLVStore->size()
                << " logical volumes."
                << std::endl << std::endl;
    }
    G4PhysicalVolumeStore *pPVStore = G4PhysicalVolumeStore::GetInstance();
    if (verbose) {
        std::cout << "Found " << pPVStore->size()
                << " physical volumes."
                << std::endl << std::endl;
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::UpdateGeometry() {
    G4RunManager::GetRunManager()->DefineWorldVolume(Construct());
}

