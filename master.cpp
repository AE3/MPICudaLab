#include "master.h"
#include <fstream>


Master::Master(std::string FileName)
{
  ThreadInit();
  SyncBlock.MasterBarier();
  ReadFile(FileName);
  SyncBlock.Barier(0);
  Synchronize();
}

void Master::ThreadInit()
{
  Thread1 = new std::thread(&Master::Run, this, 1);
  Thread1 = new std::thread(&Master::Run, this, 2);
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

Master::~Master()
{
    if(Thread1->joinable()){
        Thread1->join();
    }
    if(Thread2->joinable()){
        Thread2->join();
    }
}
