#include <stdio.h>
#include <stdlib.h>

void countsort(int *in, int *out, int k, int sz) {
  int *counts = calloc(sizeof(int), k+1);
  for (int i = 0; i < sz; ++i) {
    counts[in[i]] += 1;
  }
  int out_index = 0;
  for (int i = 0; i < k+1; ++i) {
    for (int j = 0; j < counts[i]; ++j) {
      out[out_index] = i;
      out_index++;
    }
  }
  free(counts);
}

int max(int *arr, int sz) {
  int max = 0;
  for (int i = 0; i < sz; ++i) {
    if (arr[i] > max) {
      max = arr[i];
    }
  }
  return max;
}

#define arrsz(arr) (sizeof(arr)/sizeof(arr[0]))

int main() {
  int arr[] = {6,18,26,4,9,0,1,3,4,2,66,7,5,8,9,2,5,12,34};
  int barr[arrsz(arr)];
  countsort(arr, barr, max(arr, arrsz(arr)), arrsz(arr));
  for (int i = 0; i < arrsz(barr); ++i) {
    printf("%d ", barr[i]);
  }
}
