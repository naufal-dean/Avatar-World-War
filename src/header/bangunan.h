/*** ADT Bangunan ***/

#ifndef BANGUNAN_H
#define BANGUNAN_H

#include "boolean.h"
#include "point.h"

typedef struct {
    int Kepemilikan;    // Pemain yang memiliki bangunan, 0 jika tidak dimiliki siapapun
    int N;              // Jumlah pasukan
    int Level;          // Level bangunan, 1-4
    int A;              // Nilai penambahan pasukan
    int M;              // Maksimum penambahan pasukan
    boolean P;          // Pertahanan
    int U;              // Pasukan awal
} Properti;
typedef struct {
  	char Tipe;
    Point Lokasi;
    Properti Prop;
} Bangunan;

/*** Selektor ***/
#define Tipe(B) (B).Tipe
#define Lokasi(B) (B).Lokasi
#define Pemilik(B) (B).Prop.Kepemilikan
#define Pasukan(B) (B).Prop.N
#define Level(B) (B).Prop.Level
#define Penambahan(B) (B).Prop.A
#define Maksimum(B) (B).Prop.M
#define Pertahanan(B) (B).Prop.P
#define PAwal(B) (B).Prop.U

/* DEFINISI PROTOTIPE PRIMITIF */
/*** Konstruktor ***/
Bangunan MakeBangunan (char T, Point L);
/* Membentuk sebuah Bangunan dari komponen-komponennya */
/* Bangunan yang terbentuk memiliki level 1 */

/*** Kelompok interaksi dengan I/O device, BACA / TULIS ***/
void BacaBangunan (Bangunan * B);
/* Membaca nilai komponen Bangunan dari input device dan membentuk
   Bangunan B */
/* Komponen dibaca dalam 1 baris, dipisahkan 1 buah spasi */
/* Contoh: C 1 3
   akan membentuk Bangunan <'C',(1,3)> */
/* I.S. Sembarang */
/* F.S. B terdefinisi */
void TulisBangunan (Bangunan B);
/* Nilai B ditulis ke layar dengan format "Tipe (Lokasi)"
   tanpa spasi, enter, atau karakter lain di depan, belakang,
   atau di antaranya. */
/* Contoh: <'C',(1,3)> ditulis "Castle (1,3)"*/
/* I.S. B terdefinisi */
/* F.S. B tertulis di layar dengan format "Tipe (Lokasi)" */

/*** Kelompok operasi relasional terhadap Bangunan ***/
boolean EQBangunan (Bangunan B1, Bangunan B2);
/* Mengirimkan true jika Tipe dan Lokasi B1 sama dengan B2 */

/*** Kelompok Mekanisme Game ***/
void UpgradeLevel(Bangunan * B);
/* Meningkatkan level Bangunan B */
/* I.S. B terdefinisi */
/* F.S. Jika terdapat M / 2 pasukan dan level < 4, level B naik satu tingkat
   dan pasukan berkurang sebanyak M / 2.
   Jika tidak, B tetap dan menuliskan pesan gagal */
void AssignProperti(Bangunan * B);
/* Melakukan assignment properti Bangunan B sesuai tabel pada spesifikasi */
/* I.S. B terdefinisi, mungkin properti belum terdefinisi */
/* F.S. Properti B terdefinisi */
void AssignPropertiHelper(Bangunan * B, int A, int M, boolean P);
/* Assign nilai A, M, P, ke B */
/* I.S. B terdefinisi */
/* F.S. Properti A, M, P diassign ke B */

#endif // BANGUNAN_H
