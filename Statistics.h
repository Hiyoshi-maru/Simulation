/**
******************************************************************************
* @file    Statistics.h
* @author  Tokugawa
* @version 1.0
* @date    24-January-2018
* @brief   Function Declarations for statistics
*
*
@verbatim
******************************************************************************
**/
#ifndef STATISTIC_H
#define STATISTIC_H
#include "Basic.h"
void CalculateSIR(Layer &layer1, Layer &layer2, vector<double> &result);
double Threshold(Layer &layer1, Layer &layer2, parameter para);
vector<uint> DegreeSorted(Layer &layer);
vector<uint>BetweennessSorted(Layer &layer);
#endif