# WorstCaseBenchmark

Determine the speed of various AceSorting functions when given data arrays that
could trigger worst case runtime. Three types of arrays are tested:

* random array
* already sorted array
* reverse sorted array

**Version**: AceSorting v0.1

**DO NOT EDIT**: This file was auto-generated using `make README.md`.

## Dependencies

This program depends on the following libraries:

* [AceCommon](https://github.com/bxparks/AceCommon)

## How to Generate

This requires the [AUniter](https://github.com/bxparks/AUniter) script
to execute the Arduino IDE programmatically.

The `Makefile` has rules to generate the `*.txt` results file for several
microcontrollers that I usually support, but the `$ make benchmarks` command
does not work very well because the USB port of the microcontroller is a
dynamically changing parameter. I created a semi-automated way of collect the
`*.txt` files:

1. Connect the microcontroller to the serial port. I usually do this through a
USB hub with individually controlled switch.
2. Type `$ auniter ports` to determine its `/dev/ttyXXX` port number (e.g.
`/dev/ttyUSB0` or `/dev/ttyACM0`).
3. If the port is `USB0` or `ACM0`, type `$ make nano.txt`, etc.
4. Switch off the old microontroller.
5. Go to Step 1 and repeat for each microcontroller.

The `generate_table.awk` program reads one of `*.txt` files and prints out an
ASCII table that can be directly embedded into this README.md file. For example
the following command produces the table in the Nano section below:

```
$ ./generate_table.awk < nano.txt
```

Fortunately, we no longer need to run `generate_table.awk` for each `*.txt`
file. The process has been automated using the `generate_readme.py` script which
will be invoked by the following command:
```
$ make README.md
```

## CPU Time Changes

**v0.1**

* Initial results.
    * Both Bubble Sort and Insertion Sort perform the best when given arrays
      which are already sorted. But they perform the worst given an array which
      is reverse sorted.
    * Other sorting algorithms seem immune from these 2 extremes, giving sorting
      times which are similar to sorting array with random elements.

## Results

The following results show the runtime of each sorting function in milliseconds,
when sorting different sized arrays.

### Arduino Nano

* 16MHz ATmega328P
* Arduino IDE 1.8.13
* Arduino AVR Boards 1.8.3
* `micros()` has a resolution of 4 microseconds

```
+-----------------------------+---------+---------+---------+----------+
| Function                    | arrSize |  random |  sorted | reversed |
|-----------------------------+---------+---------+---------+----------|
| qsort()                     |     300 |   4.882 |   3.985 |    4.144 |
|-----------------------------+---------+---------+---------+----------|
| bubbleSort()                |     300 |  40.555 |   0.364 |   47.307 |
| insertionSort()             |     300 |   7.283 |   0.587 |   14.628 |
|-----------------------------+---------+---------+---------+----------|
| shellSortClassic()          |     300 |   5.636 |   5.445 |    5.556 |
| shellSortKnuth()            |     300 |   3.353 |   3.083 |    3.189 |
| shellSortTokuda()           |     300 |   4.688 |   4.474 |    4.576 |
|-----------------------------+---------+---------+---------+----------|
| combSort13()                |     300 |   6.554 |   6.408 |    6.493 |
| combSort125()               |     300 |   7.560 |   7.419 |    7.501 |
|-----------------------------+---------+---------+---------+----------|
| quickSortMiddle()           |     300 |   4.203 |   4.081 |    4.075 |
| quickSortMedian()           |     300 |   4.676 |   4.501 |    4.493 |
| quickSortMedianSwapped()    |     300 |   4.035 |   3.963 |    3.961 |
+-----------------------------+---------+---------+---------+----------+

```

### SparkFun Pro Micro

* 16 MHz ATmega32U4
* Arduino IDE 1.8.13
* SparkFun AVR Boards 1.1.13
* `micros()` has a resolution of 4 microseconds

```
+-----------------------------+---------+---------+---------+----------+
| Function                    | arrSize |  random |  sorted | reversed |
|-----------------------------+---------+---------+---------+----------|
| qsort()                     |     300 |   4.905 |   4.007 |    4.164 |
|-----------------------------+---------+---------+---------+----------|
| bubbleSort()                |     300 |  40.549 |   0.367 |   47.556 |
| insertionSort()             |     300 |   7.587 |   0.585 |   14.713 |
|-----------------------------+---------+---------+---------+----------|
| shellSortClassic()          |     300 |   5.670 |   5.474 |    5.584 |
| shellSortKnuth()            |     300 |   3.360 |   3.100 |    3.206 |
| shellSortTokuda()           |     300 |   4.709 |   4.498 |    4.600 |
|-----------------------------+---------+---------+---------+----------|
| combSort13()                |     300 |   6.592 |   6.442 |    6.527 |
| combSort125()               |     300 |   7.603 |   7.457 |    7.539 |
|-----------------------------+---------+---------+---------+----------|
| quickSortMiddle()           |     300 |   4.266 |   4.104 |    4.097 |
| quickSortMedian()           |     300 |   4.669 |   4.524 |    4.518 |
| quickSortMedianSwapped()    |     300 |   4.073 |   3.986 |    3.980 |
+-----------------------------+---------+---------+---------+----------+

```

### SAMD21 M0 Mini

* 48 MHz ARM Cortex-M0+
* Arduino IDE 1.8.13
* SparkFun SAMD Core 1.8.3

```
+-----------------------------+---------+---------+---------+----------+
| Function                    | arrSize |  random |  sorted | reversed |
|-----------------------------+---------+---------+---------+----------|
| qsort()                     |    1000 |   3.925 |   3.497 |    3.565 |
|-----------------------------+---------+---------+---------+----------|
| bubbleSort()                |    1000 | 140.763 |   0.422 |  153.816 |
| insertionSort()             |    1000 |  30.304 |   0.507 |   59.750 |
|-----------------------------+---------+---------+---------+----------|
| shellSortClassic()          |    1000 |   4.693 |   4.530 |    4.594 |
| shellSortKnuth()            |    1000 |   2.665 |   2.537 |    2.589 |
| shellSortTokuda()           |    1000 |   4.418 |   4.297 |    4.368 |
|-----------------------------+---------+---------+---------+----------|
| combSort13()                |    1000 |   6.436 |   6.357 |    6.384 |
| combSort125()               |    1000 |   7.528 |   7.485 |    7.511 |
|-----------------------------+---------+---------+---------+----------|
| quickSortMiddle()           |    1000 |   3.057 |   2.982 |    2.979 |
| quickSortMedian()           |    1000 |   3.270 |   3.214 |    3.211 |
| quickSortMedianSwapped()    |    1000 |   3.064 |   3.029 |    3.026 |
+-----------------------------+---------+---------+---------+----------+

```

### STM32

* STM32 "Blue Pill", STM32F103C8, 72 MHz ARM Cortex-M3
* Arduino IDE 1.8.13
* STM32duino 2.0.0

```
+-----------------------------+---------+---------+---------+----------+
| Function                    | arrSize |  random |  sorted | reversed |
|-----------------------------+---------+---------+---------+----------|
| qsort()                     |    1000 |   2.971 |   2.700 |    2.747 |
|-----------------------------+---------+---------+---------+----------|
| bubbleSort()                |    1000 |  77.157 |   0.237 |   79.292 |
| insertionSort()             |    1000 |  15.334 |   0.307 |   30.510 |
|-----------------------------+---------+---------+---------+----------|
| shellSortClassic()          |    1000 |   3.523 |   3.397 |    3.455 |
| shellSortKnuth()            |    1000 |   2.502 |   2.367 |    2.422 |
| shellSortTokuda()           |    1000 |   2.540 |   2.469 |    2.508 |
|-----------------------------+---------+---------+---------+----------|
| combSort13()                |    1000 |   6.876 |   6.804 |    6.823 |
| combSort125()               |    1000 |   7.109 |   7.093 |    7.109 |
|-----------------------------+---------+---------+---------+----------|
| quickSortMiddle()           |    1000 |   3.254 |   3.195 |    3.192 |
| quickSortMedian()           |    1000 |   2.899 |   2.848 |    2.845 |
| quickSortMedianSwapped()    |    1000 |   3.003 |   2.986 |    2.980 |
+-----------------------------+---------+---------+---------+----------+

```

### ESP8266

* NodeMCU 1.0 clone, 80MHz ESP8266
* Arduino IDE 1.8.13
* ESP8266 Boards 2.7.4

```
+-----------------------------+---------+---------+---------+----------+
| Function                    | arrSize |  random |  sorted | reversed |
|-----------------------------+---------+---------+---------+----------|
| qsort()                     |    1000 |   1.858 |   1.630 |    1.664 |
|-----------------------------+---------+---------+---------+----------|
| bubbleSort()                |    1000 |  77.660 |   0.238 |   81.368 |
| insertionSort()             |    1000 |  11.205 |   0.289 |   23.150 |
|-----------------------------+---------+---------+---------+----------|
| shellSortClassic()          |    1000 |   2.999 |   2.929 |    2.958 |
| shellSortKnuth()            |    1000 |   1.777 |   1.717 |    1.739 |
| shellSortTokuda()           |    1000 |   2.257 |   2.210 |    2.237 |
|-----------------------------+---------+---------+---------+----------|
| combSort13()                |    1000 |   3.117 |   3.072 |    3.079 |
| combSort125()               |    1000 |   3.640 |   3.617 |    3.626 |
|-----------------------------+---------+---------+---------+----------|
| quickSortMiddle()           |    1000 |   1.832 |   1.799 |    1.796 |
| quickSortMedian()           |    1000 |   1.955 |   1.919 |    1.916 |
| quickSortMedianSwapped()    |    1000 |   1.795 |   1.775 |    1.773 |
+-----------------------------+---------+---------+---------+----------+

```

### ESP32

* ESP32-01 Dev Board, 240 MHz Tensilica LX6
* Arduino IDE 1.8.13
* ESP32 Boards 1.0.6

```
+-----------------------------+---------+---------+---------+----------+
| Function                    | arrSize |  random |  sorted | reversed |
|-----------------------------+---------+---------+---------+----------|
| qsort()                     |    1000 |   0.682 |   0.607 |    0.619 |
|-----------------------------+---------+---------+---------+----------|
| bubbleSort()                |    1000 |  21.690 |   0.068 |   22.429 |
| insertionSort()             |    1000 |   4.731 |   0.095 |    9.868 |
|-----------------------------+---------+---------+---------+----------|
| shellSortClassic()          |    1000 |   0.901 |   0.870 |    0.882 |
| shellSortKnuth()            |    1000 |   0.578 |   0.551 |    0.562 |
| shellSortTokuda()           |    1000 |   0.705 |   0.684 |    0.697 |
|-----------------------------+---------+---------+---------+----------|
| combSort13()                |    1000 |   1.428 |   1.416 |    1.421 |
| combSort125()               |    1000 |   1.581 |   1.577 |    1.581 |
|-----------------------------+---------+---------+---------+----------|
| quickSortMiddle()           |    1000 |   0.731 |   0.715 |    0.714 |
| quickSortMedian()           |    1000 |   0.758 |   0.746 |    0.745 |
| quickSortMedianSwapped()    |    1000 |   0.706 |   0.701 |    0.700 |
+-----------------------------+---------+---------+---------+----------+

```

### Teensy 3.2

* 96 MHz ARM Cortex-M4
* Arduino IDE 1.8.13
* Teensyduino 1.53
* Compiler options: "Faster"

```
+-----------------------------+---------+---------+---------+----------+
| Function                    | arrSize |  random |  sorted | reversed |
|-----------------------------+---------+---------+---------+----------|
| qsort()                     |    1000 |   1.281 |   1.111 |    1.138 |
|-----------------------------+---------+---------+---------+----------|
| bubbleSort()                |    1000 |  32.923 |   0.095 |   36.584 |
| insertionSort()             |    1000 |  12.124 |   0.200 |   24.522 |
|-----------------------------+---------+---------+---------+----------|
| shellSortClassic()          |    1000 |   1.849 |   1.787 |    1.818 |
| shellSortKnuth()            |    1000 |   1.145 |   1.084 |    1.114 |
| shellSortTokuda()           |    1000 |   1.449 |   1.403 |    1.434 |
|-----------------------------+---------+---------+---------+----------|
| combSort13()                |    1000 |   2.574 |   2.544 |    2.554 |
| combSort125()               |    1000 |   3.014 |   2.998 |    3.008 |
|-----------------------------+---------+---------+---------+----------|
| quickSortMiddle()           |    1000 |   1.153 |   1.136 |    1.134 |
| quickSortMedian()           |    1000 |   1.264 |   1.248 |    1.246 |
| quickSortMedianSwapped()    |    1000 |   1.217 |   1.203 |    1.201 |
+-----------------------------+---------+---------+---------+----------+

```

