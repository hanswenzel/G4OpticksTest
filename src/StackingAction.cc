/* ------------------------------------------------------------------------
            |\___/|       
            )     (    
           =\     /=
             )===(
            /     \         CaTS: Calorimeter and Tracker Simulation
            |     |         Author: Hans Wenzel (Fermilab)
           /       \
           \       /
            \__  _/
              ( (
               ) )
              (_(
-------------------------------------------------------------------------*/
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#include "StackingAction.hh"
#include "StackingActionMessenger.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"
#include "G4TrackStatus.hh"
#include "G4ios.hh"
#include "G4VProcess.hh"
#include "G4ClassificationOfNewTrack.hh"
#include "G4PhysicalConstants.hh"
#include "G4PhysicsOrderedFreeVector.hh"
#include "G4Material.hh" 
#include "G4MaterialPropertyVector.hh"
#include "g4analysis.hh"
#include <cmath>
#include <map>
#include <set>
using namespace std;
StackingAction* StackingAction::instance = 0;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#define G4ANALYSIS_USE TRUE
//#ifdef G4ANALYSIS_USE
//Analysis* StackingAction::analysis;
//#endif

StackingAction::StackingAction() :
killPi0(false),
killeta(false),
killGammafromnCapture(false)
//histo_beta(0),
//EGammahisto(0),
//ENeutronhisto(0),
//EProtonhisto(0),
//CaptureGammahisto(0) 
{
    //#ifdef G4ANALYSIS_USE
    //analysis = Analysis::getInstance();
    //#endif
    pMessenger = new StackingActionMessenger(this);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

StackingAction::~StackingAction() {
    delete pMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ClassificationOfNewTrack StackingAction::ClassifyNewTrack(const G4Track * aTrack) {
    G4ClassificationOfNewTrack classification = fWaiting;
    if (aTrack->GetParentID() == 0) return classification;
    if (aTrack->GetDefinition()->GetParticleName() == "pi0") {
        if (killPi0) {
            classification = fKill;
        }
    }
    if (aTrack->GetDefinition()->GetParticleName() == "eta") {
        if (killeta) {
            classification = fKill;
        }
    }
    if (aTrack->GetDefinition()->GetParticleName() == "gamma") {
        if (aTrack->GetCreatorProcess()->GetProcessName() == "nCapture") {
            if (killGammafromnCapture) {
                classification = fKill;
            }
        }
    }
    //#ifdef G4ANALYSIS_USE
    //   FillHistos(aTrack);
    //#endif
    if (aTrack->GetDefinition()->GetParticleName() == "neutron") {
        auto analysisManager = G4AnalysisManager::Instance();
        analysisManager->FillH1(0, aTrack->GetKineticEnergy());
    }
    if (aTrack->GetDefinition()->GetParticleName() == "proton") {
        auto analysisManager = G4AnalysisManager::Instance();
        analysisManager->FillH1(1, aTrack->GetKineticEnergy());
    }
    return classification;
}
//#ifdef G4ANALYSIS_USE

void StackingAction::BeginRun() {
    G4cout << "********************StackingAction::BeginRun" << G4endl;
    /*
        VolumeDirset.clear();
        Volumeset.clear();
        Particles.clear();
        Processes.clear();
        NHistosbyproc.clear();
        NHistosbypart.clear();
        ENeutronhistosbyproc.clear();
        EProtonhistosbyproc.clear();
        EP_ev_protonhistosbyproc.clear();
        EP_sp_protonhistosbyproc.clear();
        EP_he_protonhistosbyproc.clear();
        BetaHistosbypart.clear();
        //
        analysis->Stackingdir->cd();
        histo_beta = new TH1F("beta", "beta of created particles", 100, 0, 1.);
        EGammahisto = new TH1F("EGamma", "Energy of created Gammas", 100, 0, 2.0);
        ENeutronhisto = new TH1F("ENeutron", "Energy of created Neutrons", 200, 0, 100);
        EProtonhisto = new TH1F("EProton", "Energy of created Protons", 200, 0, 100);
        EP_ev_protonhisto = new TH1F("EProton_ev", "Energy of created Protons", 200, 0, 20 * CLHEP::MeV);
        EP_sp_protonhisto = new TH1F("EProton_sp", "Energy of created Protons", 200, 0, 1000 * CLHEP::MeV);
        EP_he_protonhisto = new TH1F("EProton_he", "Energy of created Protons", 200, 0, 10000 * CLHEP::MeV);
        CaptureGammahisto = new TH1F("CaptureGamma", "Creation time of nCapture photons", 200, 0, 10000);
        partdir = analysis->Stackingdir->mkdir("Particles");
        procdir = analysis->Stackingdir->mkdir("Processes");
        ebypartdir = analysis->Stackingdir->mkdir("Energycont");
        Volumesdir = analysis->Stackingdir->mkdir("Volumes");
        G4cout << "********* Path:  " << Volumesdir->GetPath() << G4endl;
     */
}

void StackingAction::FillHistos(const G4Track * aTrack) {
    /*
        if (aTrack->GetDefinition()->GetParticleName() == "gamma") {
            EGammahisto->Fill(aTrack->GetTotalEnergy());
            if (aTrack->GetCreatorProcess()->GetProcessName() == "nCapture") {
                CaptureGammahisto->Fill(aTrack->GetGlobalTime() / CLHEP::ns);
            }
        }
        G4String VolumeName = aTrack->GetVolume()->GetName();
        if (Volumeset.find(VolumeName) == Volumeset.end()) {
            Volumeset.insert(VolumeName);
            G4cout << "********* VolumeName:  " << VolumeName << "  " << VolumeDirset.size() << G4endl;
            G4cout << "********* Path:  " << Volumesdir->GetPath() << G4endl;
            VolumeDirset.insert(std::make_pair(VolumeName, Volumesdir->mkdir(VolumeName.c_str())));
        }
        const G4double charge = aTrack->GetDefinition()->GetPDGCharge();
        G4String particleType = aTrack->GetDefinition()->GetParticleName();
        G4String fragment = "Fragment";
        if (aTrack->GetParticleDefinition()->GetParticleType() == "nucleus" && aTrack->GetParticleDefinition()->GetParticleSubType() == "generic") {
            particleType = fragment;
        }

        if (Particles.find(VolumeName) == Particles.end()) {
            std::map<G4String, G4int> tmpmap;
            Particles.insert(std::make_pair(VolumeName, tmpmap));
            Particles[VolumeName].insert(std::make_pair(particleType, 1));
        } else if (Particles[VolumeName].find(particleType) == Particles[VolumeName].end()) {
            Particles[VolumeName].insert(std::make_pair(particleType, 1));
        } else {
            Particles[VolumeName].at(particleType)++;
        }
        G4String CrProcess = aTrack->GetCreatorProcess()->GetProcessName();
        if (Processes.find(VolumeName) == Processes.end()) {
            std::map<G4String, G4int> tmpmap;
            Processes.insert(std::make_pair(VolumeName, tmpmap));
            Processes[VolumeName].insert(std::make_pair(CrProcess, 1));
        } else if (Processes[VolumeName].find(CrProcess) == Processes[VolumeName].end()) {
            Processes[VolumeName].insert(std::make_pair(CrProcess, 1));
        } else {
            Processes[VolumeName].at(CrProcess)++;
        }
        // 
        // Neutrons and protons are of particular interest
        //
        if (aTrack->GetDefinition()->GetParticleName() == "neutron") {
            ENeutronhisto->Fill(aTrack->GetKineticEnergy());
            G4String CrProcess = aTrack->GetCreatorProcess()->GetProcessName();
            VolumeDirset[VolumeName]->cd();
            if (ENeutronhistosbyproc.find(VolumeName) == ENeutronhistosbyproc.end()) {
                std::map<G4String, TH1F*> tmpmap;
                ENeutronhistosbyproc.insert(std::make_pair(VolumeName, tmpmap));
                G4String hname = "ne_" + CrProcess;
                const char* hisname = hname.c_str();
                TH1F *histo_ne = new TH1F(hisname, "energy of created neutron", 200, 0, 100);
                ENeutronhistosbyproc[VolumeName].insert(std::make_pair(CrProcess, histo_ne));
                ENeutronhistosbyproc[VolumeName].at(CrProcess)->Fill(aTrack->GetKineticEnergy());
            } else if (ENeutronhistosbyproc[VolumeName].find(CrProcess) == ENeutronhistosbyproc[VolumeName].end()) {
                G4String hname = "ne_" + CrProcess;
                const char* hisname = hname.c_str();
                TH1F *histo_ne = new TH1F(hisname, "energy of created neutron", 200, 0, 100);
                ENeutronhistosbyproc[VolumeName].insert(std::make_pair(CrProcess, histo_ne));
                ENeutronhistosbyproc[VolumeName].at(CrProcess)->Fill(aTrack->GetKineticEnergy());

            } else {
                ENeutronhistosbyproc[VolumeName].at(CrProcess)->Fill(aTrack->GetKineticEnergy());
            }
        }

        if (aTrack->GetDefinition()->GetParticleName() == "proton") {
            G4String pname = aTrack->GetDefinition()->GetParticleName();
            //        G4cout << pname << " "   << aTrack -> GetKineticEnergy()/CLHEP::MeV << G4endl;
            G4String myname = pname;
            G4double ekin = aTrack -> GetKineticEnergy() / CLHEP::MeV;
            myname = "p_he";
            if (ekin < 10.) {
                myname = "p_ev";
            } else if (ekin < 500.) {
                myname = "p_sp";
            }

            //        G4cout << pname << "  "<< myname <<  aTrack-> GetKineticEnergy() << G4endl;
            pname = myname;

            if (pname == "proton") {

                EProtonhisto->Fill(aTrack->GetKineticEnergy());
                G4String CrProcess = aTrack->GetCreatorProcess()->GetProcessName();
                VolumeDirset[VolumeName]->cd();
                if (EProtonhistosbyproc.find(VolumeName) == EProtonhistosbyproc.end()) {
                    std::map<G4String, TH1F*> tmpmap;
                    EProtonhistosbyproc.insert(std::make_pair(VolumeName, tmpmap));
                    G4String hname = "p_" + CrProcess;
                    const char* hisname = hname.c_str();
                    TH1F *histo_ne = new TH1F(hisname, "energy of created proton", 200, 0, 100);
                    EProtonhistosbyproc[VolumeName].insert(std::make_pair(CrProcess, histo_ne));
                    EProtonhistosbyproc[VolumeName].at(CrProcess)->Fill(aTrack->GetKineticEnergy());
                } else if (EProtonhistosbyproc[VolumeName].find(CrProcess) == EProtonhistosbyproc[VolumeName].end()) {
                    G4String hname = "p_" + CrProcess;
                    const char* hisname = hname.c_str();
                    TH1F *histo_ne = new TH1F(hisname, "energy of created proton", 200, 0, 100);
                    EProtonhistosbyproc[VolumeName].insert(std::make_pair(CrProcess, histo_ne));
                    EProtonhistosbyproc[VolumeName].at(CrProcess)->Fill(aTrack->GetKineticEnergy());
                } else {
                    EProtonhistosbyproc[VolumeName].at(CrProcess)->Fill(aTrack->GetKineticEnergy());
                }

            }

            if (pname = "p_ev") {
                EP_ev_protonhisto->Fill(aTrack->GetKineticEnergy());
                G4String CrProcess = aTrack->GetCreatorProcess()->GetProcessName();
                VolumeDirset[VolumeName]->cd();
                if (EP_ev_protonhistosbyproc.find(VolumeName) == EP_ev_protonhistosbyproc.end()) {
                    std::map<G4String, TH1F*> tmpmap;
                    EP_ev_protonhistosbyproc.insert(std::make_pair(VolumeName, tmpmap));
                    G4String hname = "p_ev_" + CrProcess;
                    const char* hisname = hname.c_str();
                    TH1F *histo_ne = new TH1F(hisname, "energy of created proton", 200, 0, 20 * CLHEP::MeV);
                    EP_ev_protonhistosbyproc[VolumeName].insert(std::make_pair(CrProcess, histo_ne));
                    EP_ev_protonhistosbyproc[VolumeName].at(CrProcess)->Fill(aTrack->GetKineticEnergy());
                } else if (EP_ev_protonhistosbyproc[VolumeName].find(CrProcess) == EP_ev_protonhistosbyproc[VolumeName].end()) {
                    G4String hname = "p_ev_" + CrProcess;
                    const char* hisname = hname.c_str();
                    TH1F *histo_ne = new TH1F(hisname, "energy of created proton", 200, 0, 20 * CLHEP::MeV);
                    EP_ev_protonhistosbyproc[VolumeName].insert(std::make_pair(CrProcess, histo_ne));
                    EP_ev_protonhistosbyproc[VolumeName].at(CrProcess)->Fill(aTrack->GetKineticEnergy());
                } else {
                    EP_ev_protonhistosbyproc[VolumeName].at(CrProcess)->Fill(aTrack->GetKineticEnergy());
                }

            }

            if (pname = "p_sp") {

                EP_sp_protonhisto->Fill(aTrack->GetKineticEnergy());
                G4String CrProcess = aTrack->GetCreatorProcess()->GetProcessName();
                VolumeDirset[VolumeName]->cd();
                if (EP_sp_protonhistosbyproc.find(VolumeName) == EP_sp_protonhistosbyproc.end()) {
                    std::map<G4String, TH1F*> tmpmap;
                    EP_sp_protonhistosbyproc.insert(std::make_pair(VolumeName, tmpmap));
                    G4String hname = "p_sp_" + CrProcess;
                    const char* hisname = hname.c_str();
                    TH1F *histo_ne = new TH1F(hisname, "energy of created proton", 200, 0, 1000 * CLHEP::MeV);
                    EP_sp_protonhistosbyproc[VolumeName].insert(std::make_pair(CrProcess, histo_ne));
                    EP_sp_protonhistosbyproc[VolumeName].at(CrProcess)->Fill(aTrack->GetKineticEnergy());
                } else if (EP_sp_protonhistosbyproc[VolumeName].find(CrProcess) == EP_sp_protonhistosbyproc[VolumeName].end()) {
                    G4String hname = "p_sp_" + CrProcess;
                    const char* hisname = hname.c_str();
                    TH1F *histo_ne = new TH1F(hisname, "energy of created proton", 200, 0, 1000 * CLHEP::MeV);
                    EP_sp_protonhistosbyproc[VolumeName].insert(std::make_pair(CrProcess, histo_ne));
                    EP_sp_protonhistosbyproc[VolumeName].at(CrProcess)->Fill(aTrack->GetKineticEnergy());
                } else {
                    EP_sp_protonhistosbyproc[VolumeName].at(CrProcess)->Fill(aTrack->GetKineticEnergy());
                }

            }

            if (pname = "p_he") {
                EP_he_protonhisto->Fill(aTrack->GetKineticEnergy());
                G4String CrProcess = aTrack->GetCreatorProcess()->GetProcessName();
                VolumeDirset[VolumeName]->cd();
                if (EP_he_protonhistosbyproc.find(VolumeName) == EP_he_protonhistosbyproc.end()) {
                    std::map<G4String, TH1F*> tmpmap;
                    EP_he_protonhistosbyproc.insert(std::make_pair(VolumeName, tmpmap));
                    G4String hname = "p_he_" + CrProcess;
                    const char* hisname = hname.c_str();
                    TH1F *histo_ne = new TH1F(hisname, "energy of created proton", 200, 0, 10000 * CLHEP::MeV);
                    EP_he_protonhistosbyproc[VolumeName].insert(std::make_pair(CrProcess, histo_ne));
                    EP_he_protonhistosbyproc[VolumeName].at(CrProcess)->Fill(aTrack->GetKineticEnergy());
                } else if (EP_he_protonhistosbyproc[VolumeName].find(CrProcess) == EP_he_protonhistosbyproc[VolumeName].end()) {
                    G4String hname = "p_he_" + CrProcess;
                    const char* hisname = hname.c_str();
                    TH1F *histo_ne = new TH1F(hisname, "energy of created proton", 200, 0, 10000 * CLHEP::MeV);
                    EP_he_protonhistosbyproc[VolumeName].insert(std::make_pair(CrProcess, histo_ne));
                    EP_he_protonhistosbyproc[VolumeName].at(CrProcess)->Fill(aTrack->GetKineticEnergy());
                } else {
                    EP_he_protonhistosbyproc[VolumeName].at(CrProcess)->Fill(aTrack->GetKineticEnergy());
                }
            }
        }
        if (abs(charge) != 0.0) {
            G4double beta = aTrack->GetVelocity() / c_light;
            G4double BetaInverse = 1. / beta;
            G4String particleType = aTrack->GetDefinition()->GetParticleName();
            G4String fragment = "Fragment";
            if (aTrack->GetParticleDefinition()->GetParticleType() == "nucleus" && aTrack->GetParticleDefinition()->GetParticleSubType() == "generic") {
                particleType = fragment;
            }
            VolumeDirset[VolumeName]->cd();
            if (BetaHistosbypart.find(VolumeName) == BetaHistosbypart.end()) {
                std::map<G4String, TH1F*> tmpmap;
                BetaHistosbypart.insert(std::make_pair(VolumeName, tmpmap));
                const char* hisname = particleType.c_str();
                TH1F *histo_beta = new TH1F(hisname, "beta of created particles", 100, 0, 1.);
                BetaHistosbypart[VolumeName].insert(std::make_pair(particleType, histo_beta));
                BetaHistosbypart[VolumeName].at(particleType)->Fill(beta);
            } else if (BetaHistosbypart[VolumeName].find(particleType) == BetaHistosbypart[VolumeName].end()) {
                const char* hisname = particleType.c_str();
                TH1F *histo_beta = new TH1F(hisname, "beta of created particles", 100, 0, 1.);
                BetaHistosbypart[VolumeName].insert(std::make_pair(particleType, histo_beta));
                BetaHistosbypart[VolumeName].at(particleType)->Fill(beta);
            } else {
                BetaHistosbypart[VolumeName].at(particleType)->Fill(beta);
            }
        }
     */
}
//#endif
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void StackingAction::NewStage() {

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void StackingAction::PrepareNewEvent() {

}

void StackingAction::BeginofEvent() {
    /*
        Particles.clear();
        Processes.clear();
     */
}

void StackingAction::EndofEvent() {
    //
    // note 0 entries are not accounted for (needs to be fixed) 
    //
    /*
    std::map<G4String, std::map<G4String, G4int> >::iterator piter; // iterator over Volumes
    for (piter = Particles.begin(); piter != Particles.end(); ++piter) {
        if (NHistosbypart.find((*piter).first) == NHistosbypart.end()) {
            std::map<G4String, TH1F*> tmpmap;
            NHistosbypart.insert(std::make_pair((*piter).first, tmpmap));
        }
        std::map<G4String, G4int>::iterator pariter; // iterator over particles
        for (pariter = (*piter).second.begin(); pariter != (*piter).second.end(); ++pariter) {
            if (NHistosbypart[(*piter).first].find((*pariter).first) == NHistosbypart[(*piter).first].end()) {
                VolumeDirset[(*piter).first]->cd();
                G4String hname = "N_" + (*pariter).first;
                const char* hisname = hname.c_str();
                TH1F *histo_N = new TH1F(hisname, "Nr. of created particles", 100, 0, 2000.);
                NHistosbypart[(*piter).first].insert(std::make_pair((*pariter).first, histo_N));
                NHistosbypart[(*piter).first].at((*pariter).first)->Fill((*pariter).second);
            } else {
                NHistosbypart[(*piter).first].at((*pariter).first)->Fill((*pariter).second);
            }
        }
    }
    std::map<G4String, std::map<G4String, G4int> >::iterator viter; // iterator over Volumes
    for (viter = Processes.begin(); viter != Processes.end(); ++viter) {
        if (NHistosbyproc.find((*viter).first) == NHistosbyproc.end()) {
            std::map<G4String, TH1F*> tmpmap;
            NHistosbyproc.insert(std::make_pair((*viter).first, tmpmap));
        }
        std::map<G4String, G4int>::iterator partiter; // iterator over particles
        for (partiter = (*viter).second.begin(); partiter != (*viter).second.end(); ++partiter) {
            if (NHistosbyproc[(*viter).first].find((*partiter).first) == NHistosbyproc[(*viter).first].end()) {
                VolumeDirset[(*viter).first]->cd();
                G4String hname = "P_" + (*partiter).first;
                const char* hisname = hname.c_str();
                TH1F *histo_P = new TH1F(hisname, "Nr. of processes ", 100, 0, 2000.);
                NHistosbyproc[(*viter).first].insert(std::make_pair((*partiter).first, histo_P));
                NHistosbyproc[(*viter).first].at((*partiter).first)->Fill((*partiter).second);
            } else {
                NHistosbyproc[(*viter).first].at((*partiter).first)->Fill((*partiter).second);
            }
        }
    }
     */
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void StackingAction::Print() {

    G4cout << "===================================================" << G4endl;
    G4cout << " StackingAction configuration:      " << G4endl;
    G4cout << " Kill Pi0s :                        " << killPi0 << G4endl;
    G4cout << " Kill etas :                        " << killeta << G4endl;
    G4cout << " Kill Gammas from neutron Capture:  " << killGammafromnCapture << G4endl;
    G4cout << "===================================================" << G4endl;
}

StackingAction* StackingAction::getInstance() {
    if (instance == 0) instance = new StackingAction();
    return instance;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
