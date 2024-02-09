#include <stdio.h>

int main() {
  int a = 10;
  int b = 20;

  int *p = &a;

  /* pointer to const int */
  const int *cp = &a;
  /* const pointer to int */
  int * const pc = &a;
  /* const pointer to const int */
  const int * const cpc = &a;

  *p = 11;  // allowed
  *cp = 11; // not allowed 

  *pc = 12; // allowed
  pc = &b;  // not allowed

  cpc = &b; // not allowed
  *cpc = 12; // not allowed
}
