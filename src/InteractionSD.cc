/* ------------------------------------------------------------------------
            |\___/|       
            )     (    
           =\     /=
             )===(
            /     \         CaTS: Calorimeter and Tracker Simulation
            |     |         Author: Hans Wenzel (Fermilab)
           /       \        Created on June 23, 2014
           \       /
            \__  _/
              ( (
               ) )
              (_(
-------------------------------------------------------------------------*/
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// Geant 4 includes:
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
//#include "G4VVisManager.hh"
//#include "G4RunManager.hh"
//#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "InteractionSD.hh"
#include "G4SystemOfUnits.hh"
//#include "globals.hh"
// c++ includes:
#include <typeinfo>

InteractionSD::InteractionSD(G4String name)
: G4VSensitiveDetector(name) {
    G4String HCname = name + "_HC";
    collectionName.insert(HCname);
    G4cout << collectionName.size() << "   InteractionSD name:  " << name << " collection Name: " << HCname << G4endl;
    HCID = -1;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

InteractionSD::~InteractionSD() {
    if (fFirstInter) delete fFirstInter;
    if (fOtherInter) delete fOtherInter;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void InteractionSD::Initialize(G4HCofThisEvent* HCE) {
    G4cout << "Hits Collection capacity:  " << HCE->GetCapacity() << G4endl;
    interactionCollection = new InteractionHitsCollection
            (SensitiveDetectorName, collectionName[0]);
    if (HCID < 0) {
        G4cout << "InteractionSD::Initialize:  " << SensitiveDetectorName << "   " << collectionName[0] << G4endl;
        HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);

    }
    HCE->AddHitsCollection(HCID, interactionCollection);
    fFirstInter = new ParticleChange(true);
    fOtherInter = new ParticleChange();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool InteractionSD::ProcessHits(G4Step* aStep, G4TouchableHistory*) {

    int nsc = fFirstInter->GetNumberOfSecondaries();
    if (nsc > 0) {
        for (int i = 0; i < nsc; i++) {
            delete fFirstInter->GetSecondary(i);
        }
        fFirstInter->Clear();
    }
    nsc = fOtherInter->GetNumberOfSecondaries();
    if (nsc > 0) {
        for (int i = 0; i < nsc; i++) {
            delete fOtherInter->GetSecondary(i);
        }
        fOtherInter->Clear();
    }
    const std::vector<const G4Track*>* secs = aStep->GetSecondaryInCurrentStep();
    int nsec = secs->size();
    for (int i = 0; i < nsec; i++) {

        G4Track* tr = new G4Track(*((*secs)[i]));

        if (aStep->GetTrack()->GetTrackStatus() != fAlive) // track looses identity
        {
            if (aStep->GetTrack()->GetParentID() == 0) // primary track
            {
                fFirstInter->AddSecondary(tr);
            } else // secondary track, and it's also looses identity (re-interaction)
            {
                fOtherInter->AddSecondary(tr);
            }
        }

    } //end loop over secondaries
    //const ParticleGunActionService* beam = dynamic_cast<const ParticleGunActionService*> (G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
    //const G4ParticleGun* Gun = beam->GetGun();
    //G4cout << "hello" << G4endl;
    //G4cout << "Gun:  " << Gun->GetParticleEnergy() << G4endl;
    //G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction();
    //        G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction();
    //const G4VUserPrimaryGeneratorAction junk = G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction();
    //G4cout << "888888888888888888888888888888:   " << typeid (G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction()).name() << G4endl;
    G4int NSec = fFirstInter->GetNumberOfSecondaries();
    if (NSec > 0) {
          G4cout << " 0000000000000000000  Nr of secs. :  " << fFirstInter ->GetNumberOfSecondaries() << G4endl;
        //  G4cout << "Edep: " << aStep->GetTotalEnergyDeposit()
        //          << " Name:  " << aStep->GetTrack()->GetParticleDefinition()->GetParticleName()
        //          << "  kinetic E:  " << aStep->GetTrack()->GetKineticEnergy()
        //          << " tot Energy:  " << aStep->GetTrack()->GetTotalEnergy()
        //          << " Position: " << aStep->GetPreStepPoint()->GetPosition()
        //          << G4endl;
        const G4DynamicParticle* sec = 0;
        for (G4int i = 0; i < NSec; i++) {
            sec = fFirstInter->GetSecondary(i)->GetDynamicParticle();
            //G4cout << " 0000000000000000000"<<G4endl;
            //sec->DumpInfo();
            // if ( sec->GetDefinition()->GetParticleName()=="proton" && sec->GetKineticEnergy()>600.)
            //{

            //            G4cout << " 0000000000000000000 Name: " << sec->GetDefinition()->GetParticleName()
            //                    << " Momentum:  " << sec->GetTotalMomentum()/GeV << "GeV: " << GeV
            //                    << " kin Energy:  " << sec->GetKineticEnergy()/GeV
            //                    << " Total  energy: " << sec->GetTotalEnergy()/GeV
            //                    << " Mass:  " << sec->GetMass()<<G4endl;
            const G4String& pname = sec->GetDefinition()->GetParticleName();
            G4double pmom = (sec->GetTotalMomentum()) / GeV;
            G4double Ekin = (sec->GetKineticEnergy()) / GeV;

            G4double theta = (sec->GetMomentum()).theta();
            InteractionHit* newHit = new InteractionHit(pname, pmom, Ekin, theta);
            interactionCollection->insert(newHit);
            //}
        }
    }
    //G4cout << beam->GetParticleMomentum() << G4endl;
    return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
