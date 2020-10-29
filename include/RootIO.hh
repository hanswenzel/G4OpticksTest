#ifndef ROOTIO_HH
#define ROOTIO_HH

// Include files
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TSystem.h"

#include "PhotonHit.hh"
#include "lArTPCHit.hh"
#include "Event.hh"
/// Root IO implementation for the persistency example

class RootIO {
public:
    virtual ~RootIO();

    static RootIO* GetInstance();
 //   void Write(std::vector<lArTPCHit*>*);
 //   void Write(std::vector<PhotonHit*>*);
    void Write(Event*);

    void Close();

protected:
    RootIO();

private:

    TFile* fFile;
    int fNevents;
    TTree* ftree;
    TBranch* fevtbranch;
    Long64_t fnb;
    bool evtinitialized;
    bool treeinitialized;
};
#endif /* ROOTIO_HH */

