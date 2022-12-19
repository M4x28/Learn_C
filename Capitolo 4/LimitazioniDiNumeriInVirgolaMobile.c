//
// Created by Leonardo Birardi on 15/12/2022.
//


#include <stdio.h>


int main(void) {
    float a = 1000000.00;
    a += 0.12f;

    printf("%.2f", a);

    return 0;
}