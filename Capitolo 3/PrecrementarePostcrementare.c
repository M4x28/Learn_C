//
// Created by Leonardo Birardi on 09/12/2022.
//


#include <stdio.h>

int main(void) {
    // Declare a variable and initialize it to 5
    int x = 5;

    // Use predecrement to decrement x and then print its value
    printf("Predecrement: %d\n", ++x);

    // Use postdecrement to decrement x and then print its value
    printf("Postdecrement: %d\n", x++);

    // Print the final value of x
    printf("Final value of x: %d\n", x);

}