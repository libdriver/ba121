[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver BA121

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ba121/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

A dedicated chip for detecting the conductivity and water temperature of aqueous solutions, which integrates high-precision oscillation circuits, analog-to-digital conversion circuits, and floating-point arithmetic units. By using patented conductivity conversion algorithm and temperature correction algorithm, the detection of aqueous solution conductivity can be quickly achieved, and automatic temperature correction can be achieved over a wide temperature range to reduce measurement errors caused by changes in conductivity values with temperature.

LibDriver BA121 is a full-featured driver of BA121 launched by LibDriver.It provides the function of conductivity reading, temperature reading and other functions. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver BA121 source files.

/interface includes LibDriver BA121 UART platform independent template.

/test includes LibDriver BA121 driver test code and this code can test the chip necessary function simply.

/example includes LibDriver BA121 sample code.

/doc includes LibDriver BA121 offline document.

/datasheet includes BA121 datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface UART platform independent template and finish your platform UART driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

#### example basic

```C
#include "driver_ba121_basic.h"

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

...
    
for (i = 0; i < 3; i++)
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
    
    ...
}

...
    
/* deinit */
(void)ba121_basic_deinit();

return 0;
```

### Document

Online documents: [https://www.libdriver.com/docs/ba121/index.html](https://www.libdriver.com/docs/ba121/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.