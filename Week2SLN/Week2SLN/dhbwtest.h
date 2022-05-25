/*
 ============================================================================
 Aufgabe     : Datenstrukturen
 Autor       : koetter
 Matrikel    : DIESE DATEI NICHT AENDERN
 Version     : DIESE DATEI NICHT AENDERN
 ============================================================================
 */
#include <stdbool.h>
#include "dhbwstudent.h"
#include "dhbwstudentlist.h"


#ifndef DHBWTEST_H_
#define DHBWTEST_H_

bool testNoNulls(StudentLP* anchor_adr);
bool testMatrSort(StudentLP* anchor_adr);

Student_p generateTestStudent(int matr_nr);
StudentLP* generateTestData(int amount, bool shuffleData);

#endif /* DHBWTEST_H_ */
