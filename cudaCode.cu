/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <cuda_runtime.h>
#include <cudaCode.h>
#include <iostream>
#include <fstream>

#define THREAD 1536

__global__ void Counting(int* HalfData, int HalfDataSize, int N)
{
	int i = blockIdx.x*blockDim.x + threadIdx.x;
	if (i<HalfDataSize)
	{
		HalfData[i] *= N;
	}
}

__host__ void cudaSets(int threadID)
{
    cudaSetDevice(threadID);
    cudaSetDeviceFlags(cudaDeviceMapHost);
}

__host__ void cudaRun(int* Data, unsigned int DataSize,int i)
{
    dim3 blockDim(THREAD);
    dim3 gridDim((DataSize + blockDim.x - 1) / blockDim.x);
    std::cout<<"start count"<<std::endl;
    Counting <<<blockDim, gridDim>>> (Data, DataSize, i);
    out<<std::endl;
    cudaDeviceSynchronize();
}



__host__ void setCudaData(int* Data, int* CData)
{
    cudaHostGetDevicePointer(&Data, CData,0);
}