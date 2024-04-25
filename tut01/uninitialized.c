#include <stdio.h>

typedef struct mystruct {
    int zahl1;
    int zahl2;
    int zahl3;
} mystruct;

int main() {
    // (1)
    // demonstrate that uninitialized variables
    // can have any value
    int i;
    printf("i: %d\n", i);
    int j;
    printf("j: %d\n", j);
    int k;
    printf("k: %d\n", k);

    // (2)
    // // demonstrate that uninitialized pointers
    // // can have any value
    // mystruct *ptr;
    // printf("ptr: %p\n", ptr);
    // printf("ptr->zahl1: %d\n", ptr->zahl1);
    // printf("ptr->zahl2: %d\n", ptr->zahl2);
    // printf("ptr->zahl3: %d\n", ptr->zahl3);

    // (3)
    // // better, use NULL for uninitialized pointers
    // mystruct *ptr2 = NULL;
    // printf("ptr2: %p\n", ptr2);

    // // atleast our attempt to access the members
    // // will crash the program now
    // printf("ptr2->zahl1: %d\n", ptr2->zahl1);
    // printf("ptr2->zahl2: %d\n", ptr2->zahl2);
    // printf("ptr2->zahl3: %d\n", ptr2->zahl3);
}