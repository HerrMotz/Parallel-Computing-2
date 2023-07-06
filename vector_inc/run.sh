#!/bin/bash
#SBATCH --job-name=mavecGPU
#SBATCH --partition=gpu-test
#SBATCH --gres=gpu:1
#SBATCH --mem=100GB
#SBATCH --time=10:00

module load nvidia/cuda/11.7

srun ./vadd

