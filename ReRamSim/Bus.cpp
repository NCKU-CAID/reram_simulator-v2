#include <cmath>
#include <iostream>
#include "constant.h"
#include "typedef.h"
#include "formula.h"
#include "Bus.h"
#include "Param.h"

using namespace std;

extern Param *param;

Bus::Bus(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell): inputParameter(_inputParameter), tech(_tech), cell(_cell), FunctionUnit() {
	initialized = false;
}

void Bus::Initialize(BusMode _mode, int _numRow, int _numCol, double _delaytolerance, double _busWidth, double _unitHeight, double _unitWidth){
	//write our own design
}

void Bus::CalculateArea(double foldedratio, bool overLap) {
	//write our own design
}

void Bus::CalculateLatency(double numRead){
	//write our own design
}

void Bus::CalculatePower(double numBitAccess, double numRead) {
	//write our own design
}

void Bus::PrintProperty(const char* str) {
	//write our own design
}

void Bus::SaveOutput(const char* str) {
	//write our own design
}

