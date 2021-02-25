#!/bin/sh -f
printenv
pwd
cd ${_CONDOR_SCRATCH_DIR}
pwd
#
# This sets up the environment for osg in case we want to
# use grid services like srmcp
#
. /setup.sh
source ${VDT_LOCATION}/setup.sh
printenv
/bin/df
