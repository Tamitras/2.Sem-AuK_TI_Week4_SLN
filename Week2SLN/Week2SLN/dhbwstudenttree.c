/*
 ============================================================================
 Aufgabe     : Datenstrukturen
 Autor       : Erik Kaufmann
 Matrikel    : 1390365
 Version     : 1.0
 ============================================================================
 */
#include <stdbool.h>
#include <stdlib.h>
#include "dhbwstudent.h"
#include "dhbwstudenttree.h"

 // DIESE METHODEN NICHT AENDERN

StudentTP StudentTPAlloc(Student_p newStudent)
{
	StudentTP new = malloc(sizeof(StudentT));

	new->student = newStudent;
	new->lchild = NULL;
	new->rchild = NULL;

	return new;
}

void StudentTPFree(StudentTP tree)
{
	if (tree == NULL)
		return;

	StudentFree(tree->student);
	free(tree);
	return;
}

void StudentTFree(StudentTP* root_adr)
{

	StudentTP current = *root_adr;

	if (current == NULL)
	{
		return;
	}
	StudentTFree(&(current->lchild));
	StudentTFree(&(current->rchild));

	StudentTPFree(current);
	return;
}

StudentTP deepTPCopy(StudentTP info)
{
	if (info == NULL)
		return NULL;
	StudentTP copy = StudentTPAlloc(deepCopy(info->student));
	copy->lchild = NULL;
	copy->rchild = NULL;
	return copy;
}

// Bis hier nicht �ndern

// Ab hier Aufgaben

bool StudentTImplemented()
{
	// TODO: hier auf true aendern, damit Ihre Implementierung getestet wird
	return true;
}

bool StudentTContainsStudent(StudentTP* root_adr, Student_p student)
{
	// Rekursiv nach dem Element suchen
	// Hilfsmethode schreiben

	// set root adr
	StudentTP root = *root_adr;
	bool foundStudent = false;

	if (root->student->matrnr == student->matrnr) // gleich
	{
		//printf("<Duplicate student %s %d >\n", student->lastname, student->matrnr);
		return true;
	}
	else if (root->student->matrnr > student->matrnr) // linker baum
	{
		root = root->lchild;
	}
	else // rechter Baum
	{
		root = root->rchild;
	}

	if (root != NULL)
	{
		foundStudent = StudentTContainsStudent(&root, student);
	}

	return foundStudent;
}

StudentTP StudentTFindByMatr(StudentTP* root_adr, int matrnr)
{
	return NULL;
}

StudentTP StudentTFindByName(StudentTP* root_adr, char* lastname)
{
	return NULL;
}

StudentLP* StudentTToSortedList(StudentTP* root_adr)
{
	return NULL;
}

bool insertSorted(StudentT* studentNode, Student_p newStudent)
{
	bool ret = false;

	if (studentNode == NULL) // insertFirst
	{
		return true; // parentNode will be new StudentNode
	}
	
	else if ((studentNode)->student->matrnr > newStudent->matrnr) // left tree
	{
		ret = insertSorted((studentNode)->lchild, newStudent);
		if (ret)
		{
			if (StudentTContainsStudent(&studentNode, newStudent))
			{
				return false; // student exists
			}
			StudentTP newChild = StudentTPAlloc(newStudent);
			(studentNode)->lchild = newChild;
			//printf("New Insertion %s %d  on left tree of %s %d\n",
			//	newChild->student->lastname,
			//	newChild->student->matrnr,
			//	studentNode->student->lastname,
			//	studentNode->student->matrnr);
		}
	}
	else
	{
		ret = insertSorted((studentNode)->rchild, newStudent);
		if (ret)
		{
			if (StudentTContainsStudent(&studentNode, newStudent))
			{
				return false; // student exists
			}
			StudentTP newChild = StudentTPAlloc(newStudent);
			(studentNode)->rchild = newChild;
			//printf("New Insertion %s %d  on right tree of %s %d \n",
			//	newChild->student->lastname,
			//	newChild->student->matrnr,
			//	studentNode->student->lastname,
			//	studentNode->student->matrnr);
		}
	}
}

void StudentTInsertSorted(StudentTP* root_adr, Student_p newStudent)
{
	StudentTP current = *root_adr;
	if (current == NULL) // insertFirst
	{
		*root_adr = StudentTPAlloc(newStudent);
	}
	else
	{
		insertSorted(current, newStudent);
	}
}

int getTreeSize(StudentT* studentNode)
{
	int counter = 0;

	if (studentNode == NULL)
	{
		return 0;
	}
	else
	{
		counter = getTreeSize(studentNode->lchild) + getTreeSize(studentNode->rchild);
	}

	return counter + 1;
}

int StudentTSize(StudentTP* root_adr)
{
	int counter = 0;

	StudentTP current = *root_adr;

	if (*root_adr == NULL)
		return 0;
	else
	{
		counter = getTreeSize(current);
	}
	// Return length of tree
	// amount of all elements under the tree

	return counter;
}

int getDepth(StudentT* studentNode)
{
	if (studentNode == NULL)
		return 0;

	/* compute the depth of each subtree */
	int lDepth = getDepth(studentNode->lchild);
	int rDepth = getDepth(studentNode->rchild);

	/* use the larger one */
	if (lDepth > rDepth)
		return (lDepth + 1);
	else
		return (rDepth + 1);
}

int StudentTDepth(StudentTP* root_adr)
{
	int maxDepth = 0;

	if (root_adr == NULL)
		return 0;
	else
	{
		maxDepth = getDepth((*root_adr));
	}

	return maxDepth;
}
