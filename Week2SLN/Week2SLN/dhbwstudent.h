/*
 ============================================================================
 Aufgabe     : Datenstrukturen
 Autor       : koetter
 Matrikel    : DIESE DATEI NICHT AENDERN
 Version     : DIESE DATEI NICHT AENDERN
 ============================================================================
 */
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef DHBWSTUDENT_H_
#define DHBWSTUDENT_H_

#define MAT_SIZE 6
#define MAXITEMS 1000
#define MAXSIZE 100
#define BUF_SIZE 255

typedef struct student {
	unsigned int matrnr;
	char *lastname;

} Student, *Student_p;



char* toString(Student_p info);

Student_p StudentAlloc(char *info);

Student_p deepCopy(Student_p info);

Student_p shallowCopy(Student_p info);

int StudentEquals(Student_p s1, Student_p s2);

void StudentFree(Student_p info);



#endif /* DHBWSTUDENT_H_ */
