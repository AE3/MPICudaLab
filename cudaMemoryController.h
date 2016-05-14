/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cudaMemoryController.h
 * Author: inovitskas
 *
 * Created on 13 мая 2016 г., 11:31
 */

#ifndef CUDAMEMORYCONTROLLER_H
#define CUDAMEMORYCONTROLLER_H


class cudaMemoryController {
public:
    cudaMemoryController();
    virtual ~cudaMemoryController();
    int* cudaHostAllocMemory(unsigned int DataSize);
    int* getCudaHostAllocMemory() const {return Data;}
    unsigned int getCudaHostAllocMemorySize() const {return DataSize;}
private:
    void freeCudaMemory();
    int* Data;
    unsigned int DataSize;
};

#endif /* CUDAMEMORYCONTROLLER_H */

