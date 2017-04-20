#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 80
#define PROGWID (WIDTH - 20)
int main(int argc, char **argv)
{
    if (argc < 2) 
    {
        fprintf(stderr, "usage: %s <size>\n", argv[0]);
        return -1;
    }
    long size = atol(argv[1]);
    long bytes;
    char niceBytes[256];
    char niceTrans[256];
    char line[256];


    while(fgets(line, 256, stdin) != NULL)
    {
        
    
        sscanf(line, "%*s %*s %ld (%[^,], %[^)])", &bytes, niceBytes, niceTrans);     
    
    
        long perc = (bytes * 100)/size;
        long prog = (bytes * PROGWID)/size;
    
        printf("\r%s [%s] [", niceBytes, niceTrans);
        int i;
        for (i = 0; i < prog; i++)
            putchar('#');
        for (; i < PROGWID; i++)
            putchar(' ');
        putchar(']');
        printf(" %3d%%", perc);
    }

    return 0;
}
    

