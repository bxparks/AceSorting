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
 * @file insertionSort.h
 *
 * Insertion sort.
 * See https://en.wikipedia.org/wiki/Insertion_sort
 */

#ifndef ACE_SORTING_INSERTION_SORT_H
#define ACE_SORTING_INSERTION_SORT_H

#if ! defined(ACE_SORTING_DIRECT_INSERTION_SORT)
  /**
   * If set to 1, use the direct inlined implementation of the 2-argument
   * insertionSort(). Otherwise, use the 3-argument insertionSort() to implement
   * 2-argument insertionSort(). For insertionSort(), the compiler will optimize
   * both versions to be identical.
   */
  #define ACE_SORTING_DIRECT_INSERTION_SORT 0
#endif

namespace ace_sorting {

/**
 * Insertion sort.
 * Average complexity: O(n^2)
 * See https://en.wikipedia.org/wiki/Insertion_sort
 *
 * @tparam T type of data to sort
 */
#if ACE_SORTING_DIRECT_INSERTION_SORT
template <typename T>
void insertionSort(T data[], uint16_t n) {
  for (uint16_t i = 1; i < n; i++) {
    T temp = data[i];

    // Shift one slot to the right.
    uint16_t j;
    for (j = i; j > 0; j--) {
      if (data[j - 1] <= temp) break;
      data[j] = data[j - 1];
    }

    // This can assign 'temp' back into the original slot if no shifting was
    // done. That's ok because T is assumed to be relatively cheap to copy, and
    // checking for (i != j) is more expensive than just doing the extra
    // assignment.
    data[j] = temp;
  }
}
#else
template <typename T>
void insertionSort(T data[], uint16_t n) {
  // This lambda expression does not perform any captures, so the compiler will
  // optimize and inline the less-than expression.
  auto&& lessThan = [](const T& a, const T& b) -> bool { return a < b; };
  insertionSort(data, n, lessThan);
}
#endif

/**
 * Same as the 2-argument insertionSort() with the addition of a `lessThan`
 * lambda expression or function.
 *
 * @tparam T type of data to sort
 * @tparam F type of lambda expression or function that returns true if a < b
 */
template <typename T, typename F>
void insertionSort(T data[], uint16_t n, F&& lessThan) {
  for (uint16_t i = 1; i < n; i++) {
    T temp = data[i];

    // Shift one slot to the right.
    uint16_t j;
    for (j = i; j > 0; j--) {
      // The following is equivalent to: (data[j - 1] <= temp)
      if (! lessThan(temp, data[j - 1])) break;
      data[j] = data[j - 1];
    }

    // This can assign 'temp' back into the original slot if no shifting was
    // done. That's ok because T is assumed to be relatively cheap to copy, and
    // checking for (i != j) is more expensive than just doing the extra
    // assignment.
    data[j] = temp;
  }
}

}

#endif
