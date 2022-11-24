/*
 * I2CSensor.h
 *
 *  Created on: 25 Oct 2022
 *      Author: ruban
 */
#ifndef I2CSENSOR_H_
#define I2CSENSOR_H_
#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif
#include <cstdio>
#include <cstring>
#include "systick.h"
#include "LpcUart.h"
#include "retarget_uart.h"
class I2CSensor {
public:
	I2CSensor();
	I2CSensor(const I2CSensor &) = delete;
	virtual ~I2CSensor();
	static void Init_I2C_PinMux();
	static void setupI2CMaster();
	void SetupXferRecAndExecute(uint8_t, uint8_t*, uint16_t, uint8_t*, uint16_t);
	int16_t ReadPresserI2CM();
};

#endif /* I2CSENSOR_H_ */
