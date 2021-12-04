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
 * @mainpage AceSorting Library
 *
 * This is the Doxygen documentation for the
 * <a href="https://github.com/bxparks/AceSorting">AceSorting Library</a>.
 *
 * Click on the "Classes" menu above to see the list of classes.
 *
 * Click on the "Files" menu above to see the list of header files.
 */

#ifndef ACE_SORTING_ACE_SORTING_H
#define ACE_SORTING_ACE_SORTING_H

// Blacklist platforms using https://github.com/arduino/ArduinoCore-api due to
// incompatibilities.
#if defined(ARDUINO_API_VERSION)
#error Platforms using ArduinoCore-API not supported
#endif

// Version format: xxyyzz == "xx.yy.zz"
#define ACE_SORTING_VERSION 10000
#define ACE_SORTING_VERSION_STRING "1.0.0"

#include "ace_sorting/swap.h"
#include "ace_sorting/bubbleSort.h"
#include "ace_sorting/insertionSort.h"
#include "ace_sorting/selectionSort.h"
#include "ace_sorting/shellSort.h"
#include "ace_sorting/combSort.h"
#include "ace_sorting/quickSort.h"

#endif
