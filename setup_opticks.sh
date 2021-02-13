#------------------------------------------------------------------------------------
#SETUPDIR="/home/wenzel/gputest" 
#source /home/wenzel/gputest/set_env.sh
#------------------------------------------------------------------------------------
export WORK_DIR=/data2/wenzel/gputest5

export OptiX_INSTALL_DIR=/home/wenzel/NVIDIA-OptiX-SDK-6.5.0-linux64
export OPTICKS_COMPUTE_CAPABILITY=75
export CUDA_INSTALL_DIR=/usr/local/cuda-11.0
export CUDA_SAMPLES=/usr/local/cuda-11.0/samples
#export G4INSTALL=/data2/wenzel/geant4.10.07-install 
#export G4_INSTALL=/data2/wenzel/geant4.10.07-install
export G4INSTALL=/home/wenzel/geant4.10.06.p03_clhep-install
export G4_INSTALL=/home/wenzel/geant4.10.06.p03_clhep-install
export LOCAL_BASE=${WORK_DIR}/local
export CMAKE_PREFIX_PATH=${G4_INSTALL}:${LOCAL_BASE}/opticks/externals:${OptiX_INSTALL_DIR}:${WORK_DIR}/opticks/cmake/Modules/:${WORK_DIR}/local/opticks:${WORK_DIR}/local/opticks:${WORK_DIR}/local/opticks/externals/
export PYTHONPATH=$WORK_DIR
export OPTICKS_HOME=${WORK_DIR}/opticks
export PATH=${LOCAL_BASE}/bin:${PATH}
export OPTICKS_PREFIX=${WORK_DIR}/local/opticks                            
export OPTICKS_INSTALL_PREFIX=$LOCAL_BASE/opticks
export OPTICKS_OPTIX_PREFIX=/home/wenzel/NVIDIA-OptiX-SDK-6.5.0-linux64/
export OPTICKS_CUDA_PREFIX=/usr/local/cuda-11.0
#export G4OPTICKS_DEBUG='--rngmax 10'
export OPTICKS_EMBEDDED_COMMANDLINE_EXTRA="--rngmax 100"
#source /home/wenzel/setup/root_setup.sh
opticks-(){ . ${OPTICKS_HOME}/opticks.bash && opticks-env $* ; }
op(){ op.sh $* ; }
o(){ cd $(opticks-home) ; hg st ; }
# make sure to add the compiler options
new=" -fPIC" 
case ":${CXXFLAGS:=$new}:" in
    *:"$new":*)  ;;
    *) CXXFLAGS="$CXXFLAGS:$new"  ;;
esac
new=" -fPIC" 
case ":${CFLAGS:=$new}:" in
    *:"$new":*)  ;;
    *) CFLAGS="$CFLAGS:$new"  ;;
esac
# speed up the make process
new=" -j$(($(grep -c ^processor /proc/cpuinfo) - 1))" 
case ":${MAKEFLAGS:=$new}:" in
    *:"$new":*)  ;;
    *) MAKEFLAGS="$MAKEFLAGS:$new"  ;;
esac
# deal with the $LD_LIBRARYPATH
new=${OptiX_INSTALL_DIR}/lib64/
case ":${LD_LIBRARY_PATH:=$new}:" in
    *:"$new":*)  ;;
    *) LD_LIBRARY_PATH="$new:$LD_LIBRARY_PATH"  ;;
esac
new=${OPTICKS_HOME}/externals/lib
case ":${LD_LIBRARY_PATH:=$new}:" in
    *:"$new":*)  ;;
    *) LD_LIBRARY_PATH="$new:$LD_LIBRARY_PATH"  ;;
esac
new=${CUDA_INSTALL_DIR}/lib64/
case ":${LD_LIBRARY_PATH:=$new}:" in
    *:"$new":*)  ;;
    *) LD_LIBRARY_PATH="$new:$LD_LIBRARY_PATH"  ;;
esac
new=${LOCAL_BASE}/opticks/lib/
case ":${LD_LIBRARY_PATH:=$new}:" in
    *:"$new":*)  ;;
    *) LD_LIBRARY_PATH="$new:$LD_LIBRARY_PATH"  ;;
esac
. ${G4_INSTALL}/bin/geant4.sh
. /data2/wenzel/root_install/bin/thisroot.sh

opticks-
new=${CUDA_INSTALL_DIR}/bin
case ":${PATH:=$new}:" in
    *:"$new":*)  ;;
    *) PATH="$new:$PATH"  ;;
esac
#new=${CUDA_INSTALL_DIR}/NsightCompute-2019.3
#case ":${PATH:=$new}:" in
#    *:"$new":*)  ;;
#    *) PATH="$new:$PATH"  ;;
#esac
new=${OPTICKS_HOME}/bin/
case ":${PATH:=$new}:" in
    *:"$new":*)  ;;
    *) PATH="$new:$PATH"  ;;
esac
new=${OPTICKS_HOME}/ana/
case ":${PATH:=$new}:" in
    *:"$new":*)  ;;
    *) PATH="$new:$PATH"  ;;
esac
new=${LOCAL_BASE}/opticks/lib/
case ":${PATH:=$new}:" in
    *:"$new":*)  ;;
    *) PATH="$new:$PATH"  ;;
esac
new=${CUDA_SAMPLES}/bin/x86_64/linux/release/
case ":${PATH:=$new}:" in
    *:"$new":*)  ;;
    *) PATH="$new:$PATH"  ;;
esac
oinfo-(){
    echo 'LD_LIBRARY_PATH:';
    echo '================';
    echo  ${LD_LIBRARY_PATH}| tr : \\n;
    echo;
    echo 'PATH:';
    echo '=====';
    echo  ${PATH}| tr : \\n;
    echo;
    echo 'CMAKE_PREFIX_PATH:';
    echo '==================';
    echo  ${CMAKE_PREFIX_PATH}| tr : \\n;
    }
dinfo-(){    
    nvidia-smi;
    ${CUDA_SAMPLES}/bin/x86_64/linux/release/deviceQuery
}
#export OPTICKS_KEY=OKX4Test.X4PhysicalVolume.World_PV.b7ef5072d1d43f5b529c0c24d5432671
export OPTICKS_KEY=G4OpticksTest.X4PhysicalVolume.World_PV.f2f063d9ea288eeab99e0b1617699755
