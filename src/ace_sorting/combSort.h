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
 * @file combSort.h
 *
 * Comb sort.
 */

#ifndef ACE_SORTING_COMB_SORT_H
#define ACE_SORTING_COMB_SORT_H

#include "swap.h"

#if ! defined(ACE_SORTING_DIRECT_COMB_SORT)
  /**
   * If set to 1, use the direct inlined implementation of the 2-argument
   * combSortXxx(). Otherwise, use the 3-argument combSortXxx() to implement
   * 2-argument combSortXxx(). For combSortXxx(), the compiler will optimize
   * both versions to be identical.
   */
  #define ACE_SORTING_DIRECT_COMB_SORT 0
#endif

namespace ace_sorting {

/**
 * Comb sort using a gap factor of 1.3 (successive gap is multiplied by
 * 10 / 13). On 8-bit processors where the `int` type is 2 bytes, the
 * multiplication of `n` by 10 can overflow the 16-bit integer. So the largest
 * `n` that this function can support is 65536 / 10 or 6553.
 *
 * Average complexity: O(n^2 / 2^p).
 * See https://en.wikipedia.org/wiki/Comb_sort
 *
 * @tparam T type of data to sort
 */
#if ACE_SORTING_DIRECT_COMB_SORT
template <typename T>
void combSort13(T data[], uint16_t n) {
  bool swapped = true;

  uint16_t gap = n;
  while (swapped || gap > 1) {
    gap = gap * 10 / 13;
    if (gap == 0) gap = 1;
    swapped = false;

    uint16_t i;
    uint16_t j;
    for (i = 0, j = gap; j < n; i++, j++) {
      if (data[j] < data[i]) {
        swap(data[i], data[j]);
        swapped = true;
      }
    }
  }
}
#else
template <typename T>
void combSort13(T data[], uint16_t n) {
  // This lambda expression does not perform any captures, so the compiler will
  // optimize and inline the less-than expression.
  auto&& lessThan = [](const T& a, const T& b) -> bool { return a < b; };
  combSort13(data, n, lessThan);
}
#endif

/**
 * Same as the 2-argument combSort13() with the addition of a `lessThan` lambda
 * expression or function.
 *
 * @tparam T type of data to sort
 * @tparam F type of lambda expression or function that returns true if a < b
 */
template <typename T, typename F>
void combSort13(T data[], uint16_t n, F&& lessThan) {
  bool swapped = true;

  uint16_t gap = n;
  while (swapped || gap > 1) {
    gap = gap * 10 / 13;
    if (gap == 0) gap = 1;
    swapped = false;

    uint16_t i;
    uint16_t j;
    for (i = 0, j = gap; j < n; i++, j++) {
      if (lessThan(data[j], data[i])) {
        swap(data[i], data[j]);
        swapped = true;
      }
    }
  }
}

//-----------------------------------------------------------------------------

/**
 * Same as combSort13() with the modification that if the gap is 9 or 10, it is
 * set to 11, so that the gap sequence becomes (11, 8, 6, 4, 3, 2, 1). For
 * reasons that I don't understand, this makes the algorithm faster and more
 * resistence to outliers.
 *
 * Average complexity: O(n^2 / 2^p).
 * See https://en.wikipedia.org/wiki/Comb_sort and
 * https://rosettacode.org/wiki/Sorting_algorithms/Comb_sort.
 *
 * @tparam T type of data to sort
 */
#if ACE_SORTING_DIRECT_COMB_SORT
template <typename T>
void combSort13m(T data[], uint16_t n) {
  bool swapped = true;

  uint16_t gap = n;
  while (swapped || gap > 1) {
    gap = gap * 10 / 13;
    if (gap == 9 || gap == 10) {
      gap = 11;
    } else if (gap == 0) {
      gap = 1;
    }
    swapped = false;

    uint16_t i;
    uint16_t j;
    for (i = 0, j = gap; j < n; i++, j++) {
      if (data[j] < data[i]) {
        swap(data[i], data[j]);
        swapped = true;
      }
    }
  }
}
#else
template <typename T>
void combSort13m(T data[], uint16_t n) {
  // This lambda expression does not perform any captures, so the compiler will
  // optimize and inline the less-than expression.
  auto&& lessThan = [](const T& a, const T& b) -> bool { return a < b; };
  combSort13m(data, n, lessThan);
}
#endif

/**
 * Same as the 2-argument combSort13m() with the addition of a `lessThan` lambda
 * expression or function.
 *
 * @tparam T type of data to sort
 * @tparam F type of lambda expression or function that returns true if a < b
 */
template <typename T, typename F>
void combSort13m(T data[], uint16_t n, F&& lessThan) {
  bool swapped = true;

  uint16_t gap = n;
  while (swapped || gap > 1) {
    gap = gap * 10 / 13;
    if (gap == 9 || gap == 10) {
      gap = 11;
    } else if (gap == 0) {
      gap = 1;
    }
    swapped = false;

    uint16_t i;
    uint16_t j;
    for (i = 0, j = gap; j < n; i++, j++) {
      if (lessThan(data[j], data[i])) {
        swap(data[i], data[j]);
        swapped = true;
      }
    }
  }
}

//-----------------------------------------------------------------------------

/**
 * Comb sort using a gap factor of 4/3=1.33 (successive gap is multiplied by 3
 * / 4). The multiplication by 3 can overflow the 2-byte `int` type on 8-bit
 * processors, so the largest `n` supported by this function is 65535 / 3 or
 * 21845.
 *
 * This gap ratio seemed appealing because the division by 4 will be optimized
 * by the compiler into a right shift of 2 bits, so this algorithm does not
 * perform any integer division. Experimentation on 8-bit processors without
 * hardware dvision shows that this algorithm is slightly faster than
 * combSort13() on average.
 *
 * On 32-bit or 64-bit processors with hardware division, on larger input
 * `data`, experimentation shows that this algorithm is actually slightly slower
 * on average than combSort13(). And it seems to have a slightly higher
 * variance, with some input data causing large spikes in runtime compared to
 * the average.
 *
 * Average complexity: O(n^2 / 2^p).
 * See https://en.wikipedia.org/wiki/Comb_sort
 *
 * @tparam T type of data to sort
 */
#if ACE_SORTING_DIRECT_COMB_SORT
template <typename T>
void combSort133(T data[], uint16_t n) {
  bool swapped = true;

  uint16_t gap = n;
  while (swapped || gap > 1) {
    gap = gap * 3 / 4;
    if (gap == 0) gap = 1;
    swapped = false;

    uint16_t i;
    uint16_t j;
    for (i = 0, j = gap; j < n; i++, j++) {
      if (data[j] < data[i]) {
        swap(data[i], data[j]);
        swapped = true;
      }
    }
  }
}
#else
template <typename T>
void combSort133(T data[], uint16_t n) {
  // This lambda expression does not perform any captures, so the compiler will
  // optimize and inline the less-than expression.
  auto&& lessThan = [](const T& a, const T& b) -> bool { return a < b; };
  combSort133(data, n, lessThan);
}
#endif

/**
 * Same as the 2-argument combSort133() with the addition of a `lessThan` lambda
 * expression or function.
 *
 * @tparam T type of data to sort
 * @tparam F type of lambda expression or function that returns true if a < b
 */
template <typename T, typename F>
void combSort133(T data[], uint16_t n, F&& lessThan) {
  bool swapped = true;

  uint16_t gap = n;
  while (swapped || gap > 1) {
    gap = gap * 3 / 4;
    if (gap == 0) gap = 1;
    swapped = false;

    uint16_t i;
    uint16_t j;
    for (i = 0, j = gap; j < n; i++, j++) {
      if (lessThan(data[j], data[i])) {
        swap(data[i], data[j]);
        swapped = true;
      }
    }
  }
}

//-----------------------------------------------------------------------------

/**
 * Same as combSort133() but modified so that a gap of 9 or 10 becomes gap=11 so
 * that the final sequence becomes (11, 8, 6, 4, 3, 2, 1). Experimentation shows
 * that this is often slightly slower than than combSort133(), probably due to
 * the extra if/then/else statements in the loop.
 *
 * Average complexity: O(n^2 / 2^p).
 * See https://en.wikipedia.org/wiki/Comb_sort
 *
 * @tparam T type of data to sort
 */
#if ACE_SORTING_DIRECT_COMB_SORT
template <typename T>
void combSort133m(T data[], uint16_t n) {
  bool swapped = true;

  uint16_t gap = n;
  while (swapped || gap > 1) {
    gap = gap * 3 / 4;
    if (gap == 9 || gap == 10) {
      gap = 11;
    } else if (gap == 0) {
      gap = 1;
    }
    swapped = false;

    uint16_t i;
    uint16_t j;
    for (i = 0, j = gap; j < n; i++, j++) {
      if (data[j] < data[i]) {
        swap(data[i], data[j]);
        swapped = true;
      }
    }
  }
}
#else
template <typename T>
void combSort133m(T data[], uint16_t n) {
  // This lambda expression does not perform any captures, so the compiler will
  // optimize and inline the less-than expression.
  auto&& lessThan = [](const T& a, const T& b) -> bool { return a < b; };
  combSort133m(data, n, lessThan);
}
#endif

/**
 * Same as the 2-argument combSort133m() with the addition of a `lessThan`
 * lambda expression or function.
 *
 * @tparam T type of data to sort
 * @tparam F type of lambda expression or function that returns true if a < b
 */
template <typename T, typename F>
void combSort133m(T data[], uint16_t n, F&& lessThan) {
  bool swapped = true;

  uint16_t gap = n;
  while (swapped || gap > 1) {
    gap = gap * 3 / 4;
    if (gap == 9 || gap == 10) {
      gap = 11;
    } else if (gap == 0) {
      gap = 1;
    }
    swapped = false;

    uint16_t i;
    uint16_t j;
    for (i = 0, j = gap; j < n; i++, j++) {
      if (lessThan(data[j], data[i])) {
        swap(data[i], data[j]);
        swapped = true;
      }
    }
  }
}

}

#endif
