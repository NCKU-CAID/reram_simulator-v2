#include <cmath>
#include <iostream>
#include <vector>
#include "constant.h"
#include "formula.h"
#include "SubArray.h"


using namespace std;

SubArray::SubArray(InputParameter& _inputParameter, Technology& _tech, MemCell& _cell):
						inputParameter(_inputParameter), tech(_tech), cell(_cell),
						wlDecoder(_inputParameter, _tech, _cell),
						wlDecoderDriver(_inputParameter, _tech, _cell),
						wlNewDecoderDriver(_inputParameter, _tech, _cell),
						wlSwitchMatrix(_inputParameter, _tech, _cell),
						wlNewSwitchMatrix(_inputParameter, _tech, _cell),
						slSwitchMatrix(_inputParameter, _tech, _cell),
						mux(_inputParameter, _tech, _cell),
						muxDecoder(_inputParameter, _tech, _cell),
						precharger(_inputParameter, _tech, _cell),
						senseAmp(_inputParameter, _tech, _cell),
						sramWriteDriver(_inputParameter, _tech, _cell),
						rowCurrentSenseAmp(_inputParameter, _tech, _cell),
						adder(_inputParameter, _tech, _cell),
						dff(_inputParameter, _tech, _cell),
						multilevelSenseAmp(_inputParameter, _tech, _cell),
						multilevelSAEncoder(_inputParameter, _tech, _cell),
						shiftAdd(_inputParameter, _tech, _cell),
						/* for BP (Transpose SubArray) */
						wlDecoderBP(_inputParameter, _tech, _cell),
						wlSwitchMatrixBP(_inputParameter, _tech, _cell),
						prechargerBP(_inputParameter, _tech, _cell),
						senseAmpBP(_inputParameter, _tech, _cell),
						sramWriteDriverBP(_inputParameter, _tech, _cell),
						muxBP(_inputParameter, _tech, _cell),
						muxDecoderBP(_inputParameter, _tech, _cell),
						rowCurrentSenseAmpBP(_inputParameter, _tech, _cell),
						adderBP(_inputParameter, _tech, _cell),
						dffBP(_inputParameter, _tech, _cell),
						multilevelSenseAmpBP(_inputParameter, _tech, _cell),
						multilevelSAEncoderBP(_inputParameter, _tech, _cell),
						shiftAddBP(_inputParameter, _tech, _cell){
	initialized = false;
	readDynamicEnergyArray = writeDynamicEnergyArray = 0;
}

void SubArray::Initialize(int _numRow, int _numCol, double _unitWireRes){  //initialization module
	//write our own design
}

void SubArray::CalculateArea() {  //calculate layout area for total design
	//write our own design
}

void SubArray::CalculateLatency(double columnRes, const vector<double> &columnResistance, const vector<double> &rowResistance) {   //calculate latency for different mode
	//write our own design
}

void SubArray::CalculatePower(const vector<double> &columnResistance, const vector<double> &rowResistance) {
	//write our own design
}

void SubArray::PrintProperty() {
	//write our own design
}
