#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int N;
  printf("Enter value of N [1-10]: ");
  scanf("%d", &N);
  int *arr = (int*) malloc(sizeof(int) * N);
  if (arr == NULL) {
    return 0;
  }

  printf("Enter %d integer number(s)\n", N);
  for (int i = 0; i < N; i++) {
    printf("Enter #%d:", i+1);
    scanf("%d", &arr[i]);
  }

  int sum = 0;
  for (int i = 0; i < N; i++) {
    sum += arr[i];
  }

  printf("Sum: %d\n", sum);
  free(arr);
  return 0;
}
