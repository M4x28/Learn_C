//
// Created by Leonardo Birardi on 25/12/2022.
//

#include <stdio.h>


int main() {
// stampa l'intestazione della tabella
    printf("%10s %10s\n", "Fahrenheit", "Celsius");
    for (int fahrenheit = 0; fahrenheit <= 212; fahrenheit++) {
        double celsius = 5.0 / 9.0 * (fahrenheit - 32);
        printf("%10d F %10.3f C\n", fahrenheit, celsius);
    }

    return 0;
}
