# Changelog

* Unreleased
    * Add Selection Sort, mostly for completeness. It's another `O(N^2)` sort
      but is slower than Insertion Sort, and is not a stable sort.
    * Add [examples/HelloSort](examples/HelloSort).
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
