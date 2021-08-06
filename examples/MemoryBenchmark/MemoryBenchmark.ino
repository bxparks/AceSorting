/*
 * Determine the size of various sorting algorithms in AceSorting library.
 */

#include <stdint.h> // uint8_t, uint16_t
#include <stdlib.h> // qsort()
#include <Arduino.h>
#include <AceSorting.h>

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

// List of features of the AceSorting library that we want to examine.
#define FEATURE_BASELINE 0
#define FEATURE_BUBBLE_SORT 1
#define FEATURE_INSERTION_SORT 2
#define FEATURE_SELECTION_SORT 3
#define FEATURE_SHELL_SORT_CLASSIC 4
#define FEATURE_SHELL_SORT_KNUTH 5
#define FEATURE_SHELL_SORT_TOKUDA 6
#define FEATURE_COMB_SORT_13 7
#define FEATURE_COMB_SORT_13M 8
#define FEATURE_COMB_SORT_133 9
#define FEATURE_COMB_SORT_133M 10
#define FEATURE_QUICK_SORT_MIDDLE 11
#define FEATURE_QUICK_SORT_MEDIAN 12
#define FEATURE_QUICK_SORT_MEDIAN_SWAPPED 13
#define FEATURE_QSORT 14

// Select one of the FEATURE_* parameter and compile. Then look at the flash
// and RAM usage, compared to FEATURE_BASELINE usage to determine how much
// flash and RAM is consumed by the selected feature.
// NOTE: This line is modified by a 'sed' script in collect.sh. Be careful
// when modifying its format.
#define FEATURE 0

// Set this variable to prevent the compiler optimizer from removing the code
// being tested when it determines that it does nothing.
volatile uint8_t disableComilerOptimization;

const uint16_t DATA_SIZE = 100;
uint16_t data[DATA_SIZE];
void setupData() {
  for (uint16_t i = 0; i < DATA_SIZE; i++) {
    data[i] = random(65536);
  }
}

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
  setupData();

#if FEATURE == FEATURE_BASELINE
  // nothing
#elif FEATURE == FEATURE_QSORT
  doQsort(data, DATA_SIZE);
#elif FEATURE == FEATURE_BUBBLE_SORT
  bubbleSort(data, DATA_SIZE);
#elif FEATURE == FEATURE_INSERTION_SORT
  insertionSort(data, DATA_SIZE);
#elif FEATURE == FEATURE_SELECTION_SORT
  selectionSort(data, DATA_SIZE);
#elif FEATURE == FEATURE_SHELL_SORT_CLASSIC
  shellSortClassic(data, DATA_SIZE);
#elif FEATURE == FEATURE_SHELL_SORT_KNUTH
  shellSortKnuth(data, DATA_SIZE);
#elif FEATURE == FEATURE_SHELL_SORT_TOKUDA
  shellSortTokuda(data, DATA_SIZE);
#elif FEATURE == FEATURE_COMB_SORT_13
  combSort13(data, DATA_SIZE);
#elif FEATURE == FEATURE_COMB_SORT_13M
  combSort13m(data, DATA_SIZE);
#elif FEATURE == FEATURE_COMB_SORT_133
  combSort133(data, DATA_SIZE);
#elif FEATURE == FEATURE_COMB_SORT_133M
  combSort133m(data, DATA_SIZE);
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
