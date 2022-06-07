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
	if (*root_adr == NULL)
	{
		return NULL;
	}

	StudentTP* foundStudentAdr = NULL;
	StudentTP foundStudent = NULL;

	if ((*root_adr)->student->matrnr == matrnr)
	{
		foundStudent = (*root_adr);
	}
	else
	{
		foundStudent = StudentTFindByMatr(&(*root_adr)->lchild, matrnr);

		if (foundStudent == NULL)
			foundStudent = StudentTFindByMatr(&(*root_adr)->rchild, matrnr);

	}

	return foundStudent;
}

StudentTP StudentTFindByName(StudentTP* root_adr, char* lastname)
{
	if (*root_adr == NULL)
	{
		return NULL;
	}

	StudentTP* foundStudentAdr = NULL;
	StudentTP foundStudent = NULL;
	if(strcmp((*root_adr)->student->lastname, lastname)== 0)
	{
		foundStudent = (*root_adr);
	}
	else
	{
		foundStudent = StudentTFindByName(&(*root_adr)->lchild, lastname);

		if (foundStudent == NULL)
			foundStudent = StudentTFindByName(&(*root_adr)->rchild, lastname);
	}

	return foundStudent;
}


bool hasTwoSubRefs(StudentT* node)
{
	return (node->lchild != NULL && node->rchild != NULL);
}

bool deleteFromTree(StudentTP* root, StudentT* targetingNode)
{
	bool contained = false;

	if (root == NULL)
	{
		return false; // cant remove, tree is empty
	}
	else
	{
		// check if tree contains targetingNode
		contained = StudentTContainsStudent(root, targetingNode->student);

		if (contained) // continue
		{
			// adjust pointers
			if ((*root)->student->matrnr == targetingNode->student->matrnr) // is root
			{
				// complicated
			}
			else // not root, check if targetingNode has 2 refs (left, right
			{
				if (hasTwoSubRefs(targetingNode))
				{
					// true --> complicated
				}
				else
				{
					// has only 1 ref --> readjust ref

					if (targetingNode->lchild == NULL)
					{
						// right tree
						//targetingNode->rchild
					}
				}
			}
		}
		else // not existing in tree
		{
			return false;
		}
	}
}

void getNext(StudentLP* headOfList, StudentT* currentTreeElement)
{
	if (!currentTreeElement)
		return;

	StudentT* currentTreeStud = currentTreeElement->student;

	StudentLInsertSorted(headOfList, currentTreeStud);

	getNext(headOfList, currentTreeElement->lchild);
	getNext(headOfList, currentTreeElement->rchild);
}

StudentLP* StudentTToSortedList(StudentTP* root_adr)
{
	StudentLP headOfListAnchor = NULL;
	StudentLP* headOfList = &headOfListAnchor;

	if (root_adr == NULL)
	{
		return;
	}
	else
	{
		StudentLInsertSorted(headOfList, (*root_adr)->student);
	}

	getNext(headOfList, *root_adr);

	return deepLCopy(headOfList);

	//return headOfList;
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
				return false; // student already exists
			}
			StudentTP newChild = StudentTPAlloc(newStudent);
			(studentNode)->lchild = newChild;
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

	int tempDepthLeft = getDepth(studentNode->lchild);
	int tempDepthRight = getDepth(studentNode->rchild);

	/* use the larger one */
	if (tempDepthLeft > tempDepthRight)
		return (tempDepthLeft + 1);
	else
		return (tempDepthRight + 1);
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
