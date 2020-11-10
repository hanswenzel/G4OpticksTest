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

#include "PhotonSD.hh"
#include "G4VProcess.hh"
#include "G4OpticalPhoton.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4VVisManager.hh"
#include "ConfigurationManager.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#ifdef WITH_OPTICKS
#include "G4Opticks.hh"
#include "NPho.hpp"
#include "NPY.hpp"
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
PhotonSD::PhotonSD(G4String name)
: G4VSensitiveDetector(name), fPhotonHitsCollection(0), fHCID(0) {
    G4String HCname = name + "_HC";
    collectionName.insert(HCname);
    G4cout << collectionName.size() << "   PhotonSD name:  " << name << " collection Name: "
            << HCname << G4endl;
    fHCID = -1;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhotonSD::Initialize(G4HCofThisEvent* hce) {
    fPhotonHitsCollection = new PhotonHitsCollection(SensitiveDetectorName, collectionName[0]);
    if (fHCID < 0) {
        G4cout << "PhotonSD::Initialize:  " << SensitiveDetectorName << "   "
                << collectionName[0] << G4endl;
        fHCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    }
    hce->AddHitsCollection(fHCID, fPhotonHitsCollection);
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhotonSD::~PhotonSD() {
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool PhotonSD::ProcessHits(G4Step* aStep, G4TouchableHistory*) {
    return true;
}

void PhotonSD::EndOfEvent(G4HCofThisEvent*) {
    /*
    #ifdef WITH_OPTICKS
    G4Opticks* ok = G4Opticks::Get();
    NPY<float>* hits = ok->getHits();
 //   hits->save(".", "hits.npy");
    G4cout << "PhotonSD::EndOfEvent"
            << " num_hits " << hits->getNumItems() 
            << G4endl;

    G4cout << "EventAction::EndOfEventAction hit:  " << hits->getFloat(0, 0, 0, 0) << G4endl;
    G4cout << "EventAction::EndOfEventAction hit:  " << hits->getFloat(0, 1, 0, 0) << G4endl;
    G4cout << "EventAction::EndOfEventAction hit:  " << hits->getFloat(0, 2, 0, 0) << G4endl;
    G4cout << "EventAction::EndOfEventAction hit:  " << hits->getFloat(0, 3, 0, 0) << G4endl;
    G4cout << "EventAction::EndOfEventAction hit:  " << hits->getFloat(0, 4, 0, 0) << G4endl;
    #endif
     */
}
