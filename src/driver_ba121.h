/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_ba121.h
 * @brief     driver ba121 header file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2025-05-15
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2025/05/15  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_BA121_H
#define DRIVER_BA121_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup ba121_driver ba121 driver function
 * @brief    ba121 driver modules
 * @{
 */

/**
 * @addtogroup ba121_basic_driver
 * @{
 */

/**
 * @brief ba121 status enumeration definition
 */
typedef enum
{
    BA121_STATUS_OK                       = 0x00,        /**< ok */
    BA121_STATUS_FRAME_ERROR              = 0x01,        /**< frame error */
    BA121_STATUS_BUSY                     = 0x02,        /**< busy */
    BA121_STATUS_CHECK_ERROR              = 0x03,        /**< check error */
    BA121_STATUS_TEMPERATURE_OUT_OF_RANGE = 0x04,        /**< temperature out of range */
} ba121_status_t;

/**
 * @brief ba121 handle structure definition
 */
typedef struct ba121_handle_s
{
    uint8_t (*uart_init)(void);                               /**< point to an uart_init function address */
    uint8_t (*uart_deinit)(void);                             /**< point to an uart_deinit function address */
    uint16_t (*uart_read)(uint8_t *buf, uint16_t len);        /**< point to an uart_read function address */
    uint8_t (*uart_flush)(void);                              /**< point to an uart_flush function address */
    uint8_t (*uart_write)(uint8_t *buf, uint16_t len);        /**< point to an uart_write function address */
    void (*delay_ms)(uint32_t ms);                            /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);          /**< point to a debug_print function address */
    uint8_t inited;                                           /**< inited flag */
    uint8_t last_status;                                      /**< last status */
} ba121_handle_t;

/**
 * @brief ba121 information structure definition
 */
typedef struct ba121_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} ba121_info_t;

/**
 * @}
 */

/**
 * @defgroup ba121_link_driver ba121 link driver function
 * @brief    ba121 link driver modules
 * @ingroup  ba121_driver
 * @{
 */

/**
 * @brief     initialize ba121_handle_t structure
 * @param[in] HANDLE pointer to a ba121 handle structure
 * @param[in] STRUCTURE ba121_handle_t
 * @note      none
 */
#define DRIVER_BA121_LINK_INIT(HANDLE, STRUCTURE)            memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link uart_init function
 * @param[in] HANDLE pointer to a ba121 handle structure
 * @param[in] FUC pointer to an uart_init function address
 * @note      none
 */
#define DRIVER_BA121_LINK_UART_INIT(HANDLE, FUC)            (HANDLE)->uart_init = FUC

/**
 * @brief     link uart_deinit function
 * @param[in] HANDLE pointer to a ba121 handle structure
 * @param[in] FUC pointer to an uart_deinit function address
 * @note      none
 */
#define DRIVER_BA121_LINK_UART_DEINIT(HANDLE, FUC)          (HANDLE)->uart_deinit = FUC

/**
 * @brief     link uart_read function
 * @param[in] HANDLE pointer to a ba121 handle structure
 * @param[in] FUC pointer to an uart_read function address
 * @note      none
 */
#define DRIVER_BA121_LINK_UART_READ(HANDLE, FUC)            (HANDLE)->uart_read = FUC

/**
 * @brief     link uart_write function
 * @param[in] HANDLE pointer to a ba121 handle structure
 * @param[in] FUC pointer to an uart_write function address
 * @note      none
 */
#define DRIVER_BA121_LINK_UART_WRITE(HANDLE, FUC)           (HANDLE)->uart_write = FUC

/**
 * @brief     link uart_flush function
 * @param[in] HANDLE pointer to a ba121 handle structure
 * @param[in] FUC pointer to an uart_flush function address
 * @note      none
 */
#define DRIVER_BA121_LINK_UART_FLUSH(HANDLE, FUC)           (HANDLE)->uart_flush = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE pointer to a ba121 handle structure
 * @param[in] FUC pointer to a delay_ms function address
 * @note      none
 */
#define DRIVER_BA121_LINK_DELAY_MS(HANDLE, FUC)             (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE pointer to a ba121 handle structure
 * @param[in] FUC pointer to a debug_print function address
 * @note      none
 */
#define DRIVER_BA121_LINK_DEBUG_PRINT(HANDLE, FUC)          (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup ba121_basic_driver ba121 basic driver function
 * @brief    ba121 basic driver modules
 * @ingroup  ba121_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info pointer to a ba121 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t ba121_info(ba121_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle pointer to a ba121 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 uart initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t ba121_init(ba121_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle pointer to a ba121 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 uart deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ba121_deinit(ba121_handle_t *handle);

/**
 * @brief      read the data
 * @param[in]  *handle pointer to a ba121 handle structure
 * @param[out] *conductivity_raw pointer to a conductivity raw data buffer
 * @param[out] *conductivity_us_cm pointer to a conductivity uS/cm data buffer
 * @param[out] *temperature_raw pointer to a temperature raw data buffer
 * @param[out] *temperature pointer to a converted temperature data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 frame error
 * @note       none
 */
uint8_t ba121_read(ba121_handle_t *handle, uint16_t *conductivity_raw, uint16_t *conductivity_us_cm,
                   uint16_t *temperature_raw, float *temperature);

/**
 * @brief     baseline calibration
 * @param[in] *handle pointer to a ba121 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 baseline calibration failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 frame error
 *            - 5 response error
 * @note      none
 */
uint8_t ba121_baseline_calibration(ba121_handle_t *handle);

/**
 * @brief     set ntc resistance
 * @param[in] *handle pointer to a ba121 handle structure
 * @param[in] ohm resistance ohm
 * @return    status code
 *            - 0 success
 *            - 1 set ntc resistance failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 frame error
 *            - 5 response error
 * @note      none
 */
uint8_t ba121_set_ntc_resistance(ba121_handle_t *handle, uint32_t ohm);

/**
 * @brief     set ntc b
 * @param[in] *handle pointer to a ba121 handle structure
 * @param[in] value ntc value
 * @return    status code
 *            - 0 success
 *            - 1 set ntc b failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 frame error
 *            - 5 response error
 * @note      none
 */
uint8_t ba121_set_ntc_b(ba121_handle_t *handle, uint16_t value);

/**
 * @brief      get last status
 * @param[in]  *handle pointer to a ba121 handle structure
 * @param[out] *status pointer to a status buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ba121_get_last_status(ba121_handle_t *handle, ba121_status_t *status);

/**
 * @}
 */

/**
 * @defgroup ba121_extern_driver ba121 extern driver function
 * @brief    ba121 extern driver modules
 * @ingroup  ba121_driver
 * @{
 */

/**
 * @brief     set buffer
 * @param[in] *handle pointer to a ba121 handle structure
 * @param[in] *buf pointer to a data buffer
 * @param[in] len buffer length
 * @return    status code
 *            - 0 success
 *            - 1 set buffer failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ba121_set_buffer(ba121_handle_t *handle, uint8_t *buf, uint16_t len);

/**
 * @brief      get buffer
 * @param[in]  *handle pointer to a ba121 handle structure
 * @param[out] *buf pointer to a data buffer
 * @param[in]  len buffer length
 * @return     status code
 *             - 0 success
 *             - 1 get buffer failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ba121_get_buffer(ba121_handle_t *handle, uint8_t *buf, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
