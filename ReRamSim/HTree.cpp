#include <cmath>
#include <iostream>
#include "constant.h"
#include "typedef.h"
#include "formula.h"
#include "HTree.h"
#include "Param.h"

using namespace std;

extern Param *param;

HTree::HTree(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell): inputParameter(_inputParameter), tech(_tech), cell(_cell), FunctionUnit() {
	initialized = false;
}

void HTree::Initialize(int _numRow, int _numCol, double _delaytolerance, double _busWidth){
	//write our own design
}

void HTree::CalculateArea(double unitHeight, double unitWidth, double foldedratio) {
	//write our own design
}

void HTree::CalculateLatency(int x_init, int y_init, int x_end, int y_end, double unitHeight, double unitWidth, double numRead){
	//write our own design
}

void HTree::CalculatePower(int x_init, int y_init, int x_end, int y_end, double unitHeight, double unitWidth, double numBitAccess, double numRead) {
	//write our own design
}

void HTree::PrintProperty(const char* str) {
	//write our own design
}

double HTree::GetUnitLengthRes(double wireLength) {
	//write our own design
}
