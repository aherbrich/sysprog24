#include <stdlib.h>

int main(){
    // (1)
    // demonstrate memory leak
    int *meinezahl = malloc(32);
    return 0;

    // // (2)
    // //demonstrate how to do it right
    // int *meinezahl = malloc(sizeof(int));
    // free(meinezahl);
    // return 0;

}