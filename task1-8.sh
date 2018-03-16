#! /bin/sh
#PBS -q condo
#PBS -N task-1.8
#PBS -l nodes=1:ppn=8
#PBS -l walltime=2:00:00
#PBS -o task22.out
#PBS -e task22.err
#PBS -V
#PBS -M hpn007@ucsd.edu
#PBS -m abe
#PBS -A ucsd-train141
cd /home/ucsd-train141/PR6-segfault/
cat 8.list | xargs --max-args=2 --max-procs=1 ./chopara.sh
