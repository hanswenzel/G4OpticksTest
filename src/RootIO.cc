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

RootIO::RootIO():fNevents(0)
{
  // initialize ROOT
  TSystem ts;
  gSystem->Load("libG4OpticksTestClassesDict");

  //gDebug = 1;

  fFile = new TFile("hits.root","RECREATE");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RootIO::~RootIO()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RootIO* RootIO::GetInstance()
{
  if (instance == 0 )
  {
    instance = new RootIO();
  }
  return instance;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RootIO::Write(std::vector<lArTPCHit*>* hcont)
{
  fNevents++;

  std::ostringstream os;
  os << fNevents;
  std::string stevt = "Event_" + os.str(); 
  const char* chevt = stevt.c_str();

  G4cout << "writing " << stevt << G4endl;

  fFile->WriteObject(hcont, chevt);

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RootIO::Close()
{
  fFile->Close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

