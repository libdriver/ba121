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
 * @file      driver_ba121_read_test.c
 * @brief     driver ba121 read test source file
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

#include "driver_ba121_read_test.h"

static ba121_handle_t gs_handle;        /**< ba121 handle */

/**
 * @brief     read test
 * @param[in] times test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t ba121_read_test(uint32_t times)
{
    uint8_t res;
    uint32_t i;
    ba121_info_t info;
    
    /* link interface function */
    DRIVER_BA121_LINK_INIT(&gs_handle, ba121_handle_t);
    DRIVER_BA121_LINK_UART_INIT(&gs_handle, ba121_interface_uart_init);
    DRIVER_BA121_LINK_UART_DEINIT(&gs_handle, ba121_interface_uart_deinit);
    DRIVER_BA121_LINK_UART_READ(&gs_handle, ba121_interface_uart_read);
    DRIVER_BA121_LINK_UART_FLUSH(&gs_handle, ba121_interface_uart_flush);
    DRIVER_BA121_LINK_UART_WRITE(&gs_handle, ba121_interface_uart_write);
    DRIVER_BA121_LINK_DELAY_MS(&gs_handle, ba121_interface_delay_ms);
    DRIVER_BA121_LINK_DEBUG_PRINT(&gs_handle, ba121_interface_debug_print);
    
    /* get ba121 information */
    res = ba121_info(&info);
    if (res != 0)
    {
        ba121_interface_debug_print("ba121: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip information */
        ba121_interface_debug_print("ba121: chip is %s.\n", info.chip_name);
        ba121_interface_debug_print("ba121: manufacturer is %s.\n", info.manufacturer_name);
        ba121_interface_debug_print("ba121: interface is %s.\n", info.interface);
        ba121_interface_debug_print("ba121: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        ba121_interface_debug_print("ba121: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        ba121_interface_debug_print("ba121: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        ba121_interface_debug_print("ba121: max current is %0.2fmA.\n", info.max_current_ma);
        ba121_interface_debug_print("ba121: max temperature is %0.1fC.\n", info.temperature_max);
        ba121_interface_debug_print("ba121: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start read test */
    ba121_interface_debug_print("ba121: start read test.\n");
    
    /* ba121 init */
    res = ba121_init(&gs_handle);
    if (res != 0)
    {
        ba121_interface_debug_print("ba121: init failed.\n");

        return 1;
    }
    
    for (i = 0; i < times; i++)
    {
        uint16_t conductivity_raw;
        uint16_t conductivity_us_cm;
        uint16_t temperature_raw;
        float temperature;
        
        /* delay 1000ms */
        ba121_interface_delay_ms(1000);
        
        /* read */
        res = ba121_read(&gs_handle, &conductivity_raw, &conductivity_us_cm, &temperature_raw, &temperature);
        if (res != 0)
        {
            ba121_interface_debug_print("ba121: read failed.\n");
            (void)ba121_deinit(&gs_handle);
            
            return 1;
        }
        
        /* output */
        ba121_interface_debug_print("ba121: conductivity is %d uS/cm.\n", conductivity_us_cm);
        ba121_interface_debug_print("ba121: temperature is %0.2fC.\n", temperature);
    }
    
    /* finish read test */
    ba121_interface_debug_print("ba121: finish read test.\n");
    (void)ba121_deinit(&gs_handle);

    return 0;
}
