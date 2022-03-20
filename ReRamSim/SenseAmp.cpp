#include <cmath>
#include <iostream>
#include "constant.h"
#include "formula.h"
#include "SenseAmp.h"

using namespace std;

SenseAmp::SenseAmp(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell): inputParameter(_inputParameter), tech(_tech), cell(_cell), FunctionUnit() {
	initialized = false;
}

void SenseAmp::Initialize(int _numCol, bool _currentSense, double _senseVoltage, double _pitchSenseAmp, double _clkFreq, int _numReadCellPerOperationNeuro) {
	//write our own design
}

void SenseAmp::CalculateArea(double _newHeight, double _newWidth, AreaModify _option) {
	//write our own design
}

void SenseAmp::CalculateLatency(double numRead) {
	//write our own design
}

void SenseAmp::CalculatePower(double numRead) {
	//write our own design
}

void SenseAmp::PrintProperty(const char* str) {
	//write our own design
}
