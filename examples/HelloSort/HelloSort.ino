/*
 * Quick demo of one of the sorting functions: create an array of integers with
 * random numbers, and sort the array. Print out the unsorted and sorted arrays.
 * Other sorting functions follow the same pattern. The compiler is able to
 * infer the type of the data, so you don't normally need to specify the
 * template type to the shellSortKnuth() function.
 */

#include <Arduino.h>
#include <AceSorting.h>

using ace_sorting::shellSortKnuth;

#if !defined(SERIAL_PORT_MONITOR)
  #define SERIAL_PORT_MONITOR Serial
#endif

const uint16_t ARRAY_SIZE = 50;
int array[ARRAY_SIZE];

void printArray(int* array, uint16_t arraySize) {
  for (uint16_t i = 0; i < arraySize; i++) {
    SERIAL_PORT_MONITOR.print(array[i]);
    SERIAL_PORT_MONITOR.print(' ');
  }
  SERIAL_PORT_MONITOR.println();
}

void fillArray(int* array, uint16_t arraySize) {
  for (uint16_t i = 0; i < arraySize; i++) {
    array[i] = random(256);
  }
}

//-----------------------------------------------------------------------------

void setup() {
#if ! defined(EPOXY_DUINO)
  delay(1000);
#endif

  SERIAL_PORT_MONITOR.begin(115200);
  while (!SERIAL_PORT_MONITOR); // Leonardo/Micro

  // Attempt to get a random seed using the floating analog pin.
#if defined(EPOXY_DUINO)
  randomSeed(micros());
#else
  randomSeed(analogRead(A0));
#endif

  fillArray(array, ARRAY_SIZE);
  SERIAL_PORT_MONITOR.println("Unsorted:");
  printArray(array, ARRAY_SIZE);

  // The compiler automatically generates the correct version of
  // shellSortKnuth() based on the type of `array`.
  shellSortKnuth(array, ARRAY_SIZE);
  SERIAL_PORT_MONITOR.println("Sorted:");
  printArray(array, ARRAY_SIZE);

#if defined(EPOXY_DUINO)
  exit(0);
#endif
}

void loop() {}
