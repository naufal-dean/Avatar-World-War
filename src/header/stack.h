/* ADT Stack */
/* Tabel dan alamat top disimpan secara eksplisit */
/* Memakai array statik */

#ifndef STACK_H
#define STACK_H

#include "boolean.h"
#include "array.h"
#include "queue.h"

/* Kamus umum */
#define NilStack 0            // Indeks top stack kosong
#define MaxElStack 25         // Max elemen
#define MaxElTabSkill 7       // Max elemen tab skill

/* Definisi elemen dan koleksi objek */
typedef int AddressStack;
typedef int TabSkill[MaxElTabSkill + 1];
typedef struct {
    TabBangunan ListBangunan;   // List Bangunan
    TabSkill SkillActive1;      // List Skill aktif P1
    TabSkill SkillActive2;      // List Skill aktif P2
} ElTypeStack;
typedef struct {
    ElTypeStack T[MaxElStack + 1]; // tabel penyimpan elemen
    AddressStack Top;         // alamat Top: elemen puncak
} Stack;
// Definisi stack S kosong : S.Top = Nil
// Indeks T yang dipakai [1..MaxElStack]

/*** Selektor Stack ***/
#define Top(S) (S).Top
#define InfoTop(S) (S).T[(S).Top]
/*** Selektor ElTypeStack ***/
#define TB(E) (E).ListBangunan
#define TS1(E) (E).SkillActive1
#define ElmtTS1(E, i) ((E).SkillActive1)[(i)]
#define TS2(E) (E).SkillActive2
#define ElmtTS2(E, i) ((E).SkillActive2)[(i)]

/* DEFINISI PROTOTIPE PRIMITIF */
/*** Konstruktor ***/
void MakeEmptyStack (Stack *S);
/* I.S. S sembarang; */
/* F.S. Terbentuk Stack S kosong (Top bernilai NilStack) dengan kapasitas MaxElStack */

/*** Kelompok tes Stack kosong / penuh ***/
boolean IsStackEmpty (Stack S);
/* Mengembalikan true jika Stack S kosong */
boolean IsStackFull (Stack S);
/* Mengembalikan true jika Stack S penuh */

/*** Kelompok Add dan Del elemen ***/
void Push (Stack * S, ElTypeStack X);
/* Menambahkan X sebagai elemen Stack S */
/* I.S. S mungkin kosong, tetapi tidak penuh */
/* F.S. X menjadi Top yang baru, Top bertambah 1 */

void Pop (Stack * S, ElTypeStack * X);
/* Menghapus X dari Stack S */
/* I.S. S tidak mungkin kosong */
/* F.S. X adalah nilai elemen Top terakhir sebelum dihapus, Top berkurang 1 */

/*** Kelompok fungsi pembantu eltypestack ***/
ElTypeStack MakeElTypeStack (TabBangunan T, int S1[], int S2[]);
/* Membentuk ElTypeStack dari komponen-komponennya */

void CopyElTypeStack (ElTypeStack * Eout, ElTypeStack Ein);
/* Melakukan penyalinan Ein ke Eout */
/* I.S. Ein terdefinisi, Eout sembarang */
/* F.S. Eout sama dengan Ein */

/*** Kelompok fungsi pembantu tab skill ***/
void MakeEmptyTabSkill(TabSkill * S);
/* I.S. S sembarang */
/* F.S. Terbentuk tabel S kosong dengan elemen bernilai 0 */
/* Proses: Inisialisasi semua elemen S dengan 0 */
void CopyTabSkill(TabSkill * Sout, TabSkill Sin);
/* Melakukan penyalinan Sin ke Sout */
/* I.S. Sin terdefinisi, Sout sembarang */
/* F.S. Sout sama dengan Sin */

#endif // STACK_H
