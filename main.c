/* 
 * File:   main.c
 * Author: Matthias Drummer <s0542834>
 *
 * Created on November 7, 2013, 3:53 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student Student;

char * readLine(void);

struct Student {
    char *name;
    char *vorname;
    char *matrikelNr;
    char *studienGang;
};

// define global variables
int stackIndex = -1;
Student *stack;

/**
 * Pushes a student struct to the given stack. If the stack is full an error message is displayed.
 * 
 * @param student the student to push
 * @param stack the stack to push the student struct to
 */
void push(Student *student, Student stack[]) {

    if (stackIndex + 1 == sizeof (stack)) {
        printf("\nStack ist voll");
    } else {
        stackIndex++;
        stack[stackIndex] = *student;
    }

}

/**
 * Pops the last student struct from the stack. If the stack is empty an error message will be displayed.
 * 
 * @param stack the stack to pop the student struct from
 * @return the popped student
 */
Student pop(Student stack[]) {

    if (stackIndex < 0) {
        printf("\nStack ist leer. Bitte erst Elemente hinzufügen.");
    } else {
        Student student = stack[stackIndex];
        stackIndex--;
        return student;
    }
}

/**
 * reads a new Stunden struct from the console.
 * 
 * @return the read student
 */
Student *readStudent() {

    Student *student = (Student*) malloc(sizeof (Student));

    printf("\nName eingeben: ");
    student->name = readLine();
    printf("\nVorname eingeben: ");
    student->vorname = readLine();
    printf("\nMatrikel-Nr. eingeben: ");
    student->matrikelNr = readLine();
    printf("\nStudiengang eingeben: ");
    student->studienGang = readLine();

    return student;
}

/**
 * @See http://stackoverflow.com/questions/314401/how-to-read-a-line-from-the-console-in-c
 * @See http://www.rainydayz.org/beej/bgc/gets.html
 * 
 * @return the read line.
 */

char * readLine(void) {

    char * line = malloc(100), * linep = line;
    size_t lenmax = 100, len = lenmax;
    int c;

    if (line == NULL)
        return NULL;

    for (;;) {
        c = fgetc(stdin);
        if (c == EOF)
            break;

        if (--len == 0) {
            len = lenmax;
            char * linen = realloc(linep, lenmax *= 2);

            if (linen == NULL) {
                free(linep);
                return NULL;
            }
            line = linen + (line - linep);
            linep = linen;
        }

        if ((*line++ = c) == '\n')
            break;
    }
    *line = '\0';
    return linep;
}

void clrstdin() {
    char c;
    while ((c = getchar()) != EOF && c != '\n');
}

/*
 * Main function for the stack program.
 * 
 * @param argc the number of parameters
 * @param argv an array containing the given command line paramenters.
 */
int main(int argc, char** argv) {

    int stackSize;
    printf("Geben Sie die Größe des Stacks ein: ");
    scanf("%i", &stackSize);
    clrstdin();
    stack = (Student*) malloc(sizeof (Student) * stackSize);
    if (stack == NULL) {
        exit(-1);
    }

    short done = 0;
    while (done == 0) {

        int choose;

        printf("\n");
        printf("######################################");
        printf("\nWas wollen Sie tun?");
        printf("\n1.\tStudenten eingeben und auf Stack packen.");
        printf("\n2.\tStudenten vom Stack lesen");
        printf("\n3.\tProgramm beenden\n");
        scanf("%i", &choose);
        clrstdin();
        printf("######################################");

        switch (choose) {
            case 1:
            {
                Student *student = readStudent();
                push(student, stack);
            }
                break;
            case 2:
            {
                Student student = pop(stack);
                printf("######################################");
                printf("\nStudent vom Stack:");
                printf("\nName: %s", student.name);
                printf("\nVorname: %s", student.vorname);
                printf("\nMatrikel-Nr: %s", student.matrikelNr);
                printf("\nStudiengang: %s", student.studienGang);
                printf("######################################");
            }
                break;
            case 3:
                done = 1;
                break;
        }
    }

    printf("\nMay the force be with you, young padawan.");
    return (EXIT_SUCCESS);
}
