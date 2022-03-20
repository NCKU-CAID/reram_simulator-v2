#include <cmath>
#include <iostream>
#include "constant.h"
#include "formula.h"
#include "ShiftAdd.h"

using namespace std;

ShiftAdd::ShiftAdd(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell): inputParameter(_inputParameter), tech(_tech), cell(_cell), adder(_inputParameter, _tech, _cell), dff(_inputParameter, _tech, _cell), FunctionUnit() {
	initialized = false;
}

void ShiftAdd::Initialize(int _numUnit, int _numAdderBit, double _clkFreq, SpikingMode _spikingMode, int _numReadPulse) {
	//write our own design
}

void ShiftAdd::CalculateArea(double _newHeight, double _newWidth, AreaModify _option) {
	//write our own design
}

void ShiftAdd::CalculateLatency(double numRead) {
	//write our own design
}

void ShiftAdd::CalculatePower(double numRead) {
	//write our own design
}

void ShiftAdd::PrintProperty(const char* str) {
	//write our own design
}

void ShiftAdd::SaveOutput(const char* str) {
	//write our own design
}
