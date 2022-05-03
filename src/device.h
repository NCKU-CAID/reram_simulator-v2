#ifndef DEVICE_H_
#define DEVICE_H_

#include<fstream>

class Device
{
	protected:
		uint64_t static_power;
	public:
		Device(void* param);
		virtual uint64_t GetStaticPower();
}

#endif // DEVICE_H_
