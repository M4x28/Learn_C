#include <stdio.h>
#include "funzioniLibri.h"

int main() 
{	
	int numLibri; 
    printf("Inserisci il numero di libri: ");
    scanf("%d", &numLibri);

    Libro libri[numLibri];
    inserisciLibri(libri, numLibri);
    stampaLibri(libri, numLibri);
  
    return 0;
}

