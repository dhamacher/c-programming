//
// Created by dahamacher on 4/3/2021.
//
#include "stacks.h"

struct stack
{
    int size;
    int *stack[100];
};

struct stack create_stack()
{
    int stack[100];
    int *stack_point[100];
    *stack_point = &stack;
    struct stack obj = { 0, stack_point };

    return obj;
}

int is_empty(struct stack *obj)
{
    if ((*obj).size == 0)
        return 1;
    else
        return 0;
}

int pop(struct stack *obj)
{
    int index;
    index = (*obj).size;
    index--;
    (*obj).size = index;
    int value;
    value = (*obj).stack[index];
    return value;
}

//int push(struct stack *obj, int value)