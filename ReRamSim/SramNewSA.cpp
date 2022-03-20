#include <cmath>
#include <iostream>
#include "constant.h"
#include "formula.h"
#include "SramNewSA.h"

using namespace std;

SramNewSA::SramNewSA(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell): inputParameter(_inputParameter), tech(_tech), cell(_cell), FunctionUnit() {
	initialized = false;
}

void SramNewSA::Initialize(int _numCol, int _levelOutput) {
	//write our own design
}

void SramNewSA::CalculateArea(double _newHeight, double _newWidth, AreaModify _option) {
	//write our own design
}

void SramNewSA::CalculateLatency(double numRead) {
	//write our own design
}

void SramNewSA::CalculatePower(double numRead) {
	//write our own design
}

void SramNewSA::PrintProperty(const char* str) {
	//write our own design
}
