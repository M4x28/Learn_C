//
// Created by Leonardo Birardi on 15/12/2022.
//

/*
 * 1) !(condizione1 && condizione2) è logicamente equivalente all’espressione (!condizione1 || !condizione2)
 * 2) !(condizione1 || condizione2) è logicamente equivalente all’espressione (!condizione1 && !condizione2)
 */


#include <stdio.h>


int main(void) {
    unsigned short int a = 6, b = 2, c = 5;

    if((!(a < 5) && !(b >= 7)) == ((a > 5) && (b <= 7))) puts("!(a < 5) && !(b >= 7) e' uguale a: (a > 5) && (b <= 7)");

    if((!(a == b) || !(c != 5)) == ((a != b) || (c == 5))) puts("!(a == b) || !(c != 5) e' uguale a: (a != b) || (c == 5)");

    if((!((a <= 8) && (b > 4))) == ((a >= 8) || (b < 4))) puts("!((x <= 8) && (y > 4)) e' uguale a: (a >= 8) || (b < 4)");

    if((!((a > 4) || (b <= 6))) == ((a < 4) && (b >= 6))) puts("!((i > 4) || (j <= 6)) e' uguale a: (b < 4) && (a >= 6))");

    return 0;
}