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
#include "ConfigurationManager.hh"
#ifdef WITH_G4OPTICKS
#include "G4Opticks.hh"
#include "TrackInfo.hh"
#include "OpticksGenstep.h"
#include "OpticksFlags.hh"
#include "G4OpticksHit.hh"
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhotonSD::PhotonSD(G4String name)
: G4VSensitiveDetector(name), fPhotonHitsCollection(0), fHCID(0) {
    G4String HCname = name + "_HC";
    collectionName.insert(HCname);
    G4cout << collectionName.size() << "   PhotonSD name:  " << name << " collection Name: "
            << HCname << G4endl;
    fHCID = -1;
    verbose = ConfigurationManager::getInstance()->isEnable_verbose();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhotonSD::Initialize(G4HCofThisEvent* hce) {
    fPhotonHitsCollection = new PhotonHitsCollection(SensitiveDetectorName, collectionName[0]);
    if (fHCID < 0) {
        if (verbose) G4cout << "PhotonSD::Initialize:  " << SensitiveDetectorName << "   "
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
    G4Track* theTrack = aStep->GetTrack();
    // we only deal with optical Photons:
    if (theTrack->GetDefinition() != G4OpticalPhoton::OpticalPhotonDefinition()) {
        return false;
    }
    G4double theEdep = theTrack->GetTotalEnergy();
    const G4VProcess * thisProcess = theTrack->GetCreatorProcess();

    G4String processname;
    if (thisProcess != NULL)
        processname = thisProcess->GetProcessName();
    else
        processname = "No Process";
    unsigned theCreationProcessid;
    if (processname == "Cerenkov") {
        theCreationProcessid = 0;
    } else if (processname == "Scintillation") {
        theCreationProcessid = 1;
    } else {
        theCreationProcessid = -1;
    }
    PhotonHit* newHit = new PhotonHit(0,
            theCreationProcessid,
            etolambda(theEdep),
            theTrack->GetGlobalTime(),
            aStep->GetPostStepPoint()->GetPosition(),
            aStep->GetPostStepPoint()->GetMomentumDirection(),
            aStep->GetPostStepPoint()->GetPolarization());
    fPhotonHitsCollection->insert(newHit);
    theTrack->SetTrackStatus(fStopAndKill);
    return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhotonSD::EndOfEvent(G4HCofThisEvent*) {
    G4int NbHits = fPhotonHitsCollection->entries();
    if (verbose) G4cout << " Number of PhotonHits:  " << NbHits << G4endl;
}

double PhotonSD::etolambda(double E) {
    // input  photon energy in MeV
    // return   wavelength in nm 
    return (h * c) / (E * 1.e-9);
}
#ifdef WITH_G4OPTICKS
void PhotonSD::AddOpticksHits() {
    G4Opticks* g4ok = G4Opticks::Get();
    bool way_enabled = g4ok->isWayEnabled();
    unsigned num_hits = g4ok->getNumHit();
    G4OpticksHit hit;
    G4OpticksHitExtra hit_extra;
    G4OpticksHitExtra* hit_extra_ptr = way_enabled ? &hit_extra : NULL;
    for (unsigned i = 0; i < num_hits; i++) {
        g4ok->getHit(i, &hit, hit_extra_ptr);
      //  G4cout << "AddOpticksHits"<<G4endl;
        
        PhotonHit* newHit = new PhotonHit(
                i,
                0,
                hit.wavelength,
                hit.time,
                hit.global_position,
                hit.global_direction,
                hit.global_polarization);
        fPhotonHitsCollection->insert(newHit);
    }
    G4cout << "AddOpticksHits size:  " <<fPhotonHitsCollection->entries() <<G4endl;
}
#endif