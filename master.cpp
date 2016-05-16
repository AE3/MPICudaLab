/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   master.cpp
 * Author: inovitskas
 * 
 * Created on 13 мая 2016 г., 11:35
 */

#include "master.h"
#include <fstream>
#include <iostream>

master::master() {
    FileName = "input";
    numberGPU = 2;
    N = 5;
    std::cout << "Master constructor " << FileName << numberGPU << N << std::endl;
}

master::master(std::string FileName, int numberGPU, int numberIteration)
{
    this->FileName = FileName;
    this->numberGPU = numberGPU;
    this->N = numberIteration;
}

void master::start()
{
    threadInit();
    for(int i = 0; i<numberGPU; i++){
        std::cout << "waiting thread" << i << std::endl;
        cudaThreads.at(i)->lock.waitThread();  
        std::cout << "end waiting thread" << i << std::endl;
    }
    std::cout << "start read file" << std::endl;
    readFile();
    std::cout << "end read file" << std::endl;
    for(int i = 0 ; i<numberGPU ; i++)
        cudaThreads.at(i)->setData(i % 2 ? memoryController->getCudaHostAllocMemory() : memoryController->getCudaHostAllocMemory() + memoryController->getCudaHostAllocMemorySize() / 2, i % 2 ? memoryController->getCudaHostAllocMemorySize() / 2 : (memoryController->getCudaHostAllocMemorySize() % 2 ? memoryController->getCudaHostAllocMemorySize() / 2 + 1 : memoryController->getCudaHostAllocMemorySize() / 2));
    for(int i = 0; i<numberGPU; i++){
        std::cout << "permit thread" << i << std::endl;
        cudaThreads.at(i)->lock.permitMaster(); 
    }
    run();
}

void master::threadInit()
{
    for(int i=0 ; i<numberGPU ; i++)
    {
        cudaThread* cThread = new cudaThread();
        std::thread* thread = new std::thread(&cudaThread::start,cThread,i,N);
        cudaThreads.push_back(cThread);
        threads.push_back(thread);
    }
}

void master::readFile()
{
    unsigned int DataSize = 0;
    int* Data;
    std::ifstream in(FileName);
    in>>DataSize;
    memoryController = new cudaMemoryController();
    std::cout << "start cudaHostAllocMemory" << std::endl;
    Data = memoryController->cudaHostAllocMemory(DataSize);
    std::cout << "end cudaHostAllocMemory" << std::endl;
    for(unsigned int i=0; i<DataSize; i++)
    {
        in>>Data[i];
    }
}

void master::debugPrint()
{
    std::cout<<memoryController->getCudaHostAllocMemorySize()<<std::endl;
    for (unsigned int i = 0; i < memoryController->getCudaHostAllocMemorySize(); i++)
    {
        std::cout<<memoryController->getCudaHostAllocMemory()[i]<<" ";
    }
    std::cout<<std::endl;
}

void master::run()
{
    std::cout << "start run" << std::endl;
    for (int i = 0; i < N; i++) //magic constant
    {
        for(int j = 0; j<numberGPU; j++)
            cudaThreads.at(j)->lock.waitThread();
        std::cout << "wait run" << i << std::endl;
        for(int j = 0; j<numberGPU; j++)
            cudaThreads.at(j)->lock.permitMaster();
    }
    std::cout << "end run" << std::endl;
    debugPrint();
    std::cout << "end print" << std::endl;
}

void master::setFileName(std::string FileName)
{
    this->FileName = FileName;
}

void master::setNumberGPU(int numberGPU)
{
    this->numberGPU = numberGPU;
}

void master::setNumberIteration(int N)
{
    this->N = N;
}

master::~master() {
    delete memoryController;
}