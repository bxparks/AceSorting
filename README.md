# AceSorting

Various sorting functions targeted for the Arduino environment, implemented
using C++11 template functions. The library is intended to be
compatible with most Arduino platforms, but some tradeoffs lean in favor of
lower-end processors (e.g. AVR, lower-end STM32) as opposed to higher-end
processors with larger amounts of RAM (e.g. ESP32, higher-end STM32).

Supports the following algorithms:

* Bubble Sort
    * `bubbleSort()` (not recommended)
* Insertion Sort
    * `insertionSort()` (recommended if N < ~100 or a stable sort is needed)
* Selection Sort
    * `selectionSort()` (not recommended)
* Shell Sort
    * `shellSortClassic()`: gap factor 2
    * `shellSortKnuth()`: gap factor 3 (recommended)
    * `shellSortTokuda()`: gap factor 2.25
* Comb Sort
    * `combSort13()`: gap factor 1.3 (13/10)
    * `combSort13m()`: gap factor 1.3, modified for gaps 9 and 10 (recommended
      for 32-bit processors)
    * `combSort133()`: gap factor 1.33 (4/3) (recommended for 8-bit processors)
    * `combSort133m()`: gap factor 1.33, modified for gaps 9 and 10
* Quick Sort
    * `quickSortMiddle()`: pivot on middle element (recommended)
    * `quickSortMedian()`: pivot on median of low, mid, high
    * `quickSortMedianSwapped()`: pivot on median and swap low, mid, high

**tl;dr**

* In most cases, use `shellSortKnuth()`, costing only 142 bytes on an AVR and
  80-112 bytes on 32-bit processors. It is faster than any `O(N^2)` algorithm
  while consuming only 34-82 extra bytes of flash over `insertionSort()`.
* If `N > ~100`, and you need faster sorting, and you have sufficient memory for
  recursive functions, use `quickSortMiddle()` on 8-bit AVR processors, and
  `quickSortMedianSwapped()` on 32-bit processors.
* Use `insertionSort()` if you need a stable sort.
* Use `combSort133()` or `shellSortClassic()` to get the smallest sorting
  function faster than `O(N^2)`.
* Don't use the C library `qsort()`. It is 2-3X slower than the `quickSortXxx()`
  functions in this library, and but consumes 4-5X more in flash bytes.

**Version**: 0.1 (2021-08-04)

**Status**: Simple versions are working and stable. Need to add overloaded
versions which take a custom comparator.

**Changelog**: [CHANGELOG.md](CHANGELOG.md)

## Table of Contents

