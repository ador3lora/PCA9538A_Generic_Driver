/**
 * *****************************************************************************
 * @file    pca9538a_driver.c
 * @brief   Low-voltage 8-bit I2C-bus I/O port with interrupt and reset
 *
 * *****************************************************************************
 */

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>
#include <stddef.h>

#include "pca9538a_i2c.h"
#include "pca9538a_driver.h"

/* Export functions ----------------------------------------------------------*/

/* Initialize the structure of the used device with the necessary values */
int pca9538a_init(pca9538a_handle_t dev_hdl, pca9538a_t *cfg) {
    if (dev_hdl == NULL ||
        cfg == NULL) {
        return -2;
    }
    dev_hdl->idx = cfg->idx;
    dev_hdl->addr = cfg->addr;
    dev_hdl->busy = cfg->busy;
    dev_hdl->err = cfg->err;
    return 0;
}

/* Get the value of the specified chip register */
int pca9538a_get_reg(pca9538a_t *dev_hdl, pca9538a_reg_type_t reg_type, unsigned char *value) {
    if (dev_hdl == NULL ||
        value == NULL) {
        return -2;
    }
    int ret = 0;
    unsigned char reg_addr = 0;
    switch (reg_type) {
    case PCA9538A_REG_TYPE_INPUT:   reg_addr = PCA9538A_REG_INPUT;      break;
    case PCA9538A_REG_TYPE_OUTPUT:  reg_addr = PCA9538A_REG_OUTPUT;     break;
    case PCA9538A_REG_TYPE_POL_INV: reg_addr = PCA9538A_REG_POL_INV;    break;
    case PCA9538A_REG_TYPE_CONFIG:  reg_addr = PCA9538A_REG_CONFIG;     break;
    default: return -2;
    }
    while (dev_hdl->busy == true);
    dev_hdl->busy = true;
    if ((ret = pca9538a_i2c_read(dev_hdl->idx, dev_hdl->addr, reg_addr, value, 1)) != 0) {
        if (ret == -1) {
            dev_hdl->err = true;
            ret = -1;
        } else if (ret == -2) {
            ret = -2;
        }
    }
    dev_hdl->busy = false;
    return (int)ret;
}

/* Set the value of the specified chip register */
int pca9538a_set_reg(pca9538a_t *dev_hdl, pca9538a_reg_type_t reg_type, unsigned char value) {
    if (dev_hdl == NULL) {
        return -2;
    }
    int ret = 0;
    unsigned char reg_addr = 0;
    switch (reg_type) {
    case PCA9538A_REG_TYPE_INPUT:   reg_addr = PCA9538A_REG_INPUT;      break;
    case PCA9538A_REG_TYPE_OUTPUT:  reg_addr = PCA9538A_REG_OUTPUT;     break;
    case PCA9538A_REG_TYPE_POL_INV: reg_addr = PCA9538A_REG_POL_INV;    break;
    case PCA9538A_REG_TYPE_CONFIG:  reg_addr = PCA9538A_REG_CONFIG;     break;
    default: return -2;
    }
    while (dev_hdl->busy == true);
    dev_hdl->busy = true;
    if ((ret = pca9538a_i2c_write(dev_hdl->idx, dev_hdl->addr, reg_addr, &value, 1)) != 0) {
        if (ret == -1) {
            dev_hdl->err = true;
            ret = -1;
        } else if (ret == -2) {
            ret = -2;
        }
    }
    dev_hdl->busy = false;
    return (int)ret;
}

/* Set reset pin to inactive */
int pca9538a_enable(pca9538a_handle_t dev_hdl) {
    if (dev_hdl == NULL) {
        return -2;
    }
    int ret = 0;
    while (dev_hdl->busy == true);
    dev_hdl->busy = true;
    if ((ret = pca9538a_reset_pin_write(dev_hdl->idx, true)) != 0) {
        if (ret == -1) {
            dev_hdl->err = true;
            ret = -1;
        } else if (ret == -2) {
            ret = -2;
        }
    }
    dev_hdl->busy = false;
    return (int)ret;
}

/* Set reset pin to active */
int pca9538a_disable(pca9538a_handle_t dev_hdl) {
    if (dev_hdl == NULL) {
        return -2;
    }
    int ret = 0;
    while (dev_hdl->busy == true);
    dev_hdl->busy = true;
    if ((ret = pca9538a_reset_pin_write(dev_hdl->idx, false)) != 0) {
        if (ret == -1) {
            dev_hdl->err = true;
            ret = -1;
        } else if (ret == -2) {
            ret = -2;
        }
    }
    dev_hdl->busy = false;
    return (int)ret;
}
