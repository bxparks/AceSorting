/*
 * MIT License
 * Copyright (c) 2021 Brian T. Park
 */

/*
 * Determine runtime of potential worst case arrays:
 *  * random
 *  * already sorted
 *  * reverse sorted.
 */

#include <stdint.h> // uint8_t, uint16_t
#include <stdlib.h> // qsort()
#include <Arduino.h> // F(), __FlashStringHelper
#include <AceCommon.h>
#include <AceSorting.h>
#include "Benchmark.h"

#ifndef SERIAL_PORT_MONITOR
  #define SERIAL_PORT_MONITOR Serial
#endif

using ace_common::GenericStats;
using ace_common::isSorted;
using ace_common::reverse;
using ace_sorting::bubbleSort;
using ace_sorting::insertionSort;
using ace_sorting::selectionSort;
using ace_sorting::shellSortClassic;
using ace_sorting::shellSortKnuth;
using ace_sorting::shellSortTokuda;
using ace_sorting::combSort13;
using ace_sorting::combSort13m;
using ace_sorting::combSort133;
using ace_sorting::combSort133m;
using ace_sorting::quickSortMiddle;
using ace_sorting::quickSortMedian;
using ace_sorting::quickSortMedianSwapped;

//-----------------------------------------------------------------------------
// Benchmark parameters.
//-----------------------------------------------------------------------------

#if defined(EPOXY_DUINO)
const uint16_t ARRAY_SIZE = 30000;
const uint16_t SLOW_SAMPLE_SIZE = 3;
const uint16_t FAST_SAMPLE_SIZE = 50;
#elif defined(ARDUINO_ARCH_AVR)
const uint16_t ARRAY_SIZE = 300;
const uint16_t SLOW_SAMPLE_SIZE = 3;
const uint16_t FAST_SAMPLE_SIZE = 10;
#else
const uint16_t ARRAY_SIZE = 1000;
const uint16_t SLOW_SAMPLE_SIZE = 3;
const uint16_t FAST_SAMPLE_SIZE = 20;
#endif

//-----------------------------------------------------------------------------
// Stats helpers
//-----------------------------------------------------------------------------

/**
 * Print the result in micros for the given 'name' function or algorithm. The
 * format is:
 *
 * @verbatim
 * name arraySize randomDuration alreadySortedDuration reverseSortedDuration
 * @endverbatim
 */
static void printStats(
    const __FlashStringHelper* name,
    uint16_t arraySize,
    float randomDuration,
    float alreadySortedDuration,
    float reverseSortedDuration,
    uint16_t sampleSize) {
  SERIAL_PORT_MONITOR.print(name);
  SERIAL_PORT_MONITOR.print(' ');
  SERIAL_PORT_MONITOR.print(arraySize);
  SERIAL_PORT_MONITOR.print(' ');
  SERIAL_PORT_MONITOR.print(randomDuration, 3);
  SERIAL_PORT_MONITOR.print(' ');
  SERIAL_PORT_MONITOR.print(alreadySortedDuration, 3);
  SERIAL_PORT_MONITOR.print(' ');
  SERIAL_PORT_MONITOR.print(reverseSortedDuration, 3);
  SERIAL_PORT_MONITOR.print(' ');
  SERIAL_PORT_MONITOR.println(sampleSize);
}

static GenericStats<float> timingStats;

//-----------------------------------------------------------------------------
// Benchmark helpers
//-----------------------------------------------------------------------------

// Typedef of the lambda expression that can be converted into a simple function
// pointer.
typedef void (*SortFunction)(uint16_t array[], uint16_t n);

// Volatile to prevent the compiler from deciding that the entire program does
// nothing, causing it to opimize the whole program to nothing.
volatile uint32_t disableCompilerOptimization;

static void fillArray(uint16_t array[], uint16_t n) {
  for (uint16_t i = 0; i < n; ++i) {
    array[i] = random(65536);
  }
}

enum class InputType {
  kRandom, kSorted, kReversed
};