* [Installation](#Installation)
    * [Source Code](#SourceCode)
    * [Dependencies](#Dependencies)
* [Documentation](#Documentation)
    * [Examples](#Examples)
* [Usage](#Usage)
    * [Include Header and Namespace](#HeaderAndNamespace)
    * [Bubble Sort](#BubbleSort)
    * [Insertion Sort](#InsertionSort)
    * [Selection Sort](#SelectionSort)
    * [Shell Sort](#ShellSort)
    * [Comb Sort](#CombSort)
    * [Quick Sort](#QuickSort)
    * [C Library Qsort](#CLibraryQsort)
* [Resource Consumption](#ResourceConsumption)
    * [Flash And Static Memory](#FlashAndStaticMemory)
    * [CPU Cycles](#CpuCycles)
* [System Requirements](#SystemRequirements)
    * [Hardware](#Hardware)
    * [Tool Chain](#ToolChain)
    * [Operating System](#OperatingSystem)
* [Bugs and Limitations](#BugsAndLimitations)
* [Alternative Libraries](#AlternativeLibraries)
* [License](#License)
* [Feedback and Support](#FeedbackAndSupport)
* [Authors](#Authors)

<a name="HelloSort"></a>
## Hello Sort

This is a simplified version of the [examples/HelloSort](examples/HelloSort)
demo:

```C++
#include <Arduino.h>
#include <AceSorting.h>

using ace_sorting::shellSortKnuth;

const uint16_t ARRAY_SIZE = 50;
int array[ARRAY_SIZE];

void printArray(int* array, uint16_t arraySize) {
  for (uint16_t i = 0; i < arraySize; i++) {
    Serial.print(array[i]);
    Serial.print(' ');
  }
  Serial.println();
}

void fillArray(int* array, uint16_t arraySize) {
  for (uint16_t i = 0; i < arraySize; i++) {
    array[i] = random(256);
  }
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  while (!Serial); // Leonardo/Micro

  // Attempt to get a random seed using the floating analog pin.
  randomSeed(analogRead(A0));

  fillArray();
  Serial.println("Unsorted:");
  printArray(array, arraySize);

  // The compiler automatically generates the correct version of
  // shellSortKnuth() based on the type of `array`.
  shellSortKnuth(array, arraySize);
  Serial.println("Sorted:");
  printArray(array, arraySize);
}

void loop() {}
```

<a name="Installation"></a>
## Installation

The latest stable release will eventually be available in the Arduino IDE
Library Manager. Search for "AceSorting". Click install. (It is not there
yet.)

The development version can be installed by cloning the
[GitHub repository](https://github.com/bxparks/AceSorting), checking out the
`develop` branch, then manually copying over the contents to the `./libraries`
directory used by the Arduino IDE. (The result is a directory named
`./libraries/AceSorting`.)

The `master` branch contains the stable release.

<a name="SourceCode"></a>
### Source Code

The source files are organized as follows:
* `src/AceSorting.h` - main header file
* `src/ace_sorting/` - implementation files
* `tests/` - unit tests which require [AUnit](https://github.com/bxparks/AUnit)
* `examples/` - example sketches
* `docs/` - contains the doxygen docs and additional manual docs

<a name="Dependencies"></a>
### Dependencies

This library itself does *not* depend on any other library.

The unit tests depend on:

* AUnit (https://github.com/bxparks/AUnit)

Some of the examples may depend on:

* AceCommon (https://github.com/bxparks/AceCommon)

<a name="Documentation"></a>
## Documentation

* this `README.md` file
* [Doxygen docs](https://bxparks.github.io/AceSorting/html) on Github pages.

<a name="Examples"></a>
### Examples

* [examples/HelloSort](examples/HelloSort)
    * A demo of one of the sorting functions.
* Benchmarks
    * [examples/MemoryBenchmark](examples/MemoryBenchmark)
        * Determine flash and static RAM consumption of various algorithms.
    * [examples/AutoBenchmark](examples/AutoBenchmark)
        * Determine CPU runtime of various algorithms.
    * [examples/WorstCaseBenchmark](examples/WorstCaseBenchmark)
        * Determine CPU runtime of worst case input data (e.g. sorted, reverse
        sorted).

<a name="Usage"></a>
## Usage

<a name="HeaderAndNamespace"></a>
### Include Header and Namespace

Only a single header file `AceSorting.h` is required to use this library.
To prevent name clashes with other libraries that the calling code may use, all
classes are defined in the `ace_sorting` namespace. To use the code without
prepending the `ace_sorting::` prefix, use the `using` directive to select the
specific algorithm:

```C++
#include <Arduino.h>
#include <AceSorting.h>
using ace_sorting::shellSortKnuth;
```

<a name="BubbleSort"></a>
### Bubble Sort

See https://en.wikipedia.org/wiki/Bubble_sort.

```C++
template <typename T>
void bubbleSort(T data[], uint16_t n);
```

* Flash consumption: 44 bytes on AVR
* Additional ram consumption: none
* Runtime complexity: `O(N^2)`
* Stable sort: Yes
* **Not recommended**

<a name="InsertionSort"></a>
### Insertion Sort

See https://en.wikipedia.org/wiki/Insertion_sort.

```C++
template <typename T>
void insertionSort(T data[], uint16_t n);
```

* Flash consumption, 60 bytes on AVR
* Additional ram consumption: none
* Runtime complexity: `O(N^2)` but 5-6X faster than `bubbleSort()`
* Stable sort: Yes
* **Recommendation**: Use for N smaller than about 100 and only if you need
  a stable sort

<a name="SelectionSort"></a>
### Selection Sort

See https://en.wikipedia.org/wiki/Selection_sort.

```C++
template <typename T>
void selectionSort(T data[], uint16_t n);
```

* Flash consumption, 100 bytes on AVR
* Additional ram consumption: none
* Runtime complexity: `O(N^2)` but 2X slower than `insertionSort()`
* Stable sort: No
* **Not recommended**:
    * Larger and slower than `insertionSort()` but is not a stable sort.
    * The only thing it has going for it is that it has the least number of
      writes versus reads. Might be worth looking into if writing the data is
      much more expensive than reading the data.

<a name="ShellSort"></a>
### Shell Sort

See https://en.wikipedia.org/wiki/Shellsort. Three versions are provided in this
library:

```C++
template <typename T>
void shellSortClassic(T data[], uint16_t n);

template <typename T>
void shellSortKnuth(T data[], uint16_t n);

template <typename T>
void shellSortTokuda(T data[], uint16_t n);
```

* Flash consumption: 100-180 bytes of flash on AVR
* Additional ram consumption: none
* Runtime complexity: `O(N^k)` where `k=1.3 to 1.5`
* Stable sort: No
* **Recomendation**: Use `shellSortKnuth()`, which seems consistently faster
  than `shellSortClassic()`, just as fast as `shellSortTokuda()` but is simpler
  and takes less flash memory than `shellSortTokuda()`.

<a name="CombSort"></a>
### Comb Sort

See https://en.wikipedia.org/wiki/Comb_sort
and https://rosettacode.org/wiki/Sorting_algorithms/Comb_sort.
Four versions are provided in this library:

```C++
template <typename T>
void combSort13(T data[], uint16_t n);

template <typename T>
void combSort13m(T data[], uint16_t n);

template <typename T>
void combSort133(T data[], uint16_t n);

template <typename T>
void combSort133m(T data[], uint16_t n);
```

* Flash consumption: 106-172 bytes on AVR
* Additional ram consumption: none
* Runtime complexity: `O(N^k)` where k seems similar to Shell Sort
* Stable sort: No
* **Recommendation**:
    * Use `combSort133()` on 8-bit processors.
    * Use `combSort13m()` on 32-bit processors.

The `combSort13()` and `combSort13m()` functions use a gap factor of `10/13 =
1.3`. The `combSort13m()` function modifies the gap sequence when the gap is 9
or 10. That apparently make the algorithm faster for reasons that I have not
been able to find on the internet.

The `combSort133()` and `combSort133m()` use a gap factor of `4/3 = 1.33`. The
`4/3` ratio allows the compiler to replace an integer division with a left bit
shift, so that code is smaller and faster on 8-bit processors without hardware
integer division. The `combSort133m()` function modifies the gap sequence when
the gap is 9 or 10.

Overall, [examples/AutoBenchmark](examples/AutoBenchmark) shows that Comb Sort
is consistently slower than Shell Sort so it is difficult to recommend it over
Shell Sort.

<a name="QuickSort"></a>
### Quick Sort

https://en.wikipedia.org/wiki/Quicksort. Three versions are provided in this
library:

```C++
template <typename T>
void quickSortMiddle(T data[], uint16_t n);

template <typename T>
void quickSortMedian(T data[], uint16_t n);

template <typename T>
void quickSortMedianSwapped(T data[], uint16_t n);
```

* Flash consumption: 178-278 bytes on AVR
* Additional ram consumption: `O(log(N))` bytes on stack due to recursion
* Runtime complexity: `O(N log(N))`
* Stable sort: No
* **Recommendation**
    * Avoid on 8-bit processors with limited ram due to extra stack usage by
      recursion.
    * Use `quickSortMiddle()` if you have to, which is the smallest among the 3
      versions, but only slightly slower.

<a name="CLibraryQsort"></a>
### C Library Qsort

The C library `<stdlib.h>` provides a `qsort()` function that implements Quick
Sort. Since this is a standard C library function, it should be available on all
Arduino platforms. The signature looks like this:

```C++
#include <stdlib.h>

void qsort(void *base, size_t nmemb, size_t size,
    int (*compar)(const void *, const void *));
```

It has the following characteristics:

* Flash consumption: 1084 bytes on AVR
* Additional ram consumption: `O(log(N))` bytes on stack due to recursion
* Runtime complexity: `O(N log(N))`, but 2-3X slower than C++ versions in this
  library
* Stable sort: No
* **Not recommended** due to excessive flash consumption and slowness.

According to benchmarks, `qsort()` is 2-3X slower than the C++ `quickSortXxx()`,
and consumes 4-5X more flash memory. The `qsort()` function is probably more
sophisticated in the handling of edge cases, but it suffers from being a general
function that uses pointer to a comparator call-back function. That makes it
2-3X slower than the C++ template functions in this library. Not recommended.

<a name="ResourceConsumption"></a>
## Resource Consumption

<a name="FlashAndStaticMemory"></a>
### Flash And Static Memory

The full details of flash and static memory consumptions are given in
[examples/MemoryBenchmark](examples/MemoryBenchmark). Here are 2 samples.

**Arduino Nano (ATmega328)**

```
+---------------------------------------------------------------------+
| Functionality                          |  flash/  ram |       delta |
|----------------------------------------+--------------+-------------|
| Baseline                               |   1066/  214 |     0/    0 |
|----------------------------------------+--------------+-------------|
| bubbleSort()                           |   1110/  214 |    44/    0 |
| insertionSort()                        |   1126/  214 |    60/    0 |
| selectionSort()                        |   1154/  214 |    88/    0 |
|----------------------------------------+--------------+-------------|
| shellSortClassic()                     |   1162/  214 |    96/    0 |
| shellSortKnuth()                       |   1208/  214 |   142/    0 |
| shellSortTokuda()                      |   1248/  240 |   182/   26 |
|----------------------------------------+--------------+-------------|
| combSort13()                           |   1220/  214 |   154/    0 |
| combSort13m()                          |   1238/  214 |   172/    0 |
| combSort133()                          |   1172/  214 |   106/    0 |
| combSort133m()                         |   1194/  214 |   128/    0 |
|----------------------------------------+--------------+-------------|
| quickSortMiddle()                      |   1244/  214 |   178/    0 |
| quickSortMedian()                      |   1296/  214 |   230/    0 |
| quickSortMedianSwapped()               |   1344/  214 |   278/    0 |
|----------------------------------------+--------------+-------------|
| qsort()                                |   2150/  214 |  1084/    0 |
+---------------------------------------------------------------------+
```

**ESP8266**

```
+---------------------------------------------------------------------+
| Functionality                          |  flash/  ram |       delta |
|----------------------------------------+--------------+-------------|
| Baseline                               | 257100/26976 |     0/    0 |
|----------------------------------------+--------------+-------------|
| bubbleSort()                           | 257164/26976 |    64/    0 |
| insertionSort()                        | 257164/26976 |    64/    0 |
| selectionSort()                        | 257180/26976 |    80/    0 |
|----------------------------------------+--------------+-------------|
| shellSortClassic()                     | 257180/26976 |    80/    0 |
| shellSortKnuth()                       | 257212/26976 |   112/    0 |
| shellSortTokuda()                      | 257256/27004 |   156/   28 |
|----------------------------------------+--------------+-------------|
| combSort13()                           | 257196/26976 |    96/    0 |
| combSort13m()                          | 257212/26976 |   112/    0 |
| combSort133()                          | 257180/26976 |    80/    0 |
| combSort133m()                         | 257196/26976 |    96/    0 |
|----------------------------------------+--------------+-------------|
| quickSortMiddle()                      | 257244/26976 |   144/    0 |
| quickSortMedian()                      | 257276/26976 |   176/    0 |
| quickSortMedianSwapped()               | 257308/26976 |   208/    0 |
|----------------------------------------+--------------+-------------|
| qsort()                                | 258076/26976 |   976/    0 |
+---------------------------------------------------------------------+
```

<a name="CpuCycles"></a>
### CPU Cycles

The CPU benchmark numbers can be seen in
[examples/AutoBenchmark](examples/AutoBenchmark). All times in milliseconds.
Here are 2 samples.

**Arduino Nano (ATmega328)**

```
+---------------------+------------------------+---------+---------+---------+
|            \      N |    10 |    30 |    100 |     300 |    1000 |    3000 |
| Function    \       |       |       |        |         |         |         |
|---------------------+-------+-------+--------+---------+---------+---------|
| bubbleSort()        | 0.107 | 1.077 | 12.735 | 116.675 |         |         |
| insertionSort()     | 0.045 | 0.263 |  2.557 |  22.252 |         |         |
| selectionSort()     | 0.088 | 0.560 |  5.600 |  48.892 |         |         |
|---------------------+-------+-------+--------+---------+---------+---------|
| shellSortClassic()  | 0.074 | 0.310 |  1.706 |   6.865 |         |         |
| shellSortKnuth()    | 0.101 | 0.330 |  1.450 |   5.665 |         |         |
| shellSortTokuda()   | 0.075 | 0.327 |  1.614 |   6.540 |         |         |
|---------------------+-------+-------+--------+---------+---------+---------|
| combSort13()        | 0.160 | 0.534 |  2.214 |   8.167 |         |         |
| combSort13m()       | 0.165 | 0.550 |  2.219 |   8.181 |         |         |
| combSort133()       | 0.086 | 0.396 |  1.944 |   7.702 |         |         |
| combSort133m()      | 0.086 | 0.416 |  1.978 |   7.740 |         |         |
|---------------------+-------+-------+--------+---------+---------+---------|
| quickSortMiddle()   | 0.096 | 0.368 |  1.568 |   5.651 |         |         |
| quickSortMedian()   | 0.117 | 0.431 |  1.717 |   5.905 |         |         |
| quickSortMdnSwppd() | 0.094 | 0.341 |  1.417 |   4.909 |         |         |
|---------------------+-------+-------+--------+---------+---------+---------|
| qsort()             | 0.204 | 0.855 |  3.629 |  13.021 |         |         |
+---------------------+-------+-------+--------+---------+---------+---------+
```

**ESP8266**

```
+---------------------+------------------------+---------+---------+---------+
|            \      N |    10 |    30 |    100 |     300 |    1000 |    3000 |
| Function    \       |       |       |        |         |         |         |
|---------------------+-------+-------+--------+---------+---------+---------|
| bubbleSort()        | 0.021 | 0.192 |  2.231 |  20.143 | 225.651 |         |
| insertionSort()     | 0.009 | 0.037 |  0.362 |   3.220 |  34.646 |         |
| selectionSort()     | 0.017 | 0.085 |  0.892 |   7.930 |  87.723 |         |
|---------------------+-------+-------+--------+---------+---------+---------|
| shellSortClassic()  | 0.011 | 0.039 |  0.215 |   0.878 |   3.609 |  13.789 |
| shellSortKnuth()    | 0.010 | 0.036 |  0.172 |   0.690 |   3.022 |  11.304 |
| shellSortTokuda()   | 0.009 | 0.039 |  0.183 |   0.735 |   3.140 |  11.366 |
|---------------------+-------+-------+--------+---------+---------+---------|
| combSort13()        | 0.013 | 0.048 |  0.219 |   0.846 |   3.711 |  13.689 |
| combSort13m()       | 0.014 | 0.051 |  0.222 |   0.840 |   3.622 |  13.104 |
| combSort133()       | 0.010 | 0.040 |  0.208 |   0.796 |   3.571 |  12.430 |
| combSort133m()      | 0.010 | 0.044 |  0.206 |   0.793 |   3.465 |  12.387 |
|---------------------+-------+-------+--------+---------+---------+---------|
| quickSortMiddle()   | 0.013 | 0.045 |  0.185 |   0.651 |   2.519 |   8.307 |
| quickSortMedian()   | 0.016 | 0.052 |  0.200 |   0.677 |   2.551 |   8.403 |
| quickSortMdnSwppd() | 0.012 | 0.039 |  0.159 |   0.558 |   2.122 |   7.109 |
|---------------------+-------+-------+--------+---------+---------+---------|
| qsort()             | 0.028 | 0.092 |  0.416 |   1.516 |   6.010 |  20.789 |
+---------------------+-------+-------+--------+---------+---------+---------+
```

<a name="SystemRequirements"></a>
## System Requirements

<a name="Hardware"></a>
### Hardware

This library has Tier 1 support on the following boards:

* Arduino Nano (16 MHz ATmega328P)
* SparkFun Pro Micro (16 MHz ATmega32U4)
* SAMD21 M0 Mini (48 MHz ARM Cortex-M0+)
* STM32 Blue Pill (STM32F103C8, 72 MHz ARM Cortex-M3)
* NodeMCU 1.0 (ESP-12E module, 80MHz ESP8266)
* WeMos D1 Mini (ESP-12E module, 80 MHz ESP8266)
* ESP32 dev board (ESP-WROOM-32 module, 240 MHz dual core Tensilica LX6)
* Teensy 3.2 (72 MHz ARM Cortex-M4)

Tier 2 support can be expected on the following boards, mostly because I don't
test these as often:

* ATtiny85 (8 MHz ATtiny85)
* Arduino Pro Mini (16 MHz ATmega328P)
* Teensy LC (48 MHz ARM Cortex-M0+)
* Mini Mega 2560 (Arduino Mega 2560 compatible, 16 MHz ATmega2560)

The following boards are **not** supported:

* Any platform using the ArduinoCore-API
  (https://github.com/arduino/ArduinoCore-api).
    * For example, Nano Every, MKRZero, and Raspberry Pi Pico RP2040.

<a name="ToolChain"></a>
### Tool Chain

* [Arduino IDE 1.8.13](https://www.arduino.cc/en/Main/Software)
* [Arduino CLI 0.14.0](https://arduino.github.io/arduino-cli)
* [SpenceKonde ATTinyCore 1.5.2](https://github.com/SpenceKonde/ATTinyCore)
* [Arduino AVR Boards 1.8.3](https://github.com/arduino/ArduinoCore-avr)
* [Arduino SAMD Boards 1.8.9](https://github.com/arduino/ArduinoCore-samd)
* [SparkFun AVR Boards 1.1.13](https://github.com/sparkfun/Arduino_Boards)
* [SparkFun SAMD Boards 1.8.3](https://github.com/sparkfun/Arduino_Boards)
* [STM32duino 2.0.0](https://github.com/stm32duino/Arduino_Core_STM32)
* [ESP8266 Arduino 2.7.4](https://github.com/esp8266/Arduino)
* [ESP32 Arduino 1.0.6](https://github.com/espressif/arduino-esp32)
* [Teensyduino 1.53](https://www.pjrc.com/teensy/td_download.html)

<a name="OperatingSystem"></a>
### Operating System

I use Ubuntu 20.04 for the vast majority of my development. I expect that the
library will work fine under MacOS and Windows, but I have not explicitly tested
them.

<a name="BugsAndLimitations"></a>
## Bugs and Limitations

* The number of elements `n` of the input `data` array is of type `uint16_t`.
    * The maximum size of the input array is 65535.
    * If you need bigger, copy the sorting algorithm that you want and change
      the `uint16_t n` to a `uint32_t n`.
    * Using a fixed `uint16_t` means that the edge case behavior of these
      algorithms are consistency across all platforms.
    * Certain implementation choices and optimizations can be made if we know
      that `n` cannot exceed a bounded value. For example, the
      `shellSortTokuda()` function can use a pre-generated sequence of gaps
      which is a reasonable size because it only needs to go up to 65535.
    * The alternative was to use the `size_t` type whose size is different on
      different platforms: 2 bytes on 8-bit processors, 4 bytes on 32-bit
      processors, and 8 bytes on 64-bit processors. However, I did not want to
      worry about edge case behavior of some of these algorithms for extremely
      large values of `n`.
* No hybrid sorting algorithms.
    * Different sorting algorithms are more efficient at different ranges of
      `N`. So hybrid algorithms will use different sorting algorithms at
      different points in their iteration. An example is the
      [Introsort](https://en.wikipedia.org/wiki/Introsort) which uses Quick
      Sort, then switches to Heap Sort when the recursion depth becomes too
      high, then switches to Insertion Sort when `N` is below a threshold.
    * This library currently does not implement such sorting algorithms, partly
      because they are more difficult to write and validate, and partly because
      these hybrid algorithms will inevitably consume more flash memory, which
      is usually a scarce resource in embedded environments.

<a name="AlternativeLibraries"></a>
## Alternative Libraries

When I looked for sorting algorithm libraries for Arduino I found a small
handful, but I found them unsuitable for me.

* https://github.com/LinnesLab/KickSort
    * Much of the AceSorting library was inspired by the KickSort library.
    * The problem is that its `shellSort()` implementation was copied from
      this post (https://forum.arduino.cc/index.php?topic=280486.0) from 2014.
      Unfortunately, that implementation of Shell Sort is incorrect.
    * No unit tests provided.
* https://github.com/emilv/ArduinoSort
    * Implements the Insertion Sort, which is an `O(N^2)` algorithm.
    * Some unit testing provided.
    * It is not suitable for array sizes greater than about 100.
* https://github.com/luisllamasbinaburo/Arduino-QuickSort
    * Documentation is in Spanish which I unfortunately do not understand.
    * Provides a single version of Quick Sort, the equivalent of
      `quickSortMiddle()` provided by this library.
    * No unit tests provided.
* https://github.com/arduino-libraries/Arduino_AVRSTL
    * Provides a template `sort()` function.
    * Often STL library functions are too general, therefore, too bloated for
      many resource constrained environments. I suspect that the STL `sort()`
      function falls into this category.
    * The library is configured to target only the `avr` and `megaavr`
      platforms. Does it work on other processors? I don't know, and I don't
      want to spend the time to figure that out, because working with the STL
      code is too painful.
    * No unit tests provided.

Here are some of the reasons that I created my own library:

* Shell Sort is one of my favorite sorting algorithms because it can be very
  fast and very small. But the KickSort library provides an incorrect
  implementation which is even slower than Bubble Sort.
* Most libraries do not come with unit tests, so I do not know what other bugs
  are lurking in the code.
* Most libraries do not evaluate the memory and CPU consumption of their sorting
  algorithms. I wanted to know these numbers precisely so that I could make
  informed trade off decisions.
* I did not want to deal with the complexity of the C++ STL library. It is just
  too painful in an embedded environment.
* Lastly, I wanted to implement my own sorting routines to make sure that I had
  a complete understanding of each algorithm. I had forgotten so much since my
  undergraduate years.

<a name="License"></a>
## License

[MIT License](https://opensource.org/licenses/MIT)

<a name="FeedbackAndSupport"></a>
## Feedback and Support

If you have any questions, comments and other support questions about how to
use this library, use the
[GitHub Discussions](https://github.com/bxparks/AceSorting/discussions)
for this project. If you have bug reports or feature requests, file a ticket in
[GitHub Issues](https://github.com/bxparks/AceSorting/issues). I'd love to hear
about how this software and its documentation can be improved. I can't promise
that I will incorporate everything, but I will give your ideas serious
consideration.

Please refrain from emailing me directly unless the content is sensitive. The
problem with email is that I cannot reference the email conversation when other
people ask similar questions later.

<a name="Authors"></a>
## Authors

Created by Brian T. Park (brian@xparks.net).
