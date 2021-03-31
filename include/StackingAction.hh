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
#ifndef StackingAction_H
#define StackingAction_H 1

#include "globals.hh"
#include "G4UserStackingAction.hh"
#include "StackingActionMessenger.hh"
#define G4ANALYSIS_USE TRUE
#ifdef G4ANALYSIS_USE
//#include "CaTS_Analysis.hh"
//#include "TH1.h"
#endif
#include <map>
#include <set>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class StackingAction : public G4UserStackingAction {
public:
    StackingAction();
    ~StackingAction();

    G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
    void NewStage();
    void PrepareNewEvent();

    void SetkillPi0(G4bool kPi0) {
        killPi0 = kPi0;
    };

    void Setkilleta(G4bool keta) {
        killeta = keta;
    };

    void SetkillGammafromnCapture(G4bool kGamma) {
        killGammafromnCapture = kGamma;
    };
    void Print();
    void BeginRun();
    void BeginofEvent();
    void EndofEvent();
    static StackingAction* getInstance();
private:
    G4bool killPi0;
    G4bool killeta;
    G4bool killGammafromnCapture;
    StackingActionMessenger* pMessenger;
#ifdef G4ANALYSIS_USE
/*
//    static Analysis* analysis;
    TDirectory *partdir;
    TDirectory *procdir;
    TDirectory *ebypartdir;
    TDirectory *Volumesdir;
    //
    TH1F* histo_beta;
    TH1F* EGammahisto;
    TH1F* ENeutronhisto;
    TH1F* EProtonhisto;
    TH1F* EP_ev_protonhisto;
    TH1F* EP_sp_protonhisto;
    TH1F* EP_he_protonhisto;
    TH1F* CaptureGammahisto;
    //
    // The following histograms are filled for each Volume
    //
    std::map<G4String, std::map<G4String, G4int> >Particles;
    std::map<G4String, std::map<G4String, G4int> >Processes;
    std::map<G4String, std::map<G4String, TH1F*> >NHistosbyproc;
    std::map<G4String, std::map<G4String, TH1F*> >NHistosbypart;
    //
    std::map<G4String, std::map<G4String, TH1F*> > ENeutronhistosbyproc;
    std::map<G4String, std::map<G4String, TH1F*> > EProtonhistosbyproc;
    std::map<G4String, std::map<G4String, TH1F*> > EP_ev_protonhistosbyproc;
    std::map<G4String, std::map<G4String, TH1F*> > EP_sp_protonhistosbyproc;
    std::map<G4String, std::map<G4String, TH1F*> > EP_he_protonhistosbyproc;
    std::map<G4String, std::map<G4String, TH1F*> > BetaHistosbypart;
    //  
    std::set<G4String> Volumeset;
    std::map<G4String, TDirectory *> VolumeDirset;
*/
    static StackingAction* instance;

    void FillHistos(const G4Track* aTrack);
#endif
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif

