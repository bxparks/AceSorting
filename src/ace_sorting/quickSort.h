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
 * @file quickSort.h
 *
 * Quick sort algorithms.
 */

#ifndef ACE_SORTING_QUICK_SORT_H
#define ACE_SORTING_QUICK_SORT_H

#include "swap.h"

namespace ace_sorting {

/**
 * Quick sort using Hoare's original partition where the pivot is the middle
 * of the array. If the original array is already close to sorted, this
 * algorithm runs in O(N log(N)). Average complexity: O(N log(N))
 *
 * See https://en.wikipedia.org/wiki/Quicksort
 *
 * @tparam T type of data to sort
 */
template <typename T>
void quickSortMiddle(T data[], uint16_t n) {
  if (n <= 1) return;
  
  T pivot = data[n / 2];
  T* left = data;
  T* right = data + n - 1;
  
  while (left <= right) {
		if (*left < pivot) {
      left++;
		} else if (*right > pivot) {
      right--;
		} else {
      swap(*left, *right);
			left++;
			right--;
		}
  }

	quickSortMiddle(data, right - data + 1);
	quickSortMiddle(left, data + n - left);
}

/**
 * Quick sort using Sedgewick's recommendation of using the median of low,
 * middle and high. If the original array is already close to sorted or reverse
 * sorted, this algorithm runs in O(N log(N)). Average complexity: O(N log(N))
 *
 * See https://en.wikipedia.org/wiki/Quicksort
 *
 * @tparam T type of data to sort
 */
template <typename T>
void quickSortMedian(T data[], uint16_t n) {
  if (n <= 1) return;
  
  // Select the median of data[low], data[mid], and data[high] as the estimate
  // of the ideal pivot. Don't swap (low, mid) or (mid, high) (compare that
  // quickSortMedianSwapped()) to save flash memory. They will get swapped in
  // the partitioning while-loop below.
  uint16_t mid = n / 2;
  T pivot = data[mid];
  if (data[0] > data[n - 1]) {
    swap(data[0], data[n - 1]);
  }
  if (data[0] > pivot) {
    pivot = data[0];
  } else if (pivot > data[n - 1]) {
    pivot = data[n - 1];
  }

  T* left = data;
  T* right = data + n - 1;
  
  while (left <= right) {
		if (*left < pivot) {
      left++;
		} else if (*right > pivot) {
      right--;
		} else {
      swap(*left, *right);
			left++;
			right--;
		}
  }

	quickSortMedian(data, right - data + 1);
	quickSortMedian(left, data + n - left);
}

/**
 * Same as quickSortMedian(), but swap the low and high so that low, mid, and
 * high elements become sorted. This means that the low and high are already
 * partitioned, so we can omit those 2 points from the partitioning while-loop.
 * This code consumes a lot more flash memory due to the additional swap()
 * calls.
 *
 * @tparam T type of data to sort
 */
template <typename T>
void quickSortMedianSwapped(T data[], uint16_t n) {
  if (n <= 1) return;
  
  // Select the median of data[low], data[mid], and data[high] as the estimate
  // of the ideal pivot. In the process, the (low, mid, high) become sorted.
  uint16_t mid = n / 2;
  T pivot = data[mid];
  if (data[0] > data[n - 1]) {
    swap(data[0], data[n - 1]);
  }
  if (data[0] > pivot) {
    swap(data[0], data[mid]);
  } else if (pivot > data[n - 1]) {
    swap(data[mid], data[n - 1]);
  }
  pivot = data[mid];

  // We can skip the low and high because they are already sorted.
  T* left = data + 1;
  T* right = data + n - 2;
  
  while (left <= right) {
		if (*left < pivot) {
      left++;
		} else if (*right > pivot) {
      right--;
		} else {
      swap(*left, *right);
			left++;
			right--;
		}
  }

	quickSortMedianSwapped(data, right - data + 1);
	quickSortMedianSwapped(left, data + n - left);
}

}

#endif
