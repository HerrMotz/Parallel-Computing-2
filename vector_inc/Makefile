all:
	nvcc -rdc=true -arch=sm_70 --std=c++11 vadd.cu -o vadd 
	sbatch ./run.sh
debug:
	nvcc -g -G -arch=sm_70 --std=c++11 vadd.cu -o debug