/*
 * Determine the size of various sorting algorithms in AceSorting library.
 */

#include <stdint.h> // uint8_t, uint16_t
#include <stdlib.h> // qsort()
#include <Arduino.h>
#include <AceSorting.h>

using ace_sorting::bubbleSort;
using ace_sorting::insertionSort;
using ace_sorting::shellSortClassic;
using ace_sorting::shellSortKnuth;
using ace_sorting::shellSortTokuda;
using ace_sorting::combSort13;
using ace_sorting::combSort125;
using ace_sorting::quickSortMiddle;
using ace_sorting::quickSortMedian;
using ace_sorting::quickSortMedianSwapped;

// List of features of the AceSorting library that we want to examine.
#define FEATURE_BASELINE 0
#define FEATURE_QSORT 1
#define FEATURE_BUBBLE_SORT 2
#define FEATURE_INSERTION_SORT 3
#define FEATURE_SHELL_SORT_CLASSIC 4
#define FEATURE_SHELL_SORT_KNUTH 5
#define FEATURE_SHELL_SORT_TOKUDA 6
#define FEATURE_COMB_SORT_13 7
#define FEATURE_COMB_SORT_125 8
#define FEATURE_QUICK_SORT_MIDDLE 9
#define FEATURE_QUICK_SORT_MEDIAN 10
#define FEATURE_QUICK_SORT_MEDIAN_SWAPPED 11

// Select one of the FEATURE_* parameter and compile. Then look at the flash
// and RAM usage, compared to FEATURE_BASELINE usage to determine how much
// flash and RAM is consumed by the selected feature.
// NOTE: This line is modified by a 'sed' script in collect.sh. Be careful
// when modifying its format.
#define FEATURE 0

// Set this variable to prevent the compiler optimizer from removing the code
// being tested when it determines that it does nothing.
volatile uint8_t disableComilerOptimization;

uint16_t data[] = {1, 0, 3, 32, 3, 43, 20, 39, 88, 18};
const uint16_t DATA_SIZE = sizeof(data) / sizeof(data[0]);

#if FEATURE == FEATURE_QSORT
int compare(const void* a, const void* b) {
  uint16_t va = *((uint16_t*) a);
  uint16_t vb = *((uint16_t*) b);
  return (va < vb) ? -1 : ((va == vb) ? 0 : 1);
}

void doQsort(uint16_t data[], uint16_t n) {
  qsort(data, n, sizeof(uint16_t), compare);
}
#endif

void setup() {
#if FEATURE == FEATURE_BASELINE
  // nothing
#elif FEATURE == FEATURE_QSORT
  runQsort(data, DATA_SIZE);
#elif FEATURE == FEATURE_BUBBLE_SORT
  bubbleSort(data, DATA_SIZE);
#elif FEATURE == FEATURE_INSERTION_SORT
  insertionSort(data, DATA_SIZE);
#elif FEATURE == FEATURE_SHELL_SORT_CLASSIC
  shellSortClassic(data, DATA_SIZE);
#elif FEATURE == FEATURE_SHELL_SORT_KNUTH
  shellSortKnuth(data, DATA_SIZE);
#elif FEATURE == FEATURE_SHELL_SORT_TOKUDA
  shellSortTokuda(data, DATA_SIZE);
#elif FEATURE == FEATURE_COMB_SORT_13
  combSort13(data, DATA_SIZE);
#elif FEATURE == FEATURE_COMB_SORT_125
  combSort125(data, DATA_SIZE);
#elif FEATURE == FEATURE_QUICK_SORT_MIDDLE
  quickSortMiddle(data, DATA_SIZE);
#elif FEATURE == FEATURE_QUICK_SORT_MEDIAN
  quickSortMedian(data, DATA_SIZE);
#elif FEATURE == FEATURE_QUICK_SORT_MEDIAN_SWAPPED
  quickSortMedianSwapped(data, DATA_SIZE);
#else
  #error Unknown FEATURE
#endif

  // We pick a random index into data[] to prevent the compiler from optimizing
  // away the data[] array. I tried `disableComilerOptimization =
  // data[disableComilerOptimization]` but the SparkFun SAMD Core compiler
  // optimized that away (maybe it figured out that `volatile
  // disableComilerOptimization` parameter was never used in the program).
  disableComilerOptimization = data[random(DATA_SIZE)];
}

void loop() {
}
