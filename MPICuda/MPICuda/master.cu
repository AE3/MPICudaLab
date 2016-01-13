#define THREAD 1536

#include "master.h"
#include <fstream>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__global__ void Counting(int* HalfData, int HalfDataSize, int N)
{
	int i = blockIdx.x*blockDim.x + threadIdx.x;
	if (i<HalfDataSize)
	{
		HalfData[i] *= N;
	}
}

__host__ void Master::Run(int ThreadID)
{
  cudaSetDevice(ThreadID-1);
  cudaSetDeviceFlags(cudaDeviceMapHost);
  SyncBlock.Barier(ThreadID);
  int* DevData;
  int* HalfData=ThreadID % 2 ? Data : Data + DataSize / 2;
  cudaHostGetDevicePointer(&DevData,HalfData,0);
  int HalfDataSize=ThreadID % 2 ? DataSize / 2 : (DataSize % 2 ? DataSize / 2 + 1 : DataSize / 2);
  dim3 block_dim(THREAD);
	dim3 grid_dim((HalfDataSize + block_dim.x - 1) / block_dim.x);
  for (int i = 1; i <= N; i++)
  {
	Counting << <block_dim, grid_dim >> > (HalfData, HalfDataSize, i);
    cudaDeviceSynchronize();
    SyncBlock.Barier(ThreadID);
  }
}



__host__ void Master::ReadFile(std::string FileName)
{
  std::ifstream in(FileName);
  in>>DataSize>>N;
  if (cudaSuccess != cudaHostAlloc((void**)&Data, DataSize*sizeof(int), cudaHostAllocWriteCombined | cudaHostAllocMapped))
  {
	  return;
  }
  for(unsigned int i=0; i<DataSize; i++)
  {
    in>>Data[i];
  }
}
