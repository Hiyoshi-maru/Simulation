#include "main.h"
int main(int argc, char* argv[]){
	/**/
	srand((unsigned int)time(NULL));
	uint ProcessNumber = sizeof(sim)/sizeof(sim[0]);
	HANDLE* Parameter=new HANDLE [ProcessNumber];
	uint* ParameterID=new uint[ProcessNumber];
	DWORD* ParameterExitCode=new DWORD[ProcessNumber];
	for (unsigned int i = 0; i < ProcessNumber; i++){
		Parameter[i] = (HANDLE)_beginthreadex(
			NULL,
			0,
			ParameterThread,
			&sim[i],
			CREATE_SUSPENDED,
			&ParameterID[i]
			);
		if (Parameter[i] == 0){ cout << "Fail to create a thread" << endl; exit(0); }
		cout << "Thread " << i + 1 << " begins" << endl;
		ResumeThread(Parameter[i]);
	}
	for (unsigned int i = 0; i < ProcessNumber; i++){
		WaitForSingleObject(Parameter[i], INFINITE);
	}
	cout << endl;
	for (unsigned int i = 0; i < ProcessNumber; i++){
		GetExitCodeThread(Parameter[i], &ParameterExitCode[i]);
		cout << "Thread " << i + 1 << " ends with code " << ParameterExitCode[i] << endl;
		CloseHandle(Parameter[i]);
	}
	delete[] Parameter;
	delete[]ParameterID;
	delete[] ParameterExitCode;
	cout << "Total Time:" << clock() << endl;
	
	/*
	Layer layer1(1000,"WS");
	Layer layer2(1000,"WS");
	layer1.Genlay(0.5);
	layer2.Genlay(0.5);
	return 0;*/
}