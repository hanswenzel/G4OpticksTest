#!/bin/csh
# 
# File:   run_G4_grid.csh
# Author: wenzel
#
# Created on Feb 25, 2021, 10:02:31 AM
#
# $1 = condor Cluster
# $2 = condor Process
# $3 = name of Particle 
# $4 = Energy of Particle 
# $5 = Number of events
# $6 = x-position 
# $7 = y-position
# $8 = z-position
# $9 = x-direction 
# $10= y-direction
# $11= z-direction
# $12= GEANT Physics list
#--------------------------------------------------------------------------- 
if ($#argv < 12) then
    echo " script needs 12 input variables"
    exit
endif
echo " submitting process "  ${2} "to the grid"
echo start now
/bin/date
pwd
@ SEED         = $1 + $2
set Cluster    = $1
set Process    = $2 
set Particle   = `echo $3  | sed s/\'//g`
set Energy     = `echo $4  | sed s/\'//g`
set NRofEvents = `echo $5  | sed s/\'//g`
set xposition  = `echo $6  | sed s/\'//g`
set yposition  = `echo $7  | sed s/\'//g`
set zposition  = `echo $8  | sed s/\'//g`
set xdirection = `echo $9  | sed s/\'//g`
set ydirection = `echo $10 | sed s/\'//g`
set zdirection = `echo $11 | sed s/\'//g`
setenv PHYSLIST  `echo $12 | sed s/\'//g`
#
set FILENAME=/ilc/sid/wenzel/Grid/G4_data/BGO_${PHYSLIST}_${Particle}_${Energy}_${xposition}_${Cluster}_${Process}_hits.root
set HISTONAME=/ilc/sid/wenzel/Grid/G4_data/BGO_${PHYSLIST}_${Particle}_${Energy}_${xposition}_${Cluster}_${Process}_analysis.root
echo $FILENAME
echo $HISTONAME
echo $PHYSLIST
echo start
/bin/date
cd ${_CONDOR_SCRATCH_DIR} 
echo Particle ${Particle}
setenv ROOTSYS  /grid/app/wenzel/Grid/root-install/
setenv LD_LIBRARY_PATH ${ROOTSYS}/lib:${LD_LIBRARY_PATH}
printenv
#source /grid/app/wenzel/Grid/root-install/bin/thisroot.csh
. /grid/app/wenzel/Grid/geant4.9.5.p01-install/bin/geant4.csh

setenv G4LEVELGAMMADATA /grid/app/wenzel/Grid/geant4.9.5.p01-install/share/Geant4-9.5.1/data/PhotonEvaporation2.2
setenv G4NEUTRONXSDATA /grid/app/wenzel/Grid/geant4.9.5.p01-install/share/Geant4-9.5.1/data/G4NEUTRONXS1.1
setenv G4LEDATA /grid/app/wenzel/Grid/geant4.9.5.p01-install/share/Geant4-9.5.1/data/G4EMLOW6.23
setenv G4NEUTRONHPDATA /grid/app/wenzel/Grid/geant4.9.5.p01-install/share/Geant4-9.5.1/data/G4NDL4.0
setenv G4RADIOACTIVEDATA /grid/app/wenzel/Grid/geant4.9.5.p01-install/share/Geant4-9.5.1/data/RadioactiveDecay3.4
setenv G4ABLADATA /grid/app/wenzel/Grid/geant4.9.5.p01-install/share/Geant4-9.5.1/data/G4ABLA3.0
setenv G4PIIDATA /grid/app/wenzel/Grid/geant4.9.5.p01-install/share/Geant4-9.5.1/data/G4PII1.3
setenv G4REALSURFACEDATA /grid/app/wenzel/Grid/geant4.9.5.p01-install/share/Geant4-9.5.1/data/RealSurface1.0
setenv LD_LIBRARY_PATH /grid/app/wenzel/Grid/G4-build-local/:${LD_LIBRARY_PATH}
printenv 
/bin/cat > /tmp/run_G4.mac << EOF+ 
/G4/random/randomSeed  ${SEED}
/G4/RootIO/Filename ${FILENAME}
/G4/Analysis/Filename ${HISTONAME}
/tracking/verbose 0
/gun/particle ${Particle}
/gun/direction ${xdirection} ${ydirection} ${zdirection}
/gun/position  ${xposition}  ${yposition}  ${zposition}
/gun/energy ${Energy} GeV
/run/beamOn ${NRofEvents}
EOF+

/bin/more run_G4.mac
cp  /grid/app/wenzel/Grid/G4-build-local/vis.mac .
cp  /grid/app/wenzel/Grid/G4-build-local/pythia_event.data .
ls
/grid/app/wenzel/Grid/G4-build-local/G4  /grid/app/wenzel/Grid/G4/gdml/crystalcal_bgo.gdml /tmp/run_G4.mac
/bin/date


