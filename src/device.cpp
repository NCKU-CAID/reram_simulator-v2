#include"device.h"

device::device(void* param)
{
	this.static_power=*((uint64_t*)param);
}

uint64_t get_static_power()
{
	return this.static_power;
}
