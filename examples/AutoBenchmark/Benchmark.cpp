/*
 * MIT License
 * Copyright (c) 2021 Brian T. Park
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
const uint16_t DATA_SIZES[] = {10, 30, 100, 300, 1000, 3000, 10000, 30000};
//const uint16_t DATA_SIZES[] = {65000};
const uint16_t SLOW_SAMPLE_SIZE = 3;
const uint16_t FAST_SAMPLE_SIZE = 25;
#elif defined(ARDUINO_AVR_PROMICRO)
// ATmega32U4 has 2.5kB of ram, so it can handle N=1000... except qsort()
// which seems to run out of stack space.
const uint16_t DATA_SIZES[] = {10, 30, 100, 300, 1000};
const uint16_t SLOW_SAMPLE_SIZE = 3;
const uint16_t FAST_SAMPLE_SIZE = 25;
#elif defined(ARDUINO_ARCH_AVR)
const uint16_t DATA_SIZES[] = {10, 30, 100, 300};
const uint16_t SLOW_SAMPLE_SIZE = 3;
const uint16_t FAST_SAMPLE_SIZE = 25;
#else
// All 32-bit boards that I own can handle at least N=3000.
const uint16_t DATA_SIZES[] = {10, 30, 100, 300, 1000, 3000};
const uint16_t SLOW_SAMPLE_SIZE = 3;
const uint16_t FAST_SAMPLE_SIZE = 20;
#endif
const uint16_t NUM_DATA_SIZES = sizeof(DATA_SIZES) / sizeof(DATA_SIZES[0]);

//-----------------------------------------------------------------------------
// Stats helpers
//-----------------------------------------------------------------------------

/**
 * Print the result in micros for the given 'name' function or algorithm. The
 * format is:
 *
 * @verbatim
 * name min avg max sampleSize
 * @endverbatim
 *
 * @param name name of the benchmark
 * @param instance of GenericStats
 * @param samplesize number of independent timingStats samples used, to get
 *        the min(), avg() and max()
 */
static void printStats(
    const __FlashStringHelper* name,
    const GenericStats<float>& stats,
    uint16_t sampleSize,
    uint16_t dataSize) {
  SERIAL_PORT_MONITOR.print(name);
  SERIAL_PORT_MONITOR.print(' ');
  SERIAL_PORT_MONITOR.print(dataSize);
  SERIAL_PORT_MONITOR.print(' ');
  SERIAL_PORT_MONITOR.print(stats.getMin(), 3);
  SERIAL_PORT_MONITOR.print(' ');
  SERIAL_PORT_MONITOR.print(stats.getAvg(), 3);
  SERIAL_PORT_MONITOR.print(' ');
  SERIAL_PORT_MONITOR.print(stats.getMax(), 3);
  SERIAL_PORT_MONITOR.print(' ');
  SERIAL_PORT_MONITOR.println(sampleSize);
}

static GenericStats<float> timingStats;

//-----------------------------------------------------------------------------
// Benchmark helpers
//-----------------------------------------------------------------------------

// Typedef of the lambda expression that can be converted into a simple function
// pointer.
typedef void (*SortFunction)(uint16_t data[], uint16_t n);

// Volatile to prevent the compiler from deciding that the entire program does
// nothing, causing it to opimize the whole program to nothing.
volatile uint32_t disableCompilerOptimization;

// Pointer to the data array created by malloc() and free(). This is a global
// variable to avoid using capture in the lambda expression, so that it can
// degenerate into a function pointer.
uint16_t* array;

static void fillArray(uint16_t data[], uint16_t n) {
  for (uint16_t i = 0; i < n; ++i) {
    data[i] = random(65536);
  }
}

static int compare(const void* a, const void* b) {
  uint16_t va = *((uint16_t*) a);
  uint16_t vb = *((uint16_t*) b);
  return (va < vb) ? -1 : ((va == vb) ? 0 : 1);
}

static void doQsort(uint16_t data[], uint16_t n) {
  qsort(data, n, sizeof(uint16_t), compare);
}

