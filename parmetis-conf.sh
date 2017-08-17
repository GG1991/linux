#!/bin/bash 

cmake -DGKLIB_PATH=$HOME/libs/parmetis-4.0.3/metis/GKlib 
      -DMETIS_PATH=$HOME/libs/parmetis-4.0.3/metis 
      -DCMAKE_C_COMPILER=$HOME/libs/openmpi-install/bin/mpicc .
