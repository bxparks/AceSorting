# WorstCaseBenchmark

Determine the speed of various AceSorting functions when given data arrays that
could trigger worst case runtime. Three types of arrays are tested:

* random array
* already sorted array
* reverse sorted array

**Version**: AceSorting v1.0.0

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

**v1.0.0**
* Upgrade tool chains. No significant change.

## Results

The following results show the runtime of each sorting function in milliseconds,
when sorting different sized arrays.

### Arduino Nano

* 16MHz ATmega328P
* Arduino IDE 1.8.16, Arduino CLI 0.19.2
* Arduino AVR Boards 1.8.3
* `micros()` has a resolution of 4 microseconds

```
+-----------------------------+------+---------+---------+----------+
| Function                    |    N |  random |  sorted | reversed |
|-----------------------------+------+---------+---------+----------|
| bubbleSort()                |  300 | 118.835 |   0.360 |  141.205 |
| insertionSort()             |  300 |  21.685 |   0.585 |   42.715 |
| selectionSort()             |  300 |  46.269 |  45.880 |   47.448 |
|-----------------------------+------+---------+---------+----------|
| shellSortClassic()          |  300 |   6.908 |   4.780 |    5.985 |
| shellSortKnuth()            |  300 |   5.733 |   3.083 |    4.132 |
| shellSortTokuda()           |  300 |   6.558 |   4.474 |    5.496 |
|-----------------------------+------+---------+---------+----------|
| combSort13()                |  300 |   8.160 |   6.408 |    7.242 |
| combSort13m()               |  300 |   8.160 |   6.416 |    7.248 |
| combSort133()               |  300 |   7.674 |   5.885 |    6.714 |
| combSort133m()              |  300 |   7.544 |   5.891 |    6.718 |
|-----------------------------+------+---------+---------+----------|
| quickSortMiddle()           |  300 |   5.648 |   4.088 |    4.018 |
| quickSortMedian()           |  300 |   5.885 |   4.485 |    4.414 |
| quickSortMedianSwapped()    |  300 |   4.854 |   3.956 |    3.920 |
|-----------------------------+------+---------+---------+----------|
| qsort()                     |  300 |  12.925 |   3.986 |    5.557 |
+-----------------------------+------+---------+---------+----------+

```

### SparkFun Pro Micro

* 16 MHz ATmega32U4
* Arduino IDE 1.8.16, Arduino CLI 0.19.2
* SparkFun AVR Boards 1.1.13
* `micros()` has a resolution of 4 microseconds

```
+-----------------------------+------+---------+---------+----------+
| Function                    |    N |  random |  sorted | reversed |
|-----------------------------+------+---------+---------+----------|
| bubbleSort()                |  300 | 117.500 |   0.365 |  141.936 |
| insertionSort()             |  300 |  21.139 |   0.585 |   42.940 |
| selectionSort()             |  300 |  46.521 |  46.116 |   47.695 |
|-----------------------------+------+---------+---------+----------|
| shellSortClassic()          |  300 |   6.973 |   4.801 |    6.018 |
| shellSortKnuth()            |  300 |   5.675 |   3.100 |    4.155 |
| shellSortTokuda()           |  300 |   6.612 |   4.496 |    5.522 |
|-----------------------------+------+---------+---------+----------|
| combSort13()                |  300 |   8.135 |   6.441 |    7.280 |
| combSort13m()               |  300 |   8.160 |   6.447 |    7.285 |
| combSort133()               |  300 |   7.702 |   5.914 |    6.747 |
| combSort133m()              |  300 |   7.765 |   5.920 |    6.756 |
|-----------------------------+------+---------+---------+----------|
| quickSortMiddle()           |  300 |   5.676 |   4.107 |    4.040 |
| quickSortMedian()           |  300 |   5.941 |   4.509 |    4.437 |
| quickSortMedianSwapped()    |  300 |   4.914 |   3.978 |    3.938 |
|-----------------------------+------+---------+---------+----------|
| qsort()                     |  300 |  12.989 |   4.008 |    5.696 |
+-----------------------------+------+---------+---------+----------+

```

### SAMD21 M0 Mini

* 48 MHz ARM Cortex-M0+
* Arduino IDE 1.8.16, Arduino CLI 0.19.2
* SparkFun SAMD Core 1.8.4

