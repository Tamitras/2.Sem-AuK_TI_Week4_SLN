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


#ifndef DHBWSTUDENTTREE_H_
#define DHBWSTUDENTTREE_H_

typedef struct student_t {
	Student_p student;
	struct student_t *lchild;
	struct student_t *rchild;

} StudentT, *StudentTP;


//Erzeugt einen Baumknoten mit dem übergebenen Studenten
StudentTP StudentTPAlloc(Student_p newStudent);

//Gibt eine einzelne Listenzelle und darin enthaltenen Studenten frei
void StudentTPFree(StudentTP info);
//Gibt eine Liste und darin enthaltene Zellen frei
void StudentTFree(StudentTP* root_adr);


//Gibt einen einzelnen Baumknoten und darin enthaltenen Studenten frei
void StudentLPFree(StudentLP info);
//Gibt einen Baum und darin enthaltene Knoten frei
void StudentLFree(StudentLP* anchor_adr);

//Kopiert einen Baumknoten und enthaltenen Studenten
StudentTP deepTPCopy(StudentTP info);



//Aufgaben ab hier

//Auf true setzen, damit der Baum getestet wird
bool StudentTImplemented();

//Gibt true zurueck, wenn ein gleicher Student im Baum enthalten ist
//Verwenden Sie den Schluessel (Matrikel), um diese Pruefung effizient durchzufuehren
bool StudentTContainsStudent(StudentTP* root_adr, Student_p student);

//Findet den ersten Studenten mit der Matrikelnummer und gibt ihn zurück
//Verwenden Sie den Schluessel (Matrikel), um diese Pruefung effizient durchzufuehren
//NULL, falls kein Student mit der Matrikelnummer im Baum ist
StudentTP StudentTFindByMatr(StudentTP* root_adr, int matrnr);

//Findet den ersten Studenten mit dem Namen und gibt ihn zurück
//NULL, falls kein Student mit der Matrikelnummer im Baum ist
StudentTP StudentTFindByName(StudentTP* root_adr, char *lastname);

//Gibt eine nach Matrikelnummer sortierte Liste der Studenten im Baum zurück
//In der Liste soll sich eine Kopie (deepCopy) der Studenten befinden
StudentLP* StudentTToSortedList(StudentTP* root_adr);

//Fuegt den Studenten anhand des Schluessels in den Baum ein
void StudentTInsertSorted(StudentTP* root_adr, Student_p newStudent);

//Gibt die Anzahl der Knoten im Baum zurueck
int StudentTSize(StudentTP* root_adr);

//Gibt die Tiefe des Baums zurueck
int StudentTDepth(StudentTP* root_adr);



#endif /* DHBWSTUDENTTREE_H_ */
