#include <cmath>
#include <iostream>
#include "constant.h"
#include "typedef.h"
#include "formula.h"
#include "DRAM.h"
#include "Param.h"

using namespace std;

extern Param *param;

DRAM::DRAM(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell): inputParameter(_inputParameter), tech(_tech), cell(_cell), FunctionUnit() {
	initialized = false;
}

void DRAM::Initialize(int DRAMtype){

}

void DRAM::CalculateLatency(double numRead){

}

void DRAM::CalculatePower(double numRead) {

}

void DRAM::PrintProperty(const char* str) {

}

void DRAM::SaveOutput(const char* str) {

}
