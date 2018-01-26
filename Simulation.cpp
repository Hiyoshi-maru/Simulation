/**
******************************************************************************
* @file    Simulation.h
* @author  Tokugawa
* @version 1.0
* @date    25-January-2018
* @brief   Function Implementations for Simulation.h
*
*
@verbatim
******************************************************************************
**/
#include "Simulation.h"
const uint STEP = 500;
const uint TIMES = 20;
void Simulation(Layer &layer1,Layer &layer2, Sim sim, string type){
	if (type == "Parameters_Effect"){
		string directory("d:\\Tokugawa\\MultiNet_Disease\\Test\\");
		if (_access((directory + sim.Factor).c_str(), 0) != 0)system(("md " + directory + sim.Factor).c_str());
		for (uint i = 0; i < sim.Number; i++){
			vector<double>temp1;
			vector<double>temp2;
			vector<double>Result;
			layer1.Deslay(1);
			layer2.Deslay(1);
			uint para1u, para2u;
			layer1.ChaType(sim.para[i].get<string>("NetworkType_1"));
			layer2.ChaType(sim.para[i].get<string>("NetworkType_2"));
			if (sim.para[i].get<string>("NetworkType_1") == "ER"){
				para1u = sim.para[i].get<double>("NetPara_1");
				layer1.Genlay(para1u);
			}
			else layer1.Genlay(sim.para[i].get<double>("NetPara_1"));
			if (sim.para[i].get<string>("NetworkType_2")=="ER"){
				para2u = sim.para[i].get<double>("NetPara_2");
				layer2.Genlay(para2u);
			}
			else layer2.Genlay(sim.para[i].get<double>("NetPara_2"));
			OverLap(layer1, layer2, sim.para[i].get<double>("OverlapPercentage"));
			for (uint k = 0; k < TIMES; k++){
				init(layer1, layer2, sim.para[i]);
				for (uint j = 0; j < STEP; j++){
					spread(layer1, layer2, sim.para[i]);
					recover(layer1, layer2, sim.para[i]);
					CalculateSIR(layer1, layer2, temp1);
				}
				if (temp2.size() == 0){ temp2.assign(temp1.begin(), temp1.end()); }
				else { transform(temp1.begin(), temp1.end(), temp2.begin(), temp2.begin(), [](double a, double b){return a + b; }); }
				layer1.Deslay(0);
				layer2.Deslay(0);
				vector<double>().swap(temp1);
			}
			Result.resize(temp2.size());
			transform(temp2.begin(), temp2.end(), Result.begin(), [](double a){return a / TIMES; });
			vector<double>().swap(temp2);
			directory = "d:\\Tokugawa\\MultiNet_Disease\\Datafiles\\";
			directory = directory + sim.Factor + "\\" + sim.para[i].get<string>("NetworkType_1")+"\\";
			if (_access(directory.c_str(), 0) != 0)system(("md " + directory).c_str());
			directory = directory + "\\" + sim.para[i].Tostring() + ".txt";
			if (_access(directory.c_str(), 0) == 0)remove(directory.c_str());
			Foperation(Result, directory);
		}
		
	}
	else if (type == "Threshold_Effect"){
		string directory("d:\\Tokugawa\\MultiNet_Disease\\Threshold_Effect\\");
		if (_access((directory + sim.Factor).c_str(), 0) != 0)system(("md " + directory + sim.Factor).c_str());
		vector<double>Result;
		for (uint i = 0; i < sim.Number; i++){	
			layer1.Deslay(1);
			layer2.Deslay(1);
			uint para1u, para2u;
			layer1.ChaType(sim.para[i].get<string>("NetworkType_1"));
			layer2.ChaType(sim.para[i].get<string>("NetworkType_2"));
			if (sim.para[i].get<string>("NetworkType_1") == "ER"){
				para1u = sim.para[i].get<double>("NetPara_1");
				layer1.Genlay(para1u);
			}
			else layer1.Genlay(sim.para[i].get<double>("NetPara_1"));
			if (sim.para[i].get<string>("NetworkType_2") == "ER"){
				para2u = sim.para[i].get<double>("NetPara_2");
				layer2.Genlay(para2u);
			}
			else layer2.Genlay(sim.para[i].get<double>("NetPara_2"));
			OverLap(layer1, layer2, sim.para[i].get<double>("OverlapPercentage"));
			init(layer1, layer2, sim.para[i]);
			layer1.Deslay(0);
			///此处根据需要进行传播
			for (uint j = 0; j < STEP; j++){
				//cout << std::left << sim.Factor << " Parameter" << i + 1 << "," << k + 1 << "Times Simulation, " <<"STEP " << j + 1 << endl;
				spread(layer1, layer2, sim.para[i]);
				recover(layer1, layer2, sim.para[i]);
				layer1.Deslay(0);
				Result.push_back(Threshold(layer1, layer2, sim.para[i]));
				//Calculate(layer1, layer2, temp1);
			}
		}
		directory = directory + sim.Factor + "\\" + sim.Factor + ".txt";
		Foperation(Result, directory.c_str(), sim.Number); 
	}
	else if (type == "Immunization_Effect"){
		string directory("d:\\Tokugawa\\MultiNet_Disease\\Immunization\\Simulation\\");
		if (_access((directory + sim.Factor).c_str(), 0) != 0)system(("md " + directory + sim.Factor).c_str());
		uint para1u, para2u;
		/*生成网络*/
		layer1.ChaType(sim.para[0].get<string>("NetworkType_1"));
		layer2.ChaType(sim.para[0].get<string>("NetworkType_1"));
		if (sim.para[0].get<string>("NetworkType_1") == "ER"){
			para1u = sim.para[0].get<double>("NetPara_1");
			layer1.Genlay(para1u);
		}
		else layer1.Genlay(sim.para[0].get<double>("NetPara_1"));
		if (sim.para[0].get<string>("NetworkType_2") == "ER"){
			para2u = sim.para[0].get<double>("NetPara_2");
			layer2.Genlay(para2u);
		}
		else layer2.Genlay(sim.para[0].get<double>("NetPara_2"));
		OverLap(layer1, layer2, sim.para[0].get<double>("OverlapPercentage"));
		vector<uint>SortedDegree;
		vector<uint>SortedBetweenness;
		if (sim.Factor == "DegreeTargeted")SortedDegree = DegreeSorted(layer1);
		else if (sim.Factor == "BetweennessTargeted")SortedBetweenness = BetweennessSorted(layer1);
		for (uint i = 0; i < sim.Number; i++){
			vector<double>temp1;
			vector<double>temp2;
			vector<double>Result;
			for (double immunization = 0; immunization < 0.5; immunization += 0.05){
				for (uint k = 0; k < TIMES; k++){
					cout << "Times " << k << endl;
					if (sim.Factor == "DegreeTargeted")Immunization::Targeted(layer1, layer2, SortedDegree, immunization);
					else if (sim.Factor == "BetweennessTargeted")Immunization::Targeted(layer1, layer2, SortedBetweenness, immunization);
					else if (sim.Factor == "Acquaintance")Immunization::Acquaintance(layer1, layer2, immunization);
					init(layer1, layer2, sim.para[0]);
					for (uint j = 0; j < STEP; j++){
						cout << "Step :" << j << endl;
						spread(layer1, layer2, sim.para[i]);
						recover(layer1, layer2, sim.para[i]);
						CalculateSIR(layer1, layer2, temp1);
					}
					if (temp2.size() == 0){ temp2.assign(temp1.begin(), temp1.end()); }
					else { transform(temp1.begin(), temp1.end(), temp2.begin(), temp2.begin(), [](double a, double b){return a + b; }); }
					layer1.Deslay(0);
					layer2.Deslay(0);
					vector<double>().swap(temp1);
				}
				Result.resize(temp2.size());
				transform(temp2.begin(), temp2.end(), Result.begin(), [](double a){return a / TIMES; });
				vector<double>().swap(temp2);
				//layer1.Deslay(1);
				//layer2.Deslay(1);
				directory = "d:\\Tokugawa\\MultiNet_Disease\\Immunization\\Simulation\\";
				directory = directory + sim.Factor + "\\" + sim.para[i].get<string>("NetworkType_1");
				if (_access(directory.c_str(), 0) != 0)system(("md " + directory).c_str());
				directory = directory + "\\" + sim.para[i].Tostring() + '_' + to_string(immunization) + ".txt";
				if (_access(directory.c_str(), 0) == 0)remove(directory.c_str());
				Foperation(Result, directory);
			}
		}
	}
}
void Foperation(vector<double> result, string filename/*,uint number*/){

	ofstream file;
	file.open(filename, ios::out | ios::app);
	if (!file){ cout << "File Open Failed！"; }
	else{
		for (uint i = 0; i < result.size() - 5; i = i + 6)
		{
			file << setprecision(4) << fixed << result.at(i) << '\t'
				<< setprecision(4) << fixed << result.at(i + 1) << '\t'
				<< setprecision(4) << fixed << result.at(i + 2) << '\t'
				<< setprecision(4) << fixed << result.at(i + 3) << '\t'
				<< setprecision(4) << fixed << result.at(i + 4) << '\t'
				<< setprecision(4) << fixed << result.at(i + 5) << endl;
		}

		file.close();
	}
	/*
	ofstream file;
	file.open(filename, ios::out | ios::app);
	if (!file){ cout << "文件未打开！"; }
	for (uint i = 0; i < STEP; i++){
	for (uint j = 0; j < number; j++){
	file << setprecision(6) << fixed << result.at(i + j*STEP) << '\t';

	}
	file << endl;
	}*/

	file.close();
}
void Foperation(vector<double> result, string filename,uint number){

	/*ofstream file;
	file.open(filename, ios::out | ios::app);
	if (!file){ cout << "文件未打开！"; }
	else{
		for (uint i = 0; i < result.size() - 5; i = i + 6)
		{
			file << setprecision(4) << fixed << result.at(i) << '\t'
				<< setprecision(4) << fixed << result.at(i + 1) << '\t'
				<< setprecision(4) << fixed << result.at(i + 2) << '\t'
				<< setprecision(4) << fixed << result.at(i + 3) << '\t'
				<< setprecision(4) << fixed << result.at(i + 4) << '\t'
				<< setprecision(4) << fixed << result.at(i + 5) << endl;
		}

		file.close();
	}
	*/
	ofstream file;
	file.open(filename, ios::out | ios::app);
	if (!file){ cout << "File Open Failed！"; }
	for (uint i = 0; i < STEP; i++){
	for (uint j = 0; j < number; j++){
	file << setprecision(6) << fixed << result.at(i + j*STEP) << '\t';

	}
	file << endl;
	}

	file.close();
}