/* Data Structure & Algorithms(ELE00007I) program code
*  Examination number:¡¡Y3834764
*/
#include "hashTable.h"

struct wordDic;

struct wordDic* wordDicConstructor();

void wordDicDestructor(struct wordDic* dic);

void wordAddToDic(struct wordDic* dic, char* word);

void dicDisplay(struct wordDic* dic);

void importTextFile(struct wordDic* dic, char* filename);

void swap(char** a, char** b);

int partition(struct wordDic* dic, int low, int high);

void quickSort(struct wordDic* dic, int low, int high);

void entryPoint(struct wordDic* dic);

void list2HashTable(struct wordDic* dic, struct HashTable* hashTable);

int lettercmp ( char a, char b );

int mincmp( int a, int b );

int strparcmp ( char* a, char* b );

void linearSearch(struct HashTable* hashTable, struct resultStack* stack, char* target, int index);

void selectWord(struct resultStack* stack);