/**
******************************************************************************
* @file    Propagation.h
* @author  Tokugawa
* @version 1.0
* @date    23-January-2018
* @brief   Function Declarations and Macros for Propagation process
*
*
@verbatim
******************************************************************************
**/
#ifndef PROPAGATION_H
#define PROPAGATION_H
#include <algorithm>
#include "Basic.h"
/**************************Function Declarations****************************************/
/**************************Function Declarations****************************************/
void OverLap(Layer &layer1, Layer &layer2, double overlap);
void touch(uint type, Layer &layer1, Layer &layer2, uint id1, uint id2, parameter para);
void spread(Layer &layer1, Layer &layer2, parameter para);
void recover(Layer &layer1, Layer &layer2, parameter para);
void init(Layer &layer1, Layer &layer2, parameter para);
/**************************Function Declarations****************************************/
#endif