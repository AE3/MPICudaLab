/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   block.h
 * Author: inovitskas
 *
 * Created on 13 мая 2016 г., 14:01
 */

#ifndef BLOCK_H
#define BLOCK_H

#include <cstdatomic>

class block {
public:
    block();
    void init();
    virtual ~block();
    void waitingMaster();
    void waitThread();
    void permitMaster();
    void printStatus();
    
private:
    std::atomic<bool> threadStatus;
    std::atomic<bool> masterStatus;
};

#endif /* BLOCK_H */

