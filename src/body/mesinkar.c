#include <stdio.h>
#include <errno.h>
#include "../header/mesinkar.h"

char CC;
boolean EOP;
char MARK;

static FILE * pita;
static int retval;

void START(char * path) {
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita atau stdin (sesuai input path)
   posisinya adalah pada jendela.
   I.S. : sembarang
   F.S. : CC adalah karakter pertama pada pita. Jika CC != MARK maka EOP akan padam (false).
          Jika CC = MARK maka EOP akan menyala (true) */

    /* Algoritma */
    errno = 0;
    if (path == NULL) { // Baca dari stdin
        pita = stdin;
        MARK = MARKSTDIN;
    } else { // Baca dari file
        pita = fopen(path,"r");
        MARK = MARKFILE;
    }
    if (pita == NULL) {
        printf("Error number: %d \n", errno);
        if (errno == 2) {
            printf("No such file or directory.\n");
        }
    } else { // Not error
        ADV();
    }

}

void ADV() {
/* Pita dimajukan satu karakter.
   I.S. : Karakter pada jendela =
          CC, CC != MARK
   F.S. : CC adalah karakter berikutnya dari CC yang lama,
          CC mungkin = MARK.
          Jika  CC = MARK maka EOP akan menyala (true) */

    /* Algoritma */
    retval = fscanf(pita,"%c",&CC);
    EOP = (CC == MARK);
    if (EOP) {
        fclose(pita);
    }
}
