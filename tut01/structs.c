#include <stdio.h>

int main() {
    // (1)
    // show that the size of a struct
    // normally is the sum of the sizes of its members
    struct MyData
    {
        int data1;
        int data2;
        int data3;
    };

    printf("Size of struct MyData: %d\n", sizeof(struct MyData));

    // // (2)
    // // show that the size of a struct
    // // can be larger than the sum of the sizes of its members
    // // due to alignment

    // struct MyData2
    // {
    //     char data1;
    //     int data2;
    //     char data3;
    // };

    // printf("Size of struct MyData2: %d\n", sizeof(struct MyData2));

    // // (3)
    // // show that restructuring the members of a struct
    // // can reduce the size of the struct

    // struct MyData3
    // {
    //     char data1;
    //     char data2;
    //     int data3;
    // };

    // printf("Size of struct MyData3: %d\n", sizeof(struct MyData3));

    // // (4)
    // // show that each member of a struct is aligned
    // // to a multiple of its size, hence the size of the struct
    // // is a multiple of the size of the largest member

    // struct MyData4
    // {
    //     char data1;
    //     short data2;
    //     char data3;
    //     int data4;
    // };

    // printf("Size of struct MyData4: %d\n", sizeof(struct MyData4));


    // // (5)
    // // show what the compiler does to align the members
    // // of a struct

    // struct MyData5
    // {
    //     char data1;
    //     char padding[1];
    //     short data2;
    //     char data3;
    //     char padding2[3];
    //     int data4;
    // };

    // printf("Size of struct MyData5: %d\n", sizeof(struct MyData5));

    // // (6)
    // // show how one can access single/multiple bits 
    // // in a struct

    // struct MyData6
    // {
    //     unsigned char data1 : 1;
    //     unsigned char data2 : 1;
    //     unsigned char data3 : 2;
    //     unsigned char data4 : 4;
    // };

    // struct MyData6 data;

    // data.data1 = 0b1;
    // data.data2 = 0b0;
    // data.data3 = 0b00;
    // data.data4 = 0b0110;

    // printf("This should show an 'a'?: %c\n", data);

    // // (7)
    // // show a neat trick with a union
    // union MyData7
    // {
    //     struct
    //     {
    //         unsigned char data1 : 1;
    //         unsigned char data2 : 1;
    //         unsigned char data3 : 2;
    //         unsigned char data4 : 4;
    //     } bits;
    //     unsigned char raw;
    // };

    // union MyData7 data2;

    // data2.bits.data1 = 0b1;
    // data2.bits.data2 = 0b0;
    // data2.bits.data3 = 0b00;
    // data2.bits.data4 = 0b0110;

    // printf("This should show an 'a'?: %c\n", data2.raw);
}