static void runSort(
    const __FlashStringHelper* name,
    uint16_t dataSize,
    uint16_t sampleSize,
    SortFunction sortFunction) {

  timingStats.reset();
  array = new uint16_t[dataSize];

  for (uint8_t k = 0; k < sampleSize; k++) {
    fillArray(array, dataSize);
    bool issorted = isSorted(array, dataSize);
    if (issorted) {
      SERIAL_PORT_MONITOR.println(F("Original array is unexpectedly sorted"));
    }

    yield();
    uint32_t startMicros = micros();
    sortFunction(array, dataSize);
    uint32_t elapsedMicros = micros() - startMicros;
    yield();
    disableCompilerOptimization = array[0];

    issorted = isSorted(array, dataSize);
    if (! issorted) {
      SERIAL_PORT_MONITOR.println(F("Sorted array is NOT sorted!"));
    }
    timingStats.update((float) elapsedMicros / 1000.0);
  }

  delete[] array;
  printStats(name, timingStats, sampleSize, dataSize);
}

static void runSortForSizes(
    const __FlashStringHelper* name,
    uint16_t sampleSize,
    SortFunction sortFunction) {
  for (uint16_t i = 0; i < NUM_DATA_SIZES; i++) {
    uint16_t dataSize = DATA_SIZES[i];

    // Don't run O(N^2) sorting algorithms on large arrays because they take too
    // long to finish.
    if (sortFunction == &bubbleSort<uint16_t>
        || sortFunction == &insertionSort<uint16_t>
        || sortFunction == &selectionSort<uint16_t>) {
      if (dataSize > 1000) break;
    }
    // Don't run qsort for N>=1000 on Pro Micro because it runs out of stack
    // space.
    #if defined(ARDUINO_AVR_PROMICRO)
      if (sortFunction == doQsort && dataSize >= 1000) break;
    #endif

    // Don't run bubbleSort() with N>=1000 any AVR because it takes too long.
    #if defined(ARDUINO_ARCH_AVR)
      if (sortFunction == &bubbleSort<uint16_t> && dataSize >= 1000) break;
    #endif

    runSort(name, dataSize, sampleSize, sortFunction);
  }
}

//-----------------------------------------------------------------------------
// Benchmarks
//-----------------------------------------------------------------------------

void runBenchmarks() {
#if ! defined(EPOXY_DUINO)
  runSortForSizes(
      F("bubbleSort()"), SLOW_SAMPLE_SIZE, bubbleSort<uint16_t>);
#endif
  runSortForSizes(
      F("insertionSort()"), SLOW_SAMPLE_SIZE, insertionSort<uint16_t>);
  runSortForSizes(
      F("selectionSort()"), SLOW_SAMPLE_SIZE, selectionSort<uint16_t>);

  runSortForSizes(
      F("shellSortClassic()"), FAST_SAMPLE_SIZE, shellSortClassic<uint16_t>);
  runSortForSizes(
      F("shellSortKnuth()"), FAST_SAMPLE_SIZE, shellSortKnuth<uint16_t>);
  runSortForSizes(
      F("shellSortTokuda()"), FAST_SAMPLE_SIZE, shellSortTokuda<uint16_t>);

  runSortForSizes(
      F("combSort13()"), FAST_SAMPLE_SIZE, combSort13<uint16_t>);
  runSortForSizes(
      F("combSort13m()"), FAST_SAMPLE_SIZE, combSort13m<uint16_t>);
  runSortForSizes(
      F("combSort133()"), FAST_SAMPLE_SIZE, combSort133<uint16_t>);
  runSortForSizes(
      F("combSort133m()"), FAST_SAMPLE_SIZE, combSort133m<uint16_t>);

  runSortForSizes(
      F("quickSortMiddle()"), FAST_SAMPLE_SIZE, quickSortMiddle<uint16_t>);
  runSortForSizes(
      F("quickSortMedian()"), FAST_SAMPLE_SIZE, quickSortMedian<uint16_t>);
  runSortForSizes(
      F("quickSortMedianSwapped()"),
      FAST_SAMPLE_SIZE,
      quickSortMedianSwapped<uint16_t>);
  runSortForSizes(
      F("qsort()"), FAST_SAMPLE_SIZE, doQsort);
}
