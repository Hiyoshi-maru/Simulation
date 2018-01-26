/**
******************************************************************************
* @file    MultiProcess.cpp
* @author  Tokugawa
* @version 1.0
* @date    26-January-2018
* @brief   Function Implemetataion for MultiProcess.h
*
*
@verbatim
******************************************************************************
**/
#include "MultiProcess.h"
const uint PERSON = 500;
ResearchType SelectedType = PARAMETER_EFFECT;
//ResearchType SelectedType = Threshold_EFFECT;
//ResearchType SelectedType = Immunization_EFFECT 
unsigned WINAPI ParameterThread(LPVOID lpParameter){
 	Layer layer1(PERSON);
	Layer layer2(PERSON);
	Sim * sim = (Sim*)(lpParameter);
#if SelectedType == PARAMETER_EFFECT
	Simulation(layer1, layer2, *sim,"Parameters_Effect");
#elif SelectedType == Threshold_EFFECT
	Simulation(layer1, layer2, *sim,"Threshold_Effect");
#elif SelectedType == Immunization_EFFECT
	Simulation(layer1, layer2, *sim,"Immunization_Effect");
#endif
	_endthreadex(0);
	return 0;
}