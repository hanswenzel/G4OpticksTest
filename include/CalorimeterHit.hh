// Calorimeter Art Hits  

#ifndef CALORIMETERHIT_HH
#define CALORIMETERHIT_HH

#include <vector>

class CalorimeterHit {
private:
    int ID;
    double Edep;
    double em_Edep;
    double nonem_Edep;
    double xpos;
    double ypos;
    double zpos;
    double time;

    // Default constructor
public:

    CalorimeterHit() {
    }

    // Hide the following from Root
#ifndef __GCCXML__

    CalorimeterHit(int id, double edep, double emedep, double nonemdep, double xp, double yp, double zp, double t) :
    ID(id),
    Edep(edep),
    em_Edep(emedep),
    nonem_Edep(nonemdep),
    xpos(xp),
    ypos(yp),
    zpos(zp),
    time(t) {
    }

    void SetID(int id) {
        ID = id;
    };

    void SetEdep(double de) {
        Edep = de;
    };

    void Setem_Edep(double de) {
        em_Edep = de;
    };

    void Setnonem_Edep(double de) {
        nonem_Edep = de;
    };

    void SetXpos(double x) {
        xpos = x;
    };

    void SetYpos(double y) {
        xpos = y;
    };

    void SetZpos(double z) {
        xpos = z;
    };

    void SetTime(double t) {
        time = t;
    };

    int GetID() const {
        return ID;
    };

    double GetEdep() const {
        return Edep;
    };

    double GetEdepEM() const {
        return em_Edep;
    };

    double GetEdepnonEM() const {
        return nonem_Edep;
    };

    double GetXpos() const {
        return xpos;
    };

    double GetYpos() const {
        return ypos;
    };

    double GetZpos() const {
        return zpos;
    };

    double GetTime() const {
        return time;
    };

#endif

};

typedef std::vector<CalorimeterHit> CalorimeterHitCollection;

#endif
