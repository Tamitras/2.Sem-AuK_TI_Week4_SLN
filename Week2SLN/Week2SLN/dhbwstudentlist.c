/*
 ============================================================================
 Aufgabe     : Datenstrukturen - Woche 4
 Autor       : Erik Kaufmann	
 Matrikel    : 139
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

void StudentLInsertFirst(StudentLP *anchor_adr, Student_p newStudent)
{
	StudentLP oldFirst = *anchor_adr;
	StudentLP newFirst = StudentLPAlloc(newStudent);
	*anchor_adr = newFirst;
	newFirst->next = oldFirst;
}

void StudentLInsertLast(StudentLP *anchor_adr, Student_p newStudent)
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

int StudentLSize(StudentLP *anchor_adr)
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

void StudentLFree(StudentLP *anchor_adr)
{
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

StudentLP *deepLCopy(StudentLP *anchor_adr)
{
	if (anchor_adr == NULL)
		return NULL;

	StudentLP *copy = malloc(sizeof(StudentLP));
	*copy = NULL;

	StudentLP current = *anchor_adr;

	while (current)
	{
		StudentLInsertLast(copy, deepCopy(current->student));
		current = current->next;
	}

	return copy;
}

StudentLP *StudentsFromFile(char *filename)
{
	FILE *in = fopen(filename, "r");

	char string[BUF_SIZE];
	StudentLP *all_students = malloc(sizeof(StudentLP));
	*all_students = NULL;
	StudentLP reverse_students_anchor = NULL;
	StudentLP *reverse_students = &reverse_students_anchor;

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

bool StudentLContainsStudent(StudentLP *anchor_adr, Student_p student)
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

StudentLP StudentLExtractStudent(StudentLP *anchor_adr, Student_p student)
{
	// start from the first link
	StudentLP head = *anchor_adr;
	StudentLP current = *anchor_adr;
	StudentLP before = NULL;

	// printf("---------------------------------------------------\n");

	// if list is empty
	if (current == NULL)
		return NULL;

	// iterate over linked list
	while (current)
	{
		if (strcmp(current->student->lastname, student->lastname) == 0 && current->student->matrnr == student->matrnr)
		{
			// lastname is equal
			// matrnr is equal
			// extract
			StudentLP temp = current;
			// printf("FoundStud to remove: %d %s\n", temp->student->matrnr, temp->student->lastname);

			if (before)
			{
				// printf("BeforeFoundStud: %d %s\n", before->student->matrnr, before->student->lastname);
				before->next = current->next;
			}
			else
			{
				// printf("No Before, %d %s is Head\n",temp->student->matrnr, temp->student->lastname);
				if (current->next)
				{
					// printf("New current: %d\n", current->next->student->matrnr);
					current = current->next;

					// printf("Head old: %d %s\n", (*anchor_adr)->student->matrnr, (*anchor_adr)->student->lastname);
					*anchor_adr = current;
					// printf("Head new: %d %s\n", (*anchor_adr)->student->matrnr, (*anchor_adr)->student->lastname);
				}
				else
				{
					*anchor_adr = NULL;
				}
			}

			// printf("Extract Student (Found Stud): %d %s\n", temp->student->matrnr, temp->student->lastname);

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

StudentLP StudentLFindStudent(StudentLP *anchor_adr, Student_p student)
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

StudentLP StudentLFindByMatr(StudentLP *anchor_adr, int matrnr)
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

StudentLP StudentLFindByName(StudentLP *anchor_adr, char *lastname)
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

void StudentLInsertSorted(StudentLP *anchor_adr, Student_p newStudent)
{
	// start from the first link
	StudentLP current = *anchor_adr;
	StudentLP before = NULL;

	if (newStudent->matrnr == 0)
	{
		return;
	}

	if (*anchor_adr == NULL)
	{
		StudentLInsertFirst(anchor_adr, newStudent);
		return;
	}

	// iterate over linked list
	while (current)
	{
		if (current->next == NULL)
		{
			if (newStudent->matrnr < current->student->matrnr)
			{
				StudentLP newStud = StudentLPAlloc(newStudent);

				if (before == NULL)
				{
					// Set new Stud as new Head of List
					StudentLP oldHead = *anchor_adr;
					*anchor_adr = newStud;
					newStud->next = oldHead;
				}
				else
				{
					before->next = newStud;
				}
			}
			else
			{
				if (StudentLContainsStudent(anchor_adr, newStudent))
				{
					return;
				}
				else
				{
					StudentLInsertLast(anchor_adr, newStudent);
				}
			}

			return;
		}
		else
		{
			if (current->student->matrnr < newStudent->matrnr && current->next->student->matrnr > newStudent->matrnr)
			{
				StudentLP newStudentLP = StudentLPAlloc(newStudent);

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
					StudentLP newStudentLP = StudentLPAlloc(newStudent);

					before->next = newStudentLP;
					newStudentLP->next = current;
				}

				return;
			}
			else
			{
				// get next
				before = current;
				current = current->next;
			}
		}
	}
}
