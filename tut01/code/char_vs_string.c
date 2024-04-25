#include <stdio.h>

int main() {
    //(1)
    // demonstrate that char and (a single character)
    // string are two different things
    char c = 'c';
    char* s = "c";

    printf("c: %c\n", c);
    printf("s: %s\n", s);

    // // (2)
    // // show that the the first byte of the char pointer s was 
    // // assigned to the char c

    // c = s;  // equal to c = "c"; would not do the intended thing
    // printf("c: %c\n", c);
    
    // printf("s: %p\n", s);
    // printf("c: %x = %hhu\n", c&0xff, c);

}