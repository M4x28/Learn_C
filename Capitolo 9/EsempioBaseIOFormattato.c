//
// Created by Leonardo Birardi on 25/12/2022.
//

#include <stdio.h>


int main(void) {

    // I/O Formattato
    printf("%d\n", 455);
    printf("%i\n", 455); // i come d in printf
    printf("%d\n", +455); // non viene stampato il segno piu'
    printf("%d\n", -455); // viene stampato il segno meno
    printf("%hd\n", 32000);
    printf("%ld\n", 2000000000L); // suffisso L per letterale long int
    printf("%o\n", 455); // ottale
    printf("%u\n", 455);
    printf("%u\n", -455);
    printf("%x\n", 455); // esadecimale con lettere minuscole
    printf("%X\n", 455); // esadecimale con lettere maiuscole

    // Specificatori di conversione in virgola mobile
    printf("%e\n", 1234567.89);  // stampa la e con 6 cifre di precisione
    printf("%e\n", +1234567.89); // non viene stampato il segno piu'
    printf("%e\n", -1234567.89); // viene stampato il meno
    printf("%E\n", 1234567.89);  // stampa la E con 6 cifre di precisione
    printf("%f\n", 1234567.89); // sei cifre a destra del punto decimale
    printf("%g\n", 1234567.89); // stampa con la lettera minuscola e, oppure usa formato f
    printf("%G\n", 1234567.89); // stampa con la lettera maiuscola E, oppure usa formato f

    // Stringhe e caratteri
    char character = 'A'; // inizializza un char
    printf("%c\n", character);
    printf("%s\n", "This is a string");
    char string[] = "This is a string"; // inizializza un array di char
    printf("%s\n", string);
    const char *stringPtr = "This is also a string"; // puntatore a char
    printf("%s\n", stringPtr);
    puts("Printing a %% in a format control string\n");

    // Specificare la larghezza del campo di stampa
    printf("%4d\n", 1);  // stampa a dx
    printf("%4d\n", 12);
    printf("%4d\n", 123);
    printf("%4d\n", 1234);
    printf("%-4d\n", 1);  // stampa a sx
    printf("%-4d\n", 12);
    printf("%-4d\n", 123);
    printf("%-4d\n", 1234);
    printf("%4d\n", -1);
    printf("%4d\n", -12);
    printf("%4d\n", -123);
    printf("%4d\n", -1234);

    // Specificare la precisione per interi, numeri in virgola mobile e stringhe
    puts("Using precision for integers");
    int i = 873; // inizializza int i
    printf("\t%.4d\n\t%.9d\n\n", i, i); // utilizza rispettivamente 4 e 9 caratteri per rappresentare il numero
    puts("Using precision for floating-point numbers");
    double f = 123.94536; // inizializza double f
    printf("\t%.3f\n\t%.3e\n\t%.3g\n\n", f, f,
           f); // rappresenta il valore fp con 3 cifre dopo la virgola, per g/G è il numero max di cifre
    char s[] = "Happy Birthday"; // inizializza l'array di char s
    printf("\t%.11s\n", s); // stampa i primi 11 caratteri della stringa

    // Combinare larghezza di campo e precisioni
    printf("%*.*f", 7, 2, 98.736);  // larghezza campo e precisione dinamica

    // Stampa dei numeri positivi con segno
    printf("%+d\n%+d\n", 786, -786);

    // Stampa con flag spazio
    printf("% d\n% d\n", 547, -547);

    // Stampare un valore ottale (0X) utilizzando #
    printf("%#x\n", 1427);

    // Stampa con flag 0
    printf("%09d\n", 452);  // riempio di 0 da sx

    // Squillo
    printf("\a");

    // Insieme di scansioni con scanf
    char z[9]; // definisci l'array z
    printf("%s", "Enter string: ");
    scanf("%8[aeiou]", z); // cerca un insieme di caratteri
    printf("The input was \"%s\"\n", z);

    printf("%s", "Enter string: ");
    scanf("%8[^aeiou]", z); // insieme di scansione invertito
    printf("The input was \"%s\"\n", z);

    // Larghezze di campo con scanf
    int x, y;
    printf("%s", "Enter a six digit integer: ");
    scanf("%2d%d", &x, &y);
    printf("The integers input were %d and %d\n", x, y);

    // Tralasciare caratteri in uno stream di input (spesso utilizzato con le date)
    int month = 0, day = 0, year = 0;
    printf("%s", "Enter a date in the form mm-dd-yyyy: ");
    scanf("%d%*c%d%*c%d", &month, &day, &year);  // l'operatore %*c come carattere di soppressione dell'assegnazione
    printf("month = %d day = %d year = %d\n\n", month, day, year);


    return 0;
}