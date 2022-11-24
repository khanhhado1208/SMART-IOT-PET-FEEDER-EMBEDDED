/*
 * Pressuresensor.h
 *
 *  Created on: Nov 24, 2022
 *      Author: Omistaja
 */

#ifndef PRESSURESENSOR_H_
#define PRESSURESENSOR_H_
#include "DigitalIoPin.h"
class Pressuresensor {
public:
	Pressuresensor();
	virtual ~Pressuresensor();
	void start();
	int get_value();
};

#endif /* PRESSURESENSOR_H_ */
