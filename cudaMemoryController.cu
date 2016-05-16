/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "cudaMemoryController.h"
#include <cuda_runtime.h>
#include <iostream>

cudaMemoryController::cudaMemoryController()
{
    Data = NULL;
    DataSize = 0;
}
cudaMemoryController::~cudaMemoryController() {
    freeCudaMemory();
}

int* cudaMemoryController::cudaHostAllocMemory(unsigned int DataSize)
{
    std::cout << "Data ? NULL" << DataSize << std::endl;
    if(Data != NULL)
    {
        std::cout << "Data ! NULL" << std::endl;
        freeCudaMemory();
        Data = NULL;
    }
    std::cout << "cudaHostAlloc" << std::endl;
    if (cudaSuccess != cudaHostAlloc((void**)&Data, DataSize*sizeof(int), cudaHostAllocWriteCombined | cudaHostAllocMapped))
    {
        std::cout << "cudaNotSuccess" << std::endl;
        Data = NULL;
        return Data;
    }
    this->DataSize = DataSize;
    std::cout << "return Data" << std::endl;
    return Data;
}

void cudaMemoryController::freeCudaMemory()
{
    cudaFree(Data);
}