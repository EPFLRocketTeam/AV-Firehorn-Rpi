/*******************************************************************************
 *   @file   ADXL375.c
 *   @brief  Implementation of ADXL375 Driver.
 *   @author DBogdan (dragos.bogdan@analog.com)
********************************************************************************
 * Copyright 2012(c) Analog Devices, Inc.
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Analog Devices, Inc. nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *  - The use of this software may or may not infringe the patent rights
 *    of one or more patent holders.  This license does not release you
 *    from the requirement that you obtain separate licenses from these
 *    patent holders to use this software.
 *  - Use of the software either in source or binary form, must be run
 *    on or directly connected to an Analog Devices Inc. component.
 *
 * THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT,
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL ANALOG DEVICES BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, INTELLECTUAL PROPERTY RIGHTS, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
********************************************************************************
 *   SVN Revision: 795
*******************************************************************************/

/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/
#include "adxl375.h"		// ADXL375 definitions.
#include "i2c_common.h"	// Communication definitions.
#include <stdint.h>
/******************************************************************************/
/************************ Variables Definitions *******************************/
/******************************************************************************/


/******************************************************************************/
/************************ Functions Definitions *******************************/
/******************************************************************************/

/*!
 * @brief This internal API is used to validate the device structure pointer for
 * null conditions.
 */
static int8_t null_ptr_check(const struct adxl375_dev *dev)
{
    int8_t rslt;

    if ((dev == NULL) || (dev->read == NULL) || (dev->write == NULL) ||
		(dev->delay_us == NULL) || (dev->intf_ptr == NULL))
    {
        /* Device structure pointer is not valid */
        rslt = ADXL375_E_NULL_PTR;
    }
    else
    {
        /* Device structure is fine */
        rslt = ADXL375_OK;
    }

    return rslt;
}

/*!
 * @brief This internal API interleaves the register address between the
 * register data buffer for burst write operation.
 */
static void interleave_reg_addr(const uint8_t *reg_addr, uint8_t *temp_buff,
								const uint8_t *reg_data, uint32_t len)
{
    uint32_t index;

    for (index = 1; index < len; index++)
    {
        temp_buff[(index * 2) - 1] = reg_addr[index];
        temp_buff[index * 2] = reg_data[index];
    }
}

/*!
 * @brief This API reads the data from the given register address of the sensor.
 */
int8_t adxl375_get_regs(uint8_t reg_addr, uint8_t *reg_data, uint32_t len,
						struct adxl375_dev *dev) {
	int8_t rslt;
    
	/* Check for null pointer in the device structure */
	rslt = null_ptr_check(dev);
	
	/* Proceed if null check is fine */
    if ((rslt != ADXL375_OK) || (reg_data == NULL)) {
		return ADXL375_E_NULL_PTR;
	}

	/* Read the data using I2C */
	dev->intf_rslt = dev->read(reg_addr, reg_data, len, dev->intf_ptr);
	
	/* Check for communication error */
	if (dev->intf_rslt != ADXL375_OK) {
		return ADXL375_E_COMM_FAIL;
	}

	return ADXL375_OK;
}

/*!
 * @brief This API writes the data from the given register address of the sensor.
 */
int8_t adxl375_set_regs(uint8_t *reg_addr, const uint8_t *reg_data,
					    int32_t len, struct adxl375_dev *dev) {
	int8_t rslt;
	uint8_t temp_buff[len * 2];
    uint32_t temp_len;
	/* Check for null pointer in the device structure */
    rslt = null_ptr_check(dev);

	/* Proceed if null check is fine */
    if ((rslt != ADXL375_OK) || (reg_addr == NULL) || (reg_data == NULL)) {
		return ADXL375_E_NULL_PTR;
	}

	if (len == 0) return ADXL375_E_INVALID_LEN;

	/* Burst write mode */
	if (len > 1) {
		/* Interleave register address w.r.t data for burst write */
		interleave_reg_addr(reg_addr, temp_buff, reg_data, len);
		temp_len = len * 2;
	} else {
		temp_len = len;
	}

	dev->intf_rslt = dev->write(reg_addr[0],temp_buff,temp_len,dev->intf_ptr);

	/* Check for communication error */
	if (dev->intf_rslt != ADXL375_OK) return ADXL375_E_COMM_FAIL;
    
	return ADXL375_OK;
}

