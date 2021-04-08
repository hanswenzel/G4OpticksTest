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
#include "CalorimeterHit.hh"
#include "DRCalorimeterHit.hh"
using namespace std;

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
    //    TH1F* hedep = new TH1F("energy", "edep", 1100, 0.0, 105000.);
    //TH1F* hnceren = new TH1F("nceren", "nceren", 70000, 0.0, 7000000.);
    TFile fo(argv[1]);
    std::vector<lArTPCHit*>* hits;
    std::vector<PhotonHit*>* hitsp;
    //  avoid unused variable warning
    //    (void) hits;
    //    (void) hitsp;
    fo.GetListOfKeys()->Print();
    Event *event = new Event();
    TTree *Tevt = (TTree*) fo.Get("Events");
    Tevt->SetBranchAddress("event.", &event);
    TBranch* fevtbranch = Tevt->GetBranch("event.");
    Int_t nevent = fevtbranch->GetEntries();
    bool verbose = false;
    if (verbose) cout << " Nr. of Events:  " << nevent << endl;
    double max = 0.;
    double min = 1000000;
    double nmax = 0.;
    double nmin = 1000000000;
    for (Int_t i = 0; i < nevent; i++) {
        fevtbranch->GetEntry(i);
        std::map<G4String, std::vector<G4VHit*> > *hcmap = event->GetHCMap();
        std::map<G4String, std::vector<G4VHit*> >::iterator hciter;
        cout << "Number of Hit collections:  " << hcmap->size() << endl;
        for (hciter = hcmap->begin(); hciter != hcmap->end(); hciter++) {
            cout << (*hciter).first << endl;
            std::vector<G4VHit*> hits = (*hciter).second;
            //std::vector<G4String> hits;
            G4int NbHits = hits.size();
            if ((*hciter).first == "CalorimeterVolume_DRCalorimeter_HC") {
                for (G4int ii = 0; ii < NbHits; ii++) {
                    DRCalorimeterHit* drcaloHit = dynamic_cast<DRCalorimeterHit*> (hits.at(ii));
                    const double ed = drcaloHit->GetEdep();
                    if (ed > max) max = ed;
                    if (ed < min) min = ed;
                    const unsigned int nceren = drcaloHit->GetNceren();
                    if (nceren > nmax) nmax = nceren;
                    if (nceren < nmin) nmin = nceren;
                }
            }
        }
    }
    outfile->cd();
    TH1F* hedep = new TH1F("energy", "edep", 100, min, max);
    TH1F* hnceren = new TH1F("nceren", "nceren", 100, nmin, nmax);
    for (Int_t i = 0; i < nevent; i++) {
        fevtbranch->GetEntry(i);
        std::map<G4String, std::vector<G4VHit*> >* hcmap = event->GetHCMap();
        std::map<G4String, std::vector<G4VHit*> >::iterator hciter;
        for (hciter = hcmap->begin(); hciter != hcmap->end(); hciter++) {
            std::vector<G4VHit*> hits = (*hciter).second;
            G4int NbHits = hits.size();
            cout << "Number of Hits   :  " << hits.size() << endl;
            if ((hciter)->first == "CalorimeterVolume_DRCalorimeter_HC") {
                for (G4int ii = 0; ii < NbHits; ii++) {
                    DRCalorimeterHit* drcaloHit = dynamic_cast<DRCalorimeterHit*> (hits.at(ii));
                    hedep->Fill(drcaloHit->GetEdep());
                    hnceren->Fill(drcaloHit->GetNceren());
                }
            }
            if ((hciter)->first == "Det_Photondetector") {
                for (G4int ii = 0; ii < NbHits; ii++) {
                    PhotonHit* photonHit = dynamic_cast<PhotonHit*> (hits.at(ii));
                    cout << "X: " << photonHit->GetPosition().getX() << endl;
                    cout << "Y: " << photonHit->GetPosition().getY() << endl;
                    cout << "Z: " << photonHit->GetPosition().getZ() << endl;
                }
            }
        }
    }
    //hedep->Fit("gaus");
    //hnceren->Fit("gaus");
    outfile->Write();
}

