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
+-----------------------------+------+---------+---------+----------+
| Function                    |    N |  random |  sorted | reversed |
|-----------------------------+------+---------+---------+----------|
| bubbleSort()                |  300 | 118.835 |   0.360 |  141.205 |
| insertionSort()             |  300 |  21.685 |   0.585 |   42.715 |
|-----------------------------+------+---------+---------+----------|
| shellSortClassic()          |  300 |   7.422 |   5.445 |    6.546 |
| shellSortKnuth()            |  300 |   5.746 |   3.084 |    4.132 |
| shellSortTokuda()           |  300 |   6.500 |   4.474 |    5.498 |
|-----------------------------+------+---------+---------+----------|
| combSort13()                |  300 |   8.188 |   6.408 |    7.241 |
| combSort13m()               |  300 |   8.307 |   6.414 |    7.248 |
| combSort133()               |  300 |   7.679 |   5.886 |    6.714 |
| combSort133m()              |  300 |   7.748 |   5.892 |    6.721 |
|-----------------------------+------+---------+---------+----------|
| quickSortMiddle()           |  300 |   5.523 |   4.084 |    4.019 |
| quickSortMedian()           |  300 |   5.807 |   4.489 |    4.412 |
| quickSortMedianSwapped()    |  300 |   4.870 |   3.968 |    3.926 |
|-----------------------------+------+---------+---------+----------|
| qsort()                     |  300 |  12.952 |   3.987 |    5.558 |
+-----------------------------+------+---------+---------+----------+

```

### SparkFun Pro Micro

* 16 MHz ATmega32U4
* Arduino IDE 1.8.13
* SparkFun AVR Boards 1.1.13
* `micros()` has a resolution of 4 microseconds

```
+-----------------------------+------+---------+---------+----------+
| Function                    |    N |  random |  sorted | reversed |
|-----------------------------+------+---------+---------+----------|
| bubbleSort()                |  300 | 119.311 |   0.364 |  141.933 |
| insertionSort()             |  300 |  21.628 |   0.592 |   42.936 |
|-----------------------------+------+---------+---------+----------|
| shellSortClassic()          |  300 |   7.468 |   5.473 |    6.580 |
| shellSortKnuth()            |  300 |   5.627 |   3.101 |    4.154 |
| shellSortTokuda()           |  300 |   6.545 |   4.497 |    5.525 |
|-----------------------------+------+---------+---------+----------|
| combSort13()                |  300 |   8.103 |   6.442 |    7.278 |
| combSort13m()               |  300 |   8.167 |   6.448 |    7.285 |
| combSort133()               |  300 |   7.673 |   5.916 |    6.746 |
| combSort133m()              |  300 |   7.889 |   5.920 |    6.755 |
|-----------------------------+------+---------+---------+----------|
| quickSortMiddle()           |  300 |   5.580 |   4.106 |    4.041 |
| quickSortMedian()           |  300 |   5.939 |   4.509 |    4.435 |
| quickSortMedianSwapped()    |  300 |   4.972 |   3.992 |    3.949 |
|-----------------------------+------+---------+---------+----------|
| qsort()                     |  300 |  13.055 |   4.006 |    5.585 |
+-----------------------------+------+---------+---------+----------+