/*!
 * @brief Initializes the communication peripheral, checks if the ADXL375
 *		  part is present and sets configuration values.
 */
int8_t adxl375_init(struct adxl375_dev *dev, uint8_t addr) {
	int8_t rslt;
    uint8_t chip_id = 0;

	/* Initialize the I2C interface */
	rslt = adxl375_i2c_init(dev, addr);
	if (rslt) return rslt;

	/* Check for null pointer in the device structure */
    rslt = null_ptr_check(dev);
	if (rslt) return rslt;

	/* Read the chip-id of adxl375 sensor */
	rslt = adxl375_get_regs(ADXL375_DEVID, &chip_id, 1, dev);
	if (rslt) return ADXL375_E_DEV_NOT_FOUND;
	
	//Configure the ADXL375
	
	// Normal Power Mode, 100Hz operation
	uint8_t reg_addr = ADXL375_BW_RATE;
	uint8_t reg_val = (0x00|ADXL375_RATE(0x0A));
	adxl375_set_regs(&reg_addr, &reg_val,1,dev);

	//SelfTest:Off, SPI: 4-wire, Interrupts: Active High, Full_Res: On,
	//Justify: Right justified with sign extension
	reg_addr = ADXL375_DATA_FORMAT;
	reg_val=(0x00|ADXL375_RANGE(ADXL375_RANGE_PM_2G)|ADXL375_FULL_RES);
	adxl375_set_regs(&reg_addr, &reg_val,1,dev);

	//FIFO mode - Stream, Watermark interrupt set @ 30 (0x1E)samples -
	//which at ~100Hz(or even greater) provides sufficient time for FIFO to
	//be emptied
	reg_addr = ADXL375_FIFO_CTL;
	reg_val = (0x00|ADXL375_FIFO_MODE(0x2)|ADXL375_SAMPLES(0x1E));
	adxl375_set_regs(&reg_addr, &reg_val,1,dev);

	//Watermark interrupt to Int 1 - all others to Int 2
	reg_addr = ADXL375_INT_MAP;
	reg_val = (0x00|~ADXL375_WATERMARK);
	adxl375_set_regs(&reg_addr, &reg_val,1,dev);

	//Enables Watermark interrupt on Int 1 - GPIO 17
	reg_addr = ADXL375_INT_ENABLE;
	reg_val = (0x00|ADXL375_WATERMARK);
	adxl375_set_regs(&reg_addr, &reg_val,1,dev);

	//Start the ADXL375
	adxl375_set_power_mode(0x1, dev);

	return ADXL375_OK;
}

/*!
 * @brief Places the device into standby/measure mode.
 */
int8_t adxl375_set_power_mode(uint8_t pwr_mode, struct adxl375_dev *dev) {
	uint8_t oldPowerCtl = 0;
	uint8_t newPowerCtl = 0;
	int8_t rslt;
    
    rslt = adxl375_get_regs(ADXL375_POWER_CTL, &oldPowerCtl, 1, dev);
	if (rslt) return rslt;
	newPowerCtl = oldPowerCtl & ~ADXL375_PCTL_MEASURE;
	newPowerCtl = newPowerCtl | (pwr_mode * ADXL375_PCTL_MEASURE);

	uint8_t reg_addr = ADXL375_POWER_CTL;
	rslt = adxl375_set_regs(&reg_addr, &newPowerCtl, 1, dev);
	if (rslt) return rslt;
}

/*!
 * @brief Reads the output data of each axis.
 */
int8_t adxl375_get_xyz(struct adxl375_dev *dev,
					 int16_t* x, int16_t* y, int16_t* z) {
	int8_t rslt;

	rslt = adxl375_get_regs(ADXL375_DATAX0, (uint8_t*)x, 2, dev);
	if (rslt) return rslt;
	rslt = adxl375_get_regs(ADXL375_DATAY0, (uint8_t*)y, 2, dev);
	if (rslt) return rslt;
	rslt = adxl375_get_regs(ADXL375_DATAZ0, (uint8_t*)z, 2, dev);
	if (rslt) return rslt;

	return ADXL375_OK;	
}


