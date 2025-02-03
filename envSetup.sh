#!/bin/env

export SIM_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
echo "SIM_DIR = ${SIM_DIR}"

export MATHLIB_DIR="/home/cmonti/Documents/Code/Libraries/myMathLib/install/lib/cmake/mathlib"
echo "MATHLIB_DIR = ${MATHLIB_DIR}"

export GRAMEARTH_DIR="/home/cmonti/Documents/NASA_SW/GRAM/GRAM_Suite_2.0.0/GRAM Suite 2.0/install/lib/cmake/GRAM_Earth"
echo "GRAMEARTH_DIR = ${GRAMEARTH_DIR}"

export PUBSUBLIB_DIR="/home/cmonti/Documents/Code/Libraries/PubSub/install/lib/cmake/PubSub"
echo "PUBSUBLIB_DIR = ${PUBSUBLIB_DIR}"

export SIMLIBLIB_DIR="/home/cmonti/Documents/Code/Libraries/SimLib/install/lib/cmake/SimLib"
echo "SIMLIBLIB_DIR = ${SIMLIBLIB_DIR}"

export HDF5_DIR="/home/cmonti/Documents/Code/Libraries/HDF5/1.12.0/share/cmake/hdf5"

listProjectLibDirs=()

export listProjectLibDirs+=(${PUBSUBLIB_DIR})