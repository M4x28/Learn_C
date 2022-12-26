//
// Created by Leonardo Birardi on 22/12/2022.
//

#include <stdio.h>
#include <string.h>

#define INGREDIENT_NAME_LENGTH 100
#define INGREDIENT_SUBSTITUTE_LENGTH 100

// Struttura per rappresentare un ingrediente e il suo sostituto
struct IngredientSubstitute {
    char name[INGREDIENT_NAME_LENGTH];
    char substitute[INGREDIENT_SUBSTITUTE_LENGTH];
};

int main(void) {
    printf("Consultate sempre il vostro medico prima di apportare modifiche significative alla vostra dieta.\n");

    // Array di sostituti di ingredienti comuni
    struct IngredientSubstitute substitutes[] = {
            {"uova", "albumi"},
            {"zucchero", "stevia"},
            {"latticini", "latte di mandorle"},
            {"glutine", "farina di riso"}
    };
    int num_substitutes = sizeof(substitutes) / sizeof(substitutes[0]);

    // Leggere la ricetta dell'utente
    char recipe[1000];
    printf("Inserisci la tua ricetta: ");
    fgets(recipe, sizeof(recipe), stdin);

    // Analizzare la ricetta per cercare gli ingredienti specifici
    char *ingredient = strtok(recipe, " ,\n");
    while (ingredient != NULL) {
        // Controllare se l'ingrediente è presente nella lista dei sostituti
        for (int i = 0; i < num_substitutes; i++) {
            if (strcmp(ingredient, substitutes[i].name) == 0) {
                // Se l'ingrediente è presente, suggerire il suo sostituto
                printf("Per una scelta più sana, si può utilizzare %s al posto di %s.\n", substitutes[i].substitute, ingredient);
                break;
            }
        }

        // Passare all'ingrediente successivo
        ingredient = strtok(NULL, " ,\n");
    }

    return 0;
}
