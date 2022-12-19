//
// Created by Leonardo Birardi on 16/12/2022.
//

#include <stdio.h>

int fibonacci(int n)
{
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    else
        return fibonacci(n-1) + fibonacci(n-2);
}

int main()
{
    int i, n;

    printf("Inserisci il numero per la serie di Fibonacci: ");
    scanf("%d", &n);

    printf("Serie di Fibonacci: ");

    for (i = 0; i < n; i++)
        printf("%d ", fibonacci(i));

    return 0;
}
