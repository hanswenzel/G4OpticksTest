#ifdef WITH_ROOT
#include <sstream>
#include <cstring>
#include "RootIO.hh"
#include "ConfigurationManager.hh"
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

static RootIO* instance = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RootIO::RootIO() : fNevents(0) {
  //  treeinitialized = false;
    evtinitialized = false;
    TSystem ts;
    gSystem->Load("libG4OpticksTestClassesDict");
    G4String FileName = ConfigurationManager::getInstance()->getfname();
    G4cout<< "Opening File: "<< FileName<< G4endl;
    fFile = new TFile(FileName.c_str(), "RECREATE");
    TTree::SetMaxTreeSize(1000 * Long64_t(2000000000));
    // Create a ROOT Tree and one superbranch
    ftree = new TTree("Events", "ROOT tree containing Hit collections");
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

void RootIO::Write(Event* fevent) {

    if (!evtinitialized) {
        Int_t bufsize = 64000;
        fevtbranch = ftree->Branch("event.", &fevent, bufsize, 0);
        fevtbranch->SetAutoDelete(kFALSE);
        evtinitialized = true;
    }

    fFile = ftree->GetCurrentFile(); //just in case we switched to a new file
    fnb += ftree->Fill();
    fFile->Write("", TObject::kOverwrite);
}

void RootIO::Close() {
    fFile->Close();
}
#endif
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

