/*
 * I2CSensor.cpp
 *
 *  Created on: 25 Oct 2022
 *      Author: ruban
 */

#include "I2CSensor.h"
/* I2C clock is set to 1.8MHz */
#define I2C_CLK_DIVIDER         (40)
/* 9.6kHz I2C bit-rate */
#define I2C_BITRATE         (9600)

#define I2C_MODE    (0)

#define I2C_SLAVE_ADDRESS (0x40)

static I2CM_XFER_T  i2cmXferRec;
I2CSensor::I2CSensor() {
	Init_I2C_PinMux();
	setupI2CMaster();
}
I2CSensor::~I2CSensor() {}
/* Initializes pin muxing for I2C interface - note that SystemInit() may
   already setup your pin muxing at system startup */
void I2CSensor::Init_I2C_PinMux(void)
{
#if defined(BOARD_NXP_LPCXPRESSO_1549)
	Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 22, IOCON_DIGMODE_EN | I2C_MODE);
	Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 23, IOCON_DIGMODE_EN | I2C_MODE);
	Chip_SWM_EnableFixedPin(SWM_FIXED_I2C0_SCL);
	Chip_SWM_EnableFixedPin(SWM_FIXED_I2C0_SDA);
#else
#error "No I2C Pin Muxing defined for this example"
#endif
}
void I2CSensor::setupI2CMaster(){
	/* Enable I2C clock and reset I2C peripheral - the boot ROM does not do this */
	Chip_I2C_Init(LPC_I2C0);
	/* Setup clock rate for I2C */
	Chip_I2C_SetClockDiv(LPC_I2C0, I2C_CLK_DIVIDER);
	/* Setup I2CM transfer rate */
	Chip_I2CM_SetBusSpeed(LPC_I2C0, I2C_BITRATE);
	/* Enable Master Mode */
	Chip_I2CM_Enable(LPC_I2C0);
}
void I2CSensor::SetupXferRecAndExecute(uint8_t devAddr, uint8_t* txBuffPtr, uint16_t txSize, uint8_t* rxBuffPtr, uint16_t rxSize) {
	/* Setup I2C transfer record */
	i2cmXferRec.slaveAddr = devAddr;
	i2cmXferRec.status = 0;
	i2cmXferRec.txSz = txSize;
	i2cmXferRec.rxSz = rxSize;
	i2cmXferRec.txBuff = txBuffPtr;
	i2cmXferRec.rxBuff = rxBuffPtr;
	Chip_I2CM_XferBlocking(LPC_I2C0, &i2cmXferRec);
}
int16_t I2CSensor::ReadPresserI2CM(void)
{
	uint8_t presser[3]; // reading data
	uint8_t PresserRegisterAddress = (0xF1); // the command for reading value
	uint8_t txSz = 1; // Transmit data size


	/* Read Sensor presser sensor */
	SetupXferRecAndExecute(
		/* The Sensor I2C bus address */
		I2C_SLAVE_ADDRESS,
		/* Transmit one byte, the presser Sensor register address */
		&PresserRegisterAddress, txSz,
		/* Receive back three bytes, the contents of the presser register */
		presser, 3);

	/* Test for valid operation */
	if (i2cmXferRec.status == I2CM_STATUS_OK) {
		// calculate presser different between H,L
		int16_t pres = ((int16_t)presser[0] << 8) | presser[1];

		return pres / 240 * 0.95f; // return the presser
	}
	return -404; // if status of is not normal, then report the error msg

	//return -400; // if the sensor on standby mode, then report the error msg


}

