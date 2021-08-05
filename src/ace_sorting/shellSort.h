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
 * @file shellSort.h
 *
 * Shell sort with different gap algorithms.
 */

#ifndef ACE_SORTING_SHELL_SORT_H
#define ACE_SORTING_SHELL_SORT_H

#include "swap.h"

namespace ace_sorting {

/**
 * Shell sort with gap size reduced by factor of 2 each iteration.
 * Average complexity: Between O(n^1.3) to O(n^1.5)
 * See https://en.wikipedia.org/wiki/Shellsort
 *
 * @tparam T type of data to sort
 */
template <typename T>
void shellSortClassic(T data[], uint16_t n) {
	uint16_t gap = n;
	while (gap > 1) {
		gap /= 2;

    // Do insertion sort of each sub-array separated by gap.
		for (uint16_t i = gap; i < n; i++) {
      T temp = data[i];

      // Shift one slot to the right.
      uint16_t j;
      for (j = i; j >= gap; j -= gap) {
        if (data[j - gap] <= temp) break;
        data[j] = data[j - gap];
      }

      // Just like insertionSort(), this can assign 'temp' back into the
      // original slot if no shifting was done. That's ok because T is assumed
      // to be relatively cheap to copy, and checking for (i != j) is more
      // expensive than just doing the extra assignment.
      data[j] = temp;
		}
	}
}

/**
 * Shell sort using gap size from Knuth.
 * Average complexity: Between O(n^1.3) to O(n^1.5)
 *
 * @tparam T type of data to sort
 */
template <typename T>
void shellSortKnuth(T data[], uint16_t n) {
  // Calculate the largest gap using Knuth's formula. If n is a compile-time
  // constant and relatively "small" (observed to be true at least up to 100),
  // the compiler will precalculate the loop below and replace it with a
  // compile-time constant.
	uint16_t gap = 1;
  while (gap < n / 3) {
    gap = gap * 3 + 1;
  }

	while (gap > 0) {
    // Do insertion sort of each sub-array separated by gap.
		for (uint16_t i = gap; i < n; i++) {
      T temp = data[i];

      // Shift one slot to the right.
      uint16_t j;
      for (j = i; j >= gap; j -= gap) {
        if (data[j - gap] <= temp) break;
        data[j] = data[j - gap];
      }

      // Just like insertionSort(), this can assign 'temp' back into the
      // original slot if no shifting was done. That's ok because T is assumed
      // to be relatively cheap to copy, and checking for (i != j) is more
      // expensive than just doing the extra assignment.
      data[j] = temp;
		}

    gap = (gap - 1) / 3;
	}
}

/**
 * Shell sort using gap sizes empirically determined by Tokuda. See
 * https://en.wikipedia.org/wiki/Shellsort and https://oeis.org/A108870.
 * Average complexity: Between O(n^1.3) to O(n^1.5)
 *
 * @tparam T type of data to sort
 */
template<typename T>
void shellSortTokuda(T data[], const uint16_t n)
{
  // Experimentally observed ideal gaps.
  // https://en.wikipedia.org/wiki/Shellsort
  // https://oeis.org/A108870
  static const uint16_t sGaps[] = {
      1, 4, 9, 20, 46, 103, 233, 525, 1182, 2660, 5985, 13467, 30301, 
  };
  const uint16_t nGaps = sizeof(sGaps) / sizeof(uint16_t);

  // Find the starting gap.
	uint16_t iGap;
  for (iGap = 0; sGaps[iGap] < n && iGap < nGaps; iGap++) {}
  if (iGap != 0) iGap--;

	while (true) {
    uint16_t gap = sGaps[iGap];

    // Do insertion sort of each sub-array separated by gap.
		for (uint16_t i = gap; i < n; i++) {
      T temp = data[i];

      // Shift one slot to the right.
      uint16_t j;
      for (j = i; j >= gap; j -= gap) {
        if (data[j - gap] <= temp) break;
        data[j] = data[j - gap];
      }

      // Just like insertionSort(), this can assign 'temp' back into the
      // original slot if no shifting was done. That's ok because T is assumed
      // to be relatively cheap to copy, and checking for (i != j) is more
      // expensive than just doing the extra assignment.
      data[j] = temp;
		}

    if (iGap == 0) break;
    iGap--;
	}
}

}

#endif
