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
 * @file selectionSort.h
 *
 * Selection sort.
 */

#ifndef ACE_SORTING_SELECTION_SORT_H
#define ACE_SORTING_SELECTION_SORT_H

#include "swap.h"

namespace ace_sorting {

/**
 * Selection sort.
 * Average complexity: O(n^2)
 *
 * @tparam T type of data to sort
 */
template <typename T>
void selectionSort(T data[], uint16_t n) {
  for (uint16_t i = 0; i < n; i++) {

    // Loop to find the smallest element.
    uint16_t iSmallest = i;
    T smallest = data[i];

    // Starting the loop with 'j = i + 1' increases flash usage on AVR by 12
    // bytes. But it does not reduce the execution time signficantly, because
    // the (i + 1) will be done anyway by the j++ in the loop. So the only thing
    // we save is a single redundant 'smallest < smallest' comparison.
    for (uint16_t j = i; j < n; j++) {
      if (data[j] < smallest) {
        iSmallest = j;
        smallest = data[j];
      }
    }

    // This extra check (i != iSmallest) is not really necessary, because if the
    // first element was already the smallest, it would swap the value back into
    // itself. However, the one situation where Selection Sort *might* be used
    // over Insertion Sort is when the write operation is far more expensive
    // than a read operation. So this test preserves that advantage of the
    // Selection Sort, by avoiding doing an unnecessary swap.
    if (i != iSmallest) {
      swap(data[i], data[iSmallest]);
    }
  }
}

}

#endif
