//
// Created by Leonardo Birardi on 09/12/2022.
//


#include <stdio.h>


int main( void ) {
    int n;

    printf("Inserisci fino a che numero calcolare quadrato e numero: ");
    scanf("%d", &n);


    puts("numero quadrato cubo");
    for(int i = 0; i <= n; i++) {
        printf(" %d       %d      %d\n", i, i*i, i*i*i);
    }

    return 0;
}