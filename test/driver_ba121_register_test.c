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
 * @file      driver_ba121_register_test.c
 * @brief     driver ba121 register test source file
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

#include "driver_ba121_register_test.h"

static ba121_handle_t gs_handle;        /**< ba121 handle */

/**
 * @brief  register test
 * @return status code
 *         - 0 success
 *         - 1 test failed
 * @note   none
 */
uint8_t ba121_register_test(void)
{
    uint8_t res;
    ba121_status_t status;
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
    
    /* start register test */
    ba121_interface_debug_print("ba121: start register test.\n");
    
    /* ba121 init */
    res = ba121_init(&gs_handle);
    if (res != 0)
    {
        ba121_interface_debug_print("ba121: init failed.\n");

        return 1;
    }
    
    /* ba121_set_ntc_resistance test */
    ba121_interface_debug_print("ba121: ba121_set_ntc_resistance test.\n");
    
    /* set ntc resistance */
    ba121_interface_debug_print("ba121: set ntc resistance 10k.\n");
    
    /* set ntc resistance */
    res = ba121_set_ntc_resistance(&gs_handle, 10 * 1000);
    if (res != 0)
    {
        ba121_interface_debug_print("ba121: set ntc resistance failed.\n");
        (void)ba121_deinit(&gs_handle);
        
        return 1;
    }
    ba121_interface_debug_print("ba121: check ntc resistance %s.\n", res == 0 ? "ok" : "error");
    
    /* ba121_set_ntc_b test */
    ba121_interface_debug_print("ba121: ba121_set_ntc_b test.\n");
    
    /* set ntc b */
    ba121_interface_debug_print("ba121: set ntc b 3435.\n");
    
    /* set ntc b */
    res = ba121_set_ntc_b(&gs_handle, 3435);
    if (res != 0)
    {
        ba121_interface_debug_print("ba121: set ntc b failed.\n");
        (void)ba121_deinit(&gs_handle);
        
        return 1;
    }
    ba121_interface_debug_print("ba121: check ntc b %s.\n", res == 0 ? "ok" : "error");
    
#if (BA121_ENABLE_BASELINE_TEST != 0)
    /* ba121_baseline_calibration test */
    ba121_interface_debug_print("ba121: ba121_baseline_calibration test.\n");
    
    /* baseline calibration */
    ba121_interface_debug_print("ba121: baseline calibration.\n");
    
    /* baseline calibration */
    res = ba121_baseline_calibration(&gs_handle);
    if (res != 0)
    {
        ba121_interface_debug_print("ba121: baseline calibration failed.\n");
        (void)ba121_deinit(&gs_handle);
        
        return 1;
    }
    ba121_interface_debug_print("ba121: check baseline calibration %s.\n", res == 0 ? "ok" : "error");
#endif
    
    /* ba121_get_last_status test */
    ba121_interface_debug_print("ba121: ba121_get_last_status test.\n");
    
    /* get last status */
    res = ba121_get_last_status(&gs_handle, &status);
    if (res != 0)
    {
        ba121_interface_debug_print("ba121: get last status failed.\n");
        (void)ba121_deinit(&gs_handle);
        
        return 1;
    }
    ba121_interface_debug_print("ba121: last status is 0x%02X.\n", (uint8_t)status);
    
    /* finish register test */
    ba121_interface_debug_print("ba121: finish register test.\n");
    (void)ba121_deinit(&gs_handle);

    return 0;
}
