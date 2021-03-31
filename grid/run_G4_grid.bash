#!/bin/bash
# 
# File:   run_G4_grid.bash
# Author: wenzel
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
#echo "Args" "$@"
echo "Nr of Args" "$#" 
if [[ "$#" -ne 12 ]]; then
    echo " script needs 12 input variables"
    exit
fi
echo " submitting process "  ${2} "to the grid"
echo start now
/bin/date
pwd
SEED=$((${1} + ${2})) 
echo "seed $SEED" 
Cluster=$1
Process=$2 
Particle=${3}
echo $Cluster
echo $Process
echo ${Particle} 
Energy=${4}
echo $Energy
NRofEvents=${5}
xposition=${6} 
yposition=${7} 
zposition=${8}  
xdirection=${9} 
ydirection=${10} 
zdirection=${11} 
PHYSLIST=${12} 
#
FILENAME=/data2/wenzel/G4_data/PBWO_${PHYSLIST}_${Particle}_${Energy}_${xposition}_${Cluster}_${Process}_hits.root
echo $FILENAME
echo $PHYSLIST
echo start
/bin/date
cd ${_CONDOR_SCRATCH_DIR} 
pwd
#echo Particle ${Particle}
printenv
source /data2/wenzel/gputest1_10.7.p01/setup_opticks.sh
export LD_LIBRARY_PATH=/data2/wenzel/gputest1_10.7.p01/G4OpticksTest-install/bin/:$LD_LIBRARY_PATH
#cd /data2/wenzel/gputest10/G4OpticksTest-install/bin

/bin/cat > pip_IO_DR2.mac << EOF
/run/initialize 
#
#
#/process/inactivate Scintillation
/process/optical/scintillation/setStackPhotons false
#
# the Cerenkov process is needed even when we run on GPU (to get the number of photons to be produced) but we don't put optical photons on the stack
#
/process/activate  Cerenkov 
/process/optical/cerenkov/verbose 0
/process/optical/cerenkov/setStackPhotons false
/run/physicsModified
#
/run/initialize 
/random/setSeeds ${SEED} ${SEED}
/G4OpticksTest/FileName ${FILENAME}
/G4OpticksTest/writeHits true 
/G4OpticksTest/enable_opticks false
/gun/particle ${Particle}
/gun/direction ${xdirection} ${ydirection} ${zdirection}
/gun/position  ${xposition}  ${yposition}  ${zposition} cm
/gun/energy ${Energy} GeV
/run/beamOn ${NRofEvents}
EOF
#/bin/more run_G4.mac
cp  /data2/wenzel/gputest1_10.7.p01/G4OpticksTest/macros/*.mac .
/data2/wenzel/gputest1_10.7.p01/G4OpticksTest-install/bin/G4OpticksTest -gdml /data2/wenzel/gputest10/G4OpticksTest-install/bin/crystalcal_pbwo.gdml -pl ${PHYSLIST} -macro pip_IO_DR2.mac
/bin/date
