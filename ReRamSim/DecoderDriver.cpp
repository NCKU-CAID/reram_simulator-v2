#include <cmath>
#include <iostream>
#include "constant.h"
#include "formula.h"
#include "DecoderDriver.h"

using namespace std;

DecoderDriver::DecoderDriver(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell): inputParameter(_inputParameter), tech(_tech), cell(_cell), FunctionUnit() {
	initialized = false;
}

void DecoderDriver::Initialize(int _mode, int _numOutput /* # of array rows/columns */, int numLoad) {
	//write our own design
}

void DecoderDriver::CalculateArea(double _newHeight, double _newWidth, AreaModify _option) {
	//write our own design
}

void DecoderDriver::CalculateLatency(double _rampInput, double _capLoad1, double _capLoad2, double _resLoad, double numRead, double numWrite) {
	//write our own design
}

void DecoderDriver::CalculatePower(double numReadCellPerOp, double numWriteCellPerOp, double numRead, double numWrite) {
	//write our own design
}

void DecoderDriver::PrintProperty(const char* str) {
	//write our own design
}

void DecoderDriver::SaveOutput(const char* str) {
	//write our own design
}

