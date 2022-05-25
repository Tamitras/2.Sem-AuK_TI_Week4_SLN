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

bool studentoutput = false;

char *toString(Student_p info)
{
	char *string = malloc(sizeof(char) * BUF_SIZE);
	snprintf(string, BUF_SIZE, "%06d %s", info->matrnr, info->lastname);
	return string;
}

Student_p StudentAlloc(char *info)
{
	if ((info == NULL) || strlen(info) < MAT_SIZE + 3)
		return NULL;

	Student_p new = malloc(sizeof(Student));

	char matrnr_char[MAT_SIZE + 1];
	strncpy(matrnr_char, info, MAT_SIZE);
	matrnr_char[MAT_SIZE] = '\0';
	new->matrnr = atoi(matrnr_char);

	char *lastname_p = &info[MAT_SIZE + 1];

	if (studentoutput)
	{
		printf("new->matrnr: %s      %d\n", matrnr_char, new->matrnr);
		printf("Reading.. strlen(lastname_p)=%ld, str=%s\n", strnlen(lastname_p, MAXSIZE), lastname_p);
	}

	new->lastname = malloc(sizeof(char) * (strlen(lastname_p)) +1);
	strncpy(new->lastname, lastname_p, (strlen(lastname_p)));
	new->lastname[strlen(lastname_p)] = '\0';

	if (studentoutput)
	{
		printf("Creating student with matrnr %06d and lastname %s at address %ld\n", new->matrnr, new->lastname, new);
		printf("strlen: %ld\n", strlen(new->lastname));
	}

	return new;
}

Student_p deepCopy(Student_p info)
{
	if (info == NULL)
		return NULL;
	char *formatted = toString(info);

	if (studentoutput)
	{
		printf("Deep copy of: %s\n", formatted);
	}

	Student_p copy = StudentAlloc(formatted);

	free(formatted);
	return copy;
}

Student_p shallowCopy(Student_p info)
{
	if (info)
	{
		return info;
	}
	else
	{
		return NULL;
	}
}

int StudentEquals(Student_p s1, Student_p s2)
{
	if (s1 == NULL && s2 == NULL)
	{
		return true;
	}
	else if (s1 != NULL && s2 != NULL)
	{
		return (s1->matrnr == s2->matrnr && strcmp(s1->lastname, s2->lastname) == 0);
	}
	else
	{
		return false;
	}
}

void StudentFree(Student_p info)
{
	if (info == NULL)
		return;

	free(info->lastname);
	free(info);
	return;
}