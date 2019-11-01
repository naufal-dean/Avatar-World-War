/*** ADT Mesin Kata ***/

#ifndef MESINKATA_H
#define MESINKATA_H

#include "boolean.h"
#include "mesinkar.h"
#include "kata.h"

#define NMax 50
#define BLANK ' '

/* State Mesin Kata */
extern boolean EndKata;
extern Kata CKata;

void IgnoreBlank();
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang
   F.S. : CC ≠ BLANK atau CC = MARK */

void STARTKATA(char * path);
/* I.S. : CC sembarang
   F.S. : EndKata = true, dan CC = MARK;
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */

void ADVKATA();
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi,
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.
   Proses : Akuisisi kata menggunakan procedure AkuisisiKata */

void AkuisisiKata();
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi;
          CC = BLANK atau CC = MARK;
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */

/*** Kelompok input stdin ***/
void ScanInt(int * input);
/* Membaca integer dari keyboard memakai mesinkar. */
/* I.S. input sembarang */
/* F.S. nilai input sesuai masukan pengguna */

void ScanChar(char * input);
/* Membaca char dari keyboard memakai mesinkar. */
/* I.S. input sembarang */
/* F.S. nilai input sesuai masukan pengguna */

void ScanKata(Kata * input);
/* Membaca Kata dari keyboard memakai mesinkar. */
/* I.S. input sembarang */
/* F.S. nilai input sesuai masukan pengguna */

#endif // MESINKATA_H
