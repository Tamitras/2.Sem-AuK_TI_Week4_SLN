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
#include "dhbwstudentlist.h"


#ifndef DHBWSTUDENTMAP_H_
#define DHBWSTUDENTMAP_H_

typedef struct student_m {
	int maxsize;
	int currsize;
	int (*hashf)(Student_p student, int maxsize);
	Student_p *table;

} StudentM, *StudentMP;

//Erzeugt eine Hash-Tabelle mit gewaehlter Groesse und Hash-Funktion
StudentMP StudentMPAlloc(int mapsize, int (*hashf)(Student_p student, int maxsize));

//Gibt eine Hash-Tabelle und darin enthaltene Studenten
void StudentMPFree(StudentMP map);

//Schlechte Hash-Funktion nach Matrikelnummer, gibt Wert zwischen 0 und maxsize-1 zurueck
int dumbHashByMatr(Student_p student, int maxsize);



//Aufgaben ab hier

//Auf true setzen, damit die Hash-Tabelle getestet wird
bool StudentMImplemented();

//Hash-Funktion nach Matrikelnummer, gibt Wert zwischen 0 und maxsize-1 zurueck
int hashByMatr(Student_p student, int maxsize);

//Hash-Funktion nach Name, gibt Wert zwischen 0 und maxsize-1 zurueck
int hashByName(Student_p student, int maxsize);

//Hash-Funktion nach Name und Matrikelnummer, gibt Wert zwischen 0 und maxsize-1 zurueck
int hashByBoth(Student_p student, int maxsize);

//Findet einen gleichen Studenten in der Tabelle und gibt ihn zurück
//NULL, falls kein gleicher Student in der Tabelle ist
Student_p StudentMFind(StudentMP map, Student_p student);

//Aendert die Groesse der Tabelle und fuehrt ein Rehashing aller enthaltenen Studenten durch
//Alle nicht mehr benoetigten Datenstrukturen muessen nach dem Rehashing freigegeben werden
void StudentMRehash(StudentMP map, int newsize);

//Fuegt einen Studenten mittels der gewaehlten Hashfunktion in die Tabelle ein
//Kollisionen werden mittels Linear Probing aufgeloest
bool StudentMInsert(StudentMP map, Student_p newStudent);

//Gibt die aktuelle Anzahl von Elementen in der Tabelle zurueck
int StudentMSize(StudentMP map);

//Gibt eine (unsortierte) Liste aller Elemente in der Tabelle zurueck
//Achtung: Nullwerte sollen nicht enthalten sein
StudentLP* StudentMToList(StudentMP map);



#endif /* DHBWSTUDENTMAP_H_ */
