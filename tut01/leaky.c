#include <stdlib.h>
#include <stdio.h>

int main(){
    // (1)
    // demonstrate memory leak
    int *meinezahl = malloc(32);
    printf("%p\n", meinezahl);
    return 0;

    // // (2)
    // //demonstrate how to do it right
    // int *meinezahl = malloc(sizeof(int));
    printf("%p\n", meinezahl);
    // free(meinezahl);
    // return 0;

}