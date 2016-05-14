/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cudaThread.h
 * Author: inovitskas
 *
 * Created on 13 мая 2016 г., 11:19
 */

#ifndef CUDATHREAD_H
#define CUDATHREAD_H
#include "block.h"

class cudaThread {
public:
    cudaThread();
    void start(int threadID, int N);
    void setData(int* Data, unsigned int DataSize);
    virtual ~cudaThread();
    block lock;
private:
    int threadID;
    int* Data;
    unsigned int DataSize;
};

#endif /* CUDATHREAD_H */

