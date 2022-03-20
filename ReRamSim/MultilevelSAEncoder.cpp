#include <cmath>
#include <iostream>
#include "constant.h"
#include "formula.h"
#include "MultilevelSAEncoder.h"

using namespace std;

MultilevelSAEncoder::MultilevelSAEncoder(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell): inputParameter(_inputParameter), tech(_tech), cell(_cell), FunctionUnit() {
	initialized = false;
}

void MultilevelSAEncoder::Initialize(int _numLevel, int _numEncoder){
	//write our own design
}

void MultilevelSAEncoder::CalculateArea(double _newHeight, double _newWidth, AreaModify _option) {
	//write our own design
}

void MultilevelSAEncoder::CalculateLatency(double _rampInput, double numRead){
	//write our own design
}

void MultilevelSAEncoder::CalculatePower(double numRead) {
	//write our own design
}

void MultilevelSAEncoder::PrintProperty(const char* str) {
	//write our own design
}
