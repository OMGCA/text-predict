/* Data Structure & Algorithms(ELE00007I) program code
*  Examination number:　Y3834764
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "textPred.h"
#include "stack.h"
#include "hashTable.h"

int main()
{
    /*structure and variable initialization*/
    struct wordDic* oriDic = wordDicConstructor();
    struct HashTable* wordHash = HashTableConstructor(3000);
    struct resultStack* stack = StackConstructor();
    char userInput[32];
    int index;

    /*Import, sort and classify*/
    importTextFile(oriDic, "words.txt");//import file into oriDic
    //dicDisplay(oriDic);

    entryPoint(oriDic);//Quick sort the oriDic list
    list2HashTable(oriDic, wordHash);//Classify words in regard to the first letter.

    while ( StackIsEmpty(stack) == 1 )
    {
        printf("Input your text here:");
        fgets(userInput, sizeof(userInput), stdin);//Retrieve user input.
        userInput[strlen(userInput)-1] = NULL; //As fgets reads the "\n", the last char will be set to NULL.
        index = userInput[0];//Get the slot index
        binarySearch(wordHash, stack, userInput, index);//Searching through this slot
        StackDisplay(stack);
        printf("\n");
    }

    selectWord(stack);

    /*Memory freeing*/
    wordDicDestructor(oriDic);
    HashTableDestructor(wordHash);
    StackDestructor(stack);

    return 0;
}