```
+-----------------------------+------+---------+---------+----------+
| Function                    |    N |  random |  sorted | reversed |
|-----------------------------+------+---------+---------+----------|
| bubbleSort()                | 1000 | 371.306 |   0.357 |  397.757 |
| insertionSort()             | 1000 |  89.944 |   0.505 |  178.220 |
| selectionSort()             | 1000 | 157.648 | 157.590 |  152.474 |
|-----------------------------+------+---------+---------+----------|
| shellSortClassic()          | 1000 |   5.840 |   3.693 |    4.946 |
| shellSortKnuth()            | 1000 |   5.104 |   2.537 |    3.581 |
| shellSortTokuda()           | 1000 |   6.701 |   4.297 |    5.709 |
|-----------------------------+------+---------+---------+----------|
| combSort13()                | 1000 |   8.535 |   6.744 |    7.266 |
| combSort13m()               | 1000 |   8.308 |   7.105 |    7.621 |
| combSort133()               | 1000 |   8.439 |   6.433 |    6.956 |
| combSort133m()              | 1000 |   7.969 |   6.790 |    7.316 |
|-----------------------------+------+---------+---------+----------|
| quickSortMiddle()           | 1000 |   4.191 |   2.959 |    2.908 |
| quickSortMedian()           | 1000 |   4.340 |   3.197 |    3.151 |
| quickSortMedianSwapped()    | 1000 |   3.730 |   3.025 |    2.975 |
|-----------------------------+------+---------+---------+----------|
| qsort()                     | 1000 |  12.257 |   3.642 |    5.013 |
+-----------------------------+------+---------+---------+----------+

```

### STM32

* STM32 "Blue Pill", STM32F103C8, 72 MHz ARM Cortex-M3
* Arduino IDE 1.8.16, Arduino CLI 0.19.2
* STM32duino 2.0.0

```
+-----------------------------+------+---------+---------+----------+
| Function                    |    N |  random |  sorted | reversed |
|-----------------------------+------+---------+---------+----------|
| bubbleSort()                | 1000 | 244.076 |   0.252 |  251.282 |
| insertionSort()             | 1000 |  49.589 |   0.379 |   97.852 |
| selectionSort()             | 1000 |  91.203 |  91.176 |   91.190 |
|-----------------------------+------+---------+---------+----------|
| shellSortClassic()          | 1000 |   5.499 |   3.466 |    4.673 |
| shellSortKnuth()            | 1000 |   5.047 |   2.367 |    3.467 |
| shellSortTokuda()           | 1000 |   3.708 |   2.372 |    3.134 |
|-----------------------------+------+---------+---------+----------|
| combSort13()                | 1000 |   7.901 |   6.541 |    6.889 |
| combSort13m()               | 1000 |   6.709 |   6.064 |    6.372 |
| combSort133()               | 1000 |   6.954 |   5.798 |    6.120 |
| combSort133m()              | 1000 |   7.604 |   6.915 |    7.278 |
|-----------------------------+------+---------+---------+----------|
| quickSortMiddle()           | 1000 |   4.387 |   3.196 |    3.130 |
| quickSortMedian()           | 1000 |   3.795 |   2.851 |    2.818 |
| quickSortMedianSwapped()    | 1000 |   3.328 |   2.991 |    2.860 |
|-----------------------------+------+---------+---------+----------|
| qsort()                     | 1000 |   8.307 |   2.699 |    3.641 |
+-----------------------------+------+---------+---------+----------+

```

### ESP8266

* NodeMCU 1.0 clone, 80MHz ESP8266
* Arduino IDE 1.8.16, Arduino CLI 0.19.2
* ESP8266 Boards 3.0.2

```
+-----------------------------+------+---------+---------+----------+
| Function                    |    N |  random |  sorted | reversed |
|-----------------------------+------+---------+---------+----------|
| bubbleSort()                | 1000 | 166.901 |   0.175 |  181.192 |
| insertionSort()             | 1000 |  31.064 |   0.225 |   62.579 |
| selectionSort()             | 1000 |  69.026 |  68.998 |   69.010 |
|-----------------------------+------+---------+---------+----------|
| shellSortClassic()          | 1000 |   3.044 |   1.903 |    2.546 |
| shellSortKnuth()            | 1000 |   2.630 |   1.304 |    1.840 |
| shellSortTokuda()           | 1000 |   2.362 |   1.592 |    2.017 |
|-----------------------------+------+---------+---------+----------|
| combSort13()                | 1000 |   3.997 |   3.304 |    3.499 |
| combSort13m()               | 1000 |   3.895 |   3.480 |    3.675 |
| combSort133()               | 1000 |   3.866 |   3.161 |    3.357 |
| combSort133m()              | 1000 |   3.747 |   3.337 |    3.531 |
|-----------------------------+------+---------+---------+----------|
| quickSortMiddle()           | 1000 |   2.369 |   1.691 |    1.655 |
| quickSortMedian()           | 1000 |   2.377 |   1.739 |    1.704 |
| quickSortMedianSwapped()    | 1000 |   1.952 |   1.617 |    1.582 |
|-----------------------------+------+---------+---------+----------|
| qsort()                     | 1000 |   5.800 |   1.747 |    2.371 |
+-----------------------------+------+---------+---------+----------+

```

