/* Data Structure & Algorithms(ELE00007I) program code
*  Examination number:¡¡Y3834764
*/
struct resultStack;

struct resultStack* StackConstructor();

void StackDestructor(struct resultStack* stack);

int StackIsEmpty(struct resultStack* stack);

int StackIsFull(struct resultStack* stack);

void StackElementPush(struct resultStack* stack, char* word);

char* StackElementPop(struct resultStack* stack);

void StackDisplay(struct resultStack* stack);

char* StackElementRetrieve(struct resultStack* stack, int index);

int StackNumberOfWordsRetrieve(struct resultStack* stack);