#!/bin/env

export SIM_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
echo "SIM_DIR = ${SIM_DIR}"

export MATHLIB_DIR="/home/cmonti/Documents/Coding/Libraries/myMathLib/install/lib64/cmake/mathlib"
echo "MATHLIB_DIR = ${MATHLIB_DIR}"

export GRAMEARTH_DIR="/home/cmonti/Documents/NASA_SW_Downloads/GRAM/GRAM_Suite_1.5.1/install/lib64/cmake/GRAM_Earth"
echo "GRAMEARTH_DIR = ${GRAMEARTH_DIR}"

export PUBSUBLIB_DIR="/home/cmonti/Documents/Coding/Libraries/PubSub/install/lib64/cmake/PubSub"
echo "PUBSUBLIB_DIR = ${PUBSUBLIB_DIR}"

export SIMLIBLIB_DIR="/home/cmonti/Documents/Coding/Libraries/SimLib/install/lib64/cmake/SimLib"
echo "SIMLIBLIB_DIR = ${SIMLIBLIB_DIR}"

export HDF5_DIR="/home/cmonti/Documents/Coding/Libraries/HDF5/1.12.0/share/cmake/hdf5"

listProjectLibDirs=()

export listProjectLibDirs+=(${PUBSUBLIB_DIR})