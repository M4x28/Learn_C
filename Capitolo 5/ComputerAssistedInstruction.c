//
// Created by Leonardo Birardi on 16/12/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void new_question(int *num1, int *num2, int level);
int check_answer(int num1, int num2, int answer);

int main() {
    int num1, num2, answer, correct = 0, incorrect = 0;
    int level;
    printf("Inserisci il livello di difficolta' (1-3): ");
    scanf("%d", &level);

    while (correct + incorrect < 10) {
        new_question(&num1, &num2, level);
        printf("Quanto fa %d per %d? ", num1, num2);
        scanf("%d", &answer);
        if (check_answer(num1, num2, answer)) {
            correct++;
            int r = rand() % 4;
            if (r == 0) {
                printf("Very good!\n");
            } else if (r == 1) {
                printf("Excellent!\n");
            } else if (r == 2) {
                printf("Nice work!\n");
            } else {
                printf("Keep up the good work!\n");
            }
        } else {
            incorrect++;
            int r = rand() % 4;
            if (r == 0) {
                printf("No. Please try again.\n");
            } else if (r == 1) {
                printf("Wrong. Try once more.\n");
            } else if (r == 2) {
                printf("Don't give up!\n");
            } else {
                printf("No. keep trying.\n");
            }
        }
    }

    int percentage = (correct / (correct + incorrect)) * 100;
    if (percentage < 75) {
        printf("Please ask your teacher for extra help.\n");
    } else {
        printf("Congratulations, you are ready to go to the next level!\n");
    }

    return 0;
}

void new_question(int *num1, int *num2, int level) {
    srand(time(NULL));
    *num1 = rand() % (int)pow(10, level);
    *num2 = rand() % (int)pow(10, level);
}

int check_answer(int num1, int num2, int answer) {
    return num1 * num2 == answer;
}