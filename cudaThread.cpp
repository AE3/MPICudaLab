/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cudaThread.cpp
 * Author: inovitskas
 * 
 * Created on 13 мая 2016 г., 11:19
 */

#include "cudaThread.h"
#include "cudaCode.h"
#include <iostream>

cudaThread::cudaThread() {
}

cudaThread::~cudaThread() {
}

void cudaThread::start(int threadID, int N)
{
    lock.init();
    std::cout << "lock init " << threadID << std::endl;
    this->threadID = threadID;
    cudaSets(threadID);
    std::cout << "waiting master" << threadID << std::endl;
    lock.waitingMaster();
    std::cout << "waiting master end" << threadID << std::endl;
    for (int i = 1; i <= N; i++) //вернуть N
    {
        std::cout << "cudaRun" << threadID << std::endl;
        cudaRun(Data,DataSize,i);
        std::cout << "waiting master" << threadID << std::endl;
        lock.waitingMaster();
    }
}

void cudaThread::setData(int* Data, unsigned int DataSize)
{
    std::cout << "Half Data " << Data[0] << std::endl;
    std::cout << this->Data << std::endl;
    this->Data = setCudaData(Data);
    std::cout << this->Data << std::endl;
    this->DataSize = DataSize;
}