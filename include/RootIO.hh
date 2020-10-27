#ifndef ROOTIO_HH
#define ROOTIO_HH

// Include files
#include "TROOT.h"
#include "TFile.h"
#include "TSystem.h"
#include "PhotonHit.hh"
#include "lArTPCHit.hh"

/// Root IO implementation for the persistency example

class RootIO {
public:
    virtual ~RootIO();

    static RootIO* GetInstance();
    void Write(std::vector<lArTPCHit*>*);
    void Write(std::vector<PhotonHit*>*);
    void Close();

protected:
    RootIO();

private:

    TFile* fFile;
    int fNevents;

};
#endif /* ROOTIO_HH */

