/**
 * Driver.c
 *
 * Schedule is in the format
 *
 *  [name] [priority] [CPU burst]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "access.h"
#include "list.h"
#include "schedulers.h"

#define SIZE    100

int main(int argc, char *argv[])
{
    FILE *in;
    char *temp;
    char access[SIZE];

    int position;

    in = fopen(argv[1],"r");
    while (fgets(access,SIZE,in) != NULL) {
        temp = strdup(access);
        position = atoi(strsep(&temp,","));
        add(position);

        free(temp);
    }
    fclose(in);

    // invoke the scheduler
    schedule();

    return 0;
}
