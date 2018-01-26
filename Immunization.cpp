/**
******************************************************************************
* @file    Immunization.h
* @author  Tokugawa
* @version 1.0
* @date    23-January-2018
* @brief    Implementation for Immunization.h
*
*
@verbatim
******************************************************************************
**/
#include "Immunization.h"

void Immunization::Acquaintance(Layer &layer1, Layer &layer2, double percentage){
	if (layer1.Get<uint>("Nnum") != layer2.Get<uint>("Nnum") || percentage > 1)return;
	uint Nnum = layer1.Get<uint>("Nnum");
	uint Lnum = layer1.Get<uint>("Lnum");
	uint Number = round(percentage*Nnum);
	vector<vector<uint>>connectivity = layer1.Connectivity();
	for (uint i = 0; i < Number;){
		uint RdNode = rand() % Nnum;
		uint SelectedNode = rand() % connectivity.at(RdNode).size();
		if (layer1.GetNode(connectivity.at(RdNode).at(SelectedNode))->get<char>("Disease") == 'R')continue;
		else { layer1.GetNode(connectivity.at(RdNode).at(SelectedNode))->set<char>("Disease", 'R'); i++; }
	}
}
void Immunization::Targeted(Layer &layer1, Layer& layer2, vector<uint>Sorted, double percentage){
	if (layer1.Get<uint>("Nnum") != layer2.Get<uint>("Nnum") || percentage > 1)return;
	uint Nnum = layer1.Get<uint>("Nnum");
	uint Number = round(percentage*Nnum);
	for (uint i = 0; i < Number; i++){
		layer1.GetNode(Sorted.at(i))->set<char>("Disease", 'R');
	}
}