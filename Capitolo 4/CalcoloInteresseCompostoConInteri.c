//
// Created by Leonardo Birardi on 15/12/2022.
//

/* Formula: a = p(1 + r)^n
 * p è la quantità iniziale di denaro investita (cioè il capitale)
 * r è il tasso annuale d'interesse (ad esempio, .05 per 5%)
 * n è il numero degli anni
 * a è la quantità di denaro in deposito alla fine dell’anno n.
*/

#include <stdio.h>
#include <math.h>


int main(void) {
    int principal = 100000; // capitale iniziale tratttato come centesimo di euro, 100000 = 1000.00
    int rate = 5; // tasso d'interesse annuale

    // stampa le intestazioni delle colonne della tabella
    printf("%4s%15s%30s\n", "Year", "Amount in INT", "Amount on deposit in DOUBLE");

    // calcola la quantità in deposito per ognuno dei dieci anni
    for (unsigned short int year = 0; year <= 10; ++year) {

        // calcola la nuova quantità per un anno specifico
        // !!! Dividiamo per la potenza di 100 per evitare overflow
        // dopo alcuni test int ha la stessa grandezza di long long
        int amount = (principal * pow(100 + rate, year)) / pow(100, year);
        if(amount > 150797748) break;

        // stampa una riga della tabella
        double temp = (double) amount / 100.00;
        printf("%4u%12d%21.2f\n", year, amount, temp);
    }

}