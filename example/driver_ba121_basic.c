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
 * @file      driver_ba121_basic.c
 * @brief     driver ba121 basic source file
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

#include "driver_ba121_basic.h"

static ba121_handle_t gs_handle;        /**< ba121 handle */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t ba121_basic_init(void)
{
    uint8_t res;
    
    /* link interface function */
    DRIVER_BA121_LINK_INIT(&gs_handle, ba121_handle_t);
    DRIVER_BA121_LINK_UART_INIT(&gs_handle, ba121_interface_uart_init);
    DRIVER_BA121_LINK_UART_DEINIT(&gs_handle, ba121_interface_uart_deinit);
    DRIVER_BA121_LINK_UART_READ(&gs_handle, ba121_interface_uart_read);
    DRIVER_BA121_LINK_UART_FLUSH(&gs_handle, ba121_interface_uart_flush);
    DRIVER_BA121_LINK_UART_WRITE(&gs_handle, ba121_interface_uart_write);
    DRIVER_BA121_LINK_DELAY_MS(&gs_handle, ba121_interface_delay_ms);
    DRIVER_BA121_LINK_DEBUG_PRINT(&gs_handle, ba121_interface_debug_print);
    
    /* ba121 init */
    res = ba121_init(&gs_handle);
    if (res != 0)
    {
        ba121_interface_debug_print("ba121: init failed.\n");
        
        return 1;
    }
    
#if (BA121_BASIC_SEND_CONFIG != 0)
    /* set default ntc resistance */
    res = ba121_set_ntc_resistance(&gs_handle, BA121_BASIC_DEFAULT_NTC_RESISTANCE);
    if (res != 0)
    {
        ba121_interface_debug_print("ba121: set ntc resistance failed.\n");
        (void)ba121_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default ntc b */
    res = ba121_set_ntc_b(&gs_handle, BA121_BASIC_DEFAULT_NTC_B);
    if (res != 0)
    {
        ba121_interface_debug_print("ba121: set ntc b failed.\n");
        (void)ba121_deinit(&gs_handle);
        
        return 1;
    }
#endif
    
    return 0;
}

/**
 * @brief      basic example read
 * @param[out] *conductivity_us_cm pointer to a conductivity uS/cm data buffer
 * @param[out] *temperature_deg pointer to a converted temperature data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t ba121_basic_read( uint16_t *conductivity_us_cm, float *temperature_deg)
{
    uint8_t res;
    uint16_t conductivity_raw;
    uint16_t temperature_raw;

    /* read */
    res = ba121_read(&gs_handle, &conductivity_raw, conductivity_us_cm, &temperature_raw, temperature_deg);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t ba121_basic_deinit(void)
{
    /* deinit ba121 */
    if (ba121_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example baseline calibration
 * @return status code
 *         - 0 success
 *         - 1 baseline calibration failed
 * @note   none
 */
uint8_t ba121_basic_baseline_calibration(void)
{
    /* baseline calibration */
    if (ba121_baseline_calibration(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example get last status
 * @param[out] *status pointer to a status buffer
 * @return     status code
 *             - 0 success
 *             - 1 get last status failed
 * @note       none
 */
uint8_t ba121_basic_get_last_status(ba121_status_t *status)
{
    /* get last status */
    if (ba121_get_last_status(&gs_handle, status) != 0)
    {
        return 1;
    }
    
    return 0;
}
