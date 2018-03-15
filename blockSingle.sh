#! /bin/sh
#PBS -q condo
#PBS -N task-2.2
#PBS -l nodes=1:ppn=8
#PBS -l walltime=8:00:00
#PBS -o task22.out
#PBS -e task22.err
#PBS -V
#PBS -M hpn007@ucsd.edu
#PBS -m abe
#PBS -A ucsd-train141
cd /home/ucsd-train141/PR6-segfault/
cat xargs.list | xargs --max-args=2 --max-procs=7 ./blockd.sh
