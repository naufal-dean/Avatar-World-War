#ifndef CONSOLE_H
#define CONSOLE_H

#include "boolean.h"
#include "ADT/array/array.h"
#include "ADT/bangunan/bangunan.h"
#include "ADT/graph/graph.h"
#include "ADT/kata/kata.h"
#include "ADT/listlinier/listlinier.h"
#include "ADT/matriks/matriks.h"
#include "ADT/mesinkar/mesinkar.h"
#include "ADT/mesinkata/mesinkata.h"
#include "ADT/point/point.h"
#include "ADT/queue/queue.h"
#include "ADT/stack/stack.h"
#include "ADT/status/status.h"

#include "pcolor.h"
#include "console.h"

/*** Kelompok Fungsi Command ***/
boolean AttackCommand();
/* Melaksanakan command ATTACK */
/* Mengembalikan true jika attack berhasil, dan sebaliknya */
boolean LevelUpCommand();
/* Melaksanakan command LEVEL_UP */
/* Mengembalikan true jika level up berhasil, dan sebaliknya */
boolean SkillCommand();
/* Melaksanakan command SKILL dan membersikhkan undo stack */
/* Mengembalikan true jika pemakaian skill berhasil, dan sebaliknya */
boolean UndoCommand();
/* Melaksanakan command UNDO */
/* Selalu mengembalikan true, karena undo selalu berhasil */
boolean EndTurnCommand();
/* Melaksanakan command END_TURN */
/* Selalu mengembalikan true, karena end turn selalu berhasil */
void SaveCommand();
/* Melaksanakan command SAVE */
/* I.S. GameStatus terdefinisi */
/* F.S. Melakukan proses penyimpanan GameStatus ke path file yang diberikan */
void LoadCommand();
/* Melaksanakan command LOAD */
/* I.S. GameStatus sembarang, file load terdefinisi dan valid */
/* F.S. Melakukan proses loading data pada file load yang diberikan ke GameStatus */
boolean MoveCommand();
/* Melaksanakan command MOVE */
/* Mengembalikan true jika move berhasil, dan sebaliknya */
void HelpCommand();
/* Melaksanakan command HELP */
/* I.S. Kondisi sembarang */
/* F.S. Menampilkan panel bantuan ke layar */
void BuildingsCommand();
/* Melaksanakan command BUILDINGS */
/* I.S. GameStatus terdefinisi */
/* F.S. Menampilkan list Bangunan ke layar */
boolean TroopHack();
/* Menambahkan/mengurangkan jumlah pasukan pada building apapun */
boolean OwnerHack();
/* Mengganti kepemilikan building apapun, semua atribut dari building tersebut (selain pemilik) tetap sama */


#endif // CONSOLE_H
