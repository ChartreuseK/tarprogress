/**
* Usage: tar <tar options and such> --checkpoint-action=echo='%T' 2>&1 >/dev/null| ./prog <total size>
*
* Sample Output:
* $ tar cf test.tar --checkpoint=100 --checkpoint-action=echo="%T" debian-8.7.1-amd64-netinst.iso 2>&1 >/dev/null| ./prog 260046848
248MiB [360MiB/s] [########################################################### ]  99%
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Width to draw the line at (TODO: read terminal width)
#define WIDTH 80
// Width to draw the actual progress bar [####   ]
#define PROGWID (WIDTH - 20)

int main(int argc, char **argv)
{
    if (argc < 2) 
    {
        fprintf(stderr, "usage: %s <total size>\n", argv[0]);
        return -1;
    }
    long size = atol(argv[1]);
    long bytes;

    // Woo magic numbers, probably fix these later
    char niceBytes[256];
    char niceTrans[256];
    char line[256];

    while(fgets(line, 256, stdin) != NULL)
    {
        // Line looks something like:
        // tar: W: 255989760 (245MiB, 575MiB/s)
        // Or possibly tar: R: 10240 (10KiB, 19MiB/s),W: 0 (0B, 0B/s),D: 10240
        // See: https://www.gnu.org/software/tar/manual/html_section/tar_26.html
        sscanf(line, "%*s %*s %ld (%[^,], %[^)])", &bytes, niceBytes, niceTrans);     
    
        long perc = (bytes * 100)/size;
        long prog = (bytes * PROGWID)/size;

        // Show transferred size and rate
        printf("\r%s [%s] [", niceBytes, niceTrans);
        // Draw a progress bar
        int i;
        for (i = 0; i < prog; i++)
            putchar('#');
        for (; i < PROGWID; i++)
            putchar(' ');
        putchar(']');
        // Show percent at end
        printf(" %3d%%", perc);
    }

    return 0;
}
    

