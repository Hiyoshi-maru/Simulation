
/**
******************************************************************************
* @file    Basic.h
* @author  Tokugawa
* @version 1.0
* @date    23-January-2018
* @brief   Basic Class Implementation(No Template)
*
*
@verbatim
******************************************************************************
**/
/************************Defination and Implementation************************/
#include"Basic.h"
parameter::parameter(
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
	double WeakEffect) {

	this->NetType_1 = NetType_1;
	this->NetType_2 = NetType_2;
	this->NetPara_1 = NetPara_1;
	this->NetPara_2 = NetPara_2;
	this->InitialInfected_1 = InitialInfected_1;
	this->InitialInfected_2 = InitialInfected_2;
	this->Beta_1 = Beta_1;
	this->Beta_2 = Beta_2;
	this->Mu_1 = Mu_1;
	this->Mu_2 = Mu_2;
	this->Pi = Pi;
	this->Pr = Pr;
	this->Qi = Qi;
	this->Qr = Qr;
	this->OverlapPercentage = OverlapPercentage;
	this->WeakPercentage = WeakPercentage;
	this->WeakEffect = WeakEffect;
}
string parameter::Tostring(){
	return NetType_1 +
		"_" + NetType_2 +
		"_" + to_string(NetPara_1) +
		"_" + to_string(NetPara_2) +
		"_" + to_string(InitialInfected_1) +
		"_" + to_string(InitialInfected_2) +
		"_" + to_string(Beta_1) +
		"_" + to_string(Beta_2) +
		"_" + to_string(Mu_1) +
		"_" + to_string(Mu_2) +
		"_" + to_string(Pi) +
		"_" + to_string(Pr) +
		"_" + to_string(Qi) +
		"_" + to_string(Qr) +
		"_" + to_string(OverlapPercentage) +
		"_" + to_string(WeakPercentage) +
		"_" + to_string(WeakEffect);
}

Node::Node(uint ID = 0, char Disease = 'S', uint Degree = 0, double Coefficient = 1.0){
	this->ID = ID;
	this->Disease = Disease;
	this->Degree = Degree;
	this->Coefficient = Coefficient;
}

void Line::setL(uint ID_1, uint ID_2, bool Flag){
	this->ID_1 = ID_1;
	this->ID_2 = ID_2;
	this->Flag = Flag;
}
uint Line::get(string Element){
	if (Element == "ID1")return ID_1;
	else if (Element == "ID2")return ID_2;
	else if (Element == "Flag")return Flag;
	else {
		cout << std::left << "Class Line::get--Undefined Element!" << endl;
		return 0;
	}
}

Layer::Layer(uint Nnum, string Type){
	this->Nnum = Nnum;
	this->Type = Type;
	Lnum = 0;
	uint Lmax = Nnum*(Nnum - 1) / 2;
	if (Nnum > 0){
		Ncursor = new Node[Nnum];
		for (uint i = 0; i < Nnum; i++){
			Ncursor[i].set<uint>("ID", i);
			Ncursor[i].set<uint>("Degree", 0);
		}
	}
	else Ncursor = NULL;
	if (Lmax > 0){
		Lcursor = new Line[Lmax];
	}
	else Lcursor = NULL;
}
Layer::~Layer(){
	if (Ncursor != NULL)delete[]Ncursor;
	if (Lcursor != NULL)delete[]Lcursor;
}
Node* Layer::GetNode(uint ID){
	if (ID >= 0 && ID < Nnum)return Ncursor + ID;
	else {
		cout << std::left << "Class Layer::GetNode--No Such Node!" << endl;
		return NULL;
	}
}
Line* Layer::GetLine(uint LineIndex){
	if (LineIndex >= 0 && LineIndex < Lnum)return Lcursor + LineIndex;
	else {
		cout << std::left << "Class Layer::GetLine--No Such Line!" << endl;
		return NULL;
	}
}
void Layer::ChaType(string NetType){
	if (Lnum == 0)Type = NetType;
}
vector<vector<uint>> Layer::Connectivity(){
	if (Ncursor == NULL || Lcursor == NULL)exit(-1);
	vector<vector<uint>>connectivity(Nnum);
	for (uint i = 0; i < Lnum; i++){
		connectivity.at((Lcursor + i)->get("ID1")).push_back((Lcursor + i)->get("ID2"));
		connectivity.at((Lcursor + i)->get("ID2")).push_back((Lcursor + i)->get("ID1"));
	}
	return connectivity;
}
void Layer::Deslay(uint type){////复原已经传播后的的网络
	if (type == 0){
		if (Ncursor == NULL&& Nnum == 0)return;
		if (Lcursor == NULL&&Lnum == 0)return;
		for (uint i = 0; i < Nnum; i++){
			Ncursor[i].set<char>("Disease", 'S');
			//Ncursor[i].set<double>("Coefficient", 1.0);
		}
	}
	else if (type == 1){
		if (Ncursor == NULL&& Nnum == 0)return;
		if (Lcursor == NULL&&Lnum == 0)return;
		for (uint i = 0; i < Lnum; i++){
			Lcursor[i].setL();
		}
		Lnum = 0;
		for (uint i = 0; i < Nnum; i++){
			Ncursor[i].set<char>("Disease", 'S');
			Ncursor[i].set<uint>("Degree", 0);
			Ncursor[i].set<double>("Coefficient", 1.0);
		}


	}
}
/************************Defination and Implementation************************/