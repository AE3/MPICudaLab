/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   block.cpp
 * Author: inovitskas
 * 
 * Created on 13 мая 2016 г., 14:01
 */

#include "block.h"
#include <iostream>

block::block() {
    init();
}

void block::init()
{
    threadStatus.store(false);
    masterStatus.store(false);
}

void block::waitingMaster()
{
    threadStatus.store(true);
    while (!masterStatus.load());
    init();
}

void block::waitThread()
{
    while (!threadStatus.load());
}

void block::permitMaster()
{
    masterStatus.store(true);
}

void block::printStatus()
{
}

block::~block() {
    
}

