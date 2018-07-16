/* Data Structure & Algorithms(ELE00007I) program code
*  Examination number:¡¡Y3834764
*/
#include <stdio.h>
#include <stdlib.h>

#define MAXWORDLENGTH 128
#define STACKLENGTH 600
struct resultStack
{
    int length;
    int top;
    char* word[STACKLENGTH][MAXWORDLENGTH];
};

struct resultStack* StackConstructor()
{
    struct resultStack* stack;
    stack = malloc(sizeof(struct resultStack));
    stack->word[STACKLENGTH][MAXWORDLENGTH] = malloc(STACKLENGTH*sizeof(char*));

    stack->length = STACKLENGTH;
    stack->top = 0;

    return stack;

}

void StackDestructor(struct resultStack* stack)
{
    free(stack->word);
    free(stack);

    stack = NULL;
}

int StackIsEmpty(struct resultStack* stack)
{
    if ( stack->top == 0 )
        return 1;
    else
        return 0;
}

int StackIsFull(struct resultStack* stack)
{
    if ( stack->top == STACKLENGTH + 1 )
        return 1;
    else
        return 0;
}

void StackElementPush(struct resultStack* stack, char* word)
{
    if (StackIsFull(stack) == 1)
    {
        printf("Stack reaches maximum capacity.\n");
    }
    else
    {
        stack->word[stack->top][128] = word;
        stack->top++;
    }
}

char* StackElementPop(struct resultStack* stack)
{
    if(StackIsEmpty(stack) == 1)
    {
        printf("Stack is empty.\n");
        return "[NoElementFound]";
    }
    else
    {
        stack->top--;;
        return stack->word[stack->top-1];
    }
}

void StackDisplay(struct resultStack* stack)
{
    if ( StackIsEmpty(stack) == 1 )
    {
        printf("No result found.\n");
    }
    else
    {
        int counter = 0;
        for ( counter = 0; counter < stack->top; counter++ )
        {
            printf("%s\n", stack->word[counter][MAXWORDLENGTH]);
        }
    }
}

char* StackElementRetrieve(struct resultStack* stack, int index)
{
    return stack->word[index][MAXWORDLENGTH];
}

int StackNumberOfWordsRetrieve(struct resultStack* stack)
{
    return stack->top;
}
