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
 * @file      main.c
 * @brief     main source file
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
#include "driver_ba121_register_test.h"
#include "driver_ba121_read_test.h"
#include "shell.h"
#include "clock.h"
#include "delay.h"
#include "uart.h"
#include "getopt.h"
#include <ctype.h>
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];        /**< uart buffer */
volatile uint16_t g_len;   /**< uart buffer length */

/**
 * @brief     ba121 full function
 * @param[in] argc arg numbers
 * @param[in] **argv arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t ba121(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"times", required_argument, NULL, 1},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint32_t times = 3;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* times */
            case 1 :
            {
                /* set times */
                times = atoi(optarg);
                
                break;
            }
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_reg", type) == 0)
    {
        /* run register test */
        if (ba121_register_test() != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("t_read", type) == 0)
    {
        /* run read test */
        if (ba121_read_test(times) != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("e_read", type) == 0)
    {
        uint8_t res;
        uint16_t conductivity_us_cm;
        float temperature;
        uint32_t i;
        
        /* init */
        res = ba121_basic_init();
        if (res != 0)
        {
            return 1;
        }
        
        for (i = 0; i < times; i++)
        {
            /* delay 1000ms */
            ba121_interface_delay_ms(1000);
            
            /* read */
            res = ba121_basic_read(&conductivity_us_cm, &temperature);
            if (res != 0)
            {
                ba121_interface_debug_print("ba121: read failed.\n");
                (void)ba121_basic_deinit();
                
                return 1;
            }
            
            /* output */
            ba121_interface_debug_print("ba121: %d/%d.\n", i + 1, times);
            ba121_interface_debug_print("ba121: conductivity is %d uS/cm.\n", conductivity_us_cm);
            ba121_interface_debug_print("ba121: temperature is %0.2fC.\n", temperature);
        }
        
        /* deinit */
        (void)ba121_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_baseline", type) == 0)
    {
        uint8_t res;
        
        /* init */
        res = ba121_basic_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* baseline calibration */
        res = ba121_basic_baseline_calibration();
        if (res != 0)
        {
            (void)ba121_basic_deinit();
            
            return 1;
        }
        
        /* baseline calibration */
        ba121_interface_debug_print("ba121: baseline calibration.\n");
        
        /* deinit */
        (void)ba121_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_status", type) == 0)
    {
        uint8_t res;
        ba121_status_t status;
        
        /* init */
        res = ba121_basic_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* get last status */
        res = ba121_basic_get_last_status(&status);
        if (res != 0)
        {
            (void)ba121_basic_deinit();
            
            return 1;
        }
        
        /* get last status */
        ba121_interface_debug_print("ba121: last status is 0x%02X.\n", (uint8_t)status);
        
        /* deinit */
        (void)ba121_basic_deinit();
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        ba121_interface_debug_print("Usage:\n");
        ba121_interface_debug_print("  ba121 (-i | --information)\n");
        ba121_interface_debug_print("  ba121 (-h | --help)\n");
        ba121_interface_debug_print("  ba121 (-p | --port)\n");
        ba121_interface_debug_print("  ba121 (-t reg | --test=reg)\n");
        ba121_interface_debug_print("  ba121 (-t read | --test=read) [--times=<num>]\n");
        ba121_interface_debug_print("  ba121 (-e read | --example=read) [--times=<num>]\n");
        ba121_interface_debug_print("  ba121 (-e status | --example=status)\n");
        ba121_interface_debug_print("  ba121 (-e baseline | --example=baseline)\n");
        ba121_interface_debug_print("\n");
        ba121_interface_debug_print("Options:\n");
        ba121_interface_debug_print("  -e <read | status | baseline>, --example=<read | status | baseline>\n");
        ba121_interface_debug_print("                                  Run the driver example.\n");
        ba121_interface_debug_print("  -h, --help                      Show the help.\n");
        ba121_interface_debug_print("  -i, --information               Show the chip information.\n");
        ba121_interface_debug_print("  -p, --port                      Display the pins used by this device to connect the chip.\n");
        ba121_interface_debug_print("  -t <reg | read>, --test=<reg | read>\n");
        ba121_interface_debug_print("                                  Run the driver test.\n");
        ba121_interface_debug_print("      --times=<num>               Set the running times.([default: 3])\n");
        
        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        ba121_info_t info;
        
        /* print ba121 info */
        ba121_info(&info);
        ba121_interface_debug_print("ba121: chip is %s.\n", info.chip_name);
        ba121_interface_debug_print("ba121: manufacturer is %s.\n", info.manufacturer_name);
        ba121_interface_debug_print("ba121: interface is %s.\n", info.interface);
        ba121_interface_debug_print("ba121: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        ba121_interface_debug_print("ba121: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        ba121_interface_debug_print("ba121: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        ba121_interface_debug_print("ba121: max current is %0.2fmA.\n", info.max_current_ma);
        ba121_interface_debug_print("ba121: max temperature is %0.1fC.\n", info.temperature_max);
        ba121_interface_debug_print("ba121: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        ba121_interface_debug_print("ba121: TX connected to GPIOA PIN3.\n");
        ba121_interface_debug_print("ba121: RX connected to GPIOA PIN2.\n");
        
        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;
    
    /* stm32f407 clock init and hal init */
    clock_init();
    
    /* delay init */
    delay_init();
    
    /* uart init */
    uart_init(115200);
    
    /* shell init && register ba121 function */
    shell_init();
    shell_register("ba121", ba121);
    uart_print("ba121: welcome to libdriver ba121.\n");
    
    while (1)
    {
        /* read uart */
        g_len = uart_read(g_buf, 256);
        if (g_len != 0)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart_print("ba121: run failed.\n");
            }
            else if (res == 2)
            {
                uart_print("ba121: unknown command.\n");
            }
            else if (res == 3)
            {
                uart_print("ba121: length is too long.\n");
            }
            else if (res == 4)
            {
                uart_print("ba121: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart_print("ba121: param is invalid.\n");
            }
            else
            {
                uart_print("ba121: unknown status code.\n");
            }
            uart_flush();
        }
        delay_ms(100);
    }
}
