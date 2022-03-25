/**
 * *****************************************************************************
 * @file	pca9538a_i2c.c
 * @brief	Hardware abstraction layer
 *
 * *****************************************************************************
 */

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>
#include <string.h>

#include <nrf_drv_twi.h>
#include <nrf_error.h>

#include "app_i2c.h"
#include "pca9538a_i2c.h"

/* Export functions ----------------------------------------------------------*/

/* Get data from I/O port expander */
int pca9538a_i2c_read(unsigned int dev_idx, unsigned int dev_addr, unsigned char reg_addr, unsigned char *dest, unsigned int len) {
	if (dev_idx >= PCA9538A_USED_NUM ||
		dest == NULL) {
		return -2;
	}
	/*------------------------------------------------------------------------*/
	/* Specify a custom I2C read function here -------------------------------*/
	/* The function must return a value (-1) in case of a hardware error -----*/
	/*------------------------------------------------------------------------*/
	if (nrf_drv_twi_tx(	&m_twi,
						(uint8_t)dev_addr,
						(uint8_t *)&reg_addr,
						(uint8_t)sizeof(uint8_t),
						true) != NRF_SUCCESS) {
		return -1;
	}
	if (nrf_drv_twi_rx(	&m_twi,
						(uint8_t)dev_addr,
						(uint8_t *)dest,
						(uint8_t)len) != NRF_SUCCESS) {
		return -1;
	}
	return 0;
}

/* Send data to I/O port expander */
int pca9538a_i2c_write(unsigned int dev_idx, unsigned int dev_addr, unsigned char reg_addr, unsigned char *src, unsigned int len) {
	if (dev_idx >= PCA9538A_USED_NUM ||
		src == NULL) {
		return -2;
	}
	/*------------------------------------------------------------------------*/
	/* Specify a custom I2C write function here ------------------------------*/
	/* The function must return a value (-1) in case of a hardware error -----*/
	/*------------------------------------------------------------------------*/
	uint8_t tx_item[sizeof(uint8_t) + len];
	memset(tx_item, 0, sizeof(uint8_t) + len);
	memcpy(tx_item, &reg_addr, sizeof(uint8_t));
	memcpy(tx_item + sizeof(uint8_t), src, len);
	if (nrf_drv_twi_tx(	&m_twi,
						(uint8_t)dev_addr,
						tx_item,
						(uint8_t)(sizeof tx_item),
						false) != NRF_SUCCESS) {
		return -1;
	}
	return 0;
}

/* Set device reset pin state */
int pca9538a_reset_pin_write(unsigned int dev_idx, bool value) {
	if (dev_idx >= PCA9538A_USED_NUM) {
		return -2;
	}
	/*------------------------------------------------------------------------*/
	/* Specify a custom reset output state change function here --------------*/
	/* The function must return a value (-1) in case of a hardware error -----*/
	/*------------------------------------------------------------------------*/
	return 0;
}
