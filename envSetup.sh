#!/bin/env

SIM_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
echo "SIM_DIR = ${SIM_DIR}"

export MATHLIB_DIR="/home/cmonti/Documents/Coding/Libraries/myMathLib/install/lib64/cmake/mathlib"
echo "MATHLIB_DIR = ${MATHLIB_DIR}"

listProjectLibDirs=()

export listProjectLibDirs+=(${MATHLIB_DIR})