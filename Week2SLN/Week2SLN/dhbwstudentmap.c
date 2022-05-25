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
#include "dhbwstudent.h"
#include "dhbwstudentmap.h"

//DIESE METHODEN NICHT AENDERN

StudentMP StudentMPAlloc(int mapsize, int (*hashf)(Student_p student, int maxsize)) {
	StudentMP new = malloc(sizeof(StudentM));

	new->currsize = 0;
	new->maxsize = mapsize;
	new->hashf = hashf;
	new->table = calloc(mapsize, sizeof(Student_p));
	return new;
}

void StudentMPFree(StudentMP map) {
	if (map == NULL)
			return;

	for(int i = 0; i < map->maxsize; i++) {
		StudentFree(map->table[i]);
	}

	free(map);
}

int dumbHashByMatr(Student_p student, int maxsize) {
	//this is a bad hash function as it only gives you 10 possible values
	//and ignores the lower digits completely
	return (student->matrnr / 100000) % maxsize;
}


//Bis hier nicht �ndern



//Ab hier Aufgaben



bool StudentMImplemented() {
	//TODO: hier auf true aendern, damit Ihre Implementierung getestet wird
	return false;
}
int hashByMatr(Student_p student, int maxsize) {
	return -1;
}

int hashByName(Student_p student, int maxsize) {
	return -1;
}

int hashByBoth(Student_p student, int maxsize) {
	return -1;
}

Student_p StudentMFind(StudentMP map, Student_p student) {
	return NULL;
}

void StudentMRehash(StudentMP map, int newsize) {

}

bool StudentMInsert(StudentMP map, Student_p newStudent) {
	return false;
}

int StudentMSize(StudentMP map) {
	return -1;
}

StudentLP* StudentMToList(StudentMP map) {
	return NULL;
}

