#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include "constant.h"
#include "formula.h"
#include "WeightGradientUnit.h"
#include "Param.h"

using namespace std;
extern Param *param;

WeightGradientUnit::WeightGradientUnit(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell): 
										inputParameter(_inputParameter), tech(_tech), cell(_cell), FunctionUnit(),
										wlDecoder(_inputParameter, _tech, _cell),
										wlSwitchMatrix(_inputParameter, _tech, _cell),
										mux(_inputParameter, _tech, _cell),
										muxDecoder(_inputParameter, _tech, _cell),
										precharger(_inputParameter, _tech, _cell),
										senseAmp(_inputParameter, _tech, _cell),
										sramWriteDriver(_inputParameter, _tech, _cell),
										adder(_inputParameter, _tech, _cell),
										dff(_inputParameter, _tech, _cell),
										multilevelSenseAmp(_inputParameter, _tech, _cell),
										multilevelSAEncoder(_inputParameter, _tech, _cell),
										shiftAdd(_inputParameter, _tech, _cell),
										accumulation(_inputParameter, _tech, _cell),
										bufferInput(_inputParameter, _tech, _cell),
										bufferOutput(_inputParameter, _tech, _cell){
	initialized = false;
}

void WeightGradientUnit::Initialize(int _numMemRow, int _numMemCol) {
	//write our own design
}

void WeightGradientUnit::CalculateArea() {  //calculate layout area for total design
	//write our own design
}

void WeightGradientUnit::CalculateLatency(int numRead, int numBitDataLoad) {
	//write our own design
}

void WeightGradientUnit::CalculatePower(int numRead, int numBitDataLoad) {
	//write our own design
}

void WeightGradientUnit::PrintProperty(const char* str) {
	//write our own design
}
