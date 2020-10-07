# G4OpticksTest
Example that demonstrates how to use opticks from within Geant4 for the creation and propagation of optical photons. This requires the opticks environment to be set up properly. (for instructions how to install opticks see e.g. https://cdcvs.fnal.gov/redmine/projects/g4gpu/wiki/Installation_on_the_LQ_cluster . At the moment we use the following external packages and versions thereof:  

nvidia Optix 6.5

nvidia cuda 10.1

geant4 10.4.p02

boost 1.61.0

xercesc 3.2.2

openmesh 6.3

glew 1.13.0

glfw 3.1.1

cmake 3.14.1




To get started : 
git clone https://github.com/hanswenzel/G4OpticksTest.git

cd G4OpticksTest/

now have a look at set_env_lq.sh and change the variables on the top to point to the opticks installation you want to use and change it accordingly. The provided set_env_lq.sh gives an example.  After you changed it:

cp set_env_lq.sh set_env.sh

source setup_opticks.sh 

cd ../

mkdir G4OpticksTest-build

cd G4OpticksTest-build
<p>
cmake   -DCMAKE_BUILD_TYPE=Debug \
<br>-DCMAKE_PREFIX_PATH="${LOCAL_BASE}/opticks/externals;${LOCAL_BASE}/opticks" \
<br>-DOPTICKS_PREFIX=${LOCAL_BASE}/opticks \
<br>-DCMAKE_MODULE_PATH=${OPTICKS_HOME}/cmake/Modules \
<br>-DCMAKE_INSTALL_PREFIX=../G4OpticksTest-install \
<br>../G4OpticksTest
</p>
make install

cd ../G4OpticksTest-install/bin

./G4OpticksTest G4Opticks.gdml muon.mac
