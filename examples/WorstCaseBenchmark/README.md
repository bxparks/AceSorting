# WorstCaseBenchmark

Determine the speed of various AceSorting functions when given data arrays that
could trigger worst case runtime. Three types of arrays are tested:

* random array
* already sorted array
* reverse sorted array

**Version**: AceSorting v0.3

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
| selectionSort()             |  300 |  48.884 |  48.453 |   50.044 |
|-----------------------------+------+---------+---------+----------|
| shellSortClassic()          |  300 |   6.906 |   4.780 |    5.987 |
| shellSortKnuth()            |  300 |   5.732 |   3.084 |    4.132 |
| shellSortTokuda()           |  300 |   6.558 |   4.474 |    5.496 |
|-----------------------------+------+---------+---------+----------|
| combSort13()                |  300 |   8.160 |   6.409 |    7.242 |
| combSort13m()               |  300 |   8.162 |   6.414 |    7.248 |
| combSort133()               |  300 |   7.671 |   5.882 |    6.714 |
| combSort133m()              |  300 |   7.545 |   5.890 |    6.720 |
|-----------------------------+------+---------+---------+----------|
| quickSortMiddle()           |  300 |   5.648 |   4.090 |    4.018 |
| quickSortMedian()           |  300 |   5.888 |   4.485 |    4.414 |
| quickSortMedianSwapped()    |  300 |   4.875 |   3.968 |    3.932 |
|-----------------------------+------+---------+---------+----------|
| qsort()                     |  300 |  12.926 |   3.987 |    5.558 |
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
| bubbleSort()                |  300 | 119.305 |   0.365 |  141.935 |
| insertionSort()             |  300 |  21.625 |   0.589 |   42.940 |
| selectionSort()             |  300 |  49.151 |  48.709 |   50.303 |
|-----------------------------+------+---------+---------+----------|
| shellSortClassic()          |  300 |   6.960 |   4.803 |    6.017 |
| shellSortKnuth()            |  300 |   5.713 |   3.100 |    4.154 |
| shellSortTokuda()           |  300 |   6.562 |   4.498 |    5.527 |
|-----------------------------+------+---------+---------+----------|
| combSort13()                |  300 |   8.109 |   6.443 |    7.280 |
| combSort13m()               |  300 |   8.204 |   6.448 |    7.288 |
| combSort133()               |  300 |   7.752 |   5.916 |    6.750 |
| combSort133m()              |  300 |   7.700 |   5.921 |    6.754 |
|-----------------------------+------+---------+---------+----------|
| quickSortMiddle()           |  300 |   5.803 |   4.107 |    4.038 |
| quickSortMedian()           |  300 |   5.864 |   4.508 |    4.436 |
| quickSortMedianSwapped()    |  300 |   4.949 |   3.990 |    3.952 |
|-----------------------------+------+---------+---------+----------|
| qsort()                     |  300 |  13.084 |   4.006 |    5.587 |
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
| bubbleSort()                | 1000 | 428.877 |   0.422 |  460.607 |
| insertionSort()             | 1000 |  89.600 |   0.504 |  178.246 |
| selectionSort()             | 1000 | 157.524 | 157.464 |  152.365 |
|-----------------------------+------+---------+---------+----------|
| shellSortClassic()          | 1000 |   5.865 |   3.693 |    4.947 |
| shellSortKnuth()            | 1000 |   5.114 |   2.537 |    3.580 |
| shellSortTokuda()           | 1000 |   6.678 |   4.297 |    5.708 |
|-----------------------------+------+---------+---------+----------|
| combSort13()                | 1000 |   8.163 |   6.355 |    6.889 |
| combSort13m()               | 1000 |   7.875 |   6.694 |    7.222 |
| combSort133()               | 1000 |   7.798 |   6.057 |    6.593 |
| combSort133m()              | 1000 |   7.624 |   6.394 |    6.932 |
|-----------------------------+------+---------+---------+----------|
| quickSortMiddle()           | 1000 |   4.212 |   2.958 |    2.909 |
| quickSortMedian()           | 1000 |   4.387 |   3.202 |    3.152 |
| quickSortMedianSwapped()    | 1000 |   3.751 |   3.024 |    2.976 |
|-----------------------------+------+---------+---------+----------|
| qsort()                     | 1000 |  11.968 |   3.518 |    4.892 |
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
| bubbleSort()                | 1000 | 241.152 |   0.254 |  251.291 |
| insertionSort()             | 1000 |  46.977 |   0.366 |   90.953 |
| selectionSort()             | 1000 | 105.225 | 105.186 |  105.208 |
|-----------------------------+------+---------+---------+----------|
| shellSortClassic()          | 1000 |   5.527 |   3.245 |    4.591 |
| shellSortKnuth()            | 1000 |   5.036 |   2.366 |    3.466 |
| shellSortTokuda()           | 1000 |   3.928 |   2.273 |    3.189 |
|-----------------------------+------+---------+---------+----------|
| combSort13()                | 1000 |   7.861 |   6.544 |    6.913 |
| combSort13m()               | 1000 |   7.395 |   6.617 |    6.971 |
| combSort133()               | 1000 |   7.542 |   6.304 |    6.653 |
| combSort133m()              | 1000 |   7.067 |   6.387 |    6.743 |
|-----------------------------+------+---------+---------+----------|
| quickSortMiddle()           | 1000 |   3.829 |   2.685 |    2.659 |
| quickSortMedian()           | 1000 |   4.219 |   3.304 |    3.235 |
| quickSortMedianSwapped()    | 1000 |   3.275 |   2.904 |    2.794 |
|-----------------------------+------+---------+---------+----------|
| qsort()                     | 1000 |   8.783 |   2.664 |    3.643 |
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
| bubbleSort()                | 1000 | 227.582 |   0.238 |  243.636 |
| insertionSort()             | 1000 |  34.636 |   0.288 |   68.875 |
| selectionSort()             | 1000 |  93.804 |  93.914 |   87.739 |
|-----------------------------+------+---------+---------+----------|
| shellSortClassic()          | 1000 |   3.602 |   2.506 |    3.100 |
| shellSortKnuth()            | 1000 |   3.007 |   1.714 |    2.209 |
| shellSortTokuda()           | 1000 |   3.142 |   2.211 |    2.741 |
|-----------------------------+------+---------+---------+----------|
| combSort13()                | 1000 |   3.765 |   3.073 |    3.253 |
| combSort13m()               | 1000 |   3.622 |   3.234 |    3.417 |
| combSort133()               | 1000 |   3.604 |   2.940 |    3.120 |
| combSort133m()              | 1000 |   3.482 |   3.102 |    3.282 |
|-----------------------------+------+---------+---------+----------|
| quickSortMiddle()           | 1000 |   2.496 |   1.799 |    1.749 |
| quickSortMedian()           | 1000 |   2.570 |   1.921 |    1.874 |
| quickSortMedianSwapped()    | 1000 |   2.125 |   1.777 |    1.728 |
|-----------------------------+------+---------+---------+----------|
| qsort()                     | 1000 |   6.026 |   1.632 |    2.320 |
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
| bubbleSort()                | 1000 |  65.067 |   0.067 |   67.146 |
| insertionSort()             | 1000 |  15.068 |   0.092 |   29.422 |
| selectionSort()             | 1000 |  33.620 |  33.620 |   32.592 |
|-----------------------------+------+---------+---------+----------|
| shellSortClassic()          | 1000 |   1.267 |   0.774 |    1.065 |
| shellSortKnuth()            | 1000 |   1.102 |   0.552 |    0.778 |
| shellSortTokuda()           | 1000 |   1.112 |   0.683 |    0.942 |
|-----------------------------+------+---------+---------+----------|
| combSort13()                | 1000 |   1.750 |   1.417 |    1.492 |
| combSort13m()               | 1000 |   1.644 |   1.491 |    1.568 |
| combSort133()               | 1000 |   1.632 |   1.365 |    1.439 |
| combSort133m()              | 1000 |   1.588 |   1.441 |    1.516 |
|-----------------------------+------+---------+---------+----------|
| quickSortMiddle()           | 1000 |   0.990 |   0.715 |    0.697 |
| quickSortMedian()           | 1000 |   0.961 |   0.745 |    0.728 |
| quickSortMedianSwapped()    | 1000 |   0.834 |   0.700 |    0.681 |
|-----------------------------+------+---------+---------+----------|
| qsort()                     | 1000 |   2.096 |   0.608 |    0.849 |
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
| bubbleSort()                | 1000 |  98.817 |   0.095 |  109.561 |
| insertionSort()             | 1000 |  36.406 |   0.199 |   73.164 |
| selectionSort()             | 1000 |  57.563 |  57.511 |   57.535 |
|-----------------------------+------+---------+---------+----------|
| shellSortClassic()          | 1000 |   2.708 |   1.590 |    2.333 |
| shellSortKnuth()            | 1000 |   2.332 |   1.084 |    1.668 |
| shellSortTokuda()           | 1000 |   2.308 |   1.403 |    2.005 |
|-----------------------------+------+---------+---------+----------|
| combSort13()                | 1000 |   3.253 |   2.544 |    2.745 |
| combSort13m()               | 1000 |   3.146 |   2.680 |    2.879 |
| combSort133()               | 1000 |   3.128 |   2.451 |    2.653 |
| combSort133m()              | 1000 |   3.057 |   2.586 |    2.789 |
|-----------------------------+------+---------+---------+----------|
| quickSortMiddle()           | 1000 |   1.550 |   1.136 |    1.101 |
| quickSortMedian()           | 1000 |   1.600 |   1.248 |    1.207 |
| quickSortMedianSwapped()    | 1000 |   1.404 |   1.203 |    1.162 |
|-----------------------------+------+---------+---------+----------|
| qsort()                     | 1000 |   4.598 |   1.111 |    1.646 |
+-----------------------------+------+---------+---------+----------+

```

