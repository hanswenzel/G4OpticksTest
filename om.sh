#!/bin/bash -l

opticks-
om-  # environment setup (oe-) and build functions om-cmake etc..

sdir=$(pwd)
name=$(basename $sdir)
exe=$OPTICKS_PREFIX/bin/$name

rm $exe

if [ ! -f "$exe" ]; then
    bdir=/tmp/$USER/opticks/$name/build 
    rm -rf $bdir 
    mkdir -p $bdir && cd $bdir && pwd 
    type om-cmake
    om-cmake $sdir
    make install   
else
    echo exe $exe exists already : delete it to rebuild
fi

cd $sdir 


o-lldb-identify(){
   : macOS has some security that prevents /usr/bin/lldb from seeing DYLD_LIBRARY_PATH envvar
   : however direct use of the lldb binary from within the Xcode bundle does not suffer from this restriction

   local lldb_bin=/Applications/Xcode/Xcode_10_1.app/Contents/Developer/usr/bin/lldb
   [ ! -f "$lldb_bin" ] && echo $FUNCNAME : WARNING lldb_bin $lldb_bin DOES NOT EXIST && return 1 
   export LLDB=$lldb_bin 
   return 0 
}
o-lldb-identify

args="gdml/G4Opticks.gdml muon.mac"

case $(uname) in 
  Darwin) runline="$LLDB $exe $args" ;; 
   Linux) runline="gdb --args $exe $args" ;; 
esac

echo $runline
eval $runline

