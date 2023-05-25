//
// Created by Leonardo Birardi on 05/04/2023.
//

#include <stdio.h>
#include <stdlib.h>

#define NUM_STUDENTS 5

// Prototypes
void get_and_write_students(FILE *fp, int students);
void get_student_info(char *name, int *grade);
void open_file(FILE **fp, char *filename, char *mode);
void print_passed_students(FILE *fp);
void write_student_info_on_file(FILE *fp, char *name, int grade);


int main() {
    FILE *fp;

    open_file(&fp, "grades.txt", "w");
    get_and_write_students(fp, NUM_STUDENTS);
    fclose(fp);

    open_file(&fp, "grades.txt", "r");
    print_passed_students(fp);
    fclose(fp);

    return 0;
}


void open_file(FILE **fp, char *filename, char *mode) {
    *fp = fopen(filename, mode);
    if (*fp == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
}

void get_student_info(char *name, int *grade) {
    printf("Enter name: ");
    scanf("%s", name);
    printf("Enter grade: ");
    scanf("%d", grade);
}

void write_student_info_on_file(FILE *fp, char *name, int grade) {
    fprintf(fp, "%s %d\n", name, grade);
}

void get_and_write_students(FILE *fp, int students) {
    char name[50];
    int grade;
    int i;

    for (i = 0; i < students; i++) {
        get_student_info(name, &grade);
        write_student_info_on_file(fp, name, grade);
    }
}

void print_passed_students(FILE *fp) {
    char name[50];
    int grade;

    printf("\nStudents who passed:\n");
    while (fscanf(fp, "%s %d", name, &grade) != EOF) {
        if (grade >= 18) {
            printf("%s\n", name);
        }
    }
}