/* Data Structure & Algorithms(ELE00007I) program code
*  Examination number:¡¡Y3834764
*/
struct HashWordElement;

struct HashWordElement* HashWordElementConstructor(char* content);

void HashWordElementDestructor(struct HashWordElement* hashWord);

struct HashTable;

struct HashTable* HashTableConstructor(int numSlots);

void HashTableDestructor(struct HashTable* hashTable);

int hashFunction(struct HashWordElement* hashWord);

int int2ASCII(int i);

void insert(struct HashTable* hashTable, char* word);

int display(struct HashTable* hashTable);

struct HashWordElement* ElementRetrieve(struct HashTable* hashTable, int index);

struct HashWordElement* NextRetrieve(struct HashWordElement* hashWord);

struct HashWordElement* PrevRetrieve(struct HashWordElement* hashWord);

char* ContentRetrieve(struct HashWordElement* hashWord);

struct HashWordElement* SpecificElementRetrieve(struct HashTable* hashTable, int index, int ind);
