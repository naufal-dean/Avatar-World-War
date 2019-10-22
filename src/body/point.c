#include <stdio.h>
#include "../header/point.h"

/*** Konstruktor ***/
Point MakePoint (int X, int Y) {
/* Membentuk sebuah Point dari komponen-komponennya */
    // Kamus lokal
    Point P;
    // Algoritma
    Absis(P) = X;
    Ordinat(P) = Y;
    return (P);
}

/*** Kelompok interaksi dengan I/O device, BACA / TULIS ***/
void BacaPoint (Point * P) {
/* Membaca nilai absis dan ordinat dari keyboard dan membentuk
Point P berdasarkan dari nilai absis dan ordinat tersebut */
/* Komponen X dan Y dibaca dalam 1 baris, dipisahkan 1 buah spasi */
/* Contoh: 1 2
akan membentuk Point <1,2> */
/* I.S. Sembarang */
/* F.S. P terdefinisi */
    // Kamus lokal
    int X, Y;
    // Algoritma
    scanf("%d %d", &X, &Y);
    (*P) = MakePoint(X, Y);
}
void TulisPoint (Point P) {
/* Nilai P ditulis ke layar dengan format "(X,Y)"
tanpa spasi, enter, atau karakter lain di depan, belakang,
atau di antaranya. */
/* I.S. P terdefinisi */
/* F.S. P tertulis di layar dengan format "(X,Y)" */
    // Algoritma
    printf("(%d,%d)", Absis(P), Ordinat(P));
}

/*** Kelompok operasi relasional terhadap Point ***/
boolean EQPoint (Point P1, Point P2) {
/* Mengirimkan true jika Absis dan Ordinat P1 sama dengan P2 */
    // Algoritma
    return ((Absis(P1) == Absis(P2)) && (Ordinat(P1) == Ordinat(P2)));
}
