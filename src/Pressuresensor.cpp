/*
 * Pressuresensor.cpp
 *
 *  Created on: Nov 24, 2022
 *      Author: Omistaja
 */

#include "Pressuresensor.h"

Pressuresensor::Pressuresensor() {
	// TODO Auto-generated constructor stub

}

Pressuresensor::~Pressuresensor() {
	// TODO Auto-generated destructor stub
}

void Pressuresensor::start(){
	DigitalIoPin d1(0,14,DigitalIoPin::output);
	DigitalIoPin d2(0,12,DigitalIoPin::output);
}

int Pressuresensor::get_value(){
	DigitalIoPin d1(0,14,DigitalIoPin::output);
	return d1.read();
}
