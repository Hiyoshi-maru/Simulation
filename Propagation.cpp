/**
******************************************************************************
* @file    Propagation.cpp
* @author  Tokugawa
* @version 1.0
* @date    24-January-2018
* @brief   Function Implementation for Propagation.h
*
*
@verbatim
******************************************************************************
**/
#include "Propagation.h"
void OverLap(Layer &layer1, Layer &layer2, double overlap){
	uint oln;
	uint Lnum = min(layer1.Get<uint>("Lnum"), layer2.Get<uint>("Lnum"));
	uint rn;
	bool flag = 0;
	vector<uint>L1;
	vector<uint>L2;
	vector<uint>::iterator it;
	oln = floor(overlap*Lnum);
	if (oln == 0)return;
	for (uint i = 0; i<Lnum; i++){//layer2
		for (uint j = 0; j < Lnum; j++){//layer1
			if (layer2.GetLine(i)->get("ID1") == layer1.GetLine(j)->get("ID1") && layer2.GetLine(i)->get("ID2") == layer1.GetLine(j)->get("ID2") || layer2.GetLine(i)->get("ID2") == layer1.GetLine(j)->get("ID1") && layer2.GetLine(i)->get("ID1") == layer1.GetLine(j)->get("ID2")){
				oln--;
				L1.push_back(i);
				L2.push_back(j);
			}
		}
		if (oln <= 0)break;
	}
	while (oln > 0){
		rn = rand() % Lnum;
		it = find(L1.begin(), L1.end(), rn);
		if (it != L1.end())continue;
		else{
			it = find(L2.begin(), L2.end(), rn);
			if (it != L2.end())continue;
		}
		layer2.GetLine(rn)->setL(layer1.GetLine(rn)->get("ID1"), layer1.GetLine(rn)->get("ID2"));
		L1.push_back(rn);
		L2.push_back(rn);
		oln--;

	}
	vector<uint>().swap(L1);
	vector<uint>().swap(L2);
}
void touch(uint type, Layer &layer1, Layer &layer2, uint id1, uint id2, parameter para){
	bool flag = false;
	double SS = para.get<double>("Beta_1");
	double SI = para.get<double>("Beta_1")*para.get<double>("Pi");
	double SR = para.get<double>("Beta_1")*para.get<double>("Pr");
	double IS = para.get<double>("Beta_1")/*para.get("Pi")*/;
	double II = para.get<double>("Beta_1")*para.get<double>("Pi")/**para.get("Pi")*/;
	double IR = para.get<double>("Beta_1")/**para.get("Pi")*/*para.get<double>("Pr");
	double RS = para.get<double>("Beta_1")/**para.get("Pr")*/;
	double RI = para.get<double>("Beta_1")*para.get<double>("Pi")/**para.get("Pr")*/;
	double RR = para.get<double>("Beta_1")*para.get<double>("Pr")/**para.get("Pr")*/;

	double SS2 = para.get<double>("Beta_2");
	double SI2 = para.get<double>("Beta_2")*para.get<double>("Qi");
	double SR2 = para.get<double>("Beta_2")*para.get<double>("Qr");
	double IS2 = para.get<double>("Beta_2")/**para.get("Qi")*/;
	double II2 = para.get<double>("Beta_2")*para.get<double>("Qi")/**para.get("Qi")*/;
	double IR2 = para.get<double>("Beta_2")/**para.get("Qi")*/*para.get<double>("Qr");
	double RS2 = para.get<double>("Beta_2")/**para.get("Qr")*/;
	double RI2 = para.get<double>("Beta_2")*para.get<double>("Qi")/**para.get("Qr")*/;
	double RR2 = para.get<double>("Beta_2")*para.get<double>("Qr")/**para.get("Qr")*/;


	char state1, state2;
	double rate, coefficient;
	uint Type = type % 2;
	Node *infector = layer1.GetNode(id1), *suscept = layer1.GetNode(id2);
	if (Type == 0){
		if (layer1.GetNode(id1)->get<char>("Disease") == 'I'&&layer1.GetNode(id2)->get<char>("Disease") == 'S'){
			infector = layer1.GetNode(id1);
			suscept = layer1.GetNode(id2);
			coefficient = suscept->get<double>("Coefficient");
			flag = true;
		}
		else if (layer1.GetNode(id1)->get<char>("Disease") == 'S'&&layer1.GetNode(id2)->get<char>("Disease") == 'I'){
			infector = layer1.GetNode(id2);
			suscept = layer1.GetNode(id1);
			coefficient = suscept->get<double>("Coefficient");
			flag = true;
		}
		if (flag){
			state1 = layer2.GetNode(infector->get<uint>("ID"))->get<char>("Disease");
			state2 = layer2.GetNode(suscept->get<uint>("ID"))->get<char>("Disease");;
			if (state1 == 'S'&& state2 == 'S')
			{
				rate = rand() / (RAND_MAX + 1.0);
				if (rate < (SS) / coefficient) suscept->set<char>("Disease", 'I');
			}
			if (state1 == 'S'&& state2 == 'I')
			{
				rate = rand() / (RAND_MAX + 1.0);
				if (rate < (SI) / coefficient) suscept->set<char>("Disease", 'I');
			}
			if (state1 == 'S'&& state2 == 'R')
			{
				rate = rand() / (RAND_MAX + 1.0);
				if (rate < (SR) / coefficient) suscept->set<char>("Disease", 'I');
			}
			if (state1 == 'I'&& state2 == 'S')
			{
				rate = rand() / (RAND_MAX + 1.0);
				if (rate < (IS) / coefficient) suscept->set<char>("Disease", 'I');
			}
			if (state1 == 'I'&& state2 == 'I')
			{
				rate = rand() / (RAND_MAX + 1.0);
				if (rate < (II) / coefficient) suscept->set<char>("Disease", 'I');
			}
			if (state1 == 'I'&& state2 == 'R')
			{
				rate = rand() / (RAND_MAX + 1.0);
				if (rate < (IR) / coefficient) suscept->set<char>("Disease", 'I');
			}
			if (state1 == 'R'&& state2 == 'S')
			{
				rate = rand() / (RAND_MAX + 1.0);
				if (rate < (RS) / coefficient) suscept->set<char>("Disease", 'I');
			}
			if (state1 == 'R'&& state2 == 'I')
			{
				rate = rand() / (RAND_MAX + 1.0);
				if (rate < (RI) / coefficient) suscept->set<char>("Disease", 'I');
			}
			if (state1 == 'R'&& state2 == 'R')
			{
				rate = rand() / (RAND_MAX + 1.0);
				if (rate < (RR) / coefficient) suscept->set<char>("Disease", 'I');
			}
		}
	}
	else if (Type == 1){
		if (layer2.GetNode(id1)->get<char>("Disease") == 'I'&&layer2.GetNode(id2)->get<char>("Disease") == 'S'){
			infector = layer2.GetNode(id1);
			suscept = layer2.GetNode(id2);
			coefficient = suscept->get<double>("Coefficient");
			flag = true;
		}
		else if (layer2.GetNode(id1)->get<char>("Disease") == 'S'&&layer2.GetNode(id2)->get<char>("Disease") == 'I'){
			infector = layer2.GetNode(id2);
			suscept = layer2.GetNode(id1);
			coefficient = suscept->get<double>("Coefficient");
			flag = true;
		}
		if (flag){
			state1 = layer1.GetNode(infector->get<uint>("ID"))->get<char>("Disease");
			state2 = layer1.GetNode(suscept->get<uint>("ID"))->get<char>("Disease");;
			if (state1 == 'S'&& state2 == 'S')
			{
				rate = rand() / (RAND_MAX + 1.0);
				if (rate < (SS2) / coefficient) suscept->set<char>("Disease", 'I');
			}
			if (state1 == 'S'&& state2 == 'I')
			{
				rate = rand() / (RAND_MAX + 1.0);
				if (rate < (SI2) / coefficient) suscept->set<char>("Disease", 'I');
			}
			if (state1 == 'S'&& state2 == 'R')
			{
				rate = rand() / (RAND_MAX + 1.0);
				if (rate < (SR2) / coefficient) suscept->set<char>("Disease", 'I');
			}
			if (state1 == 'I'&& state2 == 'S')
			{
				rate = rand() / (RAND_MAX + 1.0);
				if (rate < (IS2) / coefficient) suscept->set<char>("Disease", 'I');
			}
			if (state1 == 'I'&& state2 == 'I')
			{
				rate = rand() / (RAND_MAX + 1.0);
				if (rate < (II2) / coefficient) suscept->set<char>("Disease", 'I');
			}
			if (state1 == 'I'&& state2 == 'R')
			{
				rate = rand() / (RAND_MAX + 1.0);
				if (rate < (IR2) / coefficient) suscept->set<char>("Disease", 'I');
			}
			if (state1 == 'R'&& state2 == 'S')
			{
				rate = rand() / (RAND_MAX + 1.0);
				if (rate < (RS2) / coefficient) suscept->set<char>("Disease", 'I');
			}
			if (state1 == 'R'&& state2 == 'I')
			{
				rate = rand() / (RAND_MAX + 1.0);
				if (rate < (RI2) / coefficient) suscept->set<char>("Disease", 'I');
			}
			if (state1 == 'R'&& state2 == 'R')
			{
				rate = rand() / (RAND_MAX + 1.0);
				if (rate < (RR2) / coefficient) suscept->set<char>("Disease", 'I');
			}
		}
	}
}
void spread(Layer &layer1, Layer &layer2, parameter para){
	uint id1=0, id2=0;
	if (layer1.Get<uint>("Nnum") != layer2.Get<uint>("Nnum"))return;
	for (uint i = 0; i < layer1.Get<uint>("Lnum"); i++){
		layer1.GetLine(i)->setL(layer1.GetLine(i)->get("ID1"), layer1.GetLine(i)->get("ID2"), false);
	}
	for (uint i = 0; i < layer2.Get<uint>("Lnum"); i++){
		layer2.GetLine(i)->setL(layer2.GetLine(i)->get("ID1"), layer2.GetLine(i)->get("ID2"), false);
	}
	for (uint i = 0; i < layer1.Get<uint>("Lnum"); i++){
		do{
			id1 = rand() % layer1.Get<uint>("Lnum");
		} while (layer1.GetLine(id1)->get("Flag"));
		layer1.GetLine(id1)->setL(layer1.GetLine(id1)->get("ID1"), layer1.GetLine(id1)->get("ID2"), true);
		touch(0, layer1, layer2, layer1.GetLine(id1)->get("ID1"), layer1.GetLine(id1)->get("ID2"), para);
	}
	for (uint i = 0; i < layer2.Get<uint>("Lnum"); i++){
		do{
			id2 = rand() % layer2.Get<uint>("Lnum");
		} while (layer2.GetLine(id2)->get("Flag"));
		layer2.GetLine(id2)->setL(layer2.GetLine(id2)->get("ID1"), layer2.GetLine(id2)->get("ID2"), true);
		touch(1, layer1, layer2, layer2.GetLine(id2)->get("ID1"), layer2.GetLine(id2)->get("ID2"), para);
	}

}
void recover(Layer &layer1, Layer &layer2, parameter para){
	double rate;
	if (layer1.Get<uint>("Nnum") != layer2.Get<uint>("Nnum"))return;
	for (uint i = 0; i < layer1.Get<uint>("Nnum"); i++){
		if (layer1.GetNode(i)->get<char>("Disease") == 'I'){
	
			rate = rand() / (RAND_MAX + 1.0);
			if (rate < para.get<double>("Mu_1")*layer1.GetNode(i)->get<double>("Coefficient"))layer1.GetNode(i)->set<char>("Disease", 'R');
		}
		if (layer2.GetNode(i)->get<char>("Disease") == 'I'){
			
			rate = rand() / (RAND_MAX + 1.0);
			if (rate < para.get<double>("Mu_2")*layer2.GetNode(i)->get<double>("Coefficient"))layer2.GetNode(i)->set<char>("Disease", 'R');

		}
	}
}
void init(Layer &layer1, Layer &layer2, parameter para){
	double rate;
	if (layer1.Get<uint>("Nnum") != layer2.Get<uint>("Nnum"))return;
	else if (para.get<double>("InitialInfected_1")>1 || para.get<double>("InitialInfected_1") < 0)return;
	else if (para.get<double>("InitialInfected_2")>1 || para.get<double>("InitialInfected_2") < 0)return;
	else if (para.get<double>("WeakPercentage")>1 || para.get<double>("WeakPercentage") < 0)return;
	for (uint i = 0; i < layer1.Get<uint>("Nnum"); i++){
		rate = rand() / (RAND_MAX + 1.0);
		if (rate <para.get<double>("InitialInfected_1"))layer1.GetNode(i)->set<char>("Disease", 'I');
		else layer1.GetNode(i)->set<char>("Disease", 'S');

		rate = rand() / (RAND_MAX + 1.0);
		if (rate < para.get<double>("InitialInfected_2"))layer2.GetNode(i)->set<char>("Disease", 'I');
		else layer2.GetNode(i)->set<char>("Disease", 'S');

		rate = rand() / (RAND_MAX + 1.0);
		if (rate < para.get<double>("WeakPercentage"))
		{
			layer1.GetNode(i)->set<double>("Coefficient", para.get<double>("WeakEffect"));
			layer2.GetNode(i)->set<double>("Coefficient", para.get<double>("WeakEffect"));
		}
		else
		{
			layer1.GetNode(i)->set<double>("Coefficient", 1.0);
			layer2.GetNode(i)->set<double>("Coefficient", 1.0);
		}
	}


}

