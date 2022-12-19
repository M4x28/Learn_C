//
// Created by Leonardo Birardi on 09/12/2022.
//


#include <stdio.h>
#include <stdbool.h>


int main( void ) {
    unsigned long long int n;

    while (true) {
        if(n % 2 == 1) printf("%llu\n", n);
        n++;
    }

    return 0;
}