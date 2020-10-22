
#include "TROOT.h"
#include "TFile.h"
#include "TSystem.h"
#include "TKey.h"
//
#include "lArTPCHit.hh"

int main(int argc,char** argv) 
{
  // initialize ROOT
  TSystem ts;
  gSystem->Load("libG4OpticksTestClassesDict");
  if(argc<2) G4cout << "Missing name of the file to read!" << G4endl;
 
  TFile fo(argv[1]);
   
  std::vector<lArTPCHit*>* hits;
  fo.GetListOfKeys()->Print();
 
  TIter next(fo.GetListOfKeys());
  TKey *key;
  //double tot_en;
  while ((key=(TKey*)next()))
  {
    fo.GetObject(key->GetName(), hits);
 
    //tot_en = 0;
    G4cout << "Collection: " << key->GetName() << G4endl;
    G4cout << "Number of hits: " << hits->size() << G4endl;
    for (size_t i=0;i!=hits->size();i++)
    {
      (*hits)[i]->Print();
    }         
  }
}

