#include "pressure_sensor.h"

pressureSensor::pressureSensor(){}
pressureSensor::~pressureSensor() {
// TODO Auto-generated destructor stub
}
void pressureSensor::start(){
	DigitalIoPin d1(0,14,DigitalIoPin::output);
	DigitalIoPin d2(0,12,DigitalIoPin::output);
}

int pressureSensor::get_value(){
	DigitalIoPin d1(0,14,DigitalIoPin::output);
	return d1.read();
}

