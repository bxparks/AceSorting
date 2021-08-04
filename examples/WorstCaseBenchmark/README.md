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
| qsort()                     |     300 |  13.008 |   3.985 |    5.558 |
|-----------------------------+---------+---------+---------+----------|
| bubbleSort()                |     300 | 118.097 |   0.365 |  141.203 |
| insertionSort()             |     300 |  21.319 |   0.588 |   42.716 |
|-----------------------------+---------+---------+---------+----------|
| shellSortClassic()          |     300 |   7.378 |   5.446 |    6.548 |
| shellSortKnuth()            |     300 |   5.682 |   3.084 |    4.132 |
| shellSortTokuda()           |     300 |   6.553 |   4.474 |    5.496 |
|-----------------------------+---------+---------+---------+----------|
| combSort13()                |     300 |   8.300 |   6.408 |    7.240 |
| combSort125()               |     300 |   8.838 |   7.419 |    8.236 |
| combSort133()               |     300 |   7.744 |   5.885 |    6.712 |
|-----------------------------+---------+---------+---------+----------|
| quickSortMiddle()           |     300 |   5.524 |   4.086 |    4.021 |
| quickSortMedian()           |     300 |   5.806 |   4.488 |    4.412 |
| quickSortMedianSwapped()    |     300 |   4.870 |   3.969 |    3.926 |
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
| qsort()                     |     300 |  12.962 |   4.007 |    5.586 |
|-----------------------------+---------+---------+---------+----------|
| bubbleSort()                |     300 | 119.833 |   0.361 |  141.940 |
| insertionSort()             |     300 |  22.943 |   0.591 |   42.940 |
|-----------------------------+---------+---------+---------+----------|
| shellSortClassic()          |     300 |   7.459 |   5.472 |    6.580 |
| shellSortKnuth()            |     300 |   5.715 |   3.100 |    4.152 |
| shellSortTokuda()           |     300 |   6.527 |   4.497 |    5.526 |
|-----------------------------+---------+---------+---------+----------|
| combSort13()                |     300 |   8.161 |   6.443 |    7.280 |
| combSort125()               |     300 |   8.881 |   7.458 |    8.281 |
| combSort133()               |     300 |   7.885 |   5.916 |    6.746 |
|-----------------------------+---------+---------+---------+----------|
| quickSortMiddle()           |     300 |   5.584 |   4.109 |    4.039 |
| quickSortMedian()           |     300 |   5.941 |   4.509 |    4.438 |
| quickSortMedianSwapped()    |     300 |   4.972 |   3.993 |    3.950 |
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
| qsort()                     |    1000 |  12.034 |   3.580 |    4.955 |
|-----------------------------+---------+---------+---------+----------|
| bubbleSort()                |    1000 | 424.448 |   0.423 |  460.560 |
| insertionSort()             |    1000 |  88.043 |   0.502 |  178.232 |
|-----------------------------+---------+---------+---------+----------|
| shellSortClassic()          |    1000 |   7.549 |   4.530 |    5.808 |
| shellSortKnuth()            |    1000 |   5.053 |   2.536 |    3.580 |
| shellSortTokuda()           |    1000 |   6.697 |   4.296 |    5.708 |
|-----------------------------+---------+---------+---------+----------|
| combSort13()                |    1000 |   8.284 |   6.354 |    6.889 |
| combSort125()               |    1000 |   8.471 |   7.486 |    8.011 |
| combSort133()               |    1000 |   8.270 |   6.057 |    6.593 |
|-----------------------------+---------+---------+---------+----------|
| quickSortMiddle()           |    1000 |   4.186 |   2.960 |    2.908 |
| quickSortMedian()           |    1000 |   4.433 |   3.199 |    3.154 |
| quickSortMedianSwapped()    |    1000 |   3.722 |   3.026 |    2.977 |
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
| qsort()                     |    1000 |   8.266 |   2.658 |    3.615 |
|-----------------------------+---------+---------+---------+----------|
| bubbleSort()                |    1000 | 239.048 |   0.252 |  251.276 |
| insertionSort()             |    1000 |  45.758 |   0.363 |   90.947 |
|-----------------------------+---------+---------+---------+----------|
| shellSortClassic()          |    1000 |   6.301 |   4.024 |    5.045 |
| shellSortKnuth()            |    1000 |   5.064 |   2.367 |    3.466 |
| shellSortTokuda()           |    1000 |   3.897 |   2.469 |    3.257 |
|-----------------------------+---------+---------+---------+----------|
| combSort13()                |    1000 |   8.145 |   6.804 |    7.165 |
| combSort125()               |    1000 |   7.477 |   7.094 |    7.413 |
| combSort133()               |    1000 |   6.823 |   5.549 |    5.877 |
|-----------------------------+---------+---------+---------+----------|
| quickSortMiddle()           |    1000 |   3.994 |   2.795 |    2.762 |
| quickSortMedian()           |    1000 |   4.241 |   3.315 |    3.245 |
| quickSortMedianSwapped()    |    1000 |   3.251 |   2.907 |    2.798 |
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
| qsort()                     |    1000 |   6.025 |   1.632 |    2.311 |
|-----------------------------+---------+---------+---------+----------|
| bubbleSort()                |    1000 | 232.554 |   0.240 |  243.621 |
| insertionSort()             |    1000 |  34.589 |   0.289 |   68.880 |
|-----------------------------+---------+---------+---------+----------|
| shellSortClassic()          |    1000 |   4.076 |   2.703 |    3.252 |
| shellSortKnuth()            |    1000 |   3.014 |   1.715 |    2.208 |
| shellSortTokuda()           |    1000 |   3.137 |   2.213 |    2.740 |
|-----------------------------+---------+---------+---------+----------|
| combSort13()                |    1000 |   3.802 |   3.070 |    3.253 |
| combSort125()               |    1000 |   3.873 |   3.617 |    3.800 |
| combSort133()               |    1000 |   3.612 |   2.937 |    3.119 |
|-----------------------------+---------+---------+---------+----------|
| quickSortMiddle()           |    1000 |   2.554 |   1.854 |    1.804 |
| quickSortMedian()           |    1000 |   2.552 |   1.922 |    1.874 |
| quickSortMedianSwapped()    |    1000 |   2.111 |   1.775 |    1.725 |
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
| qsort()                     |    1000 |   2.096 |   0.614 |    0.857 |
|-----------------------------+---------+---------+---------+----------|
| bubbleSort()                |    1000 |  64.192 |   0.068 |   67.146 |
| insertionSort()             |    1000 |  14.298 |   0.092 |   29.422 |
|-----------------------------+---------+---------+---------+----------|
| shellSortClassic()          |    1000 |   1.451 |   0.871 |    1.120 |
| shellSortKnuth()            |    1000 |   1.109 |   0.551 |    0.777 |
| shellSortTokuda()           |    1000 |   1.112 |   0.683 |    0.943 |
|-----------------------------+---------+---------+---------+----------|
| combSort13()                |    1000 |   1.745 |   1.417 |    1.492 |
| combSort125()               |    1000 |   1.660 |   1.577 |    1.649 |
| combSort133()               |    1000 |   1.655 |   1.366 |    1.440 |
|-----------------------------+---------+---------+---------+----------|
| quickSortMiddle()           |    1000 |   0.988 |   0.715 |    0.697 |
| quickSortMedian()           |    1000 |   0.971 |   0.746 |    0.727 |
| quickSortMedianSwapped()    |    1000 |   0.797 |   0.673 |    0.657 |
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
| qsort()                     |    1000 |   4.621 |   1.111 |    1.654 |
|-----------------------------+---------+---------+---------+----------|
| bubbleSort()                |    1000 |  99.328 |   0.094 |  109.579 |
| insertionSort()             |    1000 |  36.491 |   0.199 |   73.174 |
|-----------------------------+---------+---------+---------+----------|
| shellSortClassic()          |    1000 |   3.014 |   1.787 |    2.402 |
| shellSortKnuth()            |    1000 |   2.332 |   1.084 |    1.668 |
| shellSortTokuda()           |    1000 |   2.311 |   1.403 |    2.005 |
|-----------------------------+---------+---------+---------+----------|
| combSort13()                |    1000 |   3.240 |   2.544 |    2.745 |
| combSort125()               |    1000 |   3.331 |   2.998 |    3.196 |
| combSort133()               |    1000 |   3.148 |   2.451 |    2.653 |
|-----------------------------+---------+---------+---------+----------|
| quickSortMiddle()           |    1000 |   1.529 |   1.136 |    1.101 |
| quickSortMedian()           |    1000 |   1.584 |   1.247 |    1.207 |
| quickSortMedianSwapped()    |    1000 |   1.401 |   1.203 |    1.163 |
+-----------------------------+---------+---------+---------+----------+

```

