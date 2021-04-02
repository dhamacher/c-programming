#include <stdio.h>

int main()
{
    int x;
    int *px;

    x = 12;
    px = &x;
    printf("Variable value: %d\nPointer address value: %d\nPointer value: %d\n", x, px, (*px));
    getchar();
}