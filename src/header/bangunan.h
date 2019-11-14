/*** ADT Bangunan ***/

#ifndef BANGUNAN_H
#define BANGUNAN_H

#include "boolean.h"
#include "point.h"

/* Kamus umum */
#define IDUndef 0

/* Definisi elemen dan koleksi objek */
typedef struct {
    int ID;             // ID Bangunan, IDUndef jika undefined
  	char Tipe;
    Point Lokasi;
    int Kepemilikan;    // Pemain yang memiliki bangunan, 0 jika tidak dimiliki siapapun
    int N;              // Jumlah pasukan
    int Level;          // Level bangunan, 1-4
    int A;              // Nilai penambahan pasukan
    int M;              // Maksimum penambahan pasukan
    boolean P;          // Pertahanan
    int U;              // Pasukan awal
    boolean S;          // Apakah bangunan sudah menyerang
} Bangunan;

/*** Selektor ***/
#define ID(B) (B).ID
#define Tipe(B) (B).Tipe
#define Lokasi(B) (B).Lokasi
#define Pemilik(B) (B).Kepemilikan
#define Pasukan(B) (B).N
#define Level(B) (B).Level
#define Penambahan(B) (B).A
#define Maksimum(B) (B).M
#define Pertahanan(B) (B).P
#define PAwal(B) (B).U
#define SudahSerang(B) (B).S

/* DEFINISI PROTOTIPE PRIMITIF */
/*** Konstruktor ***/
Bangunan MakeBangunan (int ID, char Tipe, Point Lokasi);
/* Membentuk sebuah Bangunan dari komponen-komponennya */
/* Bangunan yang terbentuk memiliki level 1 */

/*** Kelompok interaksi dengan I/O device, BACA / TULIS ***/
void BacaBangunan (Bangunan * B, int ID);
/* Membaca nilai komponen Bangunan dari input device dan membentuk
   Bangunan B */
/* Komponen dibaca dalam 1 baris, dipisahkan 1 buah spasi */
/* Contoh: C 1 3
   akan membentuk Bangunan <'C',(1,3)> */
/* I.S. Sembarang */
/* F.S. B terdefinisi */
void TulisBangunan (Bangunan B);
/* Nilai B ditulis ke layar dengan format "Tipe (Lokasi) Pasukan Level"
   tanpa spasi, enter, atau karakter lain di depan, belakang,
   atau di antaranya. */
/* Contoh: <'C',(1,3), 40, 3> ditulis "Castle (1,3) 40 lv. 3"*/
/* I.S. B terdefinisi */
/* F.S. B tertulis di layar dengan format "Tipe (Lokasi) Pasukan Level" */

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
void TambahPasukan(Bangunan * B, int Pemain);
/* Menambahkan pasukan pada awal turn */
/* I.S. B terdefinisi */
/* F.S. Jika pasukan pada B < M dan B milik Pemain, maka pasukan akan bertambah sebanyak A (tidak mungkin melebihi M) */

/*** Kelompok operasi lain ***/
void CopyBangunan(Bangunan * Bout, Bangunan Bin);
/* Melakukan penyalinan Bin ke Bout */
/* I.S. Bin terdefinisi, Bout sembarang */
/* F.S. Bout memiliki properti yang sama dengan Bin */

#endif // BANGUNAN_H
