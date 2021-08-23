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
 * See https://en.wikipedia.org/wiki/Quicksort
 */

#ifndef ACE_SORTING_QUICK_SORT_H
#define ACE_SORTING_QUICK_SORT_H

#include "swap.h"

#if ! defined(ACE_SORTING_DIRECT_QUICK_SORT)
  /**
   * If set to 1, use the direct inlined implementation of the 2-argument
   * quickSortXxx(). Otherwise, use the 3-argument quickSortXxx() to implement
   * 2-argument quickSortXxx().
   *
   * Unlike other sorting algorithms, the compiler cannot seem to optimize away
   * the extra level of indirection, probably due to the recursive calls. We
   * save 40 bytes of flash (out of 200-300 bytes) by setting this to 1 so that
   * the 2-argument variant is manually inlined.
   */
  #define ACE_SORTING_DIRECT_QUICK_SORT 1
#endif

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
#if ACE_SORTING_DIRECT_QUICK_SORT
template <typename T>
void quickSortMiddle(T data[], uint16_t n) {
  if (n <= 1) return;

  T pivot = data[n / 2];
  T* left = data;
  T* right = data + n - 1;

  while (left <= right) {
    if (*left < pivot) {
      left++;
    } else if (pivot < *right) {
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
#else
template <typename T>
void quickSortMiddle(T data[], uint16_t n) {
  // This lambda expression does not perform any captures, so the compiler ought
  // to be able to optimize and inline the less-than expression. However, the
  // optimization does not seem to work, probably because of the recursive call
  // into itself. So we set ACE_SORTING_DIRECT_QUICK_SORT=1 to use the direct
  // inlined version.
  auto&& lessThan = [](const T& a, const T& b) -> bool { return a < b; };
  quickSortMiddle(data, n, lessThan);
}
#endif

/**
 * Same as the 2-argument quickSortMiddle() with the addition of a `lessThan`
 * lambda expression or function.
 *
 * @tparam T type of data to sort
 * @tparam F type of lambda expression or function that returns true if a < b
 */
template <typename T, typename F>
void quickSortMiddle(T data[], uint16_t n, F&& lessThan) {
  if (n <= 1) return;

  T pivot = data[n / 2];
  T* left = data;
  T* right = data + n - 1;

  while (left <= right) {
    if (lessThan(*left, pivot)) {
      left++;
    } else if (lessThan(pivot, *right)) {
      right--;
    } else {
      swap(*left, *right);
      left++;
      right--;
    }
  }

  quickSortMiddle(data, right - data + 1, lessThan);
  quickSortMiddle(left, data + n - left, lessThan);
}

//-----------------------------------------------------------------------------

/**
 * Quick sort using Sedgewick's recommendation of using the median of low,
 * middle and high. If the original array is already close to sorted or reverse
 * sorted, this algorithm runs in O(N log(N)). Average complexity: O(N log(N))
 *
 * See https://en.wikipedia.org/wiki/Quicksort
 *
 * @tparam T type of data to sort
 */
#if ACE_SORTING_DIRECT_QUICK_SORT
template <typename T>
void quickSortMedian(T data[], uint16_t n) {
  if (n <= 1) return;

  // Select the median of data[low], data[mid], and data[high] as the estimate
  // of the ideal pivot. Don't swap (low, mid) or (mid, high) (compare that
  // quickSortMedianSwapped()) to save flash memory. They will get swapped in
  // the partitioning while-loop below.
  uint16_t mid = n / 2;
  T pivot = data[mid];
  if (data[n - 1] < data[0]) {
    swap(data[0], data[n - 1]);
  }
  if (pivot < data[0]) {
    pivot = data[0];
  } else if (data[n - 1] < pivot) {
    pivot = data[n - 1];
  }

  T* left = data;
  T* right = data + n - 1;

  while (left <= right) {
    if (*left < pivot) {
      left++;
    } else if (pivot < *right) {
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
#else
template <typename T>
void quickSortMedian(T data[], uint16_t n) {
  // This lambda expression does not perform any captures, so the compiler will
  // optimize and inline the less-than expression.
  auto&& lessThan = [](const T& a, const T& b) -> bool { return a < b; };
  quickSortMedian(data, n, lessThan);
}
#endif

/**
 * Same as the 2-argument quickSortMedian() with the addition of a `lessThan`
 * lambda expression or function.
 *
 * @tparam T type of data to sort
 * @tparam F type of lambda expression or function that returns true if a < b
 */
template <typename T, typename F>
void quickSortMedian(T data[], uint16_t n, F&& lessThan) {
  if (n <= 1) return;

  // Select the median of data[low], data[mid], and data[high] as the estimate
  // of the ideal pivot. Don't swap (low, mid) or (mid, high) (compare that
  // quickSortMedianSwapped()) to save flash memory. They will get swapped in
  // the partitioning while-loop below.
  uint16_t mid = n / 2;
  T pivot = data[mid];
  if (lessThan(data[n - 1], data[0])) {
    swap(data[0], data[n - 1]);
  }
  if (lessThan(pivot, data[0])) {
    pivot = data[0];
  } else if (lessThan(data[n - 1], pivot)) {
    pivot = data[n - 1];
  }

  T* left = data;
  T* right = data + n - 1;

  while (left <= right) {
    if (lessThan(*left, pivot)) {
      left++;
    } else if (lessThan(pivot, *right)) {
      right--;
    } else {
      swap(*left, *right);
      left++;
      right--;
    }
  }

  quickSortMedian(data, right - data + 1, lessThan);
  quickSortMedian(left, data + n - left, lessThan);
}

//-----------------------------------------------------------------------------

/**
 * Same as quickSortMedian(), but swap the low and high so that low, mid, and
 * high elements become sorted. This means that the low and high are already
 * partitioned, so we can omit those 2 points from the partitioning while-loop.
 * This code consumes a lot more flash memory due to the additional swap()
 * calls, but runs slightly faster.
 *
 * @tparam T type of data to sort
 */
#if ACE_SORTING_DIRECT_QUICK_SORT
template <typename T>
void quickSortMedianSwapped(T data[], uint16_t n) {
  if (n <= 1) return;

  // Select the median of data[low], data[mid], and data[high] as the estimate
  // of the ideal pivot. In the process, the (low, mid, high) become sorted.
  uint16_t mid = n / 2;
  T pivot = data[mid];
  if (data[n - 1] < data[0]) {
    swap(data[0], data[n - 1]);
  }
  if (pivot < data[0]) {
    swap(data[0], data[mid]);
  } else if (data[n - 1] < pivot) {
    swap(data[mid], data[n - 1]);
  }
  pivot = data[mid];

  // We can skip the low and high because they are already sorted.
  T* left = data + 1;
  T* right = data + n - 2;

  while (left <= right) {
    if (*left < pivot) {
      left++;
    } else if (pivot < *right) {
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
#else
template <typename T>
void quickSortMedianSwapped(T data[], uint16_t n) {
  // This lambda expression does not perform any captures, so the compiler will
  // optimize and inline the less-than expression.
  auto&& lessThan = [](const T& a, const T& b) -> bool { return a < b; };
  quickSortMedianSwapped(data, n, lessThan);
}
#endif

/**
 * Same as the 2-argument quickSortMedianSwapped() with the addition of a
 * `lessThan` lambda expression or function.
 *
 * @tparam T type of data to sort
 * @tparam F type of lambda expression or function that returns true if a < b
 */
template <typename T, typename F>
void quickSortMedianSwapped(T data[], uint16_t n, F&& lessThan) {
  if (n <= 1) return;

  // Select the median of data[low], data[mid], and data[high] as the estimate
  // of the ideal pivot. In the process, the (low, mid, high) become sorted.
  uint16_t mid = n / 2;
  T pivot = data[mid];
  if (lessThan(data[n - 1], data[0])) {
    swap(data[0], data[n - 1]);
  }
  if (lessThan(pivot, data[0])) {
    swap(data[0], data[mid]);
  } else if (lessThan(data[n - 1], pivot)) {
    swap(data[mid], data[n - 1]);
  }
  pivot = data[mid];

  // We can skip the low and high because they are already sorted.
  T* left = data + 1;
  T* right = data + n - 2;

  while (left <= right) {
    if (lessThan(*left, pivot)) {
      left++;
    } else if (lessThan(pivot, *right)) {
      right--;
    } else {
      swap(*left, *right);
      left++;
      right--;
    }
  }

  quickSortMedianSwapped(data, right - data + 1, lessThan);
  quickSortMedianSwapped(left, data + n - left, lessThan);
}

}

#endif
