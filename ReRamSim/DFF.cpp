#include <cmath>
#include <iostream>
#include "constant.h"
#include "formula.h"
#include "DFF.h"

using namespace std;

DFF::DFF(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell): inputParameter(_inputParameter), tech(_tech), cell(_cell), FunctionUnit() {
	initialized = false;
}

void DFF::Initialize(int _numDff, double _clkFreq){
	//write our own design
}

void DFF::CalculateArea(double _newHeight, double _newWidth, AreaModify _option) {
	//write our own design
}

void DFF::CalculateLatency(double _rampInput, double numRead){
	//write our own design
}

void DFF::CalculatePower(double numRead, double numDffPerOperation) {
	//write our own design
}

void DFF::PrintProperty(const char* str) {
	//write our own design
}

void DFF::SaveOutput(const char* str) {
	//write our own design
}

