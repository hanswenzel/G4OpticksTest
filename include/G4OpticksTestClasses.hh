//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file persistency/P01/include/ExP01Classes.hh
/// \brief Declaration of the classes for generating dictionaries
//
//
#include "G4VHit.hh"
#include "lArTPCHit.hh"
#include "PhotonHit.hh"
#include "InteractionHit.hh"
#include "CalorimeterHit.hh"
#include "DRCalorimeterHit.hh"
#include "TrackerHit.hh"
#include "Event.hh"
Event e;
std::vector<PhotonHit*>p;
std::vector<InteractionHit*>i;
std::vector<lArTPCHit*>a;
std::vector<CalorimeterHit*>c;
std::vector<DRCalorimeterHit*>d;
std::vector<TrackerHit*>t;
std::vector<G4VHit*>vh;
std::map<G4String, std::vector<G4VHit*> > hm; // map of Hit Collections
#undef __G4String