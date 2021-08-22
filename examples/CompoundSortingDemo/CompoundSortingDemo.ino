/*
 * Demo of a more complex sorting using a compound key and a lambda expression.
 * This version uses shellSortKnuth(), but all the other sorting algorithms have
 * the exact same function signature.
 *
 * Expected output:
 *
 * Unsorted
 * --------
 * Michael 3
 * Soren 1
 * Arun 5
 * Meilin 6
 * Emilia 3
 * Dimitri 2
 * Dembe 8
 * Nasir 10
 * Hiromi 9
 * Petra 6
 *
 * Sorted by name
 * --------------
 * Arun 5
 * Dembe 8
 * Dimitri 2
 * Emilia 3
 * Hiromi 9
 * Meilin 6
 * Michael 3
 * Nasir 10
 * Petra 6
 * Soren 1
 *
 * Sorted by (score, name)
 * -----------------------
 * Soren 1
 * Dimitri 2
 * Emilia 3
 * Michael 3
 * Arun 5
 * Meilin 6
 * Petra 6
 * Dembe 8
 * Hiromi 9
 * Nasir 10
 */

#include <string.h> // strcmp()
#include <Arduino.h>
#include <AceSorting.h>

using ace_sorting::shellSortKnuth;

// ESP32 does not define SERIAL_PORT_MONITOR
#if ! defined(SERIAL_PORT_MONITOR)
  #define SERIAL_PORT_MONITOR Serial
#endif

// Record of a person's name and score.
struct Record {
  const char* name;
  int score;
};

// List of names and their scores. This table is const so cannot be modified.
// The names and this table could be stored in PROGMEM, but that would
// significantly clutter up the code with type conversions which makes this
// example harder to understand.
const uint16_t ARRAY_SIZE = 10;
const Record RECORDS[ARRAY_SIZE] = {
  { "Michael", 3 },
  { "Soren", 1 },
  { "Arun", 5 },
  { "Meilin", 6 },
  { "Emilia", 3 },
  { "Dimitri", 2 },
  { "Dembe", 8 },
  { "Nasir", 10 },
  { "Hiromi", 9 },
  { "Petra", 6 },
};

// Print the records given an array of pointers to Record.
void printRecords(const Record* const records[], uint16_t arraySize) {
  for (uint16_t i = 0; i < arraySize; i++) {
    const Record* record = records[i];
    SERIAL_PORT_MONITOR.print(record->name);
    SERIAL_PORT_MONITOR.print(' ');
    SERIAL_PORT_MONITOR.print(record->score);
    SERIAL_PORT_MONITOR.println();
  }
}

// Fill the recordPtrs[] array with the pointers to RECORDS[]. The original
// RECORDS[] is immutable, so we need a helper array to perform the sorting.
void fillRecordPointers(const Record* recordPtrs[], uint16_t arraySize) {
  for (uint16_t i = 0; i < arraySize; i++) {
    recordPtrs[i] = &RECORDS[i];
  }
}

// Predicate that returns true if Record 'a' is less than Record 'b' by first
// looking at the 'score', then using 'name' to break the tie on score.
bool sortByScoreThenName(const Record* a, const Record* b) {
  if (a->score < b->score) {
    return true;
  } else if (a->score > b->score) {
    return false;
  } else {
    return strcmp(a->name, b->name) < 0;
  }
}

//-----------------------------------------------------------------------------

void setup() {
#if ! defined(EPOXY_DUINO)
  delay(1000);
#endif

  SERIAL_PORT_MONITOR.begin(115200);
  while (!SERIAL_PORT_MONITOR); // Leonardo/Micro

  const Record* recordPtrs[ARRAY_SIZE];
  fillRecordPointers(recordPtrs, ARRAY_SIZE);

  // Print original ordering.
  SERIAL_PORT_MONITOR.println(F("Unsorted"));
  SERIAL_PORT_MONITOR.println(F("--------"));
  printRecords(recordPtrs, ARRAY_SIZE);
  SERIAL_PORT_MONITOR.println();

  // Sort by name. Use an inline lambda expression because the predicate is
  // very short.
  SERIAL_PORT_MONITOR.println(F("Sorted by name"));
  SERIAL_PORT_MONITOR.println(F("--------------"));
  shellSortKnuth(
      recordPtrs,
      ARRAY_SIZE,
      [](const Record* a, const Record* b) {
        return strcmp(a->name, b->name) < 0;
      }
  );
  printRecords(recordPtrs, ARRAY_SIZE);
  SERIAL_PORT_MONITOR.println();

  // Sort by score then name. Use a helper function for readability because the
  // predicate is more complex, but an inlined lambda expression would work
  // perfectly fine.
  SERIAL_PORT_MONITOR.println(F("Sorted by (score, name)"));
  SERIAL_PORT_MONITOR.println(F("-----------------------"));
  shellSortKnuth(recordPtrs, ARRAY_SIZE, sortByScoreThenName);
  printRecords(recordPtrs, ARRAY_SIZE);
  SERIAL_PORT_MONITOR.println();

#if defined(EPOXY_DUINO)
  exit(0);
#endif
}

void loop() {}
