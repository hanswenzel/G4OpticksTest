#!/bin/sh
# 
# File:   scan.sh
# Author: wenzel
#
# Created on Nov 20, 2020, 10:12:41 PM
#
time ./G4OpticksTest G4Opticks_50.gdml muon.mac >& 50.log
time ./G4OpticksTest G4Opticks_100.gdml muon.mac >& 100.log
time ./G4OpticksTest G4Opticks_5000.gdml muon.mac >& 5000.log
#
time ./G4OpticksTest G4Opticks_50.gdml muon_noIO.mac >& 50_noIO.log
time ./G4OpticksTest G4Opticks_100.gdml muon_noIO.mac >& 100_noIO.log
time ./G4OpticksTest G4Opticks_5000.gdml muon_noIO.mac >& 5000_noIO.log