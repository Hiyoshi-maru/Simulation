/**
******************************************************************************
* @file    MultiProcess.h
* @author  Tokugawa
* @version 1.0
* @date    26-January-2018
* @brief   Function Declarations for multithreading
*
*
@verbatim
******************************************************************************
**/
#ifndef MULTIPROCESS_H
#define MULTIPROCESS_H
#include <thread>
#include"process.h"
#include "windows.h"
#include "Simulation.h"
using namespace std;
enum ResearchType {
	PARAMETER_EFFECT = 0,
	THRESHOLD_EFFECT = 1,
	IMMUNIZATION_EFFECT = 2
};

unsigned WINAPI ParameterThread(LPVOID lpParameter);
#endif