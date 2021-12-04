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

* In most cases, use `shellSortKnuth()`.
    * It costs only 142 bytes on an AVR and 80-112 bytes on 32-bit processors.
    * It is faster than any `O(N^2)` algorithm while consuming only 34-82 extra
      bytes of flash over `insertionSort()`.
* If `N >= ~1000`, *and* you have sufficient static memory for recursive
  functions, *and* `shellSortKnuth()` is not fast enough, use:
    * `quickSortMiddle()` on 8-bit AVR processors, and
    * `quickSortMedianSwapped()` on 32-bit processors.
* Use `combSort133()` or `shellSortClassic()` to get the smallest sorting
  function faster than `O(N^2)`.
* Use `insertionSort()` if you need a stable sort.
* Don't use the C library `qsort()`.
    * It is 2-3X slower than the `quickSortXxx()` functions in this library, and
      consumes 4-5X more in flash bytes.
* Never use Bubble Sort.
    * Insertion Sort is 5-6X faster with only a handful (0-32) bytes of extra
      flash.

**Version**: 1.0.0 (2021-12-04)

**Changelog**: [CHANGELOG.md](CHANGELOG.md)

## Table of Contents

* [Hello Sorting](#HelloSorting)
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
* [Advanced Usage](#AdvancedUsage)
    * [Function Pointer](#FunctionPointer)
    * [Lambda Expression](#LambdaExpression)
    * [Compiler Optimizations](#CompilerOptimizations)
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

<a name="HelloSorting"></a>
## Hello Sorting

This is a simplified version of the
[examples/HelloSorting](examples/HelloSorting) demo:

```C++
#include <Arduino.h>
#include <AceSorting.h>

using ace_sorting::shellSortKnuth;

const uint16_t ARRAY_SIZE = 20;
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

The latest stable release is available in the Arduino IDE Library Manager.
Search for "AceSorting". Click install.

The development version can be installed by cloning the
[GitHub repository](https://github.com/bxparks/AceSorting), checking out the
`develop` branch, then manually copying over to or creating a symlink from the
`./libraries` directory used by the Arduino IDE. (The result is a directory
or link named `./libraries/AceSorting`.)

The `master` branch contains the stable releases.

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

* [examples/HelloSorting](examples/HelloSorting)
    * A simple demo of one of the sorting functions.
* [examples/CompoundSortingDemo](examples/CompoundSortingDemo)
    * A more complex example of sorting by a compound key, first by
      `score`, then breaking any ties by `name`.
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
specific algorithm. For example, to use the `shellSortKnut()` function, use
something like this:

```C++
#include <Arduino.h>
#include <AceSorting.h>
using ace_sorting::shellSortKnuth;
```

<a name="BubbleSort"></a>
### Bubble Sort

See https://en.wikipedia.org/wiki/Bubble_sort.

```C++
namespace ace_sorting {

template <typename T>
void bubbleSort(T data[], uint16_t n);

}
```

* Flash consumption: 44 bytes on AVR
* Additional ram consumption: none
* Runtime complexity: `O(N^2)`
* Stable sort: Yes
* Performance Notes:
    * If `data[]` is already sorted, this is `O(N)`.
    * Worst performance `O(N^2)` when data is reverse sorted.
* **Not recommended**

<a name="InsertionSort"></a>
### Insertion Sort

See https://en.wikipedia.org/wiki/Insertion_sort.

```C++
namespace ace_sorting {

template <typename T>
void insertionSort(T data[], uint16_t n);

}
```

* Flash consumption, 60 bytes on AVR
* Additional ram consumption: none
* Runtime complexity: `O(N^2)` but 5-6X faster than `bubbleSort()`
* Stable sort: Yes
* Performance Notes:
    * If `data[]` is already sorted, this algorithm is `O(N)`.
    * Worst performance `O(N^2)` when data is reverse sorted.
* **Recommendation**: Use for N smaller than about 100 and only if you need
  a stable sort

<a name="SelectionSort"></a>
### Selection Sort

See https://en.wikipedia.org/wiki/Selection_sort.

```C++
namespace ace_sorting {

template <typename T>
void selectionSort(T data[], uint16_t n);

}
```

* Flash consumption, 100 bytes on AVR
* Additional ram consumption: none
* Runtime complexity: `O(N^2)` but 2X slower than `insertionSort()`
* Stable sort: No
* Performance Notes:
    * Little change in performance when data is already sorted or reverse
      sorted.
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
namespace ace_sorting {

template <typename T>
void shellSortClassic(T data[], uint16_t n);

template <typename T>
void shellSortKnuth(T data[], uint16_t n);

template <typename T>
void shellSortTokuda(T data[], uint16_t n);

}
```

* Flash consumption: 100-180 bytes of flash on AVR
* Additional ram consumption: none
* Runtime complexity: `O(N^k)` where `k=1.3 to 1.5`
* Stable sort: No
* Performance Notes:
    * As fast as Quick Sort for `N <= ~300`.
    * Little change in performance when data is already sorted or reverse
      sorted.
* **Recomendation**: Use `shellSortKnuth()`, which seems consistently faster
  than `shellSortClassic()`, just as fast as `shellSortTokuda()` but is simpler
  and takes less flash memory than `shellSortTokuda()`.

<a name="CombSort"></a>
### Comb Sort

See https://en.wikipedia.org/wiki/Comb_sort
and https://rosettacode.org/wiki/Sorting_algorithms/Comb_sort.
Four versions are provided in this library:

```C++
namespace ace_sorting {

template <typename T>
void combSort13(T data[], uint16_t n);

template <typename T>
void combSort13m(T data[], uint16_t n);

template <typename T>
void combSort133(T data[], uint16_t n);

template <typename T>
void combSort133m(T data[], uint16_t n);

}
```

* Flash consumption: 106-172 bytes on AVR
* Additional ram consumption: none
* Runtime complexity: `O(N^k)` where k seems similar to Shell Sort
* Stable sort: No
* Performance Notes:
    * Slightly slower than Shell Sort over similar data sets.
    * Little change in performance when data is already sorted or reverse
      sorted.
* Upper limits:
    * `combSort13()` and `combSort13m()`:  `n = 6553` on 8-bit AVR processors
      due to integer overflow.
    * `combSort133()` and `combSort133m()`: `n = 21845` on 8-bit AVR processors
      due to integer overflow.
* **Recommendation**:
    * Prefer Shell Sort over Comb Sort in most situations.
    * Use `combSort133()` on 8-bit processors.
    * Use `combSort13m()` on 32-bit processors.

The `combSort13()` and `combSort13m()` functions use a gap factor of `10/13 =
1.3`. The `combSort13m()` function modifies the gap sequence when the gap is 9
or 10. That apparently make the algorithm faster for reasons that I have not
been able to find on the internet.

The `combSort133()` function uses a gap factor of `4/3 = 1.33` instead of
`10/13`. The `4/3` ratio means that the gap size is multiplied by `3/4` on each
iteration, which allows the compiler to replace the integer division by `4` with
a right bit shift operation, so that code is smaller and faster on 8-bit
processors without hardware integer division.

The `combSort133m()` function essentially the same as `combSort133()` but
modifies the gap sequence when the gap is 9 or 10.

In terms of performance, [examples/AutoBenchmark](examples/AutoBenchmark) shows
that Comb Sort is consistently slower than Shell Sort so it is difficult to
recommend it over Shell Sort.

<a name="QuickSort"></a>
### Quick Sort

See https://en.wikipedia.org/wiki/Quicksort. Three versions are provided in this
library:

```C++
namespace ace_sorting {

template <typename T>
void quickSortMiddle(T data[], uint16_t n);

template <typename T>
void quickSortMedian(T data[], uint16_t n);

template <typename T>
void quickSortMedianSwapped(T data[], uint16_t n);

}
```

* `quickSortMiddle()`
    * The pivot is the middle element in each partition, regardless of its
      value.
* `quickSortMedian()`
    * The pivot is the median element among the 3 elements on the left, middle,
      and right slots of each partition.
* `quickSortMedianSwapped()`
    * The pivot is the median element among the 3 elements on the left, middle,
      and right slots of each partition.
    * The 3 elements are swapped so that they are sorted.
* Flash consumption: 178-278 bytes on AVR
* Additional ram consumption: `O(log(N))` bytes on stack due to recursion
* Runtime complexity: `O(N log(N))`
* Stable sort: No
* Performance Notes:
    * Fastest algorithm for large (`N >= ~1000`) data sets.
    * Little change in performance when data is already sorted or reverse
      sorted.
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

According to benchmarks, `qsort()` is 2-3X slower than the C++ `quickSortXxx()`
functions provided by this library, and consumes 4-5X more flash memory. The
`qsort()` function is probably more sophisticated in the handling of edge cases,
but it suffers from being a general function that uses a call-back function. The
overhead of that function call makes it 2-3X slower than the C++ template
functions in this library where the comparison function call is usually inlined
by the compiler. For these reasons, it is difficult to recommend the C-library
`qsort()` function.

<a name="AdvancedUsage"></a>
## Advanced Usage

Each sorting algorithm comes in another variant that takes 3 arguments instead
of 2 arguments. For completeness, here are the signatures of the 3-argument
variants:

```C++
namespace ace_sorting {

template <typename T, typename F>
void bubbleSort(T data[], uint16_t n, F&& lessThan);

template <typename T, typename F>
void insertionSort(T data[], uint16_t n, F&& lessThan);

template <typename T, typename F>
void selectionSort(T data[], uint16_t n, F&& lessThan);

template <typename T, typename F>
void shellSortClassic(T data[], uint16_t n, F&& lessThan);

template <typename T, typename F>
void shellSortKnuth(T data[], uint16_t n, F&& lessThan);

template <typename T, typename F>
void shellSortTokuda(T data[], uint16_t n, F&& lessThan);

template <typename T, typename F>
void combSort13(T data[], uint16_t n, F&& lessThan);

template <typename T, typename F>
void combSort13m(T data[], uint16_t n, F&& lessThan);

template <typename T, typename F>
void combSort133(T data[], uint16_t n, F&& lessThan);

template <typename T, typename F>
void combSort133m(T data[], uint16_t n, F&& lessThan);

template <typename T, typename F>
void quickSortMiddle(T data[], uint16_t n, F&& lessThan);

template <typename T, typename F>
void quickSortMedian(T data[], uint16_t n, F&& lessThan);

template <typename T, typename F>
void quickSortMedianSwapped(T data[], uint16_t n, F&& lessThan);

}
```

The 3rd argument `lessThan` is a user-defined function pointer or a lambda
expression that implements the "less than" comparison operator between 2
elements in the `data[]` array. (The `F&&` is a C++11 syntax that means "rvalue
reference to a templatized type of `F`".) In the context of this library, the
`lessThan` parameter can be thought of as a function-like thing that accepts 2
elements of type `T` and returns a `bool`. Two types of this `lessThan`
parameter is explained below.

<a name="FunctionPointer"></a>
### Function Pointer

If `lessThan` is a function pointer, then its signature should look something
like one of these:

```C++
bool lessThan(const T& a, const T& b);

bool lessThan(T a, T b);
```

The [examples/CompoundSortingDemo](examples/CompoundSortingDemo) example shows
what this looks like to sort an array of pointers to `Record` entries by
`score`, then by `name`, to break any ties:

```C++
struct Record {
  const char* name;
  int score;
};

bool sortByScoreThenName(const Record* a, const Record* b) {
  if (a->score < b->score) {
    return true;
  } else if (a->score > b->score) {
    return false;
  } else {
    return strcmp(a->name, b->name) < 0;
  }
}

const uint16_t ARRAY_SIZE = 10;
const Record RECORDS[ARRAY_SIZE] = {
  ...
};

const Record* recordPtrs[ARRAY_SIZE];

void doSorting() {
  shellSortKnuth(recordPtrs, ARRAY_SIZE, sortByScoreThenName);
  ...
}
```

<a name="LambdaExpression"></a>
### Lambda Expression

Through the magic of C++ templates, the `lessThan` parameter can also be a
lambda expression. When the comparison operator is simple and short, this
feature can save us the hassle of creating a separate function that is used only
once.

The [examples/HelloSorting](examples/HelloSorting) example shows how to sort an
array of integers in reverse order using an inlined lambda expression that
reverses the comparison operator:

```C++
const uint16_t ARRAY_SIZE = 20;
int array[ARRAY_SIZE];

void doSorting() {
  shellSortKnuth(array, ARRAY_SIZE, [](int a, int b) { return a > b; });
  ...
}
```

<a name="CompilerOptimizations"></a>
### Compiler Optimizations

All 2-argument variants of the sorting functions (except for the Quick Sort
functions `quickSortXxx()`, see below) are implemented by simply calling the
3-argument sorting functions using a default lambda expression using the `<`
operator like this:

```C++
template <typename T>
void shellSortKnuth(T data[], uint16_t n) {
  auto&& lessThan = [](const T& a, const T& b) -> bool { return a < b; };
  shellSortKnuth(data, n, lessThan);
}
```

The benchmarks in [examples/MemoryBenchmark](examples/MemoryBenchmark) show that
the compiler is able to completely optimize away the overhead of the inlined
lambda expression and produce code that is equivalent to inserting the `<`
binary operator directly into the code that implements the 3-argument variant.
No additional flash memory is consumed.

The only exception to this compiler optimization occurs with the Quick Sort
algorithms. The compiler seems unable to optimize away the extra layer of
indirection, probably due to the recursive function calls in the Quick Sort
algorithms. Therefore, the 2-argument variants of `quickSortXxx()` algorithms
are duplicated from the 3-argument variants with the simple `<` operator
hardcoded, so that the simple case of ascending sorting consumes as little flash
memory as possible. (In the source code, the `ACE_SORTING_DIRECT_QUICK_SORT`
macro is set to `1` by default to achieve this, in contrast to all other sorting
functions where the equivalent macro is set to `0`.)

<a name="ResourceConsumption"></a>
## Resource Consumption

<a name="FlashAndStaticMemory"></a>
### Flash And Static Memory

The full details of flash and static memory consumptions are given in
[examples/MemoryBenchmark](examples/MemoryBenchmark). Here are 2 samples.

**SparkFun Pro Micro (ATmega32U4)**

```
+---------------------------------------------------------------------+
| Functionality                          |  flash/  ram |       delta |
|----------------------------------------+--------------+-------------|
| Baseline                               |   4060/  354 |     0/    0 |
|----------------------------------------+--------------+-------------|
| bubbleSort()                           |   4104/  354 |    44/    0 |
| insertionSort()                        |   4120/  354 |    60/    0 |
| selectionSort()                        |   4148/  354 |    88/    0 |
|----------------------------------------+--------------+-------------|
| shellSortClassic()                     |   4156/  354 |    96/    0 |
| shellSortKnuth()                       |   4202/  354 |   142/    0 |
| shellSortTokuda()                      |   4242/  380 |   182/   26 |
|----------------------------------------+--------------+-------------|
| combSort13()                           |   4214/  354 |   154/    0 |
| combSort13m()                          |   4232/  354 |   172/    0 |
| combSort133()                          |   4166/  354 |   106/    0 |
| combSort133m()                         |   4188/  354 |   128/    0 |
|----------------------------------------+--------------+-------------|
| quickSortMiddle()                      |   4238/  354 |   178/    0 |
| quickSortMedian()                      |   4290/  354 |   230/    0 |
| quickSortMedianSwapped()               |   4336/  354 |   276/    0 |
|----------------------------------------+--------------+-------------|
| qsort()                                |   5144/  354 |  1084/    0 |
+---------------------------------------------------------------------+
```

**ESP8266**

```
+---------------------------------------------------------------------+
| Functionality                          |  flash/  ram |       delta |
|----------------------------------------+--------------+-------------|
| Baseline                               | 260497/28108 |     0/    0 |
|----------------------------------------+--------------+-------------|
| bubbleSort()                           | 260545/28108 |    48/    0 |
| insertionSort()                        | 260545/28108 |    48/    0 |
| selectionSort()                        | 260561/28108 |    64/    0 |
|----------------------------------------+--------------+-------------|
| shellSortClassic()                     | 260577/28108 |    80/    0 |
| shellSortKnuth()                       | 260577/28108 |    80/    0 |
| shellSortTokuda()                      | 260637/28128 |   140/   20 |
|----------------------------------------+--------------+-------------|
| combSort13()                           | 260609/28108 |   112/    0 |
| combSort13m()                          | 260625/28108 |   128/    0 |
| combSort133()                          | 260593/28108 |    96/    0 |
| combSort133m()                         | 260609/28108 |   112/    0 |
|----------------------------------------+--------------+-------------|
| quickSortMiddle()                      | 260641/28108 |   144/    0 |
| quickSortMedian()                      | 260673/28108 |   176/    0 |
| quickSortMedianSwapped()               | 260689/28108 |   192/    0 |
|----------------------------------------+--------------+-------------|
| qsort()                                | 261617/28108 |  1120/    0 |
+---------------------------------------------------------------------+
```

<a name="CpuCycles"></a>
### CPU Cycles

The CPU benchmark numbers can be seen in
[examples/AutoBenchmark](examples/AutoBenchmark). All times in milliseconds.
Here are 2 samples.

**SparkFun Pro Micro (ATmega32U4)**

```
+---------------------+------------------------+---------+---------+---------+
|            \      N |    10 |    30 |    100 |     300 |    1000 |    3000 |
| Function    \       |       |       |        |         |         |         |
|---------------------+-------+-------+--------+---------+---------+---------|
| bubbleSort()        | 0.083 | 1.211 | 13.093 | 118.403 |         |         |
| insertionSort()     | 0.044 | 0.259 |  2.515 |  21.941 | 240.911 |         |
| selectionSort()     | 0.084 | 0.555 |  5.388 |  46.517 | 509.037 |         |
|---------------------+-------+-------+--------+---------+---------+---------|
| shellSortClassic()  | 0.076 | 0.311 |  1.738 |   6.895 |  28.869 |         |
| shellSortKnuth()    | 0.100 | 0.336 |  1.450 |   5.681 |  25.273 |         |
| shellSortTokuda()   | 0.076 | 0.339 |  1.636 |   6.543 |  28.090 |         |
|---------------------+-------+-------+--------+---------+---------+---------|
| combSort13()        | 0.163 | 0.532 |  2.235 |   8.240 |  36.409 |         |
| combSort13m()       | 0.166 | 0.559 |  2.225 |   8.279 |  34.916 |         |
| combSort133()       | 0.085 | 0.385 |  2.030 |   7.787 |  34.229 |         |
| combSort133m()      | 0.088 | 0.422 |  1.991 |   7.713 |  34.179 |         |
|---------------------+-------+-------+--------+---------+---------+---------|
| quickSortMiddle()   | 0.098 | 0.367 |  1.601 |   5.659 |  22.104 |         |
| quickSortMedian()   | 0.118 | 0.432 |  1.701 |   5.984 |  22.732 |         |
| quickSortMdnSwppd() | 0.087 | 0.335 |  1.385 |   4.871 |  18.914 |         |
|---------------------+-------+-------+--------+---------+---------+---------|
| qsort()             | 0.202 | 0.876 |  3.685 |  13.098 |         |         |
+---------------------+-------+-------+--------+---------+---------+---------+
```

**ESP8266**

```
+---------------------+------------------------+---------+---------+---------+
|            \      N |    10 |    30 |    100 |     300 |    1000 |    3000 |
| Function    \       |       |       |        |         |         |         |
|---------------------+-------+-------+--------+---------+---------+---------|
| bubbleSort()        | 0.017 | 0.145 |  1.604 |  14.477 | 169.490 |         |
| insertionSort()     | 0.008 | 0.036 |  0.338 |   2.895 |  31.947 |         |
| selectionSort()     | 0.013 | 0.071 |  0.715 |   6.270 |  69.023 |         |
|---------------------+-------+-------+--------+---------+---------+---------|
| shellSortClassic()  | 0.008 | 0.032 |  0.180 |   0.719 |   3.030 |  11.560 |
| shellSortKnuth()    | 0.009 | 0.031 |  0.149 |   0.588 |   2.608 |  10.006 |
| shellSortTokuda()   | 0.007 | 0.029 |  0.137 |   0.552 |   2.358 |   8.532 |
|---------------------+-------+-------+--------+---------+---------+---------|
| combSort13()        | 0.014 | 0.052 |  0.238 |   0.899 |   4.001 |  14.567 |
| combSort13m()       | 0.015 | 0.056 |  0.240 |   0.903 |   3.903 |  14.197 |
| combSort133()       | 0.010 | 0.043 |  0.209 |   0.852 |   3.840 |  13.288 |
| combSort133m()      | 0.010 | 0.047 |  0.222 |   0.850 |   3.733 |  13.341 |
|---------------------+-------+-------+--------+---------+---------+---------|
| quickSortMiddle()   | 0.013 | 0.044 |  0.175 |   0.616 |   2.353 |   8.087 |
| quickSortMedian()   | 0.015 | 0.049 |  0.189 |   0.634 |   2.370 |   7.764 |
| quickSortMdnSwppd() | 0.012 | 0.037 |  0.149 |   0.513 |   1.951 |   6.597 |
|---------------------+-------+-------+--------+---------+---------+---------|
| qsort()             | 0.028 | 0.094 |  0.405 |   1.472 |   5.826 |  19.875 |
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

* [Arduino IDE 1.8.16](https://www.arduino.cc/en/Main/Software)
* [Arduino CLI 0.19.2](https://arduino.github.io/arduino-cli)
* [SpenceKonde ATTinyCore 1.5.2](https://github.com/SpenceKonde/ATTinyCore)
* [Arduino AVR Boards 1.8.3](https://github.com/arduino/ArduinoCore-avr)
* [Arduino SAMD Boards 1.8.9](https://github.com/arduino/ArduinoCore-samd)
* [SparkFun AVR Boards 1.1.13](https://github.com/sparkfun/Arduino_Boards)
* [SparkFun SAMD Boards 1.8.4](https://github.com/sparkfun/Arduino_Boards)
* [STM32duino 2.0.0](https://github.com/stm32duino/Arduino_Core_STM32)
* [ESP8266 Arduino 3.0.2](https://github.com/esp8266/Arduino)
* [ESP32 Arduino 1.0.6](https://github.com/espressif/arduino-esp32)
* [Teensyduino 1.55](https://www.pjrc.com/teensy/td_download.html)

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
      algorithms are consistent across all platforms.
    * Certain implementation choices and optimizations can be made if we know
      that `n` cannot exceed a bounded value.
        * For example, the `shellSortTokuda()` function can use a pre-generated
          sequence of gaps which is a reasonable size because it only needs to
          go up to 65535.
    * The alternative was to use the `size_t` type whose size is different on
      different platforms: 2 bytes on 8-bit processors, 4 bytes on 32-bit
      processors, and 8 bytes on 64-bit processors.
        * However, I did not want to worry about edge case behavior of some of
          these algorithms for extremely large values of `n`.
* The behavior of the sorting algorithms with a `data` size of exactly `n =
  65535` has not been validated.
    * Some algorithms may be buggy because this edge case may trigger
      an integer overflow.
    * The actual maximum value of `n` may actually be `65534` for
      some algorithms.
* Some of the Comb Sort algorithms have even lower limits of `n` due to integer
  overflows.
    * See remarks above and in the source code.
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
    * Provides a template `sort()` function, which delegates to `stable_sort()`.
    * But this implementation is a bubble sort which is `O(N^2)` and in practice
      much slower than `insertionSort()`.
        * In fairness, there is a "FIXME" note in the code which
          implies that a better algorithm ought to be provided.
    * The library is configured to target only the `avr` and `megaavr`
      platforms.
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
  too painful in small embedded programming projects.
* Lastly, I wanted to implement my own sorting routines to make sure that I had
  a complete understanding of each algorithm. I had forgotten so much since
  learning many of these in my undergraduate years.

<a name="License"></a>
## License

[MIT License](https://opensource.org/licenses/MIT)

<a name="FeedbackAndSupport"></a>
## Feedback and Support

If you have any questions, comments, or feature requests for this library,
please use the [GitHub
Discussions](https://github.com/bxparks/AceSorting/discussions) for this
project. If you have bug reports, please file a ticket in [GitHub
Issues](https://github.com/bxparks/AceSorting/issues). Feature requests should
go into Discussions first because they often have alternative solutions which
are useful to remain visible, instead of disappearing from the default view of
the Issue tracker after the ticket is closed.

Please refrain from emailing me directly unless the content is sensitive. The
problem with email is that I cannot reference the email conversation when other
people ask similar questions later.

<a name="Authors"></a>
## Authors

Created by Brian T. Park (brian@xparks.net).
