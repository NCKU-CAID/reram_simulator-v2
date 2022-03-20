#include <cmath>
#include <iostream>
#include <vector>
#include "constant.h"
#include "formula.h"
#include "Param.h"
#include "MultilevelSenseAmp.h"

using namespace std;

extern Param *param;

MultilevelSenseAmp::MultilevelSenseAmp(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell): inputParameter(_inputParameter), tech(_tech), cell(_cell), currentSenseAmp(_inputParameter, _tech, _cell), FunctionUnit() {
	initialized = false;
}

void MultilevelSenseAmp::Initialize(int _numCol, int _levelOutput, double _clkFreq, int _numReadCellPerOperationNeuro, bool _parallel) {
	//write our own design
}

void MultilevelSenseAmp::CalculateArea(double heightArray, double widthArray, AreaModify _option) {
	//write our own design
}

void MultilevelSenseAmp::CalculateLatency(const vector<double> &columnResistance, double numColMuxed, double numRead) {
	//write our own design
}

void MultilevelSenseAmp::CalculatePower(const vector<double> &columnResistance, double numRead) {
	//write our own design
}

void MultilevelSenseAmp::PrintProperty(const char* str) {
	//write our own design
}

double MultilevelSenseAmp::GetColumnLatency(double columnRes) {
	//write our own design
}

double MultilevelSenseAmp::GetColumnPower(double columnRes) {
	//write our own design
}
