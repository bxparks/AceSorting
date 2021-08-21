/*
 * Quick demo of one of the sorting functions, in this example,
 * shellSortKnuth(). All the other sorting algorithms have the exact same
 * function signature. First, create an array of integers with random numbers.
 * Then sort the array in different ways, including reverse sorting. Print out
 * the unsorted and sorted arrays. The compiler is able to infer the type of the
 * data, so you don't normally need to specify the template type to the
 * shellSortKnuth() function.
 */

#include <Arduino.h>
#include <AceSorting.h>

using ace_sorting::shellSortKnuth;

#if !defined(SERIAL_PORT_MONITOR)
  #define SERIAL_PORT_MONITOR Serial
#endif

const uint16_t ARRAY_SIZE = 50;
int array[ARRAY_SIZE];

// Print given array.
void printArray(int* array, uint16_t arraySize) {
  for (uint16_t i = 0; i < arraySize; i++) {
    SERIAL_PORT_MONITOR.print(array[i]);
    SERIAL_PORT_MONITOR.print(' ');
  }
  SERIAL_PORT_MONITOR.println();
}

// Fill array with random numbers.
void fillArray(int* array, uint16_t arraySize) {
  for (uint16_t i = 0; i < arraySize; i++) {
    array[i] = random(256);
  }
}

bool lessThan(int a, int b) {
  return a < b;
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

  SERIAL_PORT_MONITOR.print("Unsorted: ");
  fillArray(array, ARRAY_SIZE);
  printArray(array, ARRAY_SIZE);
  SERIAL_PORT_MONITOR.println();

  // Use default ascending sort order.
  SERIAL_PORT_MONITOR.print("Sorted using implicit ascending: ");
  shellSortKnuth(array, ARRAY_SIZE);
  printArray(array, ARRAY_SIZE);
  SERIAL_PORT_MONITOR.println();

  // Use function pointer.
  SERIAL_PORT_MONITOR.print("Sorted using function pointer: ");
  shellSortKnuth(array, ARRAY_SIZE, lessThan);
  printArray(array, ARRAY_SIZE);
  SERIAL_PORT_MONITOR.println();

  // Use lambda expression
  SERIAL_PORT_MONITOR.print("Sorted using lambda expression: ");
  shellSortKnuth(array, ARRAY_SIZE, [](int a, int b) { return a < b; });
  printArray(array, ARRAY_SIZE);
  SERIAL_PORT_MONITOR.println();

  // Reverse sort using lambda expression
  SERIAL_PORT_MONITOR.print("Reverse sorted using lambda expression: ");
  shellSortKnuth(array, ARRAY_SIZE, [](int a, int b) { return a > b; });
  printArray(array, ARRAY_SIZE);
  SERIAL_PORT_MONITOR.println();

#if defined(EPOXY_DUINO)
  exit(0);
#endif
}

void loop() {}
