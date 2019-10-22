#include <stdio.h>
#include "header/point.h"
#include "header/bangunan.h"

int main() {
  printf("Hello world\n");
  Point P;
  Absis(P) = 1;
  Ordinat(P) = 2;
  TulisPoint(P);

  return 0;
}
