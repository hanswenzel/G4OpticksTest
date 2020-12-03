
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "PhotonHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

G4ThreadLocal G4Allocator<PhotonHit>* PhotonHitAllocator = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhotonHit::PhotonHit()
: G4VHit(),
id(0),
pid(0),
wavelength(0),
time(0),
position(0),
direction(0),
polarization(0) {
}

void PhotonHit::SetPolarization(G4ThreeVector polarization) {
    this->polarization = polarization;
}

G4ThreeVector PhotonHit::GetPolarization() const {
    return polarization;
}

void PhotonHit::SetDirection(G4ThreeVector direction) {
    this->direction = direction;
}

G4ThreeVector PhotonHit::GetDirection() const {
    return direction;
}

void PhotonHit::SetPosition(G4ThreeVector position) {
    this->position = position;
}

G4ThreeVector PhotonHit::GetPosition() const {
    return position;
}

void PhotonHit::SetTime(G4double time) {
    this->time = time;
}

G4double PhotonHit::GetTime() const {
    return time;
}

void PhotonHit::SetWavelength(G4double wavelength) {
    this->wavelength = wavelength;
}

void PhotonHit::SetPid(unsigned pid) {
    this->pid = pid;
}

unsigned PhotonHit::GetPid() const {
    return pid;
}

void PhotonHit::SetId(unsigned id) {
    this->id = id;
}

unsigned PhotonHit::GetId() const {
    return id;
}

PhotonHit::PhotonHit(unsigned iid,
        unsigned ipid,
        G4double iwavelength,
        G4double itime,
        G4ThreeVector iposition,
        G4ThreeVector idirection,
        G4ThreeVector ipolarization) : G4VHit() {
    id = iid;
    pid = ipid;
    wavelength = iwavelength;
    time = itime;
    position = iposition;
    direction = idirection;
    polarization = ipolarization;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhotonHit::~PhotonHit() {
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhotonHit::PhotonHit(const PhotonHit& right)
: G4VHit() {
    id = right.id;
    pid = right.pid;
    wavelength = right.wavelength;
    time = right.time;
    position = right.position;
    direction = right.direction;
    polarization = right.polarization;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const PhotonHit& PhotonHit::operator=(const PhotonHit& right) {
    id = right.id;
    pid = right.pid;
    wavelength = right.wavelength;
    time = right.time;
    position = right.position;
    direction = right.direction;
    polarization = right.polarization;
    return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool PhotonHit::operator==(const PhotonHit& right) const {
    return (this == &right) ? true : false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhotonHit::Draw() {
    G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();

    if (pVVisManager) {
        G4Circle circle(position);
        circle.SetScreenSize(2.);
        circle.SetFillStyle(G4Circle::filled);
        G4Colour colour(1., 0., 0.);
        G4VisAttributes attribs(colour);
        circle.SetVisAttributes(attribs);
        pVVisManager->Draw(circle);
    }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhotonHit::Print() {
    G4cout << "id: " << id
            << " pid: " << pid
            << " wavelength: " << wavelength
            << " time: " << time
            << G4endl;
    //    position.
    //    G4ThreeVector position;
    //    G4ThreeVector direction;
    //    G4ThreeVector polarization;
    //  G4cout << "  trackID: " << fTrackID << "  chamberNb: " << fChamberNb
    //          << "  wavelength deposit[MeV]: " << fEdep
    //          << "  position[mm]: " << fPos << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

