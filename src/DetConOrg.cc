/*
 * Copyright (c) 2019 Opticks Team. All Rights Reserved.
 *
 * This file is part of Opticks
 * (see https://bitbucket.org/simoncblyth/opticks).
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); 
 * you may not use this file except in compliance with the License.  
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" BASIS, 
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  
 * See the License for the specific language governing permissions and 
 * limitations under the License.
 */


#include <cstring>
#include <iostream>
#include "DetConOrg.hh"
#include "SensitiveDetector.hh"
// detector 
#include "G4VUserDetectorConstruction.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4MaterialTable.hh"
#include "G4SDManager.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

DetConOrg::DetConOrg(const char* sdname_)
:
G4VUserDetectorConstruction(),
sdname(strdup(sdname_)) {
}

G4Material* DetConOrg::MakeWater() {
    G4double a, z, density;
    G4int nelements;
    G4Element* O = new G4Element("Oxygen", "O", z = 8, a = 16.00 * CLHEP::g / CLHEP::mole);
    G4Element* H = new G4Element("Hydrogen", "H", z = 1, a = 1.01 * CLHEP::g / CLHEP::mole);
    G4Material* mat = new G4Material("Water", density = 1.0 * CLHEP::g / CLHEP::cm3, nelements = 2);
    mat->AddElement(H, 2);
    mat->AddElement(O, 1);
    /*
        G4MaterialPropertyVector* ri = MakeWaterRI();
        ri->SetSpline(false);

        AddProperty(mat, "RINDEX", ri);
     */
    using CLHEP::eV;

    // ------------ Generate & Add Material Properties Table ------------
    //
    G4double photonEnergy[] ={2.034 * eV, 2.068 * eV, 2.103 * eV, 2.139 * eV,
        2.177 * eV, 2.216 * eV, 2.256 * eV, 2.298 * eV,
        2.341 * eV, 2.386 * eV, 2.433 * eV, 2.481 * eV,
        2.532 * eV, 2.585 * eV, 2.640 * eV, 2.697 * eV,
        2.757 * eV, 2.820 * eV, 2.885 * eV, 2.954 * eV,
        3.026 * eV, 3.102 * eV, 3.181 * eV, 3.265 * eV,
        3.353 * eV, 3.446 * eV, 3.545 * eV, 3.649 * eV,
        3.760 * eV, 3.877 * eV, 4.002 * eV, 4.136 * eV};

    const G4int nEntries = sizeof (photonEnergy) / sizeof (G4double);

    //
    // Water
    //
    G4double refractiveIndex1[] ={1.3435, 1.344, 1.3445, 1.345, 1.3455,
        1.346, 1.3465, 1.347, 1.3475, 1.348,
        1.3485, 1.3492, 1.35, 1.3505, 1.351,
        1.3518, 1.3522, 1.3530, 1.3535, 1.354,
        1.3545, 1.355, 1.3555, 1.356, 1.3568,
        1.3572, 1.358, 1.3585, 1.359, 1.3595,
        1.36, 1.3608};

    assert(sizeof (refractiveIndex1) == sizeof (photonEnergy));

    G4double absorption[] ={3.448 * m, 4.082 * m, 6.329 * m, 9.174 * m, 12.346 * m, 13.889 * m,
        15.152 * m, 17.241 * m, 18.868 * m, 20.000 * m, 26.316 * m, 35.714 * m,
        45.455 * m, 47.619 * m, 52.632 * m, 52.632 * m, 55.556 * m, 52.632 * m,
        52.632 * m, 47.619 * m, 45.455 * m, 41.667 * m, 37.037 * m, 33.333 * m,
        30.000 * m, 28.500 * m, 27.000 * m, 24.500 * m, 22.000 * m, 19.500 * m,
        17.500 * m, 14.500 * m};

    assert(sizeof (absorption) == sizeof (photonEnergy));

    G4double scintilFast[] ={1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
        1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
        1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
        1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
        1.00, 1.00, 1.00, 1.00};

    assert(sizeof (scintilFast) == sizeof (photonEnergy));

    G4double scintilSlow[] ={0.01, 1.00, 2.00, 3.00, 4.00, 5.00, 6.00,
        7.00, 8.00, 9.00, 8.00, 7.00, 6.00, 4.00,
        3.00, 2.00, 1.00, 0.01, 1.00, 2.00, 3.00,
        4.00, 5.00, 6.00, 7.00, 8.00, 9.00, 8.00,
        7.00, 6.00, 5.00, 4.00};

    assert(sizeof (scintilSlow) == sizeof (photonEnergy));

    G4MaterialPropertiesTable* myMPT1 = new G4MaterialPropertiesTable();

    myMPT1->AddProperty("RINDEX", photonEnergy, refractiveIndex1, nEntries)
            ->SetSpline(true);
    myMPT1->AddProperty("ABSLENGTH", photonEnergy, absorption, nEntries)
            ->SetSpline(true);
    myMPT1->AddProperty("FASTCOMPONENT", photonEnergy, scintilFast, nEntries)
            ->SetSpline(true);
    myMPT1->AddProperty("SLOWCOMPONENT", photonEnergy, scintilSlow, nEntries)
            ->SetSpline(true);

    myMPT1->AddConstProperty("SCINTILLATIONYIELD", 5000. / MeV);
    myMPT1->AddConstProperty("RESOLUTIONSCALE", 1.0);
    myMPT1->AddConstProperty("FASTTIMECONSTANT", 1. * ns);
    myMPT1->AddConstProperty("SLOWTIMECONSTANT", 10. * ns);
    myMPT1->AddConstProperty("YIELDRATIO", 0.8);
    G4cout << "****************************** DetConOrg::MakeWater*********************************"<<G4endl;
    myMPT1->DumpTable();
    mat->SetMaterialPropertiesTable(myMPT1);
    return mat;
}

