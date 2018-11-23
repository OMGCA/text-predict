/* Data Structure & Algorithms(ELE00007I) program code
*  Examination number:¡¡Y3834764
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "hashTable.h"
#include "stack.h"

#define DIC_CAPACITY 30000
#define MAXWORDLENGTH 128

/*Structure wordDic is used to convert the text file into the form of lists*/
struct wordDic
{
    int capacity;//The capacity of a single wordDic
    int numWords;//Actual number of words held in the struct
    char* words[DIC_CAPACITY];//Arrays of strings that contains the content of the word.
};

/*wordDic Constructor*/
struct wordDic* wordDicConstructor()
{
    struct wordDic* dic;

    dic = malloc(sizeof(struct wordDic));
    int counter = 0;
    for ( counter = 0; counter < DIC_CAPACITY; counter++ )
    {
        dic->words[counter] = (char*)malloc(MAXWORDLENGTH+1);
    }

    dic->capacity = DIC_CAPACITY;
    dic->numWords = 0;

    return dic;
}

/*wordDic Destructor*/
void wordDicDestructor(struct wordDic* dic)
{
    free(dic->words);
    free(dic);
}

/*Adding word to the structure*/
void wordAddToDic(struct wordDic* dic, char* word)
{
    dic->words[dic->numWords] = word;
    dic->numWords++;//Update the number of words
}

/*Display the dictionary*/
void dicDisplay(struct wordDic* dic)
{
    int counter = 0;
    while( counter < dic->numWords )
    {
        printf("%s\n", dic->words[counter]);
        counter++;
    }
}

/*Import a text file into the dictionary structure*/
void importTextFile(struct wordDic* dic, char* filename)
{

	FILE* fp;
	char line[128];
	char* tmp = malloc(128*sizeof(char));

	fp = fopen(filename, "r");

	if(fp == NULL){
		printf("File Not Found.\n");
		return;
	}

	while ( fgets(line, sizeof(line), fp) ) //Scan the text file line by line
    	{
        	strcpy(tmp,line);
        	wordAddToDic(dic, strdup(tmp));
	}

	fclose(fp);
}

void swap(char** a, char** b)
{
    char* c = *a;
    *a = *b;
    *b = c;
}

/*Quick Sort Algorithm*/
int partition(struct wordDic* dic, int low, int high)
{
    int pivotPoint = low;
    char* pivot = dic->words[low];

    int i = low + 1;
    for ( i = low + 1; i <= high; i++ )
    {
        if ( strcmp(dic->words[i],  pivot)<=0 )
        {
            pivotPoint++;
            swap(&dic->words[i], &dic->words[pivotPoint]);
        }
    }
    swap(&dic->words[low],&dic->words[pivotPoint]);
    return pivotPoint;
}

void quickSort(struct wordDic* dic, int low, int high)
{
    int pivotPoint;
    if ( high > low )
    {
        pivotPoint = partition(dic, low, high);
        quickSort(dic, low, pivotPoint-1);
        quickSort(dic, pivotPoint+1, high);
    }
}

void entryPoint(struct wordDic* dic)
{
    int low = 0;
    int high = dic->numWords - 1;
    quickSort(dic,low,high);
}

/*Classify the dictionary by convert the sorted list into the hash table structure*/
void list2HashTable(struct wordDic* dic, struct HashTable* hashTable)
{
    int counter = 0;
    for ( counter = 0; counter < dic->numWords; counter++ )
    {
        insert(hashTable, dic->words[counter]);
    }
}

