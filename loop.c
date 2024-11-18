#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned long long sum_primes(unsigned int limit) {
  bool *is_prime = malloc(limit * sizeof(bool));
  for (unsigned int i = 0; i < limit; i++) {
    is_prime[i] = true;
  }
  is_prime[0] = is_prime[1] = false;

  unsigned long long sum = 0;
  for (unsigned int p = 2; p < limit; p++) {
    if (is_prime[p]) {
      sum += p;
      for (unsigned int multiple = p * 2; multiple < limit; multiple += p) {
        is_prime[multiple] = false;
      }
    }
  }

  free(is_prime);
  return sum;
}

int main() {
  const unsigned int limit = 1000000; // 1 million
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);

  unsigned long long sum = sum_primes(limit);
  clock_gettime(CLOCK_MONOTONIC, &end);

  double time_taken =
      (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

  printf("Sum of primes below %u is: %llu\n", limit, sum);
  printf("Time taken: %.9f seconds\n", time_taken);

  return 0;
}
