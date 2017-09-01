#!/bin/bash
# @ job_name = paraview
# @ initialdir = ./
# @ output = paraview_%j.out
# @ error = paraview_%j.err
# @ wall_clock_limit = 00:30:00
# @ total_tasks = 16 
## K80
# @ cpus_per_task = 1
# @ gpus_per_node = 4
# @ features = k80
## M2090
## @ cpus_per_task = 12
## @ gpus_per_node = 2
## @ features = m2090
# @ X11 = 1
/gpfs/apps/NVIDIA/PARAVIEW/5.2.0/RUN/srun_paraview
