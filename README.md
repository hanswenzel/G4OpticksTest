# G4OpticksTest
Example that demonstrates how to use opticks from within Geant4 for the creation and propagation of optical photons. This requires the opticks environment to be set up properly. (for instructions how to install opticks see e.g. https://cdcvs.fnal.gov/redmine/projects/g4gpu/wiki/Installation_on_the_LQ_cluster . At the moment we use the following external packages and versions thereof:  

- nvidia Optix 6.5
- nvidia cuda 11.0
- nvidia driver 450.80.02
- geant4 10.6.p03  (with minor patch in G4Cerenkov)
- boost 1.71.0
- xercesc 3.2.2
- openmesh 6.3
- glew 1.13.0
- glfw 3.1.1
- cmake 3.18.4

To get started : 

```bash
git clone https://github.com/hanswenzel/G4OpticksTest.git
cd G4OpticksTest/

# now have a look at set_env_lq.sh and change the variables on the top to point to the opticks installation you want to use and change it accordingly.
# The provided set_env_lq.sh gives an example.
# After you changed it:

cp set_env_lq.sh set_env.sh
source setup_opticks.sh 
cd ../
mkdir G4OpticksTest-build
cd G4OpticksTest-build

cmake -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_PREFIX_PATH="${LOCAL_BASE}/opticks/externals;${LOCAL_BASE}/opticks" \
  -DOPTICKS_PREFIX=${LOCAL_BASE}/opticks \
  -DCMAKE_MODULE_PATH=${OPTICKS_HOME}/cmake/Modules \
  -DCMAKE_INSTALL_PREFIX=../G4OpticksTest-install \
  ../G4OpticksTest

make install
cd ../G4OpticksTest-install/bin
export OPTICKS_EMBEDDED_COMMANDLINE_EXTRA="--rngmax 10"
time ./G4OpticksTest G4Opticks_50000.gdml muon_IO.mac
```
