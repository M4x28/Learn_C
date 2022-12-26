//
// Created by Leonardo Birardi on 24/12/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW 12
#define COL 12

char labyrinth[ROW][COL] = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '#'},
        {'S', '.', '#', '.', '#', '.', '#', '#', '#', '#', '.', '#'},
        {'#', '#', '#', '.', '#', '.', '.', '.', '.', '#', '.', '#'},
        {'#', '.', '.', '.', '.', '#', '#', '#', '.', '#', '.', 'E'},
        {'#', '#', '#', '#', '.', '#', '.', '#', '.', '#', '.', '#'},
        {'#', '.', '.', '#', '.', '#', '.', '#', '.', '#', '.', '#'},
        {'#', '#', '.', '#', '.', '#', '.', '#', '.', '#', '.', '#'},
        {'#', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '#'},
        {'#', '#', '#', '#', '#', '#', '.', '#', '#', '#', '.', '#'},
        {'#', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
};


void printMaze() {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            printf("%c ", labyrinth[i][j]);
        }
        puts("");
    }
    puts("");
}


void cleanMaze() {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if (labyrinth[i][j] == 'X') labyrinth[i][j] = '.';
        }
    }
}


void setStartEnd() {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {

            if (j == 1 && (i > 0 || i < ROW) && labyrinth[i][j + 1] == '.' && labyrinth[i][j] == '.' &&
                labyrinth[i][j + 1] == '.' && labyrinth[i - 1][j - 1] != 'S')
                labyrinth[i][j - 1] = 'S';

            if (j == COL - 2 && (i > 0 || i < ROW) && labyrinth[i][j] == '.' && labyrinth[i - 1][j + 1] != 'E' &&
                (labyrinth[i][j - 1] == '.' || labyrinth[i - 1][j] == '.' || labyrinth[i + 1][j] == '.'))
                labyrinth[i][j + 1] = 'E';
        }
    }
    printMaze();
}

// Da fixare
void generateLabyrinth() {
    srand(time(NULL));

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if ((i == 0 || i == ROW - 1) || (j == 0 || j == COL - 1)) labyrinth[i][j] = '#';
            else {
                int randNum = rand() % 2;
                if (randNum == 0)
                    labyrinth[i][j] = '#';
                else
                    labyrinth[i][j] = '.';
            }
        }
    }
    setStartEnd();
}


int mazeTraverse() {
    unsigned int startX[4] = {}, startY[4] = {}, endX[4] = {}, endY[4] = {}, k = 0, h = 0;

    for (size_t i = 0; i < ROW; i++) {
        for (size_t j = 0; j < COL; j++) {
            if (labyrinth[i][j] == 'S') {
                startX[k] = i;
                startY[k] = j;
                k++;
            }
            if (labyrinth[i][j] == 'E') {
                endX[h] = i;
                endY[h] = j;
                k++;
            }
        }
    }

    //printf("Start: %d %d\n", startX, startY);
    //printf("End: %d %d\n", endX, endY);

    for (size_t x = 0; x < 4; x++) {
        unsigned int i = startX[x];
        unsigned int j = startY[x];
        cleanMaze();

        while (labyrinth[i][j + 1] != 'E') {

            // Fail
            if ((labyrinth[i][j + 1] == 'X' || labyrinth[i][j + 1] == '#') &&
                (labyrinth[i][j - 1] == 'X' || labyrinth[i][j - 1] == '#') &&
                (labyrinth[i + 1][j] == 'X' || labyrinth[i + 1][j] == '#') &&
                (labyrinth[i - 1][j] == 'X' || labyrinth[i - 1][j] == '#') &&
                (labyrinth[i][j] == '.' || labyrinth[i][j] == 'X')) {
                if (x == 3) {
                    cleanMaze();
                    printMaze();
                    return 0;
                } else break;
            }

            if (labyrinth[i + 1][j] == '#' && labyrinth[i][j + 1] == '#' && labyrinth[i - 1][j] == '.') {
                labyrinth[i - 1][j] = 'X';
                i--;
            }
            if (labyrinth[i + 1][j] == '#' && labyrinth[i][j + 1] == '.') {
                labyrinth[i][j + 1] = 'X';
                j++;
            }
            if ((labyrinth[i + 1][j] == 'X' || labyrinth[i + 1][j] == '#') && labyrinth[i - 1][j] == '#' &&
                labyrinth[i][j + 1] == '.') {
                labyrinth[i][j + 1] = 'X';
                j++;
            }
            if (labyrinth[i][j + 1] == '#' && labyrinth[i][j - 1] == '#' && labyrinth[i + 1][j] == '.') {
                labyrinth[i + 1][j] = 'X';
                i++;
            }
            if (labyrinth[i][j + 1] == '#' && labyrinth[i][j - 1] == '#' && labyrinth[i - 1][j] == 'X') {
                labyrinth[i][j] = 'X';
                i--;
            }
            if (labyrinth[i + 1][j] == 'X' && labyrinth[i][j + 1] == '.' &&
                (labyrinth[i - 1][j] == 'X' || labyrinth[i - 1][j] == '.')) {
                labyrinth[i][j + 1] = 'X';
                j++;
            }
            if ((labyrinth[i + 1][j] == 'X' || labyrinth[i + 1][j] == '#') &&
                (labyrinth[i][j + 1] == 'X' || labyrinth[i][j + 1] == '#') &&
                (labyrinth[i][j - 1] == 'X' || labyrinth[i][j - 1] == '#') && labyrinth[i - 1][j] == '.') {
                labyrinth[i - 1][j] = 'X';
                i--;
            }
            if ((labyrinth[i][j + 1] == 'X' || labyrinth[i][j + 1] == '#') &&
                (labyrinth[i + 1][j] == 'X' || labyrinth[i + 1][j] == '#') &&
                (labyrinth[i - 1][j] == 'X' || labyrinth[i - 1][j] == '#') && labyrinth[i][j - 1] == '.') {
                labyrinth[i][j - 1] = 'X';
                j--;
            }
            if (labyrinth[i + 1][j] == '.') {
                //labyrinth[i+1][j] = 'X';
                i++;
            }

            //printMaze();
            //printf("Current Pos: %d %d\n", i, j);
        }
        printMaze();
    }
    // Bad Maze
    return 0;
}


int main() {

    printMaze();
    mazeTraverse();

    return 0;
}