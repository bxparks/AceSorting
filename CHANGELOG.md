# Changelog

* Unreleased
* v1.0.0 (2021-12-04)
    * Add special case for SparkFun Pro Micro in `examples/AutoBenchmark` whose
      ATmega32U4 has 2.5kB of ram, enough to handle `N=1000`.
    * Fix incorrect C++ header guard in `src/AceSorting.h`.
    * Upgrade tool chain
        * Upgrade Arduino IDE to 1.8.16.
        * Upgrade Arduino CLI to 0.19.2.
        * Upgrade SparkFun SAMD to 1.8.4.
        * Upgrade ESP8266 to 3.0.2.
        * Upgrade TeensyDuino to 1.55.
* v0.3 (2021-08-23)
    * Add 3-argument versions of each sorting function which accepts a lambda
      expression or function pointer that evalutes the general "less-than"
      comparison between 2 elements in the array.
        * Can be used to implement any sorting criteria, e.g. reverse sort, or
          sorting using compound keys.
        * Reimplement 2-argument versions of each sorting function to simply
          call the 3-argument versions using a default "less-than" function
          to give simple ascending order.
        * The `quickSortXxx()` algorithms do not optimize well, probably due
          to the recursive function call, so the 2-argument version is
          duplicated from the 3-argument version.
        * Add `examples/CompoundSortingDemo` to illustrate the 3-argument
          sorting functions to sort by (name, score) pair.
        * No changes observed to flash memory consumption or CPU execution
          times.
* v0.2 (2021-08-06)
    * Add Selection Sort, mostly for completeness. It's another `O(N^2)` sort
      but is slower than Insertion Sort, and is not a stable sort.
    * Add [examples/HelloSorting](examples/HelloSorting).
    * Add **tl;dr** section in README.md to summarize my recommendations.
* v0.1 (2021-08-04)
    * Add `combSort133()` which uses a gap factor of 4/3, which eliminates
      integer division. Smaller and faster on 8-bit processors which don't have
      hardware integer division.
    * Add `combSort13m()` and `combSort133m()` which modifies the gap to 11 when
      equal to 9 and 10.
    * Add `WorstCaseBenchmark` to determine behavior at extremes (already
      sorted, and reversed sorted).
    * Add comparison to C library's builtin `qsort()`. Seems like it's 2-3X
      slower and consumes 4-5X more flash memory than `quickSortXxx()`.
    * Add unit tests.
* Initial checking (2021-08-02)
