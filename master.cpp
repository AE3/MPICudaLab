#include "master.h"
#include <fstream>

#include <thread>

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
  std::thread* Thread1 = new std::thread(&Master::Run, this, 1);
  std::thread* Thread2 = new std::thread(&Master::Run, this, 2);
  Thread1->detach();
  Thread2->detach();
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

}
