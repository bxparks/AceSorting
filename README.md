# AceSorting

Various sorting functions targeted for the Arduino environment, implemented
using C++11 templates. Supports the following algorithms:

* Bubble Sort
    * `bubbleSort()` (not recommended)
* Insertion Sort
    * `insertionSort()` (recommended if N < ~100) and stable sort is needed
* Shell Sort
    * `shellSortClassic()`: gap factor 2
    * `shellSortKnuth()`: gap factor 3 (recommended)
    * `shellSortTokuda()`: gap factor 2.25
* Comb Sort
    * `combSort13()`: gap factor 1.3
    * `combSort125()`: gap factor 1.25
    * `combSort133()`: gap factor 1.33 (recommended)
* Quick Sort
    * `quickSortMiddle()`: pivot on middle element (recommended)
    * `quickSortMedian()`: pivot on median of low, mid, high
    * `quickSortMedianSwapped()`: pivot on median and swap low, mid, high

**Version**: Initial checkin (2021-08-02)

**Status**: Work in progress.

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
    * [Shell Sort](#ShellSort)
    * [Comb Sort](#CombSort)
    * [Quick Sort](#QuickSort)
    * [C Library Qsort](#CLibraryQsort)
* [System Requirements](#SystemRequirements)
    * [Hardware](#Hardware)
    * [Tool Chain](#ToolChain)
    * [Operating System](#OperatingSystem)
* [License](#License)
* [Feedback and Support](#FeedbackAndSupport)
* [Authors](#Authors)

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

This library itself does *not* depend on any other libraries.

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

* flash consumption: 44 bytes on AVR
* additional ram consumption: none
* runtime complexity: `O(N^2)`
* stable sort
* **not recommended**

<a name="InsertionSort"></a>
### Insertion Sort

See https://en.wikipedia.org/wiki/Insertion_sort.

```C++
template <typename T>
void insertionSort(T data[], uint16_t n);
```

* flash consumption, 60 bytes on AVR
* additional ram consumption: none
* runtime complexity: `O(N^2)` but 5-6X faster than `bubbleSort()`
* stable sort
* **recommendedation**: use for N smaller than about 100 and only if you need
  a stable sort

<a name="ShellSort"></a>
### Shell Sort

See https://en.wikipedia.org/wiki/Shellsort.

```C++
template <typename T>
void shellSortClass(T data[], uint16_t n);

template <typename T>
void shellSortKnuth(T data[], uint16_t n);

template <typename T>
void shellSortTokuda(T data[], uint16_t n);
```

* flash consumption: 100-180 bytes of flash on AVR
* additional ram consumption: none
* runtime complexity: `O(N^k)` where `k=1.3 to 1.5`
* unstable sort
* **recomendation**: `shellSortKnuth()`, consistently faster than the
  other versions

<a name="CombSort"></a>
### Comb Sort

https://en.wikipedia.org/wiki/Comb_sort.

```C++
template <typename T>
void combSort13(T data[], uint16_t n);

template <typename T>
void combSort125(T data[], uint16_t n);

template <typename T>
void combSort133(T data[], uint16_t n);
```

* flash consumption: 106-154 bytes on AVR
* additional ram consumption: none
* runtime complexity: `O(N^k)` where k seems similar to Shell Sort
* unstable sort
* **recommendation**: `combSort133()`, smallest and fastest among the 3 versions

The `combSort133()` uses a gap factor of `4/3 = 1.33` instead of the `13/10`
ratio found on many websites. Each successive gap size is calculated by
multiplying by `3/4`. The compiler will optimize the division by 4 into a left
bit shift. On 8-bit processors without hardware division, this makes
`combSort133()` smaller and faster than the other versions.

However, [examples/AutoBenchmark](examples/AutoBenchmark) indicates that
Comb Sort is consistently slower than Shell Sort.

<a name="QuickSort"></a>
### Quick Sort

https://en.wikipedia.org/wiki/Quicksort.

```C++
template <typename T>
void quickSortMiddle(T data[], uint16_t n);

template <typename T>
void quickSortMedian(T data[], uint16_t n);

template <typename T>
void quickSortMedianSwapped(T data[], uint16_t n);
```

* flash consumption: 178-278 bytes on AVR
* additional ram consumption: `O(log(N))` bytes on stack due to recursion
* runtime complexity: `O(N log(N))`
* unstable sort
* **recommendation**
    * avoid on 8-bit processors with limited ram due to extra stack usage by
      recursion
    * use `quickSortMiddle()` if you have to, which is the smallest among the 3
      versions, but only slightly slower

<a name="CLibraryQsort"></a>
### C Library Qsort

```C++
#include <stdlib.h>

void qsort(void *base, size_t nmemb, size_t size,
    int (*compar)(const void *, const void *));
```

* flash consumption: 1084 bytes on AVR
* additional ram consumption: `O(log(N))` bytes on stack due to recursion
* runtime complexity: `O(N log(N))`, but 2-3X slower than C++ versions in this
  library
* unstable sort
* **not recommended** due to excessive flash consumption and slowness

The C library `qsort()` is 2-3X slower than the C++ `quickSortXxx()`, and
consumes 4-5X more flash memory. The `qsort()` function is probably more
sophisticated in terms of handling edge cases, but it is a more general function
that uses a comparator call-back function. That makes it far slower than the C++
template version. Not recommended.

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
