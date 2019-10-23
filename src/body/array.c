#include <stdio.h>
#include <stdlib.h>
#include "../header/array.h"

/*** Konstruktor ***/
void MakeEmptyTab(TabBangunan *T, int maxel) {
/* I.S. T sembarang dan maxel > 0 */
/* F.S. Jika alokasi berhasil, terbentuk tabel T kosong dengan kapasitas maxel + 1
        Jika gagal, maxel = 0 */
/* Proses: Inisialisasi semua elemen tabel T dengan ValUndefTab */
    // Kamus lokal
    IdxType i;
    // Algoritma
    // Alokasi memori
    TI(*T) = (ElTypeTab*) malloc ((maxel + 1) * sizeof(ElTypeTab));
    if (TI(*T) == NULL) {
        MaxElTab(*T) = 0;
    } else { // alokasi berhasil
        MaxElTab(*T) = maxel;
    }
    // Inisialisasi elemen dengan ValUndefTab
    for (i = IdxMin; i <= MaxElTab(*T); i++) {
        CopyBangunan(&ElmtTab((*T), i), ValUndefTab);
    }
}

void DealokasiTab(TabBangunan *T) {
/* I.S. T terdefinisi; */
/* F.S. TI(T) dikembalikan ke system, MaxElTab(T) = 0; Neff(T) = 0 */
    // Algoritma
    free(TI(*T));
    MaxElTab(*T) = 0;
}

/*** Selektor Tambahan ***/
int NbElmtTab(TabBangunan T) {
/* Mengembalikan nilai elemen efektif tabel, 0 jika tabel kosong */
    // Kamus lokal
    IdxType i;
    int count = 0;
    // Algoritma
    if (!EQBangunan(ElmtTab(T, GetFirstIdxTab(T)), ValUndefTab)) {
        for (i = GetFirstIdxTab(T); i <= MaxElTab(T); i++) {
            if (!EQBangunan(ElmtTab(T, i), ValUndefTab)) {
                count++;
            }
        }
    }
    return (count);
}
int MaxElementTab(TabBangunan T) {
/* Mengembalikan jumlah maksimum elemen yang bisa ditampung tabel */
	  return (MaxElTab(T));
}
IdxType GetFirstIdxTab(TabBangunan T) {
/* Prekondisi: Tabel T tidak kosong */
/* Mengembalikan indeks elemen T pertama */
    return (IdxMin);
}
IdxType GetLastIdxTab(TabBangunan T) {
/* Prekondisi: Tabel T tidak kosong */
/* Mengembalikan indeks elemen T terakhir */
    return (IdxMin + NbElmtTab(T) - 1);
}

/*** Kelompok tes indeks valid ***/
boolean IsIdxTabValid(TabBangunan T, IdxType i) {
/* Mengembalikan true jika i adalah indeks yang valid utk ukuran tabel */
/* yaitu antara FirstIdx(T)..maxel*/
    return ((i >= GetFirstIdxTab(T)) && (i <= MaxElementTab(T)));
}
boolean IsIdxTabEff(TabBangunan T, IdxType i) {
/* Mengembalikan true jika i adalah indeks yang terdefinisi utk tabel */
/* yaitu antara FirstIdx(T)..LastIdx(T) */
    return ((i >= GetFirstIdxTab(T)) && (i <= GetLastIdxTab(T)));
}

/*** Kelompok tes tabel kosong / penuh ***/
boolean IsTabEmpty(TabBangunan T) {
/* Mengembalikan true jika tabel T kosong, mengirimkan false jika tidak */
    return (NbElmtTab(T) == 0);
}
boolean IsTabFull(TabBangunan T) {
/* Mengembalikan true jika tabel T penuh, mengirimkan false jika tidak */
    return (NbElmtTab(T) == MaxElementTab(T));
}

/*** Kelompok interaksi dengan I/O device, BACA / TULIS ***/
void BacaIsiTab(TabBangunan *T) {
/* Baca isi tab T dari input device */
/* I.S. T sembarang dan sudah dialokasikan sebelumnya */
/* F.S. Tabel T terdefinisi */
/* Proses :
   1. Baca banyak elemen N, validasi N dan terus membaca sampai N valid
   2. Jika N > 0, baca elemen Bangunan sebanyak N kali dengan format
      "Tipe PosisiX PosisiY", contoh "C 1 3", dan assign elemen ke T
      Jika N = 0, terbentuk tabel kosong
*/
    // Kamus lokal
    IdxType i;
    int N, X, Y;
    char Tipe;
    // Algoritma
    do {
      scanf("%d", &N);
    } while(!(N >= 0 && N <= MaxElementTab(*T)));
    // Inisialisasi nilai
    for (i = GetFirstIdxTab(*T); i <= MaxElementTab(*T); i++) {
        CopyBangunan(&ElmtTab((*T), i), ValUndefTab);
    }
    // Baca nilai elemen jika N > 0
    if (N > 0) {
        for (i = GetFirstIdxTab(*T); i <= N; i++) {
            scanf("%c %d %d", &Tipe, &X, &Y);
            ElmtTab(*T, i) = MakeBangunan(Tipe, MakePoint(X, Y));
        }
    }
}
void TulisIsiTab(TabBangunan T) {
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
    // Kamus lokal
    IdxType i;
    // Algoritma
    if (IsTabEmpty(T)) {
        printf("Tidak terdapat bangunan apapun.");
    } else { // Tabel tidak kosong
        for (i = GetFirstIdxTab(T); i < (GetLastIdxTab(T)); i++) {
            printf("%d. ", i);
            TulisBangunan(ElmtTab(T,i));
            printf("\n");
        }
        printf("%d. ", i);
        TulisBangunan(ElmtTab(T,i));
    }
}

/*** Kelompok Add dan Del elemen ***/
void AddElTab(TabBangunan *T, ElTypeTab B) {
/* Menambahkan B sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. B adalah elemen terakhir T yang baru
Banyak elemen tabel bertambah satu */
    // Algoritma
    CopyBangunan(&ElmtTab((*T), (GetLastIdxTab(*T) + 1)), B);
}
void DelElTab(TabBangunan *T, ElTypeTab *B, IdxType idxDel) {
/* Menghapus elemen tabel indeks ke-i */
/* I.S. Tabel tidak kosong, i adalah indeks efektif */
/* F.S. B adalah nilai elemen terakhir T sebelum penghapusan,
        Banyaknya elemen tabel berkurang satu
        Tabel T mungkin menjadi kosong */
/* Proses: Menghapus elemen ke-i dan menggeser elemen di belakangnya agar
           tabel tetap rata kiri */
    // Kamus lokal
    IdxType i;
    // Algoritma
    CopyBangunan(B, ElmtTab((*T), idxDel));
    // Jika yang dihapus bukan elemen terakhir, geser elemen berikutnya di loop
    for (i = idxDel; i < GetLastIdxTab(*T); i++) {
        CopyBangunan(&ElmtTab((*T), i), ElmtTab((*T), i + 1));
    }
    CopyBangunan(&ElmtTab((*T), i), ValUndefTab);
}
