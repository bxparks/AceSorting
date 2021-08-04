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
| combSort133()               |     300 |   6.024 |   5.885 |    5.965 |
|-----------------------------+---------+---------+---------+----------|
| quickSortMiddle()           |     300 |   4.263 |   4.097 |    4.092 |
| quickSortMedian()           |     300 |   4.636 |   4.481 |    4.474 |
| quickSortMedianSwapped()    |     300 |   4.084 |   3.976 |    3.974 |
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
| qsort()                     |     300 |   4.938 |   4.008 |    4.165 |
|-----------------------------+---------+---------+---------+----------|
| bubbleSort()                |     300 |  38.601 |   0.365 |   47.553 |
| insertionSort()             |     300 |   7.593 |   0.596 |   14.709 |
|-----------------------------+---------+---------+---------+----------|
| shellSortClassic()          |     300 |   5.679 |   5.474 |    5.584 |
| shellSortKnuth()            |     300 |   3.360 |   3.101 |    3.205 |
| shellSortTokuda()           |     300 |   4.701 |   4.497 |    4.598 |
|-----------------------------+---------+---------+---------+----------|
| combSort13()                |     300 |   6.638 |   6.441 |    6.525 |
| combSort125()               |     300 |   7.602 |   7.456 |    7.540 |
| combSort133()               |     300 |   6.066 |   5.915 |    5.998 |
|-----------------------------+---------+---------+---------+----------|
| quickSortMiddle()           |     300 |   4.318 |   4.103 |    4.095 |
| quickSortMedian()           |     300 |   4.667 |   4.513 |    4.507 |
| quickSortMedianSwapped()    |     300 |   4.099 |   3.986 |    3.981 |
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
| qsort()                     |    1000 |   3.968 |   3.519 |    3.589 |
|-----------------------------+---------+---------+---------+----------|
| bubbleSort()                |    1000 | 142.893 |   0.421 |  153.818 |
| insertionSort()             |    1000 |  30.144 |   0.505 |   59.754 |
|-----------------------------+---------+---------+---------+----------|
| shellSortClassic()          |    1000 |   4.690 |   4.530 |    4.594 |
| shellSortKnuth()            |    1000 |   2.655 |   2.538 |    2.589 |
| shellSortTokuda()           |    1000 |   4.416 |   4.297 |    4.368 |
|-----------------------------+---------+---------+---------+----------|
| combSort13()                |    1000 |   6.436 |   6.357 |    6.384 |
| combSort125()               |    1000 |   7.530 |   7.484 |    7.511 |
| combSort133()               |    1000 |   6.169 |   6.056 |    6.083 |
|-----------------------------+---------+---------+---------+----------|
| quickSortMiddle()           |    1000 |   3.051 |   2.988 |    2.985 |
| quickSortMedian()           |    1000 |   3.268 |   3.218 |    3.215 |
| quickSortMedianSwapped()    |    1000 |   3.080 |   3.036 |    3.033 |
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
| qsort()                     |    1000 |   2.972 |   2.699 |    2.747 |
|-----------------------------+---------+---------+---------+----------|
| bubbleSort()                |    1000 |  77.157 |   0.238 |   79.291 |
| insertionSort()             |    1000 |  15.337 |   0.309 |   30.508 |
|-----------------------------+---------+---------+---------+----------|
| shellSortClassic()          |    1000 |   3.523 |   3.397 |    3.455 |
| shellSortKnuth()            |    1000 |   2.503 |   2.367 |    2.422 |
| shellSortTokuda()           |    1000 |   2.540 |   2.470 |    2.509 |
|-----------------------------+---------+---------+---------+----------|
| combSort13()                |    1000 |   6.877 |   6.803 |    6.822 |
| combSort125()               |    1000 |   7.109 |   7.094 |    7.109 |
| combSort133()               |    1000 |   5.614 |   5.549 |    5.566 |
|-----------------------------+---------+---------+---------+----------|
| quickSortMiddle()           |    1000 |   2.855 |   2.793 |    2.792 |
| quickSortMedian()           |    1000 |   3.363 |   3.315 |    3.312 |
| quickSortMedianSwapped()    |    1000 |   2.932 |   2.913 |    2.907 |
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
| qsort()                     |    1000 |   1.852 |   1.630 |    1.663 |
|-----------------------------+---------+---------+---------+----------|
| bubbleSort()                |    1000 |  78.707 |   0.238 |   81.367 |
| insertionSort()             |    1000 |  11.512 |   0.288 |   23.150 |
|-----------------------------+---------+---------+---------+----------|
| shellSortClassic()          |    1000 |   3.004 |   2.929 |    2.958 |
| shellSortKnuth()            |    1000 |   1.780 |   1.718 |    1.738 |
| shellSortTokuda()           |    1000 |   2.260 |   2.209 |    2.237 |
|-----------------------------+---------+---------+---------+----------|
| combSort13()                |    1000 |   3.105 |   3.070 |    3.079 |
| combSort125()               |    1000 |   3.628 |   3.618 |    3.626 |
| combSort133()               |    1000 |   2.972 |   2.936 |    2.946 |
|-----------------------------+---------+---------+---------+----------|
| quickSortMiddle()           |    1000 |   1.888 |   1.852 |    1.849 |
| quickSortMedian()           |    1000 |   1.955 |   1.921 |    1.918 |
| quickSortMedianSwapped()    |    1000 |   1.797 |   1.780 |    1.777 |
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
| qsort()                     |    1000 |   0.821 |   0.755 |    0.763 |
|-----------------------------+---------+---------+---------+----------|
| bubbleSort()                |    1000 |  21.712 |   0.067 |   22.429 |
| insertionSort()             |    1000 |   5.113 |   0.093 |    9.868 |
|-----------------------------+---------+---------+---------+----------|
| shellSortClassic()          |    1000 |   0.901 |   0.870 |    0.882 |
| shellSortKnuth()            |    1000 |   0.576 |   0.551 |    0.562 |
| shellSortTokuda()           |    1000 |   0.705 |   0.684 |    0.695 |
|-----------------------------+---------+---------+---------+----------|
| combSort13()                |    1000 |   1.433 |   1.416 |    1.421 |
| combSort125()               |    1000 |   1.581 |   1.577 |    1.581 |
| combSort133()               |    1000 |   1.377 |   1.364 |    1.369 |
|-----------------------------+---------+---------+---------+----------|
| quickSortMiddle()           |    1000 |   0.725 |   0.714 |    0.714 |
| quickSortMedian()           |    1000 |   0.755 |   0.745 |    0.744 |
| quickSortMedianSwapped()    |    1000 |   0.679 |   0.673 |    0.672 |
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
| qsort()                     |    1000 |   1.283 |   1.111 |    1.138 |
|-----------------------------+---------+---------+---------+----------|
| bubbleSort()                |    1000 |  32.759 |   0.095 |   36.587 |
| insertionSort()             |    1000 |  12.814 |   0.199 |   24.524 |
|-----------------------------+---------+---------+---------+----------|
| shellSortClassic()          |    1000 |   1.847 |   1.787 |    1.817 |
| shellSortKnuth()            |    1000 |   1.147 |   1.084 |    1.113 |
| shellSortTokuda()           |    1000 |   1.449 |   1.403 |    1.434 |
|-----------------------------+---------+---------+---------+----------|
| combSort13()                |    1000 |   2.581 |   2.544 |    2.554 |
| combSort125()               |    1000 |   3.014 |   2.998 |    3.008 |
| combSort133()               |    1000 |   2.481 |   2.451 |    2.461 |
|-----------------------------+---------+---------+---------+----------|
| quickSortMiddle()           |    1000 |   1.160 |   1.135 |    1.133 |
| quickSortMedian()           |    1000 |   1.262 |   1.247 |    1.245 |
| quickSortMedianSwapped()    |    1000 |   1.213 |   1.204 |    1.202 |
+-----------------------------+---------+---------+---------+----------+

```