```

### SAMD21 M0 Mini

* 48 MHz ARM Cortex-M0+
* Arduino IDE 1.8.13
* SparkFun SAMD Core 1.8.3

```
+-----------------------------+------+---------+---------+----------+
| Function                    |    N |  random |  sorted | reversed |
|-----------------------------+------+---------+---------+----------|
| bubbleSort()                | 1000 | 417.697 |   0.422 |  460.605 |
| insertionSort()             | 1000 |  90.435 |   0.505 |  178.236 |
|-----------------------------+------+---------+---------+----------|
| shellSortClassic()          | 1000 |   7.518 |   4.530 |    5.809 |
| shellSortKnuth()            | 1000 |   5.142 |   2.537 |    3.581 |
| shellSortTokuda()           | 1000 |   6.701 |   4.297 |    5.709 |
|-----------------------------+------+---------+---------+----------|
| combSort13()                | 1000 |   8.197 |   6.355 |    6.889 |
| combSort13m()               | 1000 |   7.927 |   6.693 |    7.222 |
| combSort133()               | 1000 |   7.896 |   6.057 |    6.593 |
| combSort133m()              | 1000 |   7.622 |   6.394 |    6.932 |
|-----------------------------+------+---------+---------+----------|
| quickSortMiddle()           | 1000 |   4.190 |   2.960 |    2.910 |
| quickSortMedian()           | 1000 |   4.336 |   3.201 |    3.152 |
| quickSortMedianSwapped()    | 1000 |   3.758 |   3.026 |    2.975 |
|-----------------------------+------+---------+---------+----------|
| qsort()                     | 1000 |  12.309 |   3.643 |    5.029 |
+-----------------------------+------+---------+---------+----------+

```

### STM32

* STM32 "Blue Pill", STM32F103C8, 72 MHz ARM Cortex-M3
* Arduino IDE 1.8.13
* STM32duino 2.0.0

```
+-----------------------------+------+---------+---------+----------+
| Function                    |    N |  random |  sorted | reversed |
|-----------------------------+------+---------+---------+----------|
| bubbleSort()                | 1000 | 241.144 |   0.253 |  251.281 |
| insertionSort()             | 1000 |  46.976 |   0.362 |   90.948 |
|-----------------------------+------+---------+---------+----------|
| shellSortClassic()          | 1000 |   6.290 |   4.024 |    5.045 |
| shellSortKnuth()            | 1000 |   5.098 |   2.367 |    3.466 |
| shellSortTokuda()           | 1000 |   3.908 |   2.469 |    3.256 |
|-----------------------------+------+---------+---------+----------|
| combSort13()                | 1000 |   8.072 |   6.804 |    7.165 |
| combSort13m()               | 1000 |   7.665 |   6.891 |    7.260 |
| combSort133()               | 1000 |   7.552 |   6.304 |    6.674 |
| combSort133m()              | 1000 |   7.357 |   6.652 |    7.022 |
|-----------------------------+------+---------+---------+----------|
| quickSortMiddle()           | 1000 |   3.919 |   2.796 |    2.762 |
| quickSortMedian()           | 1000 |   4.265 |   3.315 |    3.248 |
| quickSortMedianSwapped()    | 1000 |   3.248 |   2.907 |    2.797 |
|-----------------------------+------+---------+---------+----------|
| qsort()                     | 1000 |   8.280 |   2.658 |    3.592 |
+-----------------------------+------+---------+---------+----------+

```

### ESP8266

* NodeMCU 1.0 clone, 80MHz ESP8266
* Arduino IDE 1.8.13
* ESP8266 Boards 2.7.4

```
+-----------------------------+------+---------+---------+----------+
| Function                    |    N |  random |  sorted | reversed |
|-----------------------------+------+---------+---------+----------|
| bubbleSort()                | 1000 | 234.792 |   0.242 |  243.619 |
| insertionSort()             | 1000 |  34.031 |   0.291 |   68.866 |
|-----------------------------+------+---------+---------+----------|
| shellSortClassic()          | 1000 |   4.070 |   2.703 |    3.251 |
| shellSortKnuth()            | 1000 |   2.983 |   1.713 |    2.208 |
| shellSortTokuda()           | 1000 |   3.143 |   2.209 |    2.742 |
|-----------------------------+------+---------+---------+----------|
| combSort13()                | 1000 |   3.763 |   3.072 |    3.253 |
| combSort13m()               | 1000 |   3.600 |   3.234 |    3.421 |
| combSort133()               | 1000 |   3.620 |   2.935 |    3.119 |
| combSort133m()              | 1000 |   3.472 |   3.099 |    3.281 |
|-----------------------------+------+---------+---------+----------|
| quickSortMiddle()           | 1000 |   2.491 |   1.796 |    1.748 |
| quickSortMedian()           | 1000 |   2.559 |   1.924 |    1.873 |
| quickSortMedianSwapped()    | 1000 |   2.132 |   1.775 |    1.726 |
|-----------------------------+------+---------+---------+----------|
| qsort()                     | 1000 |   6.019 |   1.635 |    2.321 |
+-----------------------------+------+---------+---------+----------+

