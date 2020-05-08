#!/bin/bash
#
# interactive
# srun --pty --gres=gpu:1 --partition gpu bash
#
# sbatch --nodes=1 --partition gpu --account=g4 $Executable
#
#------------------------------------------------------------------------------------
export WORK_DIR=/home/wenzel/work/opticks
export OptiX_INSTALL_DIR=/srv/software/misc/NVIDIA-OptiX-SDK-6.5.0-linux64
export OPTICKS_COMPUTE_CAPABILITY=70
export CUDA_INSTALL_DIR=/srv/software/cuda-10.1
export CUDA_SAMPLES=/home/wenzel/NVIDIA_CUDA-10.1_Samples
#------------------------------------------------------------------------------------
module load gnu8/8.3.0
export CXX=/opt/ohpc/pub/compiler/gcc/8.3.0/bin/g++
export CC=/opt/ohpc/pub/compiler/gcc/8.3.0/bin/gcc
new=/opt/ohpc/pub/compiler/gcc/8.3.0/lib64:/opt/ohpc/pub/compiler/gcc/8.3.0/lib
case ":${LD_LIBRARY_PATH:=$new}:" in
    *:"$new":*)  ;;
    *) LD_LIBRARY_PATH="$new:$LD_LIBRARY_PATH"  ;;
esac
new=/srv/software/misc/mercurial-5.2rc0/bin
case ":${PATH:=$new}:" in
    *:"$new":*)  ;;
    *) PATH="$new:$PATH"  ;;
esac
new=/srv/software/binutils-2.31.90/bin
case ":${PATH:=$new}:" in
    *:"$new":*)  ;;
    *) PATH="$new:$PATH"  ;;
esac
new=/srv/software/binutils-2.31.90/lib
case ":${LD_LIBRARY_PATH:=$new}:" in
    *:"$new":*)  ;;
    *) LD_LIBRARY_PATH="$new:$LD_LIBRARY_PATH"  ;;
esac
#
# missing libs on the gpu node
#
new=/home/syjun/products/missing-libs-on-lq1gwn/lib:/home/syjun/products/missing-libs-on-lq1gwn/lib64
case ":${LD_LIBRARY_PATH:=$new}:" in
    *:"$new":*)  ;;
    *) LD_LIBRARY_PATH="$new:$LD_LIBRARY_PATH"  ;;
esac

#
# python
#
. /srv/software/Anaconda3-2019.03/etc/profile.d/conda.sh
conda activate py27
new=/srv/software/Anaconda3-2019.03/lib 
case ":${LD_LIBRARY_PATH:=$new}:" in
    *:"$new":*)  ;;
    *) LD_LIBRARY_PATH="$new:$LD_LIBRARY_PATH"  ;;
esac

