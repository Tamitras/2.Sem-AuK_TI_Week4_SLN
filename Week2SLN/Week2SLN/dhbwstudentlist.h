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
#include "dhbwstudent.h"


#ifndef DHBWSTUDENTLIST_H_
#define DHBWSTUDENTLIST_H_

typedef struct student_l {
	Student_p student;
	struct student_l *next;

} StudentL, *StudentLP;

//Erzeugt eine Listenzelle mit dem �bergebenen Studenten
StudentLP StudentLPAlloc(Student_p newStudent);

//F�gt einen Studenten am Anfang der Liste ein
void StudentLInsertFirst(StudentLP* anchor_adr, Student_p newStudent);

//F�gt einen Studenten am Ende der Liste ein
void StudentLInsertLast(StudentLP* anchor_adr, Student_p newStudent);

//Gibt die Laenge der Liste zurueck
int StudentLSize(StudentLP* anchor_adr);

//Gibt eine einzelne Listenzelle und darin enthaltenen Studenten frei
void StudentLPFree(StudentLP info);
//Gibt eine Liste und darin enthaltene Zellen frei
void StudentLFree(StudentLP* anchor_adr);

//Kopiert eine Listenzelle und enthaltenen Studenten
StudentLP deepLPCopy(StudentLP info);
//Kopiert eine Liste mit Listenzellen und enthaltenen Studenten
StudentLP* deepLCopy(StudentLP* anchor_adr);

//Liest eine Studentenliste aus einer Datei aus
StudentLP* StudentsFromFile(char *filename);


//Aufgaben ab hier

//Auf true setzen, damit die Liste getestet wird
bool StudentLImplemented();

//Gibt true zurueck, wenn ein gleicher Student in der Liste enthalten ist
bool StudentLContainsStudent(StudentLP* anchor_adr, Student_p student);

//Entfernt die Zelle mit dem Studenten aus der Liste und gibt sie zur�ck
//NULL, falls kein gleicher Student in der Liste ist
StudentLP StudentLExtractStudent(StudentLP* anchor_adr, Student_p student);

//Findet die Zelle mit dem Studenten aus der Liste und gibt sie zur�ck
//NULL, falls kein gleicher Student in der Liste ist
StudentLP StudentLFindStudent(StudentLP* anchor_adr, Student_p student);

//Findet den ersten Studenten mit der Matrikelnummer und gibt ihn zur�ck
//NULL, falls kein Student mit der Matrikelnummer in der Liste ist
StudentLP StudentLFindByMatr(StudentLP* anchor_adr, int matrnr);

//Findet den ersten Studenten mit dem Namen und gibt ihn zur�ck
//NULL, falls kein Student mit der Matrikelnummer in der Liste ist
StudentLP StudentLFindByName(StudentLP* anchor_adr, char *lastname);

//Fuegt den Studenten nach Matrikelnummer sortiert in die Liste ein
void StudentLInsertSorted(StudentLP* anchor_adr, Student_p newStudent);


#endif /* DHBWSTUDENTLIST_H_ */
