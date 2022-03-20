#include <cmath>
#include <iostream>
#include "constant.h"
#include "formula.h"
#include "NewMux.h"

using namespace std;

NewMux::NewMux(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell): inputParameter(_inputParameter), tech(_tech), cell(_cell), FunctionUnit() {
	// TODO Auto-generated constructor stub
	initialized = false;
}

void NewMux::Initialize(int _numInput){
	//write our own design
}

void NewMux::CalculateArea(double _newHeight, double _newWidth, AreaModify _option) {
	//write our own design
}

void NewMux::CalculateLatency(double _rampInput, double _capLoad, double numRead, double numWrite) {	// For simplicity, assume shift register is ideal
	//write our own design
}

void NewMux::CalculatePower(double numRead, double numWrite, double numWritePulse, int mode_1T1R, double activityRowRead, double activityColWrite) {
	//write our own design
}

void NewMux::PrintProperty(const char* str) {
	//write our own design
}