/*!
 * @brief Enables/disables the tap detection.
 */
int8_t adxl375_set_tap_detection(struct adxl375_dev *dev,
							 uint8_t tapType,
							 uint8_t tapAxes,
							 uint8_t tapDur,
							 uint8_t tapLatent,
							 uint8_t tapWindow,
							 uint8_t tapThresh,
							 uint8_t tapInt) {
	uint8_t oldTapAxes   = 0;
	uint8_t newTapAxes   = 0;
	uint8_t oldIntMap    = 0;
	uint8_t newIntMap    = 0;
	uint8_t oldIntEnable = 0;
	uint8_t newIntEnable = 0;
    int8_t rslt;

	rslt = adxl375_get_regs(ADXL375_TAP_AXES, &oldTapAxes, 1, dev);
	if (rslt) return rslt;
	newTapAxes = oldTapAxes & ~(ADXL375_TAP_X_EN |
								ADXL375_TAP_Y_EN |
								ADXL375_TAP_Z_EN);
	newTapAxes = newTapAxes | tapAxes;

	uint8_t reg_addr = ADXL375_TAP_AXES;
	rslt = adxl375_set_regs(&reg_addr, &newTapAxes, 1, dev);
	if (rslt) return rslt;

	reg_addr = ADXL375_DUR;
	rslt = adxl375_set_regs(&reg_addr, &tapDur, 1, dev);
	if (rslt) return rslt;

	reg_addr = ADXL375_LATENT;
	rslt = adxl375_set_regs(&reg_addr, &tapLatent, 1, dev);
	if (rslt) return rslt;

	reg_addr = ADXL375_WINDOW;
	rslt = adxl375_set_regs(&reg_addr, &tapWindow, 1, dev);
	if (rslt) return rslt;

	reg_addr = ADXL375_THRESH_TAP;
	rslt = adxl375_set_regs(&reg_addr, &tapThresh, 1, dev);
	if (rslt) return rslt;

	rslt = adxl375_get_regs(ADXL375_INT_MAP, &oldIntMap, 1, dev);
	if (rslt) return rslt;

	newIntMap = oldIntMap & ~(ADXL375_SINGLE_TAP | ADXL375_DOUBLE_TAP);
	newIntMap = newIntMap | tapInt;

	reg_addr = ADXL375_INT_MAP;
	rslt = adxl375_set_regs(&reg_addr, &newIntMap, 1, dev);
	if (rslt) return rslt;

	rslt = adxl375_get_regs(ADXL375_INT_ENABLE, &oldIntEnable, 1, dev);
	if (rslt) return rslt;

	newIntEnable = oldIntEnable & ~(ADXL375_SINGLE_TAP | ADXL375_DOUBLE_TAP);
	newIntEnable = newIntEnable | tapType;
	reg_addr = ADXL375_INT_ENABLE;
	adxl375_set_regs(&reg_addr, &newIntEnable, 1, dev);
}

/***************************************************************************//**
 * @brief Enables/disables the activity detection.
 *
 * @param actOnOff - Enables/disables the activity detection.
 *					 Example: 0x0 - disables the activity detection.
 *							  0x1 - enables the activity detection.
 * @param actAxes - Axes which participate in detecting activity.
 *					Example: 0x0 - disables axes participation.
 *							 ADXL375_ACT_X_EN - enables x-axis participation.
 *							 ADXL375_ACT_Y_EN - enables y-axis participation.
 *							 ADXL375_ACT_Z_EN - enables z-axis participation.
 * @param actAcDc - Selects dc-coupled or ac-coupled operation.
 *					Example: 0x0 - dc-coupled operation.
 *							 ADXL375_ACT_ACDC - ac-coupled operation.
 * @param actThresh - Threshold value for detecting activity. The scale factor 
                      is 62.5 mg/LSB.
 * @patam actInt - Interrupts pin.
 *				   Example: 0x0 - activity interrupts on INT1 pin.
 *							ADXL375_ACTIVITY - activity interrupts on INT2 pin.
 *
 * @return None.
*******************************************************************************/
void adxl375_set_activity_detection(uint8_t actOnOff,
								  uint8_t actAxes,
								  uint8_t actAcDc,
								  uint8_t actThresh,
								  uint8_t actInt)
{
	uint8_t oldActInactCtl = 0;
	uint8_t newActInactCtl = 0;
	uint8_t oldIntMap      = 0;
	uint8_t newIntMap      = 0;
	uint8_t oldIntEnable   = 0;
	uint8_t newIntEnable   = 0;
    
	oldActInactCtl = adxl375_get_regs(ADXL375_INT_ENABLE);
	newActInactCtl = oldActInactCtl & ~(ADXL375_ACT_ACDC |
										ADXL375_ACT_X_EN |
										ADXL375_ACT_Y_EN |
										ADXL375_ACT_Z_EN);
	newActInactCtl = newActInactCtl | (actAcDc | actAxes);
	adxl375_set_regs(ADXL375_ACT_INACT_CTL, newActInactCtl);
	adxl375_set_regs(ADXL375_THRESH_ACT, actThresh);
	oldIntMap = adxl375_get_regs(ADXL375_INT_MAP);
	newIntMap = oldIntMap & ~(ADXL375_ACTIVITY);
	newIntMap = newIntMap | actInt;
	adxl375_set_regs(ADXL375_INT_MAP, newIntMap);
	oldIntEnable = adxl375_get_regs(ADXL375_INT_ENABLE);
	newIntEnable = oldIntEnable & ~(ADXL375_ACTIVITY);
	newIntEnable = newIntEnable | (ADXL375_ACTIVITY * actOnOff);
	adxl375_set_regs(ADXL375_INT_ENABLE, newIntEnable);
}

/***************************************************************************//**
 * @brief Enables/disables the inactivity detection.
 *
 * @param inactOnOff - Enables/disables the inactivity detection.
 *					   Example: 0x0 - disables the inactivity detection.
 *							    0x1 - enables the inactivity detection.
 * @param inactAxes - Axes which participate in detecting inactivity.
 *					  Example: 0x0 - disables axes participation.
 *						  	   ADXL375_INACT_X_EN - enables x-axis.
 *							   ADXL375_INACT_Y_EN - enables y-axis.
 *							   ADXL375_INACT_Z_EN - enables z-axis.
 * @param inactAcDc - Selects dc-coupled or ac-coupled operation.
 *					  Example: 0x0 - dc-coupled operation.
 *							   ADXL375_INACT_ACDC - ac-coupled operation.
 * @param inactThresh - Threshold value for detecting inactivity. The scale 
                        factor is 62.5 mg/LSB.
 * @param inactTime - Inactivity time. The scale factor is 1 sec/LSB.
 * @patam inactInt - Interrupts pin.
 *				     Example: 0x0 - inactivity interrupts on INT1 pin.
 *							  ADXL375_INACTIVITY - inactivity interrupts on
 *												   INT2 pin.
 *
 * @return None.
*******************************************************************************/
void adxl375_set_inactivity_detection(uint8_t inactOnOff,
									uint8_t inactAxes,
									uint8_t inactAcDc,
									uint8_t inactThresh,
									uint8_t inactTime,
									uint8_t inactInt)
{
	uint8_t oldActInactCtl = 0;
	uint8_t newActInactCtl = 0;
	uint8_t oldIntMap      = 0;
	uint8_t newIntMap      = 0;
	uint8_t oldIntEnable   = 0;
	uint8_t newIntEnable   = 0;
    
	oldActInactCtl = adxl375_get_regs(ADXL375_INT_ENABLE);
	newActInactCtl = oldActInactCtl & ~(ADXL375_INACT_ACDC |
										ADXL375_INACT_X_EN |
										ADXL375_INACT_Y_EN |
										ADXL375_INACT_Z_EN);
	newActInactCtl = newActInactCtl | (inactAcDc | inactAxes);
	adxl375_set_regs(ADXL375_ACT_INACT_CTL, newActInactCtl);
	adxl375_set_regs(ADXL375_THRESH_INACT, inactThresh);
	adxl375_set_regs(ADXL375_TIME_INACT, inactTime);
	oldIntMap = adxl375_get_regs(ADXL375_INT_MAP);
	newIntMap = oldIntMap & ~(ADXL375_INACTIVITY);
	newIntMap = newIntMap | inactInt;
	adxl375_set_regs(ADXL375_INT_MAP, newIntMap);
	oldIntEnable = adxl375_get_regs(ADXL375_INT_ENABLE);
	newIntEnable = oldIntEnable & ~(ADXL375_INACTIVITY);
	newIntEnable = newIntEnable | (ADXL375_INACTIVITY * inactOnOff);
	adxl375_set_regs(ADXL375_INT_ENABLE, newIntEnable);
}

/***************************************************************************//**
 * @brief Enables/disables the free-fall detection.
 *
 * @param ffOnOff - Enables/disables the free-fall detection.
 *					Example: 0x0 - disables the free-fall detection.
 *							 0x1 - enables the free-fall detection.
 * @param ffThresh - Threshold value for free-fall detection. The scale factor 
                     is 62.5 mg/LSB.
 * @param ffTime - Time value for free-fall detection. The scale factor is 
                   5 ms/LSB.
 * @param ffInt - Interrupts pin.
 *				  Example: 0x0 - free-fall interrupts on INT1 pin.
 *						   ADXL375_FREE_FALL - free-fall interrupts on INT2 pin.
 *
 * @return None.
*******************************************************************************/
void adxl375_set_freefall_detection(uint8_t ffOnOff,
								  uint8_t ffThresh,
								  uint8_t ffTime,
								  uint8_t ffInt)
{
	uint8_t oldIntMap    = 0;
	uint8_t newIntMap    = 0;
	uint8_t oldIntEnable = 0;
	uint8_t newIntEnable = 0;
    
	adxl375_set_regs(ADXL375_THRESH_FF, ffThresh);
	adxl375_set_regs(ADXL375_TIME_FF, ffTime);
	oldIntMap = adxl375_get_regs(ADXL375_INT_MAP);
	newIntMap = oldIntMap & ~(ADXL375_FREE_FALL);
	newIntMap = newIntMap | ffInt;
	adxl375_set_regs(ADXL375_INT_MAP, newIntMap);
	oldIntEnable = adxl375_get_regs(ADXL375_INT_ENABLE);
	newIntEnable = oldIntEnable & ~ADXL375_FREE_FALL;
	newIntEnable = newIntEnable | (ADXL375_FREE_FALL * ffOnOff);
	adxl375_set_regs(ADXL375_INT_ENABLE, newIntEnable);	
}

/***************************************************************************//**
 * @brief Sets an offset value for each axis (Offset Calibration).
 *
 * @param xOffset - X-axis's offset.
 * @param yOffset - Y-axis's offset.
 * @param zOffset - Z-axis's offset.
 *
 * @return None.
*******************************************************************************/
void adxl375_set_offset(uint8_t xOffset,
					   uint8_t yOffset,
					   uint8_t zOffset)
{
	adxl375_set_regs(ADXL375_OFSX, xOffset);
	adxl375_set_regs(ADXL375_OFSY, yOffset);
	adxl375_set_regs(ADXL375_OFSZ, yOffset);
}

/*!
 *  @brief Function to initialise the I2C interface, with functions from
 *         i2c_common.h
 */
int8_t adxl375_i2c_init(struct adxl375_dev *dev, uint8_t addr) {
    if (i2c_open(addr) != 0) {
        return ADXL375_E_COMM_FAIL;
    }

    /* To initialize the user I2C function */
    dev->read = i2c_read;
    dev->write = i2c_write;
    
    /* Configure delay in microseconds */
    dev->delay_us = i2c_delay_us;

    /* Assign device address to interface pointer */
    if (get_intf_ptr(addr, &(dev->intf_ptr)) != 0) {
        return ADXL375_E_COMM_FAIL;
    }

    return ADXL375_OK;
}

/*!
 *  @brief Function to deinitialise the I2C interface, with functions from
 *         i2c_common.h
 */
int8_t adxl375_i2c_deinit(uint8_t addr) {
    if(i2c_close(addr) != 0) {
        return ADXL375_E_COMM_FAIL;
    }

    return ADXL375_OK;
}