/*Compare char variables*/
int lettercmp ( char a, char b )
{
    if ( a < b )
    {
        return -1;
    }
    else if ( a == b )
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/*Return the minimum value of the two arguments*/
int mincmp( int a, int b )
{
    if ( a < b )
        return a;
    else
        return b;
}

/*Only compare part of string*/
/*e.g: while comparing "account" and "acco"*/
/*The function will only compare the first 4 letters*/
/*Thus return 0*/
int strparcmp ( char* a, char* b )
{
    int counter = 0;
    int i = 0;
    int lenA = strlen(a);
    int lenB = strlen(b);
    int minim = mincmp(lenA, lenB);

    while ( counter < minim && i == 0 )
    {
        i = lettercmp(a[counter], b[counter]);
        counter++;
    }
    return i;

}

/*Search through a given bucket in the hash table, push all the positive results into the stack*/
void linearSearch(struct HashTable* hashTable, struct resultStack* stack, char* target, int index)
{
    struct HashWordElement* tmpWord;

    index = int2ASCII(index);

    tmpWord = ElementRetrieve(hashTable, index);
    while(NextRetrieve(tmpWord) != NULL)
    {
        if ( strparcmp(ContentRetrieve(tmpWord), target) == 0 && strlen(ContentRetrieve(tmpWord)) >= strlen(target) )
        {
            StackElementPush(stack, ContentRetrieve(tmpWord));
            tmpWord = NextRetrieve(tmpWord);
        }
        else
            tmpWord = NextRetrieve(tmpWord);
    }

    if ( strparcmp(ContentRetrieve(tmpWord), target) == 0 )
    {
        StackElementPush(stack, ContentRetrieve(tmpWord));
        tmpWord = NextRetrieve(tmpWord);
    }
    else
        tmpWord = NextRetrieve(tmpWord);

    HashWordElementDestructor(tmpWord);
}

void binarySearch(struct HashTable* hashTable, struct resultStack* stack, char* target, int index)
{
    int low = 0;
    int slotSize = 1;
    index = int2ASCII(index);
    struct HashWordElement* tmpWord = ElementRetrieve(hashTable, index);
    //struct wordDic* tmpContainer = wordDicConstructor();
    while(NextRetrieve(tmpWord)!= NULL)
    {
        slotSize++;
        tmpWord = NextRetrieve(tmpWord);
    }
    int high = slotSize - 1;
    int mid;
    int found = 0;
   
    while ( low <= high && found == 0 )
    {
        mid = (low+high)/2;
        struct HashWordElement* matchTarget = SpecificElementRetrieve(hashTable, index, mid);
        if ( strparcmp(matchTarget, target) == 0 )
        {
            while ( strparcmp(ContentRetrieve(PrevRetrieve(matchTarget)), target) == 0 )
            {
                matchTarget = PrevRetrieve(matchTarget);
            }

            while ( strparcmp(ContentRetrieve(NextRetrieve(matchTarget)), target) == 0 )
            {
                StackElementPush(stack, ContentRetrieve(matchTarget));
                matchTarget = NextRetrieve(matchTarget);
            }
            StackElementPush(stack, ContentRetrieve(matchTarget));
            
            /*Force terminate loop*/
            found = 1;
        }

        else if ( strparcmp(matchTarget, target) < 0 )
        {
            low = mid + 1;
        }

        else
        {
            high = mid - 1;
        }
    
    }
}

void selectWord(struct resultStack* stack)
{
    int keyPress;
    int index = 0;
    char* wordToDisplay = StackElementRetrieve(stack, index);
    int refreshLength = strlen(wordToDisplay);
    int limit = StackNumberOfWordsRetrieve(stack);
    int counter = 0;

    printf("\nSelect the word:\n");
    getch();
    keyPress = getch();      

    while( keyPress != 13 )//When user didn't press enter
    {
        refreshLength = strlen(wordToDisplay);

        /*Action performed when press <-- and -->*/
        if ( keyPress == 77 && index != limit - 1 ) 
            index++;
        else if ( keyPress == 75 && index != 0 )
            index--;
            
        wordToDisplay = StackElementRetrieve(stack, index);

        /*Refresh the console*/
        printf("\r");
        for ( counter = 0; counter < refreshLength; counter++ )
        {
            printf(" ");
        }
        printf("\r");
        printf("%s", wordToDisplay);
        keyPress = getch();//Get the user's key press again
    }


}