G4Material* DetConOrg::MakeAir() {
    G4double a, z, density;
    G4int nelements;
    G4Element* N = new G4Element("Nitrogen", "N", z = 7, a = 14.01 * CLHEP::g / CLHEP::mole);
    G4Element* O = new G4Element("Oxygen", "O", z = 8, a = 16.00 * CLHEP::g / CLHEP::mole);

    G4Material* mat = new G4Material("Air", density = 1.29 * CLHEP::mg / CLHEP::cm3, nelements = 2);
    mat->AddElement(N, 70. * CLHEP::perCent);
    mat->AddElement(O, 30. * CLHEP::perCent);

    G4MaterialPropertyVector* ri = MakeAirRI();
    ri->SetSpline(false);

    AddProperty(mat, "RINDEX", ri);
    return mat;
}

G4Material* DetConOrg::MakeGlass() {
    // from LXe example
    G4double a, z, density;
    G4int nelements;
    G4Element* H = new G4Element("H", "H", z = 1., a = 1.01 * CLHEP::g / CLHEP::mole);
    G4Element* C = new G4Element("C", "C", z = 6., a = 12.01 * CLHEP::g / CLHEP::mole);

    G4Material* mat = new G4Material("Glass", density = 1.032 * CLHEP::g / CLHEP::cm3, nelements = 2);
    mat->AddElement(C, 91.533 * CLHEP::perCent);
    mat->AddElement(H, 8.467 * CLHEP::perCent);

    G4MaterialPropertyVector* ri = MakeGlassRI();
    ri->SetSpline(false);

    AddProperty(mat, "RINDEX", ri);
    return mat;
}

void DetConOrg::AddProperty(G4Material* mat, const char* name, G4MaterialPropertyVector* mpv) {
    G4MaterialPropertiesTable* mpt = mat->GetMaterialPropertiesTable();
    if (mpt == NULL) mpt = new G4MaterialPropertiesTable();
    mpt->AddProperty(name, mpv);
    mat->SetMaterialPropertiesTable(mpt);
}

G4MaterialPropertyVector* DetConOrg::MakeGlassRI() {
    return MakeConstantProperty(1.49);
}

G4MaterialPropertyVector* DetConOrg::MakeConstantProperty(float value) {
    using CLHEP::eV;

    G4double photonEnergy[] = {2.034 * eV, 4.136 * eV};
    G4double propertyValue[] = {value, value};

    assert(sizeof (photonEnergy) == sizeof (propertyValue));
    const G4int nEntries = sizeof (photonEnergy) / sizeof (G4double);

    return new G4MaterialPropertyVector(photonEnergy, propertyValue, nEntries);
}


