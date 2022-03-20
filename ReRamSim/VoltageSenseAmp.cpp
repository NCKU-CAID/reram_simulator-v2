#include <cmath>
#include <iostream>
#include "constant.h"
#include "formula.h"
#include "VoltageSenseAmp.h"

using namespace std;

VoltageSenseAmp::VoltageSenseAmp(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell): inputParameter(_inputParameter), tech(_tech), cell(_cell), FunctionUnit() {
	initialized = false;
}

void VoltageSenseAmp::Initialize(int _numReadCol, double _clkFreq) {
	//write our own design
}

void VoltageSenseAmp::CalculateUnitArea() {
	//write our own design
}

void VoltageSenseAmp::CalculateArea(double _widthVoltageSenseAmp) {	// Just add up the area of all the components
	//write our own design
}

void VoltageSenseAmp::CalculateLatency(double capInputLoad, double numRead) {
	//write our own design
}

void VoltageSenseAmp::CalculatePower(double numRead) {
	//write our own design
}

void VoltageSenseAmp::PrintProperty(const char* str) {
	//write our own design
}
