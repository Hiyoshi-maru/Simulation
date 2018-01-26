/**
******************************************************************************
* @file    Immunization.h
* @author  Tokugawa
* @version 1.0
* @date    23-January-2018
* @brief    Class for Immunization Strategies
*
*
@verbatim
******************************************************************************
**/
#ifndef IMMUNIZATION_H
#define IMMUNIZATION_H
#include "Basic.h"
class Immunization{
public:
	static void Targeted(Layer &layer1, Layer& layer2, vector<uint>Sorted, double percentage);
	static void Acquaintance(Layer &layer1, Layer &layer2, double percentage);

};
#endif

