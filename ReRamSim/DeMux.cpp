#include <cmath>
#include <iostream>
#include "constant.h"
#include "formula.h"
#include "DeMux.h"

using namespace std;

DeMux::DeMux(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell): inputParameter(_inputParameter), tech(_tech), cell(_cell), FunctionUnit() {
	initialized = false;
}

void DeMux::Initialize(int _numInput, int numRow){
	//write our own design
}

void DeMux::CalculateArea(double _newHeight, double _newWidth, AreaModify _option){
	//write our own design
}

void DeMux::CalculateLatency(double _rampInput, double numRead) {	// rampInput actually is not used
	//write our own design
}

void DeMux::CalculatePower(double numRead) {
	//write our own design
}

void DeMux::PrintProperty(const char* str) {
	//write our own design
}

void DeMux::SaveOutput(const char* str) {
	//write our own design
}
