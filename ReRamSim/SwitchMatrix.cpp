#include <cmath>
#include <iostream>
#include "constant.h"
#include "formula.h"
#include "SwitchMatrix.h"

using namespace std;

SwitchMatrix::SwitchMatrix(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell): inputParameter(_inputParameter), tech(_tech), cell(_cell), dff(_inputParameter, _tech, _cell), FunctionUnit() {
	initialized = false;
}

void SwitchMatrix::Initialize(int _mode, int _numOutput, double _resTg, bool _neuro, bool _parallelWrite, double _activityRowRead, double _activityColWrite, int _numWriteCellPerOperationMemory, int _numWriteCellPerOperationNeuro, double _numWritePulse, double _clkFreq){
	//write our own design
}

void SwitchMatrix::CalculateArea(double _newHeight, double _newWidth, AreaModify _option) {
	//write our own design
}

void SwitchMatrix::CalculateLatency(double _rampInput, double _capLoad, double _resLoad, double numRead, double numWrite) {
	//write our own design
}

void SwitchMatrix::CalculatePower(double numRead, double numWrite, double activityRowRead, double activityColWrite) {
	//write our own design
}

void SwitchMatrix::PrintProperty(const char* str) {
	//write our own design
}

void SwitchMatrix::SaveOutput(const char* str) {
	//write our own design
}
