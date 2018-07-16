struct resultStack;

struct resultStack* StackConstructor();

void StackDestructor(struct resultStack* stack);

int StackIsEmpty(struct resultStack* stack);

int StackIsFull(struct resultStack* stack);

void StackElementPush(struct resultStack* stack, char* word);

char* StackElementPop(struct resultStack* stack);

void StackDisplay(struct resultStack* stack);
