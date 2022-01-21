#!/bin/bash
#PBS -l nodes=3:ppn=5,walltime=10:00:00
#PBS -N extra_walle
#PBS -q staff
#PBS -d /mnt/zfs-pool/home/cursoHPC13/escuela_programacion-paralela/examen
#PBS -o extra.log
#PBS -j oe
#PBS -V
#PBS -S /bin/bash
source $MODULESHOME/init/bash
module purge
module load Compilers/Parallel-Studio-XE-2018
NPROCS=‘wc -l < $PBS_NODEFILE‘
cat ${PBS_NODEFILE} | sort -u > $PBS_O_WORKDIR/machines.LINUX
mpirun -np $NPROCS -machinefile machines.LINUX ./programa > mpi_curso_programa.out