static float measureSort(
    uint16_t array[],
    uint16_t arraySize,
    uint16_t sampleSize,
    SortFunction sortFunction,
    InputType inputType) {

  timingStats.reset();
  for (uint8_t k = 0; k < sampleSize; k++) {
    if (inputType == InputType::kRandom) {
      fillArray(array, ARRAY_SIZE);
    } else if (inputType == InputType::kSorted) {
      fillArray(array, ARRAY_SIZE);
      shellSortKnuth(array, ARRAY_SIZE);
    } else if (inputType == InputType::kReversed) {
      fillArray(array, ARRAY_SIZE);
      shellSortKnuth(array, ARRAY_SIZE);
      reverse(array, ARRAY_SIZE);
    }

    yield();
    uint32_t startMicros = micros();
    sortFunction(array, arraySize);
    uint32_t elapsedMicros = micros() - startMicros;
    yield();

    disableCompilerOptimization = array[0];
    bool issorted = isSorted(array, arraySize);
    if (! issorted) {
      SERIAL_PORT_MONITOR.println(F("Error: Sorted array is NOT sorted!"));
    }
    timingStats.update((float) elapsedMicros / 1000.0);
  }
  return timingStats.getAvg();
}

static void runSort(
    const __FlashStringHelper* name,
    uint16_t sampleSize,
    SortFunction sortFunction) {

  uint16_t* array = new uint16_t[ARRAY_SIZE];

  // random arrays
  float randomDuration = measureSort(
      array, ARRAY_SIZE, sampleSize, sortFunction, InputType::kRandom);

  // already sorted array
  float alreadySortedDuration = measureSort(
      array, ARRAY_SIZE, sampleSize, sortFunction, InputType::kSorted);

  // reverse sorted
  reverse(array, ARRAY_SIZE);
  float reverseSortedDuration = measureSort(
      array, ARRAY_SIZE, sampleSize, sortFunction, InputType::kReversed);

  delete[] array;
  printStats(name, ARRAY_SIZE, randomDuration, alreadySortedDuration,
      reverseSortedDuration, sampleSize);
}

int compare(const void* a, const void* b) {
  uint16_t va = *((uint16_t*) a);
  uint16_t vb = *((uint16_t*) b);
  return (va < vb) ? -1 : ((va == vb) ? 0 : 1);
}

void doQsort(uint16_t array[], uint16_t n) {
  qsort(array, n, sizeof(uint16_t), compare);
}

//-----------------------------------------------------------------------------
// Benchmarks
//-----------------------------------------------------------------------------

void runBenchmarks() {
#if ! defined(EPOXY_DUINO)
  runSort(F("bubbleSort()"), SLOW_SAMPLE_SIZE, bubbleSort<uint16_t>);
#endif
  runSort(F("insertionSort()"), SLOW_SAMPLE_SIZE, insertionSort<uint16_t>);
  runSort(F("selectionSort()"), SLOW_SAMPLE_SIZE, selectionSort<uint16_t>);

  runSort(
      F("shellSortClassic()"), FAST_SAMPLE_SIZE, shellSortClassic<uint16_t>);
  runSort(F("shellSortKnuth()"), FAST_SAMPLE_SIZE, shellSortKnuth<uint16_t>);
  runSort(F("shellSortTokuda()"), FAST_SAMPLE_SIZE, shellSortTokuda<uint16_t>);

  runSort(F("combSort13()"), FAST_SAMPLE_SIZE, combSort13<uint16_t>);
  runSort(F("combSort13m()"), FAST_SAMPLE_SIZE, combSort13m<uint16_t>);
  runSort(F("combSort133()"), FAST_SAMPLE_SIZE, combSort133<uint16_t>);
  runSort(F("combSort133m()"), FAST_SAMPLE_SIZE, combSort133m<uint16_t>);

  runSort(F("quickSortMiddle()"), FAST_SAMPLE_SIZE, quickSortMiddle<uint16_t>);
  runSort(F("quickSortMedian()"), FAST_SAMPLE_SIZE, quickSortMedian<uint16_t>);
  runSort(
      F("quickSortMedianSwapped()"),
      FAST_SAMPLE_SIZE,
      quickSortMedianSwapped<uint16_t>);
  runSort(F("qsort()"), FAST_SAMPLE_SIZE, doQsort);
}
