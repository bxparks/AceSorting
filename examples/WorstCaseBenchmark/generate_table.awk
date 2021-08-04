#!/usr/bin/gawk -f
#
# Usage: process_benchmarks.awk < ${board}.txt
#
# Takes the *.txt file generated by AutoBenchmark.ino and basically does
# a GROUP BY operation on (name, dataSize). Then prints the result in the
# same order as the original 'name'.

BEGIN {
  # Set to 1 when 'SIZEOF' is detected
  collect_sizeof = 0

  # Set to 1 when 'BENCHMARKS' is detected
  collect_benchmarks = 0
}

/^SIZEOF/ {
  collect_sizeof = 1
  collect_benchmarks = 0
  sizeof_index = 0
  next
}

/^BENCHMARKS/ {
  collect_sizeof = 0
  collect_benchmarks = 1
  benchmark_index = 0
  next
}

!/^END/ {
  if (collect_sizeof) {
    s[sizeof_index] = $0
    sizeof_index++
  }
  if (collect_benchmarks) {
    u[benchmark_index]["name"] = $1
    u[benchmark_index]["dataSize"] = $2
    u[benchmark_index]["random"] = $3
    u[benchmark_index]["sorted"] = $4
    u[benchmark_index]["reversed"] = $5
    u[benchmark_index]["samples"] = $6
    benchmark_index++
  }
}

END {
  TOTAL_BENCHMARKS = benchmark_index
  TOTAL_SIZEOF = sizeof_index

  printf("+-----------------------------+------+---------+---------+----------+\n")
  printf("| Function                    |    N |  random |  sorted | reversed |\n")

  for (i = 0; i < TOTAL_BENCHMARKS; i++) {
    name = u[i]["name"]
    if (name ~ /^bubbleSort\(\)/ \
        || name ~ /^shellSortClassic\(\)/ \
        || name ~ /^combSort13\(\)/ \
        || name ~ /^quickSortMiddle\(\)/ \
        || name ~ /^qsort\(\)/ \
    ) {
      printf("|-----------------------------+------+---------+---------+----------|\n")
    }

    printf("| %-27s | %4d | %7.3f | %7.3f |  %7.3f |\n",
      name,
      u[i]["dataSize"],
      u[i]["random"],
      u[i]["sorted"],
      u[i]["reversed"]);
  }
  printf("+-----------------------------+------+---------+---------+----------+\n")
}
