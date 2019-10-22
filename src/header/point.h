/*** ADT Point ***/

#ifndef POINT_H
#define POINT_H

#include "boolean.h"

typedef struct {
		int X;		// Absis
		int Y;		// Ordinat
} Point;

/*** Selektor ***/
#define Absis(P) (P).X
#define Ordinat(P) (P).Y

/* DEFINISI PROTOTIPE PRIMITIF */
/*** Konstruktor ***/
Point MakePoint (int X, int Y);
/* Membentuk sebuah Point dari komponen-komponennya */

/*** Kelompok interaksi dengan I/O device, BACA / TULIS ***/
void BacaPoint (Point * P);
/* Membaca nilai absis dan ordinat dari keyboard dan membentuk
   Point P berdasarkan dari nilai absis dan ordinat tersebut */
/* Komponen X dan Y dibaca dalam 1 baris, dipisahkan 1 buah spasi */
/* Contoh: 1 2
   akan membentuk Point <1,2> */
/* I.S. Sembarang */
/* F.S. P terdefinisi */
void TulisPoint (Point P);
/* Nilai P ditulis ke layar dengan format "(X,Y)"
   tanpa spasi, enter, atau karakter lain di depan, belakang,
   atau di antaranya. */
/* I.S. P terdefinisi */
/* F.S. P tertulis di layar dengan format "(X,Y)" */

/*** Kelompok operasi relasional terhadap Point ***/
boolean EQPoint (Point P1, Point P2);
/* Mengirimkan true jika Absis dan Ordinat P1 sama dengan P2 */

#endif // POINT_H
