/*
 ============================================================================
 Aufgabe     : Datenstrukturen - Woche 4
 Autor       : Erik Kaufmann
 Matrikel    : 1390365
 Version     : 1.0
 ============================================================================
 */
#include <stdbool.h>
#include <stdlib.h>
#include "dhbwstudentlist.h"
#include "dhbwstudent.h"

 // DIESE METHODEN NICHT AENDERN

StudentLP StudentLPAlloc(Student_p newStudent)
{
	StudentLP new = malloc(sizeof(StudentL));

	new->student = newStudent;
	new->next = NULL;

	return new;
}

void StudentLInsertFirst(StudentLP* anchor_adr, Student_p newStudent)
{
	StudentLP oldFirst = *anchor_adr;
	StudentLP newFirst = StudentLPAlloc(newStudent);
	*anchor_adr = newFirst;
	newFirst->next = oldFirst;
}

void StudentLInsertLast(StudentLP* anchor_adr, Student_p newStudent)
{
	StudentLP current = *anchor_adr;
	StudentLP previous = NULL;

	StudentLP newLP = StudentLPAlloc(newStudent);

	while (current != NULL)
	{
		previous = current;
		current = current->next;
	}

	if (previous != NULL)
	{
		previous->next = newLP;
	}
	else
	{
		*anchor_adr = newLP;
	}
}

int StudentLSize(StudentLP* anchor_adr)
{
	StudentLP current = *anchor_adr;

	int size = 0;

	while (current != NULL)
	{
		size++;
		current = current->next;
	}

	return size;
}

void StudentLPFree(StudentLP info)
{
	if (info == NULL)
		return;

	StudentFree(info->student);
	free(info);
	return;
}

void StudentLFree(StudentLP* anchor_adr)
{
	if (anchor_adr == NULL)
	{
		return;
	}

	StudentLP current = *anchor_adr;

	while (current)
	{
		StudentLP newCurrent = current->next;
		StudentLPFree(current);
		current = newCurrent;
	}

	*anchor_adr = NULL;
	return;
}

StudentLP deepLPCopy(StudentLP info)
{
	if (info == NULL)
		return NULL;
	StudentLP copy = StudentLPAlloc(deepCopy(info->student));
	copy->next = NULL;
	return copy;
}

StudentLP* deepLCopy(StudentLP* anchor_adr)
{
	if (anchor_adr == NULL)
		return NULL;

	StudentLP* copy = malloc(sizeof(StudentLP));
	*copy = NULL;

	StudentLP current = *anchor_adr;

	while (current)
	{
		StudentLInsertLast(copy, deepCopy(current->student));
		current = current->next;
	}

	return copy;
}

StudentLP* StudentsFromFile(char* filename)
{
	FILE* in = fopen(filename, "r");

	char string[BUF_SIZE];
	StudentLP* all_students = malloc(sizeof(StudentLP));
	*all_students = NULL;
	StudentLP reverse_students_anchor = NULL;
	StudentLP* reverse_students = &reverse_students_anchor;

	while (fgets(string, BUF_SIZE, in))
	{
		// remove newline (works for both windows and unix)
		string[strcspn(string, "\r\n")] = 0;

		// printf("%s\n", string);
		StudentLInsertFirst(reverse_students, StudentAlloc(string));
	}

	// create normal ordered list
	{
		StudentLP current = *reverse_students;
		while (current != NULL)
		{
			StudentLInsertFirst(all_students, deepCopy(current->student));
			current = current->next;
		}
	}

	StudentLFree(reverse_students);

	return all_students;
}

// Bis hier nicht �ndern

// Ab hier Aufgaben

bool StudentLImplemented()
{
	// TODO: hier auf true aendern, damit Ihre Implementierung getestet wird
	return true;
}

bool StudentLContainsStudent(StudentLP* anchor_adr, Student_p student)
{
	// start from the first link
	StudentLP current = *anchor_adr;

	// if list is empty
	if (current == NULL)
		return NULL;

	// iterate over linked list
	while (current)
	{
		Student_p currentStud = current->student;

		if (strcmp(currentStud->lastname, student->lastname) == 0 && currentStud->matrnr == student->matrnr)
		{
			// lastname is equal
			// matrnr is equal
			// return current;
			return true;
		}

		// NULL if reached the tail
		if (current->next == NULL)
			return NULL;
		else
			// get next
			current = current->next;
	}

	return false;
}

