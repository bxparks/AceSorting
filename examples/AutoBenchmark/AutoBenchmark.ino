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

/*
 * A sketch that generates the min/avg/max benchmarks of various sorting
 * functions in the AceSorting library.
 *
 * @verbatim
 * {name} dataSize min avg max sampleSize
 * @endverbatim
 *
 * This file can be fed into `generate_table.awk` to extract a human-readable
 * ASCII table that can be pasted directly into the README.md file as a code
 * block.
 */

#include <Arduino.h>
#include "Benchmark.h"

#if ! defined(SERIAL_PORT_MONITOR)
#define SERIAL_PORT_MONITOR Serial
#endif

//-----------------------------------------------------------------------------

void setup() {
#if ! defined(EPOXY_DUINO)
  delay(1000); // Wait for stability on some boards, otherwise garage on Serial
#endif

  SERIAL_PORT_MONITOR.begin(115200);
  while (!SERIAL_PORT_MONITOR); // Wait for Leonardo/Micro

#if defined(EPOXY_DUINO)
  // On Unix boxes, this should be a good enough random seed.
  randomSeed(micros());
#else
  // Attempt to get some entropy from the floating analog pin.
  randomSeed(analogRead(A0));
#endif

  SERIAL_PORT_MONITOR.println(F("BENCHMARKS"));
  runBenchmarks();

  SERIAL_PORT_MONITOR.println(F("END"));

#if defined(EPOXY_DUINO)
  exit(0);
#endif
}

void loop() {}
