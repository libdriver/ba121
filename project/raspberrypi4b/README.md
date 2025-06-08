### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

UART Pin: TX/RX GPIO14/GPIO15.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```
#### 2.2 Configuration

Enable serial port.

Disable serial console.

#### 2.3 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.4 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(ba121 REQUIRED)
```

### 3. BA121

#### 3.1 Command Instruction

1. Show ba121 chip and driver information.

   ```shell
   ba121 (-i | --information)
   ```

2. Show ba121 help.

   ```shell
   ba121 (-h | --help)
   ```

3. Show ba121 pin connections of the current board.

   ```shell
   ba121 (-p | --port)
   ```
   
4. Run ba121 register test.

   ```shell
   ba121 (-t reg | --test=reg)
   ```
   
5. Run ba121 read test, num is the test times.

   ```shell
   ba121 (-t read | --test=read) [--times=<num>]
   ```

6. Run ba121 read function, num is the test times.

   ```shell
   ba121 (-e read | --example=read) [--times=<num>]
   ```

7. Run ba121 status function.

   ```shell
   ba121 (-e status | --example=status)
   ```
8. Run ba121 baseline function.

   ```shell
   ba121 (-e baseline | --example=baseline)
   ```

#### 3.2 Command Example

```shell
./ba121 -i

ba121: chip is AtomBit BA121.
ba121: manufacturer is AtomBit.
ba121: interface is UART.
ba121: driver version is 1.0.
ba121: min supply voltage is 3.3V.
ba121: max supply voltage is 5.0V.
ba121: max current is 3.00mA.
ba121: max temperature is 75.0C.
ba121: min temperature is -10.0C.
```

```shell
./ba121 -p

ba121: TX connected to GPIO15(BCM).
ba121: RX connected to GPIO14(BCM).
```

```shell
./ba121 -t reg

ba121: chip is AtomBit BA121.
ba121: manufacturer is AtomBit.
ba121: interface is UART.
ba121: driver version is 1.0.
ba121: min supply voltage is 3.3V.
ba121: max supply voltage is 5.0V.
ba121: max current is 3.00mA.
ba121: max temperature is 75.0C.
ba121: min temperature is -10.0C.
ba121: start register test.
ba121: ba121_set_ntc_resistance test.
ba121: set ntc resistance 10k.
ba121: check ntc resistance ok.
ba121: ba121_set_ntc_b test.
ba121: set ntc b 3435.
ba121: check ntc b ok.
ba121: ba121_get_last_status test.
ba121: last status is 0x00.
ba121: finish register test.
```

```shell
./ba121 -t read --times=3

ba121: chip is AtomBit BA121.
ba121: manufacturer is AtomBit.
ba121: interface is UART.
ba121: driver version is 1.0.
ba121: min supply voltage is 3.3V.
ba121: max supply voltage is 5.0V.
ba121: max current is 3.00mA.
ba121: max temperature is 75.0C.
ba121: min temperature is -10.0C.
ba121: start read test.
ba121: conductivity is 1000 uS/cm.
ba121: temperature is 23.81C.
ba121: conductivity is 1000 uS/cm.
ba121: temperature is 23.81C.
ba121: conductivity is 1000 uS/cm.
ba121: temperature is 23.81C.
ba121: finish read test.
```

```shell
./ba121 -e read --times=3

ba121: 1/3.
ba121: conductivity is 1000 uS/cm.
ba121: temperature is 23.81C.
ba121: 2/3.
ba121: conductivity is 1000 uS/cm.
ba121: temperature is 23.81C.
ba121: 3/3.
ba121: conductivity is 1000 uS/cm.
ba121: temperature is 23.81C.
```

```shell
./ba121 -e status

ba121: last status is 0x00.
```
```shell
./ba121 -e baseline

ba121: baseline calibration.
```

```shell
./ba121 -h

Usage:
  ba121 (-i | --information)
  ba121 (-h | --help)
  ba121 (-p | --port)
  ba121 (-t reg | --test=reg)
  ba121 (-t read | --test=read) [--times=<num>]
  ba121 (-e read | --example=read) [--times=<num>]
  ba121 (-e status | --example=status)
  ba121 (-e baseline | --example=baseline)

Options:
  -e <read | status | baseline>, --example=<read | status | baseline>
                                  Run the driver example.
  -h, --help                      Show the help.
  -i, --information               Show the chip information.
  -p, --port                      Display the pins used by this device to connect the chip.
  -t <reg | read>, --test=<reg | read>
                                  Run the driver test.
      --times=<num>               Set the running times.([default: 3])
```

