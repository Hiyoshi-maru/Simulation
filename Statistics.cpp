/**
******************************************************************************
* @file    Statistics.cpp
* @author  Tokugawa
* @version 1.0
* @date    24-January-2018
* @brief   Functions Implementations for Statistics
*
*
@verbatim
******************************************************************************
**/
#include "Statistics.h"
void CalculateSIR(Layer &layer1, Layer &layer2, vector<double> &result){
	if (layer1.Get<uint>("Nnum") != layer2.Get<uint>("Nnum"))return;
	uint S[2] = { 0, };
	uint I[2] = { 0, };
	uint R[2] = { 0, };
	for (uint i = 0; i < layer1.Get<uint>("Nnum"); i++){
		if (layer1.GetNode(i)->get<char>("Disease") == 'S')S[0]++;
		else if (layer1.GetNode(i)->get<char>("Disease") == 'I')I[0]++;
		else if (layer1.GetNode(i)->get<char>("Disease") == 'R')R[0]++;
		if (layer2.GetNode(i)->get<char>("Disease") == 'S')S[1]++;
		else if (layer2.GetNode(i)->get<char>("Disease") == 'I')I[1]++;
		else if (layer2.GetNode(i)->get<char>("Disease") == 'R')R[1]++;
	}
	for (uint j = 0; j < 2; j++){
		result.push_back(S[j] / (layer1.Get<uint>("Nnum") + 0.0));
		result.push_back(I[j] / (layer1.Get<uint>("Nnum") + 0.0));
		result.push_back(R[j] / (layer1.Get<uint>("Nnum") + 0.0));
	}
}
double Threshold(Layer &layer1, Layer &layer2, parameter para){
	if (layer1.Get<uint>("Nnum") != layer2.Get<uint>("Nnum"))return 0;
	uint NodeNumber = layer1.Get<uint>("Nnum");
	if (NodeNumber <= 0)return 0;
	double SSH = 0, SSV = 0, SIH = 0, SIV = 0, SRH = 0, SRV = 0;
	double k2SSH = 0, k2SSV = 0, k2SIH = 0, k2SIV = 0, k2SRH = 0, k2SRV = 0;
	double average = 0;
	double Pij = 0;
	double threshold = 0;
	uint MaxDegree1 = layer1.GetNode(0)->get<uint>("Degree");
	uint MaxDegree2 = layer2.GetNode(0)->get<uint>("Degree");
	for (uint i = 1; i < NodeNumber; i++){
		if (layer1.GetNode(i)->get<uint>("Degree")>MaxDegree1){
			MaxDegree1 = layer1.GetNode(i)->get<uint>("Degree");
		}
	}
	for (uint i = 1; i < NodeNumber; i++){
		if (layer2.GetNode(i)->get<uint>("Degree")>MaxDegree2){
			MaxDegree2 = layer2.GetNode(i)->get<uint>("Degree");
		}

	}
	for (uint i = 1; i <= MaxDegree1; i++){
		for (uint j = 1; j <= MaxDegree2; j++){
			for (uint k = 0; k < NodeNumber; k++){
				if (layer1.GetNode(k)->get<uint>("Degree") == i&&layer2.GetNode(k)->get<uint>("Degree") == j){
					if (layer1.GetNode(k)->get<char>("Disease") == 'S'&&layer2.GetNode(k)->get<char>("Disease") == 'S'){
						if (layer1.GetNode(k)->get<double>("Coefficient") == 1.0)SSH = SSH + 1;
						else SSV = SSV + 1;
					}
					else if (layer1.GetNode(k)->get<char>("Disease") == 'S'&&layer2.GetNode(k)->get<char>("Disease") == 'I'){
						if (layer1.GetNode(k)->get<double>("Coefficient") == 1.0)SIH = SIH + 1;
						else SIV = SIV + 1;
					}
					else if (layer1.GetNode(k)->get<char>("Disease") == 'S'&&layer2.GetNode(k)->get<char>("Disease") == 'R'){
						if (layer1.GetNode(k)->get<double>("Coefficient") == 1.0)SRH = SRH + 1;
						else SRV = SRV + 1;
					}
					Pij = Pij + 1;
				}
			}
			k2SSH += pow(i, 2)*SSH;
			k2SSV += pow(i, 2)*SSV;
			k2SIH += pow(i, 2)*SIH;
			k2SIV += pow(i, 2)*SIV;
			k2SRH += pow(i, 2)*SRH;
			k2SRV += pow(i, 2)*SRV;
			average += i*Pij;
			SSH = 0;
			SSV = 0;
			SIH = 0;
			SIV = 0;
			SRH = 0;
			SRV = 0;
			Pij = 0;
		}
	}
	average = average / NodeNumber;
	k2SSH = k2SSH / NodeNumber;
	k2SSV = k2SSV / NodeNumber;
	k2SIH = k2SIH / NodeNumber;
	k2SIV = k2SIV / NodeNumber;
	k2SRH = k2SRH / NodeNumber;
	k2SRV = k2SRV / NodeNumber;
	double Weak = pow((float)1 / para.get<double>("WeakEffect"), 2);
	threshold = para.get<double>("Mu_1")*average / (k2SSH + Weak*k2SSV + para.get<double>("Pi")*(k2SIH + Weak*k2SIV) + para.get<double >("Pr")*(k2SRH + Weak*k2SRV));

	return threshold;
}

