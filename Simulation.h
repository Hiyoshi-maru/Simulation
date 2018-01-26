/**
******************************************************************************
* @file    Simulation.h
* @author  Tokugawa
* @version 1.0
* @date    25-January-2018
* @brief   Function Declarations and Macros for Simulation
*
*
@verbatim
******************************************************************************
**/
#ifndef SIMULATION_H
#define SIMULATION_H
#include "stdlib.h"
#include "Basic.h"
#include "Propagation.h"
#include "Statistics.h"
#include <fstream>
#include <iomanip>
#include"io.h"
#include "Immunization.h"
using namespace std;
struct Sim{
	string Factor;
	uint Number;
	parameter para[500];
};

void Simulation(Layer &layer1, Layer &layer2, Sim sim,string type);
void Foperation(vector<double> result, string filename/*,uint number*/);
void Foperation(vector<double> result, string filename, uint number);

#endif
