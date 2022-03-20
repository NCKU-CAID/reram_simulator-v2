#include <cmath>
#include <iostream>
#include "constant.h"
#include "formula.h"
#include "SRAMWriteDriver.h"

using namespace std;

SRAMWriteDriver::SRAMWriteDriver(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell): inputParameter(_inputParameter), tech(_tech), cell(_cell), FunctionUnit() {
	initialized = false;
}

void SRAMWriteDriver::Initialize(int _numCol, double _activityColWrite, int _numWriteCellPerOperationNeuro){
	//write our own design
}

void SRAMWriteDriver::CalculateArea(double _newHeight, double _newWidth, AreaModify _option) {
	//write our own design
}

void SRAMWriteDriver::CalculateLatency(double _rampInput, double _capLoad, double _resLoad, double numWrite){
	//write our own design
}

void SRAMWriteDriver::CalculatePower(double numWrite) {
	//write our own design
}

void SRAMWriteDriver::PrintProperty(const char* str) {
	//write our own design
}
