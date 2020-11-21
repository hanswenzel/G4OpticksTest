
#include "TROOT.h"
#include "TFile.h"
#include "TSystem.h"
#include "TKey.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
//
#include "Event.hh"
#include "lArTPCHit.hh"
#include "PhotonHit.hh"
using namespace std;

/*
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    return split(s, delim, elems);
}
 */
int main(int argc, char** argv) {
    // initialize ROOT
    TSystem ts;
    gSystem->Load("libG4OpticksTestClassesDict");
    //if (argc < 2) cout << "Missing name of the file to read!" << endl;

    if (argc < 3) {
        G4cout << "Program requires 2 arguments: name of input file, name of output file" << G4endl;
        exit(1);
    }
    TFile* outfile = new TFile(argv[2], "RECREATE");
    outfile->cd();
    TH1F* wl = new TH1F("wl", "wavelength", 100, 0.0, 1000.);
    TH2F* pos = new TH2F("position", "position of charge deposit", 100, -5., 5., 400, 0, 500);
    TH2F* pos2 = new TH2F("pposition", "position of Photon Hits", 400, -500., 500., 400, -500, 500);
    TFile fo(argv[1]);

    std::vector<lArTPCHit*>* hits;
    std::vector<PhotonHit*>* hitsp;
    fo.GetListOfKeys()->Print();

    Event *event = new Event();
    TTree *Tevt = (TTree*) fo.Get("Events");
    Tevt->SetBranchAddress("event.", &event);
    TBranch* fevtbranch = Tevt->GetBranch("event.");
    Int_t nevent = fevtbranch->GetEntries();
    cout << " Nr. of Events:  " << nevent << endl;
    for (Int_t i = 0; i < nevent; i++) {
        fevtbranch->GetEntry(i);
        std::map<G4String, std::vector<G4VHit*> >* hcmap = event->GetHCMap();
        std::map<G4String, std::vector<G4VHit*> >::iterator hciter;
        cout << " Number of Hit collections:  " << hcmap->size() << endl;
        for (hciter = hcmap->begin(); hciter != hcmap->end(); hciter++) {
            std::vector<G4VHit*> hits = (*hciter).second;
            //std::vector<G4String> hits;
            G4int NbHits = hits.size();
            cout << (*hciter).first << " Number of Hits:  " << NbHits << endl;

            if ((*hciter).first == "PhotonDetector") {
                for (G4int ii = 0; ii < NbHits; ii++) {
                    PhotonHit* pHit = dynamic_cast<PhotonHit*> (hits[ii]);
                    wl->Fill(pHit->GetWavelength());   
                    pos2 ->Fill(pHit->GetPosition().getY(),pHit->GetPosition().getZ());
                }
            }
            if ((*hciter).first == "Obj_lArTPC_HC") {
                for (G4int ii = 0; ii < NbHits; ii++) {
                    lArTPCHit* tpcHit = dynamic_cast<lArTPCHit*> (hits[ii]);
                    pos->Fill(tpcHit->GetPosY(), tpcHit->GetPosZ());

                    //wl->Fill(pHit->GetWavelength());
                }
            }
        }
        outfile->Write();
    }








}

