#include <stdio.h>
#include <stdlib.h>

#define MAX_WORD 264
#define MAX_FILE 4096

int main()
{
    FILE *f = NULL;
    char c = 0;
    char filename[MAX_WORD] = "game.cmd";
    char file[MAX_FILE];
    int i = 0;

    f = fopen(filename, "r");
    if (!f)
        return 1;
    for (i = 0; fscanf(f, "%c", &c) != 1; i++)
    {
        if (c == '\r')
        {
            printf("Carro nukeado en %d\n", i);
            c = '\n';
        }
        file[i] = c;
    }
    file[i] = '\n';
    fclose(f);
    f = fopen(filename, "w");
    if (!f)
        return 1;
    fprintf(f, "%s", file);
    fclose(f);
    printf("done.");
    return 0;
}