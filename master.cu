#include "master.h"

void Master::Run(int ThreadID)
{
  cudaSetDevice(ThreadID-1);
  cudaSetDeviceFlags(cudaDeviceMapHost);
  SyncBlock.Barier(ThreadID);
  int* HalfData=ThreadID % 2 ? Data : Data + DataSize / 2;
  int HalfDataSize=ThreadID % 2 ? DataSize / 2 : (DataSize % 2 ? DataSize / 2 + 1 : DataSize / 2);
  for (int i = 1; i <= N; i++)
  {
    <<< x, y >>>Counting(HalfData, HalfDataSize, i);
    cudaDeviceSynchronize();
    SyncBlock.Barier(ThreadID);
  }
}

__global__ Counting(int* HalfData, int HalfDataSize, int N)
{
  int i=blockIdx.x*blockDim.x+threadIdx.x;
  if(i<HalfDataSize)
  {
    HalfData[i]*=N;
  }
}
