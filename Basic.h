/**
******************************************************************************
* @file    Basic.h
* @author  Tokugawa
* @version 1.0
* @date    23-January-2018
* @brief   Basic Class Definition and Implement(Template)
*
*
@verbatim
******************************************************************************
**/
#ifndef BASIC_H
#define BASIC_H
/************************Macros***********************************************/
#include<string>
#include<vector>
#include<iostream>
#include <random>
#include<algorithm>
#include <stack>
#include<queue>
using namespace std;
typedef unsigned int uint;
class parameter;
class Node;
class Line;
class Layer;
/************************Macros***********************************************/
/************************Declaration******************************************/
class parameter{
private:
	string NetType_1;
	string NetType_2;
	double NetPara_1;
	double NetPara_2;
	double InitialInfected_1;
	double InitialInfected_2;
	double Beta_1;
	double Beta_2;
	double Mu_1;
	double Mu_2;
	double Pi;//2->1,I
	double Pr;//2->1,R
	double Qi;//1->2,I
	double Qr;//1->2,R
	double OverlapPercentage;
	double WeakPercentage;
	double WeakEffect;
public:
	parameter(){}
	parameter(
		string NetType_1,
		string NetType_2,
		double NetPara_1,
		double NetPara_2,
		double InitialInfected_1,
		double InitialInfected_2,
		double Beta_1,
		double Beta_2,
		double Mu_1,
		double Mu_2,
		double Pi,
		double Pr,
		double Qi,
		double Qr,
		double OverlapPercentage,
		double WeakPercentage,
		double WeakEffect);
	template<typename Element>
	Element get(string type);
	template<> string get(string type);
	template<> double get(string type);
	string Tostring();

};

class Node{
private:
	uint ID;
	char Disease;
	uint Degree;
	double Coefficient;
public:
	Node(uint ID, char Disease, uint Degree, double Coefficient);
	template<typename Element>
	Element get(string type);
	template<typename Element>
	bool set(string type, Element data);
};

class Line{
private:
	uint ID_1;
	uint ID_2;
	bool Flag;
public:
	void setL(uint ID_1 = 0, uint ID_2 = 0, bool Flag = false);
	uint get(string Element);
};

