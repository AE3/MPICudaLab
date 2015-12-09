#include "master.h"
#include <iostream>


Master::Master(int* Data, unsigned int DataSize, int N)
{
  this->Data=Data;
  this->DataSize=DataSize;
  this->N=N;
  ThreadInit();
  Synchronize();
}

void Master::ThreadInit()
{
  Thread1 = new std::thread(&Master::Run, this, Data, DataSize / 2, 1);
  Thread1 = new std::thread(&Master::Run, this, Data + (DataSize) / 2, DataSize % 2 ? DataSize / 2 + 1 : DataSize / 2 , 2);
}

void Master::Run(int* HalfData, int HalfDataSize, int ThreadID)
{
  for (int i = 1; i <= N; i++)
  {
    for (int j = 0; j < HalfDataSize; j++)
    {
      *(HalfData + j)*=i;
    }
    SyncBlock.Barier(ThreadID);
  }
}

void Master::Print()
{
  for (unsigned int i = 0; i < DataSize; i++)
  {
      std::cout<<Data[i]<<" ";
  }
  std::cout<<std::endl;
}

void Master::Synchronize()
{
  for (int i = 1; i <= N; i++)
  {
    SyncBlock.MasterBarier();
    Print();
    SyncBlock.Barier(0);
    SyncBlock.Init();
  }
}

Master::~Master(){
    if(Thread1->joinable()){
        Thread1->join();
    }
    if(Thread2->joinable()){
        Thread2->join();
    }
}
