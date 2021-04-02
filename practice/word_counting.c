#include <stdio.h>

#define OUT 0
#define IN 1

struct stats
{
    int nl;
    int nw;
    int nc;
};


int main()
{
    int c, nl, nw, nc, state;
    printf("Start typing:\n");

    state = OUT;
    nl = nw = nc = 0;
    while((c = getchar()) != EOF)
    {
        ++nc;
        if (c == '\n')
            ++nl;
        if (c == ' ' || c == '\t' || c == '\n')
            state = OUT;
        else if (state == OUT) 
        {
            state = IN;
            ++nw;
        }
    }
    struct stats word_count = { nl, nw, nc };
    printf("%d %d %d\n", word_count.nl, word_count.nw, word_count.nc);
    c = getchar();
}