/*
MIT License

Copyright (c) 2021 Brian T. Park

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/**
 * @file bubbleSort.h
 *
 * Bubble sort.
 */

#ifndef ACE_SORTING_BUBBLE_SORT_H
#define ACE_SORTING_BUBBLE_SORT_H

#include "swap.h"

#if ! defined(ACE_SORTING_DIRECT_BUBBLE_SORT)
  /**
   * If set to 1, use the direct inlined implementation of the 2-argument
   * bubbleSort(). Otherwise, use the 3-argument bubbleSort() to implement
   * 2-argument bubbleSort(). For bubbleSort, the compiler will optimize both
   * versions to be identical.
   */
  #define ACE_SORTING_DIRECT_BUBBLE_SORT 0
#endif

namespace ace_sorting {

/**
 * Bubble sort.
 * Average complexity: O(n^2)
 *
 * @tparam T type of data to sort
 */
#if ACE_SORTING_DIRECT_BUBBLE_SORT
template <typename T>
void bubbleSort(T data[], uint16_t n) {
  bool swapped;
  do {
    swapped = false;
    for (uint16_t i = 1; i < n; i++) {
      if (data[i] < data[i - 1]) {
        swap(data[i - 1], data[i]);
        swapped = true;
      }
    }
  } while (swapped);
}
#else
template <typename T>
void bubbleSort(T data[], uint16_t n) {
  auto&& lessThan = [](const T& a, const T& b) -> bool { return a < b; };
  bubbleSort(data, n, lessThan);
}
#endif

/**
 * Same as the 2-argument bubbleSort() with the addition of a `lessThan`
 * lambda expression or function.
 *
 * @tparam T type of data to sort
 * @tparam F type of lambda expression or function that returns true if a < b
 */
template <typename T, typename F>
void bubbleSort(T data[], uint16_t n, F&& lessThan) {
  bool swapped;
  do {
    swapped = false;
    for (uint16_t i = 1; i < n; i++) {
      if (lessThan(data[i], data[i - 1])) {
        swap(data[i - 1], data[i]);
        swapped = true;
      }
    }
  } while (swapped);
}

}

#endif