StudentLP StudentLExtractStudent(StudentLP* anchor_adr, Student_p student)
{
	// start from the first link
	StudentLP current = *anchor_adr;
	StudentLP before = NULL;

	// if list is empty
	if (current == NULL)
		return NULL;

	// iterate over linked list
	while (current)
	{
		if (strcmp(current->student->lastname, student->lastname) == 0
			&& current->student->matrnr == student->matrnr)
		{
			// lastname is equal
			// matrnr is equal
			// extract
			StudentLP temp = current;

			if (before)
			{
				before->next = current->next;
			}
			else if (current->next)
			{
				current = current->next;
				*anchor_adr = current;
			}
			else
			{
				*anchor_adr = NULL;
			}

			return temp;
		}

		// NULL if reached the tail
		if (current->next == NULL)
		{
			return NULL;
		}
		else
		{
			// get next
			before = current;
			current = current->next;
		}
	}
}

StudentLP StudentLFindStudent(StudentLP* anchor_adr, Student_p student)
{
	// start from the first link
	StudentLP current = *anchor_adr;

	// if list is empty
	if (current == NULL)
		return NULL;

	// iterate over linked list
	while (current)
	{
		Student_p currentStud = current->student;

		if (strcmp(currentStud->lastname, student->lastname) == 0 && currentStud->matrnr == student->matrnr)
		{
			// lastname is equal
			// matrnr is equal
			// return current;
			return current;
		}

		// NULL if reached the tail
		if (current->next == NULL)
			return NULL;
		else
			// get next
			current = current->next;
	}
}

StudentLP StudentLFindByMatr(StudentLP* anchor_adr, int matrnr)
{
	// start from the first link
	StudentLP current = *anchor_adr;

	// if list is empty
	if (current == NULL)
		return NULL;

	// iterate over linked list
	while (current)
	{
		Student_p currentStud = current->student;

		if (currentStud->matrnr == matrnr)
			// matrnr is equal
			return current;

		// NULL if reached the tail
		if (current->next == NULL)
			return NULL;
		else
			// get next
			current = current->next;
	}
}

StudentLP StudentLFindByName(StudentLP* anchor_adr, char* lastname)
{
	// start from the first link
	StudentLP current = *anchor_adr;

	// if list is empty
	if (current == NULL)
		return NULL;

	// iterate over linked list
	while (current)
	{
		Student_p currentStud = current->student;

		if (strcmp(currentStud->lastname, lastname) == 0)
			// matrnr is equal
			return current;

		// NULL if reached the tail
		if (current->next == NULL)
			return NULL;
		else
			// get next
			current = current->next;
	}
}

void StudentLInsertSorted(StudentLP* anchor_adr, Student_p newStudent)
{
	// start from the first link
	StudentLP current = *anchor_adr;
	StudentLP before = NULL;
	StudentLP newStudentLP = NULL;

	if (newStudent->matrnr == 0)
	{
		// skip corrupt data
		// there should be no entry with matrNr == 0 
		return;
	}

	if (*anchor_adr == NULL)
	{
		// use existing method to insertFirst
		StudentLInsertFirst(anchor_adr, newStudent);
		return;
	}

	// iterate over linked list
	// as long as current not null or nullptr
	while (current)
	{
		if (current->next == NULL) // If current is tail
		{
			if (newStudent->matrnr < current->student->matrnr)
			{
				newStudentLP = StudentLPAlloc(newStudent);

				if (before == NULL)
				{
					// Set newStudent as new head of list
					StudentLP oldHead = *anchor_adr;
					*anchor_adr = newStudentLP;
					newStudentLP->next = oldHead;
				}
				else
				{
					// place in between
					before->next = newStudentLP;
				}
			}
			else
			{
				if (StudentLContainsStudent(anchor_adr, newStudent))
				{
					//avoid redundancy
					return;
				}
				else
				{
					StudentLInsertLast(anchor_adr, newStudent);
				}
			}

			return;
		}
		else // not tail
		{
			newStudentLP = StudentLPAlloc(newStudent);

			if (current->student->matrnr < newStudent->matrnr && current->next->student->matrnr > newStudent->matrnr)
			{
				newStudentLP->next = current->next;
				current->next = newStudentLP;
				return;
			}

			if (newStudent->matrnr < current->student->matrnr)
			{
				if (before == NULL) // current is head
				{
					StudentLInsertFirst(anchor_adr, newStudent);
				}
				else
				{
					before->next = newStudentLP;
					newStudentLP->next = current;
				}

				return;
			}
			else
			{
				// set before and get next
				before = current;
				current = current->next;
			}
		}
	}
}
