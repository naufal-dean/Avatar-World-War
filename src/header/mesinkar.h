/*** ADT Mesin Karakter ***/

#ifndef MESINKAR_H
#define MESINKAR_H

#include "boolean.h"

#define MARKFILE '.'
#define MARKSTDIN '\n'
/* State Mesin */
extern char CC;
extern boolean EOP;
extern char MARK;

void START(char * path, int * error);
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita atau stdin (sesuai input path)
   posisinya adalah pada jendela.
   I.S. : sembarang
   F.S. : CC adalah karakter pertama pada pita. Jika CC != MARK maka EOP akan padam (false).
          Jika CC = MARK maka EOP akan menyala (true) */

void ADV();
/* Pita dimajukan satu karakter.
   I.S. : Karakter pada jendela = CC, CC != MARK
   F.S. : CC adalah karakter berikutnya dari CC yang lama,
          CC mungkin = MARK
          Jika  CC = MARK maka EOP akan menyala (true) */

#endif // MESINKAR_H
