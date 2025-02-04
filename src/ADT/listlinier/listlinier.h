/*** ADT LIST LINIER ***/
/* List menggunakan representasi fisik pointer */

#ifndef LISTLINIER_H
#define LISTLINIER_H

#include "../../boolean.h"
#include "../bangunan/bangunan.h"

/* Kamus Umum */
#define NilList NULL

typedef int ElTypeList;	// Info elemen list berupa type bentukan "Bangunan"
typedef struct tElmtlist *AddressList;	// Alamat elemen list
typedef struct tElmtlist {
	ElTypeList Info;
	AddressList Next;
} ElmtList;
typedef struct {
	AddressList First;	// Alamat pertama list
} List;

/* Definisi list : */
/* List kosong : First(L) = NilList */
/* Setiap elemen dengan AddressList P dapat diacu Info(P), Next(P) */
/* Elemen terakhir list : jika AddressListnya Last, maka Next(Last)=NilList */

#define Info(P) (P)->Info
#define Next(P) (P)->Next
#define First(L) ((L).First)

/*** PROTOTYPE ***/
/* TEST LIST KOSONG */
boolean IsListEmpty (List L);
/* Mengirim true jika list kosong */

/* PEMBUATAN LIST KOSONG */
void CreateEmptyList (List *L);
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */

/* Manajemen Memori */
AddressList AlokasiElList (ElTypeList X);
/* Mengirimkan AddressList hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka AddressList tidak NilList, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=NilList */
/* Jika alokasi gagal, mengirimkan NilList */
void DealokasiElList (AddressList *P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian AddressList P */

/* PENCARIAN SEBUAH ELEMEN LIST */
AddressList SearchInfo (List L, ElTypeList X);
/* Mencari apakah ada elemen list dengan Info(P)= X */
/* Jika ada, mengirimkan AddressList elemen tersebut. */
/* Jika tidak ada, mengirimkan NilList */

/*** PRIMITIF BERDASARKAN NILAI ***/
/* PENAMBAHAN ELEMEN */
void InsVFirst (List *L, ElTypeList X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
void InsVLast (List *L, ElTypeList X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

/* PENGHAPUSAN ELEMEN */
void DelVFirst (List *L, ElTypeList *X);
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai Info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
void DelVLast (List *L, ElTypeList *X);
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai Info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */

/*** PRIMITIF BERDASARKAN ALAMAT ***/
/* PENAMBAHAN ELEMEN BERDASARKAN ALAMAT */
void InsertFirst (List *L, AddressList P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-AddressList P sebagai elemen pertama */
void InsertAfter (List *L, AddressList P, AddressList Prec);
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
void InsertLast (List *L, AddressList P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */

/* PENGHAPUSAN SEBUAH ELEMEN */
void DelFirst (List *L, AddressList *P);
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
void DelP (List *L, ElTypeList X);
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan Info(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika ada lebih dari satu elemen list dengan Info bernilai X */
/* maka yang dihapus hanya elemen pertama dengan Info = X */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
void DelLast (List *L, AddressList *P);
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen terakhir yg lama, */
/* jika ada */
void DelAfter (List *L, AddressList *Pdel, AddressList Prec);
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */

/*** PROSES SEMUA ELEMEN LIST ***/
void PrintInfo (List L);
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
int NbElmtList (List L);
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */

/*** PROSES TERHADAP LIST ***/
void Konkat1 (List *L1, List *L2, List *L3);
/* I.S. L1 dan L2 sembarang */
/* F.S. L1 dan L2 kosong, L3 adalah hasil konkatenasi L1 & L2 */
/* Konkatenasi dua buah list : L1 dan L2    */
/* menghasilkan L3 yang baru (dengan elemen list L1 dan L2) */
/* dan L1 serta L2 menjadi list kosong.*/
/* Tidak ada alokasi/dealokasi pada prosedur ini */

/*** Kelompok operasi lain ***/
void CopyList(List * Lout, List Lin);
/* Melakukan penyalinan Lin ke Lout */
/* I.S. Lin terdefinisi, Lout sembarang */
/* F.S. Semua elemen yang terdefinisi di Lout sama dengan Lin */

#endif // LISTLINIER_H
