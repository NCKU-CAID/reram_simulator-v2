#include <cmath>
#include <iostream>
#include "constant.h"
#include "formula.h"
#include "Precharger.h"

using namespace std;

Precharger::Precharger(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell): inputParameter(_inputParameter), tech(_tech), cell(_cell), FunctionUnit() {
	initialized = false;
}

void Precharger::Initialize(int _numCol, double _resLoad, double _activityColWrite, int _numReadCellPerOperationNeuro, int _numWriteCellPerOperationNeuro) {
	//write our own design
}

void Precharger::CalculateArea(double _newHeight, double _newWidth, AreaModify _option) {
	//write our own design
}

void Precharger::CalculateLatency(double _rampInput, double _capLoad, double numRead, double numWrite){
	//write our own design
}

void Precharger::CalculatePower(double numRead, double numWrite) {
	//write our own design
}

void Precharger::PrintProperty(const char* str) {
	//write our own design
}
