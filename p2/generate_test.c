#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define N 100


int main(){
    int r;
    FILE *fptr;
    fptr = fopen("test.txt","w");
    srand(time(NULL));

    if(fptr == NULL)
    {
        printf("Error!");   
        exit(1);             
    }

    for (size_t i = 0; i < N; i++)
    {
        r = rand()%1000;
        fprintf(fptr, "%d\n", r);
    }

    fclose(fptr);
    return 0;
}