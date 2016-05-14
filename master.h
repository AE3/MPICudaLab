/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   master.h
 * Author: inovitskas
 *
 * Created on 13 мая 2016 г., 11:35
 */

#ifndef MASTER_H
#define MASTER_H

#include <thread>
#include <vector>
#include <string>
#include "cudaMemoryController.h"
#include "cudaThread.h"

class master {
public:
    master();
    master(std::string FileName, int numberGPU, int N);
    void setFileName(std::string FileName);
    void setNumberGPU(int numberGPU);
    void setNumberIteration(int N);
    void start();
    virtual ~master();
private:
    void run();
    void readFile();
    void threadInit();
    void debugPrint();
    cudaMemoryController* memoryController;
    std::vector<cudaThread*> cudaThreads;
    std::vector<std::thread*> threads;
    std::string FileName;
    int numberGPU;
    int N;
};

#endif /* MASTER_H */

