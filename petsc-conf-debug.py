#!/usr/bin/python
if __name__ == '__main__':
  import sys
  import os
  os.environ['CC'] = 'gcc'
  #os.environ['FC'] = 'gfortran'

  sys.path.insert(0, os.path.abspath('config'))
  import configure
  configure_options = [
    '--with-mpi-dir=/home/guido/libs/openmpi-install',
    '--PETSC_ARCH=arch-linux-debug'
    ]


  configure.petsc_configure(configure_options)
