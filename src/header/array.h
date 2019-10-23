/*** ADT Array Implisit ***/
/* Elemennya berupa type bentukan "Bangunan" */
/* Elemen selalu rata kiri */
/* Memori tabel dinamik dan jumlah elemen didefinisikan secara implisit */

#ifndef ARRAY_H
#define ARRAY_H

#include "boolean.h"
#include "bangunan.h"
#include "point.h"

/* Kamus Umum */
#define IdxMin 1          // Indeks minimum array
#define IdxUndef -999     // Indeks tak terdefinisi
#define ValUndefTab MakeBangunan('#', MakePoint(0, 0))
// Nilai elemen tak terdefinisi

/* Definisi elemen dan koleksi objek */
typedef int IdxType;      // type indeks
typedef Bangunan ElTypeTab;  // type elemen tabel
typedef struct {
    ElTypeTab *TI;           // container elemen
    int MaxEl;            // maksimum elemen
} TabBangunan;
/* Indeks yang digunakan [IdxMin..MaxEl] */
/* Definisi (misal type T TabBangunan):
   Tabel kosong: semua elemen bernilai ValUndef
   Definisi elemen pertama: T.TI[i] dengan i=1
   Definisi elemen terakhir yang terdefinisi:
      T.TI[i] dengan i terbesar sehingga T.TI[i] != ValUndef */

/*** Selektor ***/
#define TI(T) (T).TI
#define Elmt(T, i) (T).TI[(i)]
#define MaxEl(T) (T).MaxEl

/* DEFINISI PROTOTIPE PRIMITIF */
/*** Konstruktor ***/
void MakeEmptyTab(TabBangunan *T, int maxel);
/* I.S. T sembarang dan maxel > 0 */
/* F.S. Jika alokasi berhasil, terbentuk tabel T kosong dengan kapasitas maxel + 1
        Jika gagal, maxel = 0 */
/* Proses: Inisialisasi semua elemen tabel T dengan ValUndef */

void Dealokasi(TabBangunan *T);
/* I.S. T terdefinisi; */
/* F.S. TI(T) dikembalikan ke system, MaxEl(T) = 0; Neff(T) = 0 */

/*** Selektor Tambahan ***/
int NbElmt(TabBangunan T);
/* Mengembalikan nilai elemen efektif tabel, 0 jika tabel kosong */
int MaxElement(TabBangunan T);
/* Mengembalikan jumlah maksimum elemen yang bisa ditampung tabel */
IdxType GetFirstIdxTab(TabBangunan T);
/* Prekondisi: Tabel T tidak kosong */
/* Mengembalikan indeks elemen T pertama */
IdxType GetLastIdxTab(TabBangunan T);
/* Prekondisi: Tabel T tidak kosong */
/* Mengembalikan indeks elemen T terakhir */

/*** Kelompok tes indeks valid ***/
boolean IsIdxTabValid(TabBangunan T, IdxType i);
/* Mengembalikan true jika i adalah indeks yang valid utk ukuran tabel */
/* yaitu antara FirstIdx(T)..maxel*/
boolean IsIdxTabEff(TabBangunan T, IdxType i);
/* Mengembalikan true jika i adalah indeks yang terdefinisi utk tabel */
/* yaitu antara FirstIdx(T)..LastIdx(T) */

/*** Kelompok tes tabel kosong / penuh ***/
boolean IsTabEmpty(TabBangunan T);
/* Mengembalikan true jika tabel T kosong, mengirimkan false jika tidak */
boolean IsTabFull(TabBangunan T);
/* Mengembalikan true jika tabel T penuh, mengirimkan false jika tidak */

/*** Kelompok interaksi dengan I/O device, BACA / TULIS ***/
void BacaIsiTab(TabBangunan *T);
/* Baca isi tab T dari input device */
/* I.S. T sembarang dan sudah dialokasikan sebelumnya */
/* F.S. Tabel T terdefinisi */
/* Proses :
   1. Baca banyak elemen N, validasi N dan terus membaca sampai N valid
   2. Jika N > 0, baca elemen Bangunan sebanyak N kali dengan format
      "Tipe PosisiX PosisiY", contoh "C 1 3", dan assign elemen ke T
      Jika N = 0, terbentuk tabel kosong
*/
void TulisIsiTab(TabBangunan T);
/* Tulis isi Tab T */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong: Tulis sesuai format
   Jika T kosong: Tulis "Tidak terdapat bangunan apapun."*/
/* Proses: Jika T tidak kosong, menuliskan isi T sesuai format.
           Jika T kosong, menuliskan "Tidak terdapat bangunan apapun." */
/* Format:
   1. Tipe(el1) (Lokasi(el1))
   ...
   n. Tipe(eln) (Lokasi(eln))
   NB: Baris pertama tidak diawali enter atau karakter apapun
       Baris terakhir tidak diakhiri enter atau karakter apapun
*/

/*** Kelompok Add dan Del elemen ***/
void AddElTab(TabBangunan *T, ElTypeTab B);
/* Menambahkan B sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. B adalah elemen terakhir T yang baru
        Banyak elemen tabel bertambah satu */
void DelElTab(TabBangunan *T, ElTypeTab *B, IdxType idxDel);
/* Menghapus elemen tabel indeks ke-i */
/* I.S. Tabel tidak kosong, i adalah indeks efektif */
/* F.S. B adalah nilai elemen terakhir T sebelum penghapusan,
        Banyaknya elemen tabel berkurang satu
        Tabel T mungkin menjadi kosong */

#endif // ARRAY_H
