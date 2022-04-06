/**
 * *****************************************************************************
 * @file    pca9538a_driver.h
 * @brief   Low-voltage 8-bit I2C-bus I/O port with interrupt and reset
 *
 * *****************************************************************************
 */

/* Define to prevent recursive inclusion */
#ifndef PCA9538A_DRV_H__
#define PCA9538A_DRV_H__

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>

/* Export constants ----------------------------------------------------------*/

/* PCA9538A registers */
#define PCA9538A_REG_INPUT      0x00U
#define PCA9538A_REG_OUTPUT     0x01U
#define PCA9538A_REG_POL_INV    0x02U
#define PCA9538A_REG_CONFIG     0x03U

/* Export typedef ------------------------------------------------------------*/

typedef struct pca9538a_s pca9538a_t;
typedef struct pca9538a_s *pca9538a_handle_t;

/**
 * @brief   Register types enumeration
 */
typedef enum {
    PCA9538A_REG_TYPE_INPUT = 0,
    PCA9538A_REG_TYPE_OUTPUT,
    PCA9538A_REG_TYPE_POL_INV,
    PCA9538A_REG_TYPE_CONFIG,
} pca9538a_reg_type_t;

struct pca9538a_s {
    unsigned int idx;
    unsigned char addr;
    bool busy;
    bool err;
};

/* Export functions prototypes -----------------------------------------------*/

/**
 * @brief       Initialize the structure of the used device with the necessary
 *              values
 * @param[out]  dev_hdl Pointer to a structure describing the device
 * @param[in]   cfg     Pointer to a structure containing initial values
 * @return
 *              - (-2): Parameter error
 *              - 0: Success
 */
int pca9538a_init(  pca9538a_handle_t dev_hdl,
                    pca9538a_t *cfg);

/**
 * @brief       Get the value of the specified chip register
 * @param[in]   dev_hdl     Pointer to a structure describing the device
 * @param[in]   reg_type    Register type
 * @param[out]  value       Variable to store the result
 * @return
 *              - (-2): Parameter error
 *              - (-1): Bus error
 *              - 0: Success
 */
int pca9538a_get_reg(   pca9538a_handle_t dev_hdl,
                        pca9538a_reg_type_t reg_type,
                        unsigned char *value);

/**
 * @brief       Set the value of the specified chip register
 * @param[in]   dev_hdl     Pointer to a structure describing the device
 * @param[in]   reg_type    Register type
 * @param[in]   value       Data to send
 * @return
 *              - (-2): Parameter error
 *              - (-1): Bus error
 *              - 0: Success
 */
int pca9538a_set_reg(   pca9538a_handle_t dev_hdl,
                        pca9538a_reg_type_t reg_type,
                        unsigned char value);

/**
 * @brief       Set reset pin to inactive
 * @param[in]   dev_hdl Pointer to a structure describing the device
 * @return
 *              - (-2): Parameter error
 *              - (-1): Hardware error
 *              - 0: Success
 */
int pca9538a_enable(pca9538a_handle_t dev_hdl);

/**
 * @brief       Set reset pin to active
 * @param[in]   dev_hdl Pointer to a structure describing the device
 * @return
 *              - (-2): Parameter error
 *              - (-1): Hardware error
 *              - 0: Success
 */
int pca9538a_disable(pca9538a_handle_t dev_hdl);

#endif  /* PCA9538A_DRV_H__ */
