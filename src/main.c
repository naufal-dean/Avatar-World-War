#include <stdio.h>
#include "header/point.h"
#include "header/bangunan.h"
#include "header/queue.h"

int main() {
  printf("Hello world\n");
  Bangunan B1, B2;
  B1 = MakeBangunan('C', MakePoint(1,1));
  CopyBangunan(&B2, B1);
  printf("%d\n", Maksimum(B1));
  printf("%d\n", Maksimum(B2));
  UpgradeLevel(&B2);
  AssignProperti(&B2);
  printf("%d\n", Maksimum(B1));
  printf("%d\n", Maksimum(B2));
  TulisBangunan(B1);
  TulisBangunan(B2);
  return 0;
}
