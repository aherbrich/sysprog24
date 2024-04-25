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

    printf("Size of struct MyData: %lu\n", sizeof(struct MyData));

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

    // printf("Size of struct MyData2: %lu\n", sizeof(struct MyData2));

    // // (3)
    // // show that restructuring the members of a struct
    // // can reduce the size of the struct

    // struct MyData3
    // {
    //     char data1;
    //     char data2;
    //     int data3;
    // };

    // printf("Size of struct MyData3: %lu\n", sizeof(struct MyData3));

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

    // printf("Size of struct MyData4: %lu\n", sizeof(struct MyData4));


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

    // printf("Size of struct MyData5: %lu\n", sizeof(struct MyData5));

    // // (6)
    // // show how one can access single/multiple bits 
    // // in a struct

    // struct MyData6
    // {
    //     unsigned char bit_one : 1;
    //     unsigned char bit_two : 1;
    //     unsigned char bit_three_to_four : 2;
    //     unsigned char bit_five_to_eight : 4;
    // };

    // struct MyData6 data;

    // data.bit_one = 0b1;
    // data.bit_two = 0b0;
    // data.bit_three_to_four = 0b00;
    // data.bit_five_to_eight = 0b0110;

    // printf("This should show an 'a'?: %c\n", data); // the compiler doesnt allow us to cast
    //                                                 // the bitfield struct to a char
    //                                                 // (which we would like too, 
    //                                                 // in order to suppress the warning)

    // // (7)
    // // show a neat trick with a union to access the bits
    // // of a byte but keep a way to access the byte itself
    // union MyData7
    // {
    //     struct
    //     {
    //         unsigned char bit_one : 1;
    //         unsigned char bit_two : 1;
    //         unsigned char bit_three_to_four : 2;
    //         unsigned char bit_five_to_eight : 4;
    //     } bits;
    //     unsigned char raw;
    // };

    // union MyData7 data2;

    // data2.bits.bit_one = 0b1;
    // data2.bits.bit_two = 0b0;
    // data2.bits.bit_three_to_four = 0b00;
    // data2.bits.bit_five_to_eight = 0b0110;

    // printf("This should show an 'a'?: %c\n", data2.raw);

    // // (8)
    // // show the union trick where one can look at the binary
    // // representation of a float

    // union MyData8
    // {
    //     float f;
    //     unsigned int i;
    // };

    // union MyData8 data3;

    // // you can check that this actually shows the binary representation
    // // by using this (https://www.h-schmidt.net/FloatConverter/IEEE754.html)
    // // online converter

    // data3.f = 3.14;
    // printf("This should show the binary representation (in hex) of 3.14: 0x%x\n", data3.i); // prints 0x4048f5c3

}