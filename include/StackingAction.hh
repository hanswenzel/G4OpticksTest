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
    static StackingAction* instance;
    void FillHistos(const G4Track* aTrack);
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif

