/**
 * *****************************************************************************
 * @file	pca9538a_i2c.h
 * @brief	Hardware abstraction layer
 *
 * *****************************************************************************
 */

/* Define to prevent recursive inclusion */
#ifndef PCA9538A_HAL_H__
#define PCA9538A_HAL_H__

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>

#include "board_def.h"

/* Export constants ----------------------------------------------------------*/

#define PCA9538A_USED_NUM	BOARD_ICS_USED_NUM_PCA9538A

/* Export functions prototypes -----------------------------------------------*/

/**
 * @brief		Get data from I/O port expander
 * @param[in]	dev_idx		Device index on the board from 0 to
 * 				PCA9538A_USED_NUM - 1
 * @param[in]	dev_addr	Target device address
 * @param[in]	reg_addr	Target register address
 * @param[out]	dest		Buffer for storing data received from the device
 * @param[in]	len			Data buffer length in bytes
 * @return
 * 				- (-2): Parameter error
 * 				- (-1): Bus error
 * 				- 0: Success
 */
int pca9538a_i2c_read(	unsigned int dev_idx,
						unsigned int dev_addr,
						unsigned char reg_addr,
						unsigned char *dest,
						unsigned int len);

/**
 * @brief		Send data to I/O port expander
 * @param[in]	dev_idx		Device index on the board from 0 to
 * 				PCA9538A_USED_NUM - 1
 * @param[in]	dev_addr	Target device address
 * @param[in]	reg_addr	Target register address
 * @param[in]	src			Buffer containing data to send
 * @param[in]	len			Data buffer length in bytes
 * @return
 * 				- (-2): Parameter error
 * 				- (-1): Bus error
 * 				- 0: Success
 */
int pca9538a_i2c_write(	unsigned int dev_idx,
						unsigned int dev_addr,
						unsigned char reg_addr,
						unsigned char *src,
						unsigned int len);

/**
 * @brief		Set device reset pin state
 * @param[in]	dev_idx	Device index on the board from 0 to
 * 				PCA9538A_USED_NUM - 1
 * @param[in]	value	Set or reset pin
 * @return
 * 				- (-2): Parameter error
 * 				- (-1): Bus error
 * 				- 0: Success
 */
int pca9538a_reset_pin_write(	unsigned int dev_idx,
								bool value);

#endif	/* PCA9538A_HAL_H__ */
