#!/bin/bash
#------------------------------------------------------------------------------------
SETUPDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
source ${SETUPDIR}/set_env.sh
#------------------------------------------------------------------------------------
# if you want to use the directory where the script is script is located
#WORKDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
export LOCAL_BASE=${WORK_DIR}/local
export PYTHONPATH=$WORK_DIR
export OPTICKS_HOME=${WORK_DIR}/opticks
export PATH=${LOCAL_BASE}/bin:${PATH}
#export PKG_CONFIG_PATH=${LOCAL_BASE}/opticks/externals/lib/pkgconfig
export OPTICKS_PREFIX=${WORK_DIR}/local/opticks							
export OPTICKS_INSTALL_PREFIX=$LOCAL_BASE/opticks
# needs to change as we move to a newer version of BOOST
export OPTICKS_BOOST_INCLUDEDIR=${LOCAL_BASE}/opticks/externals/boost/boost_1_61_0/boost/
export OPTICKS_BOOST_LIBDIR=${LOCAL_BASE}/opticks/externals/boost/boost_1_61_0/libs
opticks-(){ . ${OPTICKS_HOME}/opticks.bash && opticks-env $* ; }
#opticks-
#echo  ${LD_LIBRARY_PATH}| tr : \\n;
#echo  ${PATH}| tr : \\n;
op(){ op.sh $* ; }
o(){ cd $(opticks-home) ; hg st ; }
#. ${LOCAL_BASE}/opticks/externals/bin/geant4.sh
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
. ${LOCAL_BASE}/opticks/externals/bin/geant4.sh
opticks-
new=${CUDA_INSTALL_DIR}/bin
case ":${PATH:=$new}:" in
    *:"$new":*)  ;;
    *) PATH="$new:$PATH"  ;;
esac
new=${CUDA_INSTALL_DIR}/NsightCompute-2019.3
case ":${PATH:=$new}:" in
    *:"$new":*)  ;;
    *) PATH="$new:$PATH"  ;;
esac
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
    nvidia-smi;
    deviceQuery;
}
#export IDPATH=${WORK_DIR}/geocache
#source  /home/wenzel/root-build/bin/thisroot.sh
#export OPTICKS_KEY=OKX4Test.X4PhysicalVolume.lWorld0x4bc2710_PV.6c0b1c7e48b32eb1d3eb898e06ad0a33
export OPTICKS_KEY=OKX4Test.X4PhysicalVolume.World_PV.b7ef5072d1d43f5b529c0c24d5432671
