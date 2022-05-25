/*
 ============================================================================
 Aufgabe     : Datenstrukturen
 Autor       :
 Matrikel    :
 Version     :
 ============================================================================
 */
#include <stdbool.h>
#include <stdlib.h>
#include "dhbwstudent.h"
#include "dhbwstudenttree.h"

//DIESE METHODEN NICHT AENDERN

StudentTP StudentTPAlloc(Student_p newStudent) {
	StudentTP new = malloc(sizeof(StudentT));

	new->student = newStudent;
	new->lchild = NULL;
	new->rchild = NULL;

	return new;
}


void StudentTPFree(StudentTP tree) {
	if (tree == NULL)
		return;

	StudentFree(tree->student);
	free(tree);
	return;
}

void StudentTFree(StudentTP* root_adr) {

	StudentTP current = *root_adr;

	if (current == NULL) {
		return;
	}
	StudentTFree(&(current->lchild));
	StudentTFree(&(current->rchild));

	StudentTPFree(current);
	return;
}

StudentTP deepTPCopy(StudentTP info) {
	if (info == NULL)
		return NULL;
	StudentTP copy = StudentTPAlloc(deepCopy(info->student));
	copy->lchild = NULL;
	copy->rchild = NULL;
	return copy;
}



//Bis hier nicht �ndern



//Ab hier Aufgaben



bool StudentTImplemented() {
	//TODO: hier auf true aendern, damit Ihre Implementierung getestet wird
	return false;
}

bool StudentTContainsStudent(StudentTP* root_adr, Student_p student) {
	return false;
}

StudentTP StudentTFindByMatr(StudentTP* root_adr, int matrnr) {
	return NULL;
}

StudentTP StudentTFindByName(StudentTP* root_adr, char *lastname) {
	return NULL;
}

StudentLP* StudentTToSortedList(StudentTP* root_adr) {
	return NULL;
}

void StudentTInsertSorted(StudentTP* root_adr, Student_p newStudent) {

}

int StudentTSize(StudentTP* root_adr) {
	return -1;
}

int StudentTDepth(StudentTP* root_adr) {
	return -1;
}

