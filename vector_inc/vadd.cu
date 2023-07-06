#include <cuda.h>
#include <stdio.h>
#include <stdlib.h>


//increment wird auf host und device definiert
__host__ __device__ int increment(int a) 
{
     return a+1;
}
__host__ __device__ int add(int a, int b)
{
	return a+b;
}

__global__ void kernel(int *a, int *b, int size)
{
    int tid = threadIdx.x;    //lokaler Thread Index
    int bid = blockIdx.x;     //Index des Blockes
    int bdim= blockDim.x;     //Anzahl an Threads pro Block
    
    int i = tid+bid*bdim;     //Globale Adresse
    
    if (i<size)               //Fehlerbehandlung
      b[i]=add(a[i], b[i]);   //Increment
}


//Fülle A mit Werten
void fillA(int *a, int size)
{
   for (int i=0;i<size;i++)
      a[i]=i;
}

//Überprüfe Ergebnisse 
bool checkResult(int *a, int *b, int *c, int size)
{
   bool res=true;
   printf("a b c\n");
   for (int i=0;i<size;i++)
   {
      res&=(add(a[i],b[i])==c[i]);
      if (i<10) printf("%i %i %i\n",a[i],b[i],c[i]);
   }
   if (res) printf("Test passed\n");
   else printf("Test failed\n");
   return res;
}

int main(int argc, char**argv)
{
   //Problemgröße
   int size=1024;
   //Pointer auf Host/Device Speicher
   int *a_host, *b_host, *c_host, *a_dev, *b_dev;

   //Allokiere Host-Speicher
   a_host = (int*)malloc(size*sizeof(int));
   b_host = (int*)malloc(size*sizeof(int));
   c_host = (int*)malloc(size*sizeof(int));
   fillA(a_host,size);
   fillA(b_host,size);
   
   //Allokiere Device Speicher
   //Achtung: (void**)& sehr wichtig
   cudaMalloc((void**)&a_dev,size*sizeof(int));
   cudaMalloc((void**)&b_dev,size*sizeof(int));

   //Kopiere Host->Device
   cudaMemcpy(a_dev,a_host,size*sizeof(int),cudaMemcpyHostToDevice);
   cudaMemcpy(b_dev,b_host,size*sizeof(int),cudaMemcpyHostToDevice);

   //Konfguration des Kernels (nur 1 Dimensional): 
   //256 Threads pro Threadblock
   //Mehrere Dimensionen möglich über dim3 threads(x,y,z); -> threads.x,threads.y,threads.z
   dim3 threads(256);
   //1024/256 = 4 Threadblöcke
   //Mehrere Dimensionen wie bei Threads möglich
   dim3 grid(size/threads.x);

   //Starte Kernel mit Konfiguration <<<grid,threads>>> auf Device Speicher
   //Wichtig: Spitze Klammern <<<>>> nicht vergessen!
   //Kernel wird asynchron zu CPU ausgeführt, d.h. hier könnte die CPU noch Arbeit verrichten
   kernel<<<grid,threads>>>(a_dev,b_dev,size);

   //Kopiere Ergebnis zurück (implizite Synchronisierung)
   cudaMemcpy(c_host,b_dev,size*sizeof(int),cudaMemcpyDeviceToHost);
   checkResult(a_host,b_host,c_host,size);

   //Gib Speicher wieder frei
   cudaFree(a_dev);
   cudaFree(b_dev);
   free(a_host);
   free(b_host);
   free(c_host);
   return 0;
}
