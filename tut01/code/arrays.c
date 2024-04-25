#include <stdio.h>
#include <string.h>

int main() {
    // (1)
    // demonstrate a out of bounds access
    int wrong_access_arr[5] = {1, 2, 3, 4, 5};
    printf("wrong_access_arr[5]: %d\n", wrong_access_arr[5]);

    // // (2)
    // // demonstrate the difference between arrays and pointers
    // // (and that there is none)
    // int arr[5] = {1, 2, 3, 4, 5};
    // int *ptr = arr;
    // printf("arr:\t %p\n", arr);
    // printf("ptr:\t %p\n", ptr);
    // printf("&arr[0]: %p\n", &arr[0]);


    // // (3)
    // // demonstrate pointer arithmetic
    // printf("\n\n");
    // printf("arr+1:\t %p\n", arr+1);
    // printf("ptr+1:\t %p\n", ptr+1);
    // printf("&arr[1]: %p\n", &arr[1]);

    // // (4)
    // // demonstrate the relenvance of the type for pointer arithmetic
    // printf("\n\n");
    // printf("arr:\t\t %p\n", arr);
    // printf("(char *)arr+1:\t %p\n", (char *)arr+1);
    // printf("(short *)arr+1:\t %p\n", (short *)arr+1);
    // printf("(int *)arr+1:\t %p\n", (int *)arr+1);
    // printf("(int **)arr+1:\t %p\n", (int **)arr+1);
    // printf("&arr[1]:\t %p\n", &arr[1]);

    // // (5)
    // // demonstrate that you should never forget
    // // to allocate memory for the null terminator
    // printf("\n\n");
    // struct {
    //     char str[5];
    //     char next_str[31];
    // } s;
    
    // strncpy(s.str, "hello", 5);
    // strncpy(s.next_str, " (wupps) you shouldnt see this", 31); 
    // printf("str: %s\n", s.str);

}