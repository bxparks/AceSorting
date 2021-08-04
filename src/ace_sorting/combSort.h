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

namespace ace_sorting {

/**
 * Comb sort using a gap factor of 1.3 (successive gap multiplication by 10 /
 * 13). On 8-bit processors where the `int` type is 2 bytes, the multiplication
 * of `n` by 10 can overflow the 16-bit integer. So the largest `n` that this
 * function can support is 65536 / 10 or 6553.
 *
 * Average complexity: O(n^2 / 2^p).
 * See https://en.wikipedia.org/wiki/Comb_sort
 *
 * @tparam T type of data to sort
 */
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
			if (data[i] > data[j]) {
        swap(data[i], data[j]);
				swapped = true;
			}
		}
	}
}

/**
 * Comb sort using a gap factor of 1.25 (successive gap multiplication by 4 /
 * 5). On 8-bit processors where the `int` type is 2 bytes, the multiplication
 * of `n` by 4 can overflow the 16-bit integer. So the largest `n` that this
 * function can support is 65535 / 4 or 16383.
 *
 * Average complexity: O(n^2 / 2^p).
 * See https://en.wikipedia.org/wiki/Comb_sort
 *
 * @tparam T type of data to sort
 */
template <typename T>
void combSort125(T data[], uint16_t n) {
	bool swapped = true;

	uint16_t gap = n;
	while (swapped || gap > 1) {
		gap = gap * 4 / 5;
		if (gap == 0) gap = 1;
		swapped = false;

		uint16_t i;
    uint16_t j;
		for (i = 0, j = gap; j < n; i++, j++) {
			if (data[i] > data[j]) {
        swap(data[i], data[j]);
				swapped = true;
			}
		}
	}
}

/**
 * Comb sort using a gap factor of 1.33333333 (successive gap multiplication by
 * 3 / 4). The multiplication by 3 can overflow the 2-byte `int` type on 8-bit
 * processors, so the largest `n` supported by this function is 65535 / 3 or
 * 21845.
 *
 * The division by 4 will be optimized by the compiler into a left shift by 2
 * bits, so this algorithm does not perform any integer division, which makes
 * this function smaller and faster on 8-bit processors without hardware integer
 * division.
 *
 * Average complexity: O(n^2 / 2^p).
 * See https://en.wikipedia.org/wiki/Comb_sort
 *
 * @tparam T type of data to sort
 */
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
			if (data[i] > data[j]) {
        swap(data[i], data[j]);
				swapped = true;
			}
		}
	}
}

}

#endif