class Layer{
private:
	uint Nnum;
	uint Lnum;
	string Type;
	Node * Ncursor;
	Line * Lcursor;
public:
	Layer(uint Nnum = 0, string Type = "");
	~Layer();
	template<typename Element>
	Element Get(string Index);
	template<> uint Get(string Index);
	template<> string Get(string Index);
	Node* GetNode(uint ID);
	Line* GetLine(uint LineIndex);
	template<typename NetPara>
	void Genlay(NetPara pa);
	void Deslay(uint type);
	void ChaType(string NetType);
	//void print(char* type);
	//void Foperation(char *type);
	vector<vector<uint>> Connectivity();
};
/************************Declaration******************************************/
template<typename Element>
Element Node::get(string type){
	if (type == "ID")return ID;
	else if (type == "Degree")return Degree;
	else if (type == "Disease")return Disease;
	else if (type == "Coefficient")return Coefficient;
	else{
		cout << std::left << "Class Node::get--Undefined Element!" << endl;
		return 0;
	}

}
template<typename Element>
bool Node::set(string type, Element data){
	if (type == "ID")	ID = data;
	else if (type == "Degree") Degree = data;
	else if (type == "Disease") Disease = data;
	else if (type == "Coefficient") Coefficient = data;
	else{
		cout << std::left << "Class Node::set--Undefined Element!" << endl;
		return 0;
	}
	return 1;

}
template<> string Layer:: Get(string Index){
	if (Index == "NetType")return Type;
	else {
		cout << std::left << "Class Layer::Get<string>--Undefined Element！" << endl;
		return 0;
	}
}
template<> uint Layer::Get(string Index){
	if (Index == "Nnum")return Nnum;
	else if (Index == "Lnum")return Lnum;
	else {
		cout << std::left << "Class Layer::Get<uint>--Undefined Element！" << endl;
		return 0;
	}
}
template<typename NetPara>
void Layer::Genlay(NetPara pa){////网络生成算法
	if (Ncursor == NULL&&Nnum == 0)return;
	if (Type == "BA"&&strcmp(typeid(pa).name(), "double") == 0){
		if (pa < 2)pa = 2;
		uint SumD = 0;
		double a = 3 * (pa - 2);
		vector<double>P;
		double p=0;
		double rn1=0, rn2=0, rn3=0;
		uint Index1 = 0, Index2 = 0, Index3 = 0;
		/*构成一个三节点三条边的完全子图*/
		Lcursor[0].setL(Ncursor[0].get<uint>("ID"), Ncursor[1].get<uint>("ID"));
		Lcursor[1].setL(Ncursor[1].get<uint>("ID"), Ncursor[2].get<uint>("ID"));
		Lcursor[2].setL(Ncursor[0].get<uint>("ID"), Ncursor[2].get<uint>("ID"));
		Ncursor[0].set<uint>("Degree", 2);
		Ncursor[1].set<uint>("Degree", 2);
		Ncursor[2].set<uint>("Degree", 2);
		Lnum += 3;
		/*下面开始生成BA无标度网络,m0=m=3*/
		for (uint i = 3; i < Nnum; i++){
			for (uint j = 0; j < i; j++)SumD += (Ncursor[j].get<uint>("Degree") + a);
			for (uint j = 0; j < i; j++){
				p = (Ncursor[j].get<uint>("Degree") + a) / (SumD + 0.0);
				P.push_back(p);
			}
			for (uint j = 1; j < i; j++) P.at(j) += P.at(j - 1);
			do{
				rn1 = rand() / (RAND_MAX + 0.0);
				rn2 = rand() / (RAND_MAX + 0.0);
				rn3 = rand() / (RAND_MAX + 0.0);
				if (rn1 <= P.at(0))Index1 = 0;
				if (rn2 <= P.at(0))Index2 = 0;
				if (rn3 <= P.at(0))Index3 = 0;
				for (uint j = 0; j < i - 1; j++){
					if (rn1>P.at(j) && rn1 <= P.at(j + 1))Index1 = j + 1;
					if (rn2>P.at(j) && rn2 <= P.at(j + 1))Index2 = j + 1;
					if (rn3 > P.at(j) && rn3 <= P.at(j + 1))Index3 = j + 1;
				}
			} while (Index1 == Index2 || Index1 == Index3 || Index2 == Index3);
			Lcursor[Lnum].setL(Ncursor[Index1].get<uint>("ID"), Ncursor[i].get<uint>("ID"));
			Lnum++;
			Lcursor[Lnum].setL(Ncursor[Index2].get<uint>("ID"), Ncursor[i].get<uint>("ID"));
			Lnum++;
			Lcursor[Lnum].setL(Ncursor[Index3].get<uint>("ID"), Ncursor[i].get<uint>("ID"));
			Lnum++;
			Ncursor[Index1].set<uint>("Degree", Ncursor[Index1].get<uint>("Degree") + 1);
			Ncursor[Index2].set<uint>("Degree", Ncursor[Index2].get<uint>("Degree") + 1);
			Ncursor[Index3].set<uint>("Degree", Ncursor[Index3].get<uint>("Degree") + 1);
			Ncursor[i].set<uint>("Degree", Ncursor[i].get<uint>("Degree") + 3);
			SumD = 0;
			vector<double>().swap(P);
		}
	}
	else if (Type == "ER"&&strcmp(typeid(pa).name(), "unsigned int") == 0){//使用配置模型生成的ER随机图
		vector<uint>Rest;
		vector<uint>Index0;
		uint num = 0, rn1=0, rn2=0;
		bool flag = 0;
		default_random_engine generator;
		normal_distribution<double> distribution(/*mean=*/pa, /*stddev=*/1.0);
		for (uint i = 0; i < Nnum; i++){
			Ncursor[i].set<uint>("Degree", round(distribution(generator)));
			Rest.push_back(Ncursor[i].get<uint>("Degree"));
		}
		for (uint i = 0; i < Nnum; i++)num += Ncursor[i].get<uint>("Degree");
		if (num % 2 == 1){
			rn1 = rand() % Nnum;
			Ncursor[rn1].set<uint>("Degree", Ncursor[rn1].get<uint>("Degree") + 1);
			Rest.at(rn1)++;
		}
		num = 0;
		while (1){
			vector<uint>().swap(Index0);
			num++;
			for (uint i = 0; i < Nnum; i++){
				if (Rest.at(i) > 0)Index0.push_back(i);
			}
			if (Index0.size() <= 1 || num > 1E5)break;
			else {
				do{
					rn1 = rand() % (Index0.size());
					rn2 = rand() % (Index0.size());
				} while (rn1 == rn2);
				for (uint i = 0; i < Lnum; i++){
					if ((Lcursor[i].get("ID1") == Index0.at(rn1) && Lcursor[i].get("ID2") == Index0.at(rn2)) ||
						(Lcursor[i].get("ID2") == Index0.at(rn1) && Lcursor[i].get("ID1") == Index0.at(rn2)))
					{
						flag = 1;
						break;
					}
				}
				if (flag){ flag = 0; continue; }
				Lcursor[Lnum].setL(Index0.at(rn1), Index0.at(rn2));
				Lnum++;
				Rest.at(Index0.at(rn1))--;
				Rest.at(Index0.at(rn2))--;
			}
		}
		vector<uint>().swap(Rest);
	}
	else if (Type == "WS"&&strcmp(typeid(pa).name(), "double") == 0){
		if (pa > 1)pa = 1;
		if (pa < 0)pa = 0;
		for (uint i = 0; i < Nnum; i++){///生成规则环状网络
			uint n1=0, n2=0, n3=0;
			n1 = (i + 1) % Nnum;
			n2 = (i + 2) % Nnum;
			n3 = (i + 3) % Nnum;
			Lcursor[Lnum].setL(i, n1);
			Lnum++;
			Lcursor[Lnum].setL(i, n2);
			Lnum++;
			Lcursor[Lnum].setL(i, n3);
			Lnum++;
			Ncursor[i].set<uint>("Degree", Ncursor[i].get<uint>("Degree") + 3);
			Ncursor[n1].set<uint>("Degree", Ncursor[n1].get<uint>("Degree") + 1);
			Ncursor[n2].set<uint>("Degree", Ncursor[n2].get<uint>("Degree") + 1);
			Ncursor[n3].set<uint>("Degree", Ncursor[n3].get<uint>("Degree") + 1);
		}
		//随机重连

		for (uint i = 0; i < Lnum; i++){
			uint rn=0;
			double p=0;
			bool flag = false;
			p = rand() / (RAND_MAX + 0.0);
			if (p > pa)continue;
			while (1){
				rn = rand() % Nnum;
				if (rn == Lcursor[i].get("ID1") || rn == Lcursor[i].get("ID2"))continue;
				else{
					for (uint j = 0; j < Lnum; j++){
						if ((Lcursor[j].get("ID1") == Lcursor[i].get("ID1") && Lcursor[j].get("ID2") == rn) || (Lcursor[j].get("ID1") == rn&&Lcursor[j].get("ID2") == Lcursor[i].get("ID1"))){
							flag = true;
							break;
						}
					}
					if (flag == true){ flag = false; continue; }
					else {
						Ncursor[Lcursor[i].get("ID2")].set<uint>("Degree", Ncursor[Lcursor[i].get("ID2")].get<uint>("Degree") - 1);
						Ncursor[rn].set<uint>("Degree", Ncursor[rn].get<uint>("Degree") + 1);
						Lcursor[i].setL(Lcursor[i].get("ID1"), rn);
						break;
					}
				}
			}
		}
	}
}

template<> double parameter::get(string type){
	if (type == "NetPara_1")return NetPara_1;
	else if (type == "NetPara_2")return NetPara_2;
	else if (type == "InitialInfected_1")return InitialInfected_1;
	else if (type == "InitialInfected_2")return InitialInfected_2;
	else if (type == "Beta_1")return Beta_1;
	else if (type == "Beta_2")return Beta_2;
	else if (type == "Mu_1")return Mu_1;
	else if (type == "Mu_2")return Mu_2;
	else if (type == "Pi")return Pi;
	else if (type == "Pr")return Pr;
	else if (type == "Qi")return Qi;
	else if (type == "Qr")return Qr;
	else if (type == "OverlapPercentage")return OverlapPercentage;
	else if (type == "WeakPercentage")return WeakPercentage;
	else if (type == "WeakEffect")return WeakEffect;
	else{
		cout << std::left << "Class parameter::get<double>--Undefined Element!" << endl;
		return 0;
	}
}
template<> string parameter::get(string type){
	if (type == "NetworkType_1")return NetType_1;
	else if (type == "NetworkType_2")return NetType_2;
	else{
		cout << std::left << "Class parameter::get<string>--Undefined Element!" << endl;
		return 0;
	}
}

#endif