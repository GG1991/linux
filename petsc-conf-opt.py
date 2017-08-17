#!/usr/bin/python
if __name__ == '__main__':
  import sys
  import os
  sys.path.insert(0, os.path.abspath('config'))
  import configure
  configure_options = [
    '--with-mpi-dir=/home/guido/libs/openmpi-install',
    '--with-debugging=0',
    '--download-mpe'
    '--PETSC_ARCH=arch-linux-gcc-real-opt'
    ]
  configure.petsc_configure(configure_options)
