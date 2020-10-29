#include <sstream>

#include "RootIO.hh"
//
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4EventManager.hh"
#include "G4Event.hh"
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

static RootIO* instance = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RootIO::RootIO() : fNevents(0) {
    treeinitialized = false;
    evtinitialized = false;
    // initialize ROOT
    TSystem ts;
    gSystem->Load("libG4OpticksTestClassesDict");
    fFile = new TFile("hits.root", "RECREATE");
    TTree::SetMaxTreeSize(1000 * Long64_t(2000000000));
    // Create a ROOT Tree and one superbranch
    ftree = new TTree("Events", "ROOT tree containing Hit collections");
    G4cout << "ftree: " << ftree << G4endl;
    ftree->SetAutoSave(1000000000); // autosave when 1 Gbyte written
    //if (!treeinitialized) {
    Int_t branchStyle = 1;
    TTree::SetBranchStyle(branchStyle);


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RootIO::~RootIO() {
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RootIO* RootIO::GetInstance() {
    if (instance == 0) {
        instance = new RootIO();
    }
    return instance;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/*
void RootIO::Write(std::vector<lArTPCHit*>* hcont) {
    fNevents++;
    std::ostringstream os;
    os << fNevents;
    std::string stevt = "Event_" + os.str();
    const char* chevt = stevt.c_str();
    G4cout << "writing " << stevt << G4endl;
    fFile->WriteObject(hcont, chevt);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RootIO::Write(std::vector<PhotonHit*>* hcont) {
    fNevents++;
    std::ostringstream os;
    os << fNevents;
    std::string stevt = "Event_" + os.str();
    const char* chevt = stevt.c_str();
    G4cout << "writing " << stevt << G4endl;
    fFile->WriteObject(hcont, chevt);
}
 */
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RootIO::Write(Event* fevent) {

    if (!evtinitialized) {
        Int_t bufsize = 64000;
        fevtbranch = ftree->Branch("event.", &fevent, bufsize, 0);
        fevtbranch->SetAutoDelete(kFALSE);
        evtinitialized = true;
        /*
        std::map<G4String, std::map<G4String, products> >* pmap = fevent->Getprocessmap();
        std::map<G4String, std::map<G4String, products> >::iterator pmap_iter;
        for (pmap_iter = pmap->begin(); pmap_iter != pmap->end(); pmap_iter++) {
            G4cout << "(*pmap_iter).first: " << (*pmap_iter).first << "(*pmap_iter).second.size():    " << (*pmap_iter).second.size() << G4endl;
            std::map<G4String, products>::iterator proc_iter;
            for (proc_iter = (*pmap_iter).second.begin(); proc_iter != (*pmap_iter).second.end(); proc_iter++) {
                G4cout << "pname:  " << (*proc_iter).first
                        << "  nr.:    " << (*proc_iter).second.NParticles
                        << "  kinE.:    " << (*proc_iter).second.kinE
                        << "  totE.:    " << (*proc_iter).second.totE
                        << G4endl;
            }
        }
         */
    }


    fFile = ftree->GetCurrentFile(); //just in case we switched to a new file
    fnb += ftree->Fill();
    fFile->Write("", TObject::kOverwrite);
    //    fevts++;
    //   G4cout << "fnb: " << fnb << "   " << fevts << G4endl;
}

void RootIO::Close() {
    fFile->Close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