G4MaterialPropertyVector* DetConOrg::MakeAirRI() {
    using CLHEP::eV;
    G4double photonEnergy[] = {2.034 * eV, 2.068 * eV, 2.103 * eV, 2.139 * eV,
        2.177 * eV, 2.216 * eV, 2.256 * eV, 2.298 * eV,
        2.341 * eV, 2.386 * eV, 2.433 * eV, 2.481 * eV,
        2.532 * eV, 2.585 * eV, 2.640 * eV, 2.697 * eV,
        2.757 * eV, 2.820 * eV, 2.885 * eV, 2.954 * eV,
        3.026 * eV, 3.102 * eV, 3.181 * eV, 3.265 * eV,
        3.353 * eV, 3.446 * eV, 3.545 * eV, 3.649 * eV,
        3.760 * eV, 3.877 * eV, 4.002 * eV, 4.136 * eV};

    const G4int nEntries = sizeof (photonEnergy) / sizeof (G4double);

    G4double refractiveIndex[] = {1., 1., 1., 1.,
        1., 1., 1., 1.,
        1., 1., 1., 1.,
        1., 1., 1., 1.,
        1., 1., 1., 1.,
        1., 1., 1., 1.,
        1., 1., 1., 1.,
        1., 1., 1., 1,};

    assert(sizeof (refractiveIndex) == sizeof (photonEnergy));
    return new G4MaterialPropertyVector(photonEnergy, refractiveIndex, nEntries);
}

G4VPhysicalVolume* DetConOrg::Construct() {
    G4cout << "[ DetConOrg::Construct " << G4endl;

    G4Material* air = MakeAir();
    G4Box* so_0 = new G4Box("World", 1000., 1000., 1000.);
    G4LogicalVolume* lv_0 = new G4LogicalVolume(so_0, air, "World", 0, 0, 0);

    G4VPhysicalVolume* pv_0 = new G4PVPlacement(0, G4ThreeVector(), lv_0, "World", 0, false, 0);

    G4Material* water = MakeWater();
    G4Box* so_1 = new G4Box("Obj", 500., 500., 500.);
    G4LogicalVolume* lv_1 = new G4LogicalVolume(so_1, water, "Obj", 0, 0, 0);
    G4VPhysicalVolume* pv_1 = new G4PVPlacement(0, G4ThreeVector(), lv_1, "Obj", lv_0, false, 0);
    assert(pv_1);

    G4Material* glass = MakeGlass(); // slab of sensitive glass in the water 
    //AddProperty(glass, "EFFICIENCY", MakeConstantProperty(0.5)); 


    G4Box* so_2 = new G4Box("Det", 400., 400., 10.); // half sizes 
    //G4LogicalVolume* 
    lv_2 = new G4LogicalVolume(so_2, glass, "Det", 0, 0, 0);
    G4OpticalSurface* scintWrap = new G4OpticalSurface("ScintWrap");


    G4VPhysicalVolume* pv_2 = new G4PVPlacement(0, G4ThreeVector(0, 0, 100.), lv_2, "Det", lv_1, false, 0);
    assert(pv_2);
    new G4LogicalBorderSurface("ScintWrap", pv_1,
            pv_2,
            scintWrap);

    scintWrap->SetType(dielectric_metal);
    scintWrap->SetFinish(polished);
    scintWrap->SetModel(glisur);

    G4double pp[] = {2.0 * eV, 3.5 * eV};
    const G4int num = sizeof (pp) / sizeof (G4double);
    G4double reflectivity[] = {1., 1.};
    assert(sizeof (reflectivity) == sizeof (pp));
    G4double efficiency[] = {0.5, 0.5};
    assert(sizeof (efficiency) == sizeof (pp));
    G4MaterialPropertiesTable* scintWrapProperty
            = new G4MaterialPropertiesTable();

    scintWrapProperty->AddProperty("REFLECTIVITY", pp, reflectivity, num);
    scintWrapProperty->AddProperty("EFFICIENCY", pp, efficiency, num);
    scintWrap->SetMaterialPropertiesTable(scintWrapProperty);





    const std::string& lv_1_name = lv_1->GetName();
    //std::cout << " lv_1_name " << lv_1_name << std::endl ; 
    assert(strcmp(lv_1_name.c_str(), "Obj") == 0);

    G4cout << "] DetConOrg::Construct " << G4endl;

    return pv_0;
}

void DetConOrg::ConstructSDandField() {
    G4SDManager* SDMan = G4SDManager::GetSDMpointer();
    //   G4SDManager* SDMan = G4SDManager::GetSDMpointerIfExist();
    //    assert(SDMan && " SDMan should have been created before now ");
    SensitiveDetector* aSensitiveDetector = new SensitiveDetector(sdname);
    SDMan->AddNewDetector(aSensitiveDetector);
    G4VSensitiveDetector* sd = SDMan->FindSensitiveDetector(sdname);
    //  assert(sd && " failed for find sd with sdname ");
    lv_2->SetSensitiveDetector(sd);
}