vector<uint> DegreeSorted(Layer &layer){
	vector<pair<uint, uint>>IndexKey;
	vector<uint>SortedDegree;
	uint Nnum = layer.Get<uint>("Nnum");
	for (uint i = 0; i < Nnum; i++){
		IndexKey.push_back(make_pair(i, layer.GetNode(i)->get<uint>("Degree")));
	}
	sort(IndexKey.begin(), IndexKey.end(), [](pair<uint, uint>&node1, pair<uint, uint>&node2){return node1.second>node2.second; });
	for (uint i = 0; i < Nnum; i++){
		SortedDegree.push_back(IndexKey.at(i).first);
	}
	return SortedDegree;
}
vector<uint>BetweennessSorted(Layer &layer){
	uint Nnum = layer.Get<uint>("Nnum");
	vector<uint>SortedBetweeness;
	vector<double>BetweennessInorder(Nnum, 0);
	vector<pair<uint, double>>IndexKey;
	vector<vector<uint>>connectivity = layer.Connectivity();
	for (uint i = 0; i < Nnum; i++){
		stack<uint>S;
		vector<vector<uint>>P(Nnum);
		vector<double>sigma(Nnum, 0);
		sigma.at(i) = 1;
		vector<double>d(Nnum, -1);
		d.at(i) = 0;
		queue<uint>Q;
		Q.push(i);
		while (!Q.empty()){
			uint v = Q.front();
			Q.pop();
			S.push(v);
			for (auto w : connectivity.at(v)){
				if (d.at(w) < 0){
					Q.push(w);
					d.at(w) = d.at(v) + 1;
				}
				if (d.at(w) == d.at(v) + 1){
					sigma.at(w) = sigma.at(w) + sigma.at(v);
					P.at(w).push_back(v);
				}
			}
		}
		vector<double>delta(Nnum, 0);
		while (!S.empty()){
			uint w = S.top();
			S.pop();
			for (auto v : P.at(w)){
				delta.at(v) += (1 + delta.at(w))*sigma.at(v) / (sigma.at(w));
			}
			if (w != i)BetweennessInorder.at(w) += delta.at(w);
		}
	}
	for (uint i = 0; i < Nnum; i++){
		//BetweennessInorder.at(i) = BetweennessInorder.at(i) * 2 / (pow(Nnum, 2) - 3 * Nnum + 2);
		IndexKey.push_back(make_pair(i, BetweennessInorder.at(i)));
	}
	sort(IndexKey.begin(), IndexKey.end(), [](pair<uint, double>&node1, pair<uint, double>&node2){return node1.second>node2.second; });
	for (uint i = 0; i < Nnum; i++){
		SortedBetweeness.push_back(IndexKey.at(i).first);
	}
	return SortedBetweeness;
}