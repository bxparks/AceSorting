/*
 * Quick demo of one of the sorting functions, in this example,
 * shellSortKnuth(). All the other sorting algorithms have the exact same
 * function signature. The compiler is able to infer the type of the data, so
 * you don't normally need to specify the template type to the shellSortKnuth()
 * function.
 *
 * Expected output:
 *
 * Unsorted: 234 19 95 219 255 132 27 194 83 96 245 161 228 205 193 215 101 216
 * 120 95
 *
 * Sorted using implicit ascending: 19 27 83 95 95 96 101 120 132 161 193 194
 * 205 215 216 219 228 234 245 255
 *
 * Sorted using function pointer: 19 27 83 95 95 96 101 120 132 161 193 194 205
 * 215 216 219 228 234 245 255
 *
 * Sorted using lambda expression: 19 27 83 95 95 96 101 120 132 161 193 194 205
 * 215 216 219 228 234 245 255
 *
 * Reverse sorted using lambda expression: 255 245 234 228 219 216 215 205 194
 * 193 161 132 120 101 96 95 95 83 27 19
 */

#include <Arduino.h>
#include <AceSorting.h>

using ace_sorting::shellSortKnuth;

// ESP32 does not define SERIAL_PORT_MONITOR
#if !defined(SERIAL_PORT_MONITOR)
  #define SERIAL_PORT_MONITOR Serial
#endif

const uint16_t ARRAY_SIZE = 20;
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
