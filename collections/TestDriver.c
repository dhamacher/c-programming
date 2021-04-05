//
// Created by dahamacher on 4/3/2021.
//
#include "stacks.h"


int main()
{
    struct stack my_stack = create_stack(100);
    for(int i = 0; i < 100; i++)
    {
        *stack[i] = 2;
    }
    for(int i = 0; i < 100; i++)
    {
        printf("Element %d has value of %d", i, *stack[i]);
    }
    return 0;

}
