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
// Update: add a gdml interface (S.Y. Jun, Mar. 30, 2017)
// -----------------------------------------------------
// Geant4 headers
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4RunManager.hh"
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4StepLimiter.hh"
#include "G4HadronicProcessStore.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4UserLimits.hh"
#include "G4UnitsTable.hh"
#include "G4ios.hh"
#include "G4NistManager.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4SDManager.hh"
#include "globals.hh"
#include "G4VPhysicalVolume.hh"
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
#include "PhotonSD.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
using namespace std;
//G4LogicalVolume* logicContainer;

DetectorConstruction::DetectorConstruction(G4String fname) {
    gdmlFile = fname;
    sdnames = ConfigurationManager::getInstance()->getSDNames();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction() {
}

G4VPhysicalVolume* DetectorConstruction::Construct() {
    ReadGDML();
    const G4GDMLAuxMapType* auxmap = parser->GetAuxMap();
    std::cout << "Found " << auxmap->size()
            << " volume(s) with auxiliary information."
            << std::endl << std::endl;
    for (G4GDMLAuxMapType::const_iterator iter = auxmap->begin();
            iter != auxmap->end(); iter++) {
        std::cout << "Volume " << ((*iter).first)->GetName()
                << " has the following list of auxiliary information: "
                << std::endl;
        for (G4GDMLAuxListType::const_iterator vit = (*iter).second.begin();
                vit != (*iter).second.end(); vit++) {
            std::cout << "--> Type: " << (*vit).type
                    << " Value: " << (*vit).value << std::endl;
            if ((*vit).type == "StepLimit") {
                G4UserLimits *fStepLimit = new G4UserLimits(atof((*vit).value));
                ((*iter).first)->SetUserLimits(fStepLimit);
            }
        }
    }
    //   logicTarget = G4LogicalVolumeStore::GetInstance()->GetVolume("volTPCActiveInner");
    //    logicContainer = G4LogicalVolumeStore::GetInstance()->GetVolume("volContainer");
    G4VPhysicalVolume* worldPhysVol = parser->GetWorldVolume();
    //    PrepareLArTest();
    //    if (ConfigurationManager::getInstance()->GetstepLimit()) {
    //        G4double mxStep = ConfigurationManager::getInstance()->Getlimitval();
    //        G4UserLimits *fStepLimit = new G4UserLimits(mxStep);
    //        logicTarget->SetUserLimits(fStepLimit);
    //    }
    return worldPhysVol;
}

void DetectorConstruction::ConstructSDandField() {
    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    const G4GDMLAuxMapType* auxmap = parser->GetAuxMap();
    std::cout << "Found " << auxmap->size()
            << " volume(s) with auxiliary information."
            << std::endl << std::endl;
    for (G4GDMLAuxMapType::const_iterator iter = auxmap->begin();
            iter != auxmap->end(); iter++) {
        std::cout << "Volume " << ((*iter).first)->GetName()
                << " has the following list of auxiliary information: "
                << std::endl;
        for (G4GDMLAuxListType::const_iterator vit = (*iter).second.begin();
                vit != (*iter).second.end(); vit++) {
            std::cout << "--> Type: " << (*vit).type
                    << " Value: " << (*vit).value << std::endl;
            if ((*vit).type == "SensDet") {
                if ((*vit).value == "PhotonDetector") {
                    G4String name = ((*iter).first)->GetName() + "_Photondetector";
                    PhotonSD* aPhotonSD = new PhotonSD(name);
                    SDman->AddNewDetector(aPhotonSD);
                    sdnames->push_back(name);
                    std::cout << "new size: " << sdnames->size() << std::endl;
                    ((*iter).first)->SetSensitiveDetector(aPhotonSD);
                    std::cout << "Attaching sensitive Detector: " << (*vit).value
                            << " to Volume:  " << ((*iter).first)->GetName() << std::endl;
                    //DetectorList.push_back(std::make_pair((*iter).first->GetName(), (*vit).value));
                } else if ((*vit).value == "Tracker") {
                    G4String name = ((*iter).first)->GetName() + "_Tracker";
                    TrackerSD* aTrackerSD = new TrackerSD(name);
                    SDman->AddNewDetector(aTrackerSD);
                    sdnames->push_back(name);
                    std::cout << "new size: " << sdnames->size() << std::endl;
                    ((*iter).first)->SetSensitiveDetector(aTrackerSD);
                    std::cout << "Attaching sensitive Detector: " << (*vit).value
                            << " to Volume:  " << ((*iter).first)->GetName() << std::endl;
                    //DetectorList.push_back(std::make_pair((*iter).first->GetName(), (*vit).value));
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
                std::cout << "Setting E-Field of " << ((*iter).first)->GetName() << " to " << (*vit).value << " V/cm" << std::endl;
                double E = atof((*vit).value.c_str());
                std::cout << E << std::endl;
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
    std::cout << "Found World:  " << World-> GetName() << std::endl;
    std::cout << "World LV:  " << World->GetLogicalVolume()->GetName() << std::endl;
    G4LogicalVolumeStore *pLVStore = G4LogicalVolumeStore::GetInstance();
    std::cout << "Found " << pLVStore->size()
            << " logical volumes."
            << std::endl << std::endl;
    G4PhysicalVolumeStore *pPVStore = G4PhysicalVolumeStore::GetInstance();
    std::cout << "Found " << pPVStore->size()
            << " physical volumes."
            << std::endl << std::endl;
}
/*
void DetectorConstruction::PrepareLArTest() {


    G4MaterialPropertiesTable* LArMPT = new G4MaterialPropertiesTable();
    G4MaterialPropertiesTable* LArMPT2 = new G4MaterialPropertiesTable();
    //
    //  simple description of scintillation yield  
    //  [J Chem Phys vol 91 (1989) 1469]
    //
    G4double Rindex[] = {1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5};
    G4double FastScintEnergies[] = {6.7 * eV, 7.1 * eV, 7.4 * eV, 7.7 * eV, 7.9 * eV, 8.1 * eV, 8.4 * eV, 8.5 * eV, 8.6 * eV, 8.8 * eV, 9.0 * eV, 9.1 * eV, 9.4 * eV, 9.8 * eV, 10.4 * eV};
    G4double FastScintSpectrum[] = {0.04, 0.12, 0.27, 0.44, 0.62, 0.80, 0.91, 0.92, 0.85, 0.70, 0.50, 0.31, 0.13, 0.04, 0.01};
    assert(sizeof (FastScintSpectrum) == sizeof (FastScintEnergies));
    assert(sizeof (Rindex) == sizeof (FastScintEnergies));
    const G4int num = sizeof (FastScintEnergies) / sizeof (G4double);
    for (int jj = 0; jj < num; jj++) {
        G4double lam = ((h_Planck * c_light) / FastScintEnergies[jj]) / nm;
        std::cout << FastScintEnergies[jj] / eV << "  " << ((h_Planck * c_light) / FastScintEnergies[jj]) / nm << "   " << LArRefIndex(lam) << "  " << ArScintillationSpectrum(lam) << std::endl;
    }
    LArMPT->AddProperty("RINDEX", FastScintEnergies, Rindex, num);
    LArMPT2->AddProperty("RINDEX", FastScintEnergies, Rindex, num);
    LArMPT->AddProperty("FASTCOMPONENT", FastScintEnergies, FastScintSpectrum, num)->SetSpline(true);
    LArMPT->AddProperty("SLOWCOMPONENT", FastScintEnergies, FastScintSpectrum, num)->SetSpline(true);
    LArMPT->AddConstProperty("FASTTIMECONSTANT", 7. * ns);
    LArMPT->AddConstProperty("SLOWTIMECONSTANT", 1400. * ns);
    LArMPT->AddConstProperty("YIELDRATIO", 0.75);
    G4double scint_yield = 1.0 / (19.5 * eV);
    LArMPT->AddConstProperty("SCINTILLATIONYIELD", scint_yield / MeV);
    LArMPT->DumpTable();
    //    G4double fano = 0.11;
    // Doke et al, NIM 134 (1976)353
    //LArMPT->AddConstProperty("RESOLUTIONSCALE", fano);
    LArMPT->AddConstProperty("RESOLUTIONSCALE", 1.0);
    std::cout << "**********************************************************************" << std::endl;
    //std::cout << logicTarget->GetMaterial()->GetName() << std::endl;
    std::cout << "**********************************************************************" << std::endl;
    //logicTarget->GetMaterial()->SetMaterialPropertiesTable(LArMPT);
    logicContainer->GetMaterial()->SetMaterialPropertiesTable(LArMPT2);
}
 */
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::UpdateGeometry() {
    G4RunManager::GetRunManager()->DefineWorldVolume(Construct());
}

// The following 3 functions are described in
// https://indico.cern.ch/event/44566/contributions/1101918/attachments/943057/1337650/dipompeo.pdf
// and references therein
//

G4double DetectorConstruction::ArScintillationSpectrum(G4double kk) {
    G4double waveL;
    waveL = exp(-0.5 * ((kk - 128.0) / (2.929))*((kk - 128.0) / (2.929)));
    return waveL;
}

// Calculates the dielectric constant of LAr from the Bideau-Sellmeier formula.
// See : A. Bideau-Mehu et al., "Measurement of refractive indices of Ne, Ar,
// Kr and Xe ...", J. Quant. Spectrosc. Radiat. Transfer, Vol. 25 (1981), 395

G4double DetectorConstruction::LArEpsilon(const G4double lambda) {
    G4double epsilon;
    G4double lowLambda = 110.0; // lowLambda in  nanometer
    if (lambda < lowLambda) return 1.0e4; // lambda MUST be > 110.0 nm
    epsilon = lambda / 1000; // switch to micrometers
    epsilon = 1.0 / (epsilon * epsilon); // 1 / (lambda)^2
    epsilon = 1.2055e-2 * (0.2075 / (91.012 - epsilon) +
            0.0415 / (87.892 - epsilon) +
            4.3330 / (214.02 - epsilon));
    epsilon *= (8. / 12.); // Bideau-Sellmeier -> Clausius-Mossotti
    G4double GArRho = 0.001784; // density in g/cm3
    G4double LArRho = 1.3954; // density in g/cm3
    epsilon *= (LArRho / GArRho); // density correction (Ar gas -> LAr liquid)
    if (epsilon < 0.0 || epsilon > 0.999999) return 4.0e6;
    epsilon = (1.0 + 2.0 * epsilon) / (1.0 - epsilon); // solve Clausius-Mossotti
    return epsilon;
}
//
// Calculates the refractive index of LAr
//

G4double DetectorConstruction::LArRefIndex(const G4double lambda) {
    return ( sqrt(LArEpsilon(lambda))); // square root of dielectric constant
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
