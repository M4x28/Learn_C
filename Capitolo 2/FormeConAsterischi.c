//
// Created by Leonardo Birardi on 09/12/2022.
//


#include <stdio.h>


void stampaO();
void stampaFreccia();
void stampaRombo();
void stampaRettangolo();


int main(void) {
    int scelta;


    printf("Che simbolo vuoi stampare?[1:O, 2:Freccia, 3:Rombo, 4:Rettangolo]: ");
    scanf("%d", &scelta);

    switch (scelta) {
        case 1:
            stampaO();
            break;
        case 2:
            stampaFreccia();
            break;
        case 3:
            stampaRombo();
            break;
        case 4:
            stampaRettangolo();
            break;
    }

    return 0;
}


void stampaRettangolo() {
    puts("");
    puts("*********");
    puts("*       *");
    puts("*       *");
    puts("*       *");
    puts("*       *");
    puts("*       *");
    puts("*       *");
    puts("*       *");
    puts("*********");
}


void stampaO() {
    puts("");
    puts("  ***  ");
    puts(" *   * ");
    puts("*     *");
    puts("*     *");
    puts("*     *");
    puts("*     *");
    puts("*     *");
    puts(" *   * ");
    puts("  ***  ");
}


void stampaFreccia() {
    puts("");
    puts("  *  ");
    puts(" *** ");
    puts("*****");
    puts("  *  ");
    puts("  *  ");
    puts("  *  ");
    puts("  *  ");
    puts("  *  ");
    puts("  *  ");
}


void stampaRombo() {
    puts("");
    puts("    *    ");
    puts("   * *   ");
    puts("  *   *  ");
    puts(" *     * ");
    puts("*       *");
    puts(" *     * ");
    puts("  *   *  ");
    puts("   * *   ");
    puts("    *    ");
}