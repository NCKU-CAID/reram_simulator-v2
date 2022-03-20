#include <cmath>
#include <iostream>
#include "constant.h"
#include "formula.h"
#include "NewSwitchMatrix.h"

using namespace std;

NewSwitchMatrix::NewSwitchMatrix(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell): inputParameter(_inputParameter), tech(_tech), cell(_cell), dff(_inputParameter, _tech, _cell), FunctionUnit() {
	// TODO Auto-generated constructor stub
	initialized = false;
}

NewSwitchMatrix::~NewSwitchMatrix() {
	// TODO Auto-generated destructor stub
}

void NewSwitchMatrix::Initialize(int _numOutput, double _activityRowRead, double _clkFreq){
	//write our own design
}

void NewSwitchMatrix::CalculateArea(double _newHeight, double _newWidth, AreaModify _option) {
	//write our own design
}

void NewSwitchMatrix::CalculateLatency(double _rampInput, double _capLoad, double _resLoad, double numRead, double numWrite) {	// For simplicity, assume shift register is ideal
	//write our own design
}

void NewSwitchMatrix::CalculatePower(double numRead, double numWrite, double activityRowRead) {
	//write our own design
}

void NewSwitchMatrix::PrintProperty(const char* str) {
	//write our own design
}

void NewSwitchMatrix::SaveOutput(const char* str) {
	//write our own design
}