```

### ESP32

* ESP32-01 Dev Board, 240 MHz Tensilica LX6
* Arduino IDE 1.8.13
* ESP32 Boards 1.0.6

```
+-----------------------------+------+---------+---------+----------+
| Function                    |    N |  random |  sorted | reversed |
|-----------------------------+------+---------+---------+----------|
| bubbleSort()                | 1000 |  64.709 |   0.068 |   67.146 |
| insertionSort()             | 1000 |  14.837 |   0.092 |   29.422 |
|-----------------------------+------+---------+---------+----------|
| shellSortClassic()          | 1000 |   1.446 |   0.871 |    1.117 |
| shellSortKnuth()            | 1000 |   1.108 |   0.551 |    0.777 |
| shellSortTokuda()           | 1000 |   1.119 |   0.684 |    0.942 |
|-----------------------------+------+---------+---------+----------|
| combSort13()                | 1000 |   1.696 |   1.416 |    1.492 |
| combSort13m()               | 1000 |   1.655 |   1.493 |    1.569 |
| combSort133()               | 1000 |   1.678 |   1.365 |    1.441 |
| combSort133m()              | 1000 |   1.588 |   1.440 |    1.516 |
|-----------------------------+------+---------+---------+----------|
| quickSortMiddle()           | 1000 |   0.978 |   0.714 |    0.696 |
| quickSortMedian()           | 1000 |   0.973 |   0.746 |    0.727 |
| quickSortMedianSwapped()    | 1000 |   0.816 |   0.701 |    0.682 |
|-----------------------------+------+---------+---------+----------|
| qsort()                     | 1000 |   2.103 |   0.607 |    0.849 |
+-----------------------------+------+---------+---------+----------+

```

### Teensy 3.2

* 96 MHz ARM Cortex-M4
* Arduino IDE 1.8.13
* Teensyduino 1.53
* Compiler options: "Faster"

```
+-----------------------------+------+---------+---------+----------+
| Function                    |    N |  random |  sorted | reversed |
|-----------------------------+------+---------+---------+----------|
| bubbleSort()                | 1000 |  98.597 |   0.094 |  109.580 |
| insertionSort()             | 1000 |  35.949 |   0.200 |   73.183 |
|-----------------------------+------+---------+---------+----------|
| shellSortClassic()          | 1000 |   3.018 |   1.787 |    2.403 |
| shellSortKnuth()            | 1000 |   2.355 |   1.085 |    1.668 |
| shellSortTokuda()           | 1000 |   2.313 |   1.403 |    2.005 |
|-----------------------------+------+---------+---------+----------|
| combSort13()                | 1000 |   3.282 |   2.544 |    2.746 |
| combSort13m()               | 1000 |   3.140 |   2.681 |    2.880 |
| combSort133()               | 1000 |   3.135 |   2.451 |    2.654 |
| combSort133m()              | 1000 |   3.030 |   2.587 |    2.790 |
|-----------------------------+------+---------+---------+----------|
| quickSortMiddle()           | 1000 |   1.521 |   1.137 |    1.100 |
| quickSortMedian()           | 1000 |   1.594 |   1.249 |    1.208 |
| quickSortMedianSwapped()    | 1000 |   1.400 |   1.203 |    1.163 |
|-----------------------------+------+---------+---------+----------|
| qsort()                     | 1000 |   4.655 |   1.111 |    1.660 |
+-----------------------------+------+---------+---------+----------+

```

