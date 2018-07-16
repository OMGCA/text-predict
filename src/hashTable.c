/* Data Structure & Algorithms(ELE00007I) program code
*  Examination number:¡¡Y3834764
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "textPred.h"

#define MAXHWORDLENGTH 128
/*This structure only contens certain word and the following element*/
struct HashWordElement
{
    char content[MAXHWORDLENGTH];
    struct HashWordElement* prev;
    struct HashWordElement* next;
};

/*HashWordElement constructor*/
struct HashWordElement* HashWordElementConstructor(char* content)
{
    struct HashWordElement* hashWord;
    hashWord = malloc(sizeof(struct HashWordElement));

    strncpy(hashWord->content, content, MAXHWORDLENGTH);
    hashWord->prev = NULL;
    hashWord->next = NULL;
    
    return hashWord;
}

/*HashWordElement Destructor*/
void HashWordElementDestructor(struct HashWordElement* hashWord)
{
    free(hashWord);
}

struct HashTable
{
    int numSlots;//Number of slots held in the hash table
    int numWords;//Number of words the table acutally contains
    struct HashWordElement** slots;//Each slot is classified by the 26 alphabets, case sensitive
};

struct HashTable* HashTableConstructor(int numSlots)
{
    struct HashTable* hashTable;
    hashTable = malloc(sizeof(struct HashTable));

    hashTable->numSlots = numSlots;
    hashTable->numWords = 0;

    hashTable->slots = malloc(numSlots * sizeof(struct HashWordElement*));
    int counter = 0;
    for ( counter = 0; counter < numSlots; counter++ )
    {
        hashTable->slots[counter] = NULL;
    }

    return hashTable;
}

void HashTableDestructor(struct HashTable* hashTable)
{
    free(hashTable->slots);
    free(hashTable);
}


int hashFunction(struct HashWordElement* hashWord)
{
    int hashValue = hashWord->content[0];
    /*Convert the ASCII value to numerical index*/
    if ( hashValue >= 65 && hashValue <= 90 )
    {
        hashValue = hashValue - 65;
    }
    else if ( hashValue >= 97 && hashValue <= 122 )
    {
        hashValue = hashValue - 71;
    }

    return hashValue;
}

int int2ASCII(int i)
{
    if ( i >= 65 && i <= 90 )
    {
        i= i - 65;
    }

    else if ( i >= 97 && i <= 122 )
    {
        i = i - 71;
    }

    return i;
}

void insert(struct HashTable* hashTable, char* word)
{
    int hashValue = hashFunction(HashWordElementConstructor(word));
    if ( hashTable->slots[hashValue] == NULL )
    {
        hashTable->slots[hashValue] = HashWordElementConstructor(word);
    }
    else
    {
        struct HashWordElement* tmpWord = hashTable->slots[hashValue];

        while(tmpWord->next != NULL )
        {
            tmpWord = tmpWord->next;
        }

        tmpWord->next = HashWordElementConstructor(word);
        tmpWord->next->prev = tmpWord;
    }
    hashTable->numWords++;
}

/*Display the hash table, not used in the program, for debugging only*/
int display(struct HashTable* hashTable)
{
    if ( hashTable->numWords == 0 )
    {
        printf("This Hash Table Is Empty.\n");
        return 0;
    }

    else
    {
        int header = 65;
        int index;
        for ( header = 65; header <= 90; header++ )
        {
            index = int2ASCII(header);
            printf("%c:\n", header);
            if ( hashTable->slots[index] == NULL )
            {
                printf("No words in this catagory.\n");
            }
            else
            {
                struct HashWordElement* tmpWord = hashTable->slots[index];
                printf("%s\n", tmpWord->content);
                while(tmpWord->next != NULL)
                {                   
                    tmpWord = tmpWord->next;
                    printf("%s\n", tmpWord->content);
                }
                
            }                 
        }

        for ( header = 97; header <= 122; header++ )
        {
            index = int2ASCII(header);
            printf("%c:\n", header);
            if ( hashTable->slots[index] == NULL )
            {
                printf("No words in this catagory.\n");
            }
            else
            {
                struct HashWordElement* tmpWord = hashTable->slots[index];
                printf("%s\n", tmpWord->content);
                while(tmpWord->next != NULL)
                {                   
                    tmpWord = tmpWord->next;
                    printf("%s\n", tmpWord->content);
                }
                
            }                 
        }

        return 0;
    }
}

/*Retrieve next element outside this code file*/
struct HashWordElement* NextRetrieve(struct HashWordElement* hashWord)
{
    return hashWord->next;
}

struct HashWordElement* PrevRetrieve(struct HashWordElement* hashWord)
{
    return hashWord->prev;
}

/*Retrieve the content of a hash element outside this code file*/
char* ContentRetrieve(struct HashWordElement* hashWord)
{
    return hashWord->content;
}

/*Retrieve the first element of a certain slot outside this code file*/
struct HashWordElement* ElementRetrieve(struct HashTable* hashTable, int index)
{
    return hashTable->slots[index];
}

/*Retrieve specific element in a bucket*/
struct HashWordElement* SpecificElementRetrieve(struct HashTable* hashTable, int index, int ind)
{
    int i = 0;
    struct HashWordEleemnt* tmpWord = hashTable->slots[index];
    for ( i = 0; i < ind-1; i++ )
    {
        tmpWord = NextRetrieve(tmpWord);
    }
    return tmpWord;
}

