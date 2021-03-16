#!/bin/bash
# 
# File:   my_G4.bash
# Author: wenzel
#
# Created on Feb 27, 2021, 12:32:45 PM
#
############################################################################
# $1  = Nr of processes
# $2  = name of Particle
# $3  = Energy of Particle
# $4  = Number of events per process
# $5  = x-position 
# $6  = y-position
# $7  = z-position
# $8  = x-direction 
# $9  = y-direction
# $10 = z-direction
# $11 = GEANT Physics list
#---------------------------------------------------------------------------

if ($#argv < 11) then
    echo " scripts needs 11 input variables"
    exit
endif

echo " submitting: "  ${1} "processes to the grid"
echo start
/bin/date
rm -f  run_G4_grid
cat > run_G4_grid << +EOF
executable = $PWD/run_G4_grid.bash
transfer_executable = true
transfer_output = true
transfer_error = true
transfer_executable = true
environment = "ClusterProcess=\$(Cluster)-\$(Process)"
log = ./log/G4_grid.log.\$(Cluster).\$(Process)
notification = NEVER
output = ./stdout/G4_grid.out.\$(Cluster).\$(Process)
error = ./stderr/G4_grid.err.\$(Cluster).\$(Process)
stream_output = false
stream_error = false
ShouldTransferFiles = YES
WhenToTransferOutput = ON_EXIT
globusrsl = (maxwalltime=90000)(jobtype=single)
Arguments = \$(Cluster) \$(Process) '${2}' '${3}' '${4}' '${5}' '${6}' '${7}' '${8}' '${9}' '${10}' '${11}' 

queue ${1}
+EOF

#condor_submit run_G4_grid