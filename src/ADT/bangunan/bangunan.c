#include <stdio.h>
#include "bangunan.h"

/*** Konstruktor ***/
Bangunan MakeBangunan (int ID, char Tipe, Point Lokasi) {
/* Membentuk sebuah Bangunan dari komponen-komponennya */
/* Bangunan yang terbentuk memiliki level 1 dan tidak dimiliki siapapun */
    // Kamus lokal
    Bangunan B;
    // Algoritma
    // Properti masukan
    ID(B) = ID;
    Tipe(B) = Tipe;
    CopyPoint(&Lokasi(B), Lokasi);
    // Properti default
    Pemilik(B) = 0;
    Level(B) = 1;
    AssignProperti(&B);
    SudahSerang(B) = 0;
    return (B);
}

/*** Kelompok interaksi dengan I/O device, BACA / TULIS ***/
void BacaBangunan (Bangunan * B, int ID) {
/* Membaca nilai komponen Bangunan dari input device dan membentuk
Bangunan B */
/* Komponen dibaca dalam 1 baris, dipisahkan 1 buah spasi */
/* Contoh: C 1 3
akan membentuk Bangunan <'C',(1,3)> */
/* I.S. Sembarang */
/* F.S. B terdefinisi */
    // Kamus lokal
    int X, Y;
    char Tipe;
    // Algoritma
    scanf(" %c %d %d", &Tipe, &X, &Y);
    CopyBangunan(B, MakeBangunan(ID, Tipe, MakePoint(X, Y)));
}
void TulisBangunan (Bangunan B) {
/* Nilai B ditulis ke layar dengan format "Tipe (Lokasi)"
tanpa spasi, enter, atau karakter lain di depan, belakang,
atau di antaranya. */
/* Contoh: <'C',(1,3)> ditulis "Castle (1,3)"*/
/* I.S. B terdefinisi */
/* F.S. B tertulis di layar dengan format "Tipe (Lokasi)" */
    // Algoritma
    switch (Tipe(B)) {
      case 'C':
          printf("Castle ");
          break;
      case 'T':
          printf("Tower ");
          break;
      case 'F':
          printf("Fort ");
          break;
      case 'V':
          printf("Village ");
          break;
      default:
          printf("Undefined ");
          break;
    }
    TulisPoint(Lokasi(B));
    printf(" %d lv. %d", Pasukan(B), Level(B));
}

/*** Kelompok operasi relasional terhadap Bangunan ***/
boolean EQBangunan (Bangunan B1, Bangunan B2) {
/* Mengirimkan true jika Tipe dan Lokasi B1 sama dengan B2 */
    return (ID(B1) == ID(B2));
}

/*** Kelompok Mekanisme Game ***/
void UpgradeLevel(Bangunan * B) {
/* Meningkatkan level Bangunan B */
/* I.S. B terdefinisi */
/* F.S. Jika terdapat M / 2 pasukan dan level < 4, level B naik satu tingkat
   dan pasukan berkurang sebanyak M / 2.
   Jika tidak, B tetap dan menuliskan pesan gagal */
    // Algoritma
    if (Level(*B) < 4) {
        if (Pasukan(*B) >= (Maksimum(*B) / 2)) {
            Pasukan(*B) -= Maksimum(*B) / 2;
            Level(*B)++;
            AssignProperti(B);
        } else { // Pasukan(*B) < (Maksimum(*B) / 2)
            printf("Jumlah pasukan tidak cukup\n");
        }
    } else { // Level(*B) >= 4
        printf("Level bangunan sudah maksimum\n");
    }
}
void AssignProperti(Bangunan * B) {
/* Melakukan assignment properti Bangunan B sesuai tabel pada spesifikasi
   memakai fungsi AssignPropertiHelper */
/* I.S. B terdefinisi */
/* F.S. Properti B terdefinisi */
    // Algoritma
    switch (Tipe(*B)) {
      case 'C':
          switch (Level(*B)) {
            case 1:
                AssignPropertiHelper(B, 10, 40, false);
                Pasukan(*B) = 40;
                break;
            case 2:
                AssignPropertiHelper(B, 15, 60, false);
                break;
            case 3:
                AssignPropertiHelper(B, 20, 80, false);
                break;
            case 4:
                AssignPropertiHelper(B, 25, 100, false);
                break;
          }
          break;
      case 'T':
          switch (Level(*B)) {
            case 1:
                AssignPropertiHelper(B, 5, 20, true);
                Pasukan(*B) = 30;
                break;
            case 2:
                AssignPropertiHelper(B, 10, 30, true);
                break;
            case 3:
                AssignPropertiHelper(B, 20, 40, true);
                break;
            case 4:
                AssignPropertiHelper(B, 30, 50, true);
                break;
          }
          break;
      case 'F':
          switch (Level(*B)) {
            case 1:
                AssignPropertiHelper(B, 10, 20, false);
                Pasukan(*B) = 80;
                break;
            case 2:
                AssignPropertiHelper(B, 20, 40, false);
                break;
            case 3:
                AssignPropertiHelper(B, 30, 60, true);
                break;
            case 4:
                AssignPropertiHelper(B, 40, 80, true);
                break;
          }
          break;
      case 'V':
          switch (Level(*B)) {
            case 1:
                AssignPropertiHelper(B, 5, 20, false);
                Pasukan(*B) = 20;
                break;
            case 2:
                AssignPropertiHelper(B, 10, 30, false);
                break;
            case 3:
                AssignPropertiHelper(B, 15, 40, false);
                break;
            case 4:
                AssignPropertiHelper(B, 20, 50, false);
                break;
          }
          break;
      default:
          AssignPropertiHelper(B, 0, 0, false);
          Pasukan(*B) = 0;
          break;
    }
}
void AssignPropertiHelper(Bangunan * B, int A, int M, boolean P) {
/* Assign nilai A, M, P, ke B */
/* I.S. B terdefinisi */
/* F.S. Properti A, M, P diassign ke B */
    // Algoritma
    Penambahan(*B) = A;
    Maksimum(*B) = M;
    Pertahanan(*B) = P;
}

void TambahPasukan(Bangunan * B, int Pemain) {
/* Menambahkan pasukan pada awal turn */
/* I.S. B terdefinisi */
/* F.S. Jika pasukan pada B < M, maka pasukan akan bertambah sebanyak A (tidak mungkin melebihi M) */
    if (Pemilik(*B) == Pemain) {
        Pasukan(*B) += Penambahan(*B);
        if (Pasukan(*B) > Maksimum(*B)) {
            Pasukan(*B) = Maksimum(*B);
        }
    }
}

/*** Kelompok operasi lain ***/
void CopyBangunan(Bangunan * Bout, Bangunan Bin) {
/* Melakukan penyalinan Bin ke Bout */
/* I.S. Bin terdefinisi, Bout sembarang */
/* F.S. Bout memiliki properti yang sama dengan Bin */
    // Algoritma
    ID(*Bout) = ID(Bin);
    Tipe(*Bout) = Tipe(Bin);
    CopyPoint(&Lokasi(*Bout), Lokasi(Bin));
    Pemilik(*Bout) = Pemilik(Bin);
    Level(*Bout) = Level(Bin);
    SudahSerang(*Bout) = SudahSerang(Bin);
    AssignProperti(Bout);
    Pasukan(*Bout) = Pasukan(Bin);
}
