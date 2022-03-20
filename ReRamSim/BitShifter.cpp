#include <cmath>
#include <iostream>
#include "constant.h"
#include "formula.h"
#include "BitShifter.h"

using namespace std;

BitShifter::BitShifter(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell): inputParameter(_inputParameter), tech(_tech), cell(_cell), dff(_inputParameter, _tech, _cell), FunctionUnit() {
	initialized = false;
}

void BitShifter::Initialize(int _numUnit, int _numBit, double _clkFreq) {
	// write our own design
}

void BitShifter::CalculateArea(double _newHeight, double _newWidth, AreaModify _option) {
	// write our own design
}

void BitShifter::CalculateLatency(double numRead) {
	// write our own design
}

void BitShifter::CalculatePower(double numRead) {
	// write our own design
}

void BitShifter::PrintProperty(const char* str) {
	// write our own design
}
