#include <cstdio>
#include <ctime>
int main(int argc, char *argv[]) {
  double j = 0;
  clock_t start = clock();
  for (double i = 0; i < 1000000; i++) {
    j += i;
  }

  clock_t end = clock();
  double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
  printf("j is : %lf it took : %lf", j, elapsed);
  return 0;
}
