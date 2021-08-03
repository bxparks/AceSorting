#line 2 "SortingTest.ino"

#include <Arduino.h>
#include <AUnit.h>
#include <AceCommon.h>
#include <AceSorting.h>

using aunit::TestRunner;
using aunit::TestOnce;
using ace_common::isSorted;
using ace_sorting::bubbleSort;
using ace_sorting::insertionSort;
using ace_sorting::shellSortClassic;
using ace_sorting::shellSortKnuth;
using ace_sorting::shellSortTokuda;
using ace_sorting::combSort13;
using ace_sorting::combSort125;
using ace_sorting::quickSortMiddle;
using ace_sorting::quickSortMedian;
using ace_sorting::quickSortMedianSwapped;

//-----------------------------------------------------------------------------

static const uint16_t LIST5[] = {
  2,
  30,
  3,
  400,
  100,
};

typedef void (*SortFunction)(uint16_t data[], uint16_t n);

static void fillArray(uint16_t data[], uint16_t n) {
  for (uint16_t i = 0; i < n; ++i) {
    data[i] = random(65536);
  }
}

class SortingTest : public TestOnce {
  public:
    // Sort algorithms should not blow up if given n=0.
    void assertSort0(SortFunction sortFunction) {
      uint16_t list1[1] = {1};
      sortFunction(list1, 0);
      assertEqual(list1[0], (uint16_t) 1);
    }

    // Sort algorithms should handle n=1 by also doing nothing.
    void assertSort1(SortFunction sortFunction) {
      uint16_t list1[1] = {1};
      sortFunction(list1, 1);
      assertEqual(list1[0], (uint16_t) 1);
    }

    void assertSort2(SortFunction sortFunction) {
      uint16_t list2a[2] = {4, 1};
      sortFunction(list2a, 2);
      assertEqual(list2a[0], (uint16_t) 1);
      assertEqual(list2a[1], (uint16_t) 4);

      uint16_t list2b[2] = {1, 4};
      sortFunction(list2b, 2);
      assertEqual(list2b[0], (uint16_t) 1);
      assertEqual(list2b[1], (uint16_t) 4);
    }

    void assertSort5(SortFunction sortFunction) {
      uint16_t list5[5];
      memcpy(list5, LIST5, sizeof(LIST5));

      assertFalse(isSorted(list5, 5));
      sortFunction(list5, 5);
      assertTrue(isSorted(list5, 5));
    }

    void assertSort300(SortFunction sortFunction) {
      uint16_t dataSize = 300;
      uint16_t* data = new uint16_t[dataSize];
      fillArray(data, dataSize);

      assertFalse(isSorted(data, dataSize));
      sortFunction(data, dataSize);
      assertTrue(isSorted(data, dataSize));
      delete[] data;
    }

    void assertSort(SortFunction sortFunction) {
      assertNoFatalFailure(assertSort0(sortFunction));
      assertNoFatalFailure(assertSort1(sortFunction));
      assertNoFatalFailure(assertSort2(sortFunction));
      assertNoFatalFailure(assertSort5(sortFunction));
      assertNoFatalFailure(assertSort300(sortFunction));
    }
};

testF(SortingTest, bubbleSort) {
  assertSort(bubbleSort<uint16_t>);
}

testF(SortingTest, insertionSort) {
  assertSort(insertionSort<uint16_t>);
}

testF(SortingTest, shellSortClassic) {
  assertSort(shellSortClassic<uint16_t>);
}

testF(SortingTest, shellSortKnuth) {
  assertSort(shellSortKnuth<uint16_t>);
}

testF(SortingTest, shellSortTokuda) {
  assertSort(shellSortTokuda<uint16_t>);
}

testF(SortingTest, combSort13) {
  assertSort(combSort13<uint16_t>);
}

testF(SortingTest, combSort125) {
  assertSort(combSort125<uint16_t>);
}

testF(SortingTest, quickSortMiddle) {
  assertSort(quickSortMiddle<uint16_t>);
}

testF(SortingTest, quickSortMedian) {
  assertSort(quickSortMedian<uint16_t>);
}

testF(SortingTest, quickSortMedianSwapped) {
  assertSort(quickSortMedianSwapped<uint16_t>);
}

//----------------------------------------------------------------------------
// setup() and loop()
//----------------------------------------------------------------------------

void setup() {
#ifndef EPOXY_DUINO
  delay(1000); // wait for stability on some boards to prevent garbage Serial
#endif
  SERIAL_PORT_MONITOR.begin(115200);
  while (!SERIAL_PORT_MONITOR); // for the Arduino Leonardo/Micro only
}

void loop() {
  aunit::TestRunner::run();
}