### ESP32

* ESP32-01 Dev Board, 240 MHz Tensilica LX6
* Arduino IDE 1.8.16, Arduino CLI 0.19.2
* ESP32 Boards 1.0.6

```
+-----------------------------+------+---------+---------+----------+
| Function                    |    N |  random |  sorted | reversed |
|-----------------------------+------+---------+---------+----------|
| bubbleSort()                | 1000 |  65.540 |   0.070 |   67.146 |
| insertionSort()             | 1000 |  14.555 |   0.097 |   29.422 |
| selectionSort()             | 1000 |  29.458 |  29.477 |   28.440 |
|-----------------------------+------+---------+---------+----------|
| shellSortClassic()          | 1000 |   1.273 |   0.774 |    1.064 |
| shellSortKnuth()            | 1000 |   1.109 |   0.551 |    0.776 |
| shellSortTokuda()           | 1000 |   1.113 |   0.683 |    0.942 |
|-----------------------------+------+---------+---------+----------|
| combSort13()                | 1000 |   1.685 |   1.416 |    1.492 |
| combSort13m()               | 1000 |   1.644 |   1.493 |    1.568 |
| combSort133()               | 1000 |   1.652 |   1.364 |    1.441 |
| combSort133m()              | 1000 |   1.588 |   1.440 |    1.517 |
|-----------------------------+------+---------+---------+----------|
| quickSortMiddle()           | 1000 |   0.987 |   0.715 |    0.697 |
| quickSortMedian()           | 1000 |   0.962 |   0.745 |    0.727 |
| quickSortMedianSwapped()    | 1000 |   0.818 |   0.701 |    0.682 |
|-----------------------------+------+---------+---------+----------|
| qsort()                     | 1000 |   2.087 |   0.607 |    0.850 |
+-----------------------------+------+---------+---------+----------+

```

### Teensy 3.2

* 96 MHz ARM Cortex-M4
* Arduino IDE 1.8.16, Arduino CLI 0.19.2
* Teensyduino 1.55
* Compiler options: "Faster"

```
+-----------------------------+------+---------+---------+----------+
| Function                    |    N |  random |  sorted | reversed |
|-----------------------------+------+---------+---------+----------|
| bubbleSort()                | 1000 | 104.168 |   0.106 |  114.721 |
| insertionSort()             | 1000 |  36.445 |   0.199 |   73.171 |
| selectionSort()             | 1000 |  62.881 |  62.838 |   62.859 |
|-----------------------------+------+---------+---------+----------|
| shellSortClassic()          | 1000 |   2.709 |   1.589 |    2.333 |
| shellSortKnuth()            | 1000 |   2.332 |   1.084 |    1.667 |
| shellSortTokuda()           | 1000 |   2.307 |   1.403 |    2.005 |
|-----------------------------+------+---------+---------+----------|
| combSort13()                | 1000 |   3.240 |   2.544 |    2.745 |
| combSort13m()               | 1000 |   3.131 |   2.679 |    2.879 |
| combSort133()               | 1000 |   3.147 |   2.450 |    2.653 |
| combSort133m()              | 1000 |   3.035 |   2.586 |    2.789 |
|-----------------------------+------+---------+---------+----------|
| quickSortMiddle()           | 1000 |   1.515 |   1.136 |    1.101 |
| quickSortMedian()           | 1000 |   1.579 |   1.248 |    1.207 |
| quickSortMedianSwapped()    | 1000 |   1.427 |   1.203 |    1.163 |
|-----------------------------+------+---------+---------+----------|
| qsort()                     | 1000 |   4.662 |   1.111 |    1.668 |
+-----------------------------+------+---------+---------+----------+

```

