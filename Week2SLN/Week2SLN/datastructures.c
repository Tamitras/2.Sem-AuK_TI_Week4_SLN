/*
 ============================================================================
 Aufgabe     : Datenstrukturen
 Autor       : koetter
 Matrikel    : DIESE DATEI NICHT AENDERN
 Version     : DIESE DATEI NICHT AENDERN
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


#include "dhbwtest.h"
#include "dhbwstudent.h"
#include "dhbwstudentlist.h"
#include "dhbwstudenttree.h"
#include "dhbwstudentmap.h"

 //some string constants
static const char TRUETEXT[] = "Passed";
static const char FALSETEXT[] = "FAILED";
static const char DS_LIST[] = "List";
static const char DS_TREE[] = "Tree";
static const char DS_MAP[] = "Map";

static const char OP_EMPTYSIZE[] = "Empty size is 0";
static const char OP_EMPTYDEPTH[] = "Empty depth is 0";
static const char OP_NONULLS[] = "Contains No Nulls";
static const char OP_MINLENGTH[] = "Need >=3 elements";
static const char OP_FIND[] = "Find (existing)";
static const char OP_FINDNONEXIST[] = "Find (nonexist)";
static const char OP_FINDMATRIKEL[] = "Find By Matr (existing)";
static const char OP_FINDMATRIKEL_UNBALANCED[] = "Find By Matr (unbalanced tree)";
static const char OP_FINDMATRIKELNONEXIST[] = "Find By Matr (nonexist)";
static const char OP_CONTAINS[] = "Contains (existing)";
static const char OP_CONTAINSNONEXIST[] = "Contains (nonexist)";
static const char OP_FINDNAME[] = "Find By Name (existing)";
static const char OP_FINDNAMENONEXIST[] = "Find By Name (nonexist)";
static const char OP_FINDNAME_UNBALANCED[] = "Find By Name (unbalanced tree)";
static const char OP_EXTRACT_FIRST[] = "Extract first element";
static const char OP_EXTRACT_SECOND[] = "Extract second element";
static const char OP_EXTRACT_LAST[] = "Extract last element";
static const char OP_EXTRACT_ALL[] = "Extract all elements";
static const char OP_INSERT_BEGINNING[] = "Insert at beginning";
static const char OP_INSERT_END[] = "Insert at end";
static const char OP_INSERT_SORTED[] = "Insert sorted";
static const char OP_INSERT_UNBALANCED[] = "Insert (unbalanced tree)";
static const char OP_INSERT_SIZE[] = "Insert and size";
static const char OP_INSERT_REHASH[] = "Insert and rehash";
static const char OP_INSERT_EXISTING[] = "Insert already existing";
static const char OP_REHASH[] = "Rehash";
static const char OP_INSERT_HASH_DUMB[] = "Insert with dumbHashByMatr";
static const char OP_INSERT_HASH_MATR[] = "Insert with hashByMatr";
static const char OP_INSERT_HASH_NAME[] = "Insert with hashByName";
static const char OP_INSERT_HASH_BOTH[] = "Insert with hashByBoth";
static const char OP_FIND_HASH_DUMB[] = "Find with dumbHashByMatr";
static const char OP_FIND_HASH_MATR[] = "Find with hashByMatr";
static const char OP_FIND_HASH_NAME[] = "Find with hashByName";
static const char OP_FIND_HASH_BOTH[] = "Find with hashByBoth";
static const char OP_LIST[] = "To list";
static const char OP_SORTED_LIST[] = "To sorted list";
static const char OP_DEPTH_UNBALANCED[] = "Depth (unbalanced)";
static const char OP_DEPTH_BALANCED[] = "Depth (balanced)";

void outputBenchmarkScore(const char* datastructure, const char* operation,
	clock_t begin, clock_t end) {
	double time = ((end - begin) * 1000.0) / CLOCKS_PER_SEC;
	printf("|%-10s|%-30s|%10.2f|\n", datastructure, operation,
		time);
}

void outputTestResult(const char* datastructure, const char* operation,
	bool result, Student_p element) {
	printf("|%-10s|%-30s|%-6s|%-20s|\n", datastructure, operation,
		(result ? TRUETEXT : FALSETEXT),
		element != NULL ? toString(element) : "");
}

bool StudentLTest(StudentLP* inputList) {

	bool result = true;

	printf("\n\n%s -> starting tests\n", DS_LIST);

	//basic structural tests
	if (result) {
		result = testNoNulls(inputList);
		outputTestResult(DS_LIST, OP_NONULLS, result, NULL);
	}

	if (result) {
		result = StudentLSize(inputList) >= 3;
		outputTestResult(DS_LIST, OP_MINLENGTH, result, NULL);
	}

	//test finding of existing/nonexisting by matrikel

	if (result) {

		StudentLP current = *inputList;

		while (current != NULL) {
			Student_p current_element = current->student;
			StudentLP found_element = StudentLFindByMatr(inputList,
				current_element->matrnr);
			if (found_element == NULL
				|| !StudentEquals(current_element,
					found_element->student)) {
				result = false;
				break;
			}
			current = current->next;
		}
		outputTestResult(DS_LIST, OP_FINDMATRIKEL, result,
			current != NULL ? current->student : NULL);
	}

	if (result) {
		//7 digit matrikel never exists
		StudentLP found_element = StudentLFindByMatr(inputList, 1234567);
		result = found_element == NULL;
		outputTestResult(DS_LIST, OP_FINDMATRIKELNONEXIST, result,
			found_element != NULL ? found_element->student : NULL);
	}

	//test finding of existing/nonexisting by name

	if (result) {

		StudentLP current = *inputList;

		while (current != NULL) {
			Student_p current_element = current->student;
			StudentLP found_element = StudentLFindByName(inputList,
				current_element->lastname);
			if (found_element == NULL
				|| !(strcmp(current_element->lastname,
					found_element->student->lastname) == 0)) {
				result = false;
				break;
			}
			current = current->next;
		}
		outputTestResult(DS_LIST, OP_FINDNAME, result,
			current != NULL ? current->student : NULL);
	}

	if (result) {
		//Bielefeld doesn't exist
		StudentLP found_element = StudentLFindByName(inputList,
			"MrBielefeld404");
		result = found_element == NULL;
		outputTestResult(DS_LIST, OP_FINDNAMENONEXIST, result,
			found_element != NULL ? found_element->student : NULL);
	}

	//test sorted insert

	if (result) {
		StudentLP sorted_students_anchor = NULL;
		StudentLP* sorted_students = &sorted_students_anchor;

		StudentLP current = *inputList;

		while (current != NULL) {
			StudentLInsertSorted(sorted_students, deepCopy(current->student));
			current = current->next;
		}
		Student_p zSTudent = StudentAlloc("999999 Zzzzacharias");
		StudentLInsertSorted(sorted_students, zSTudent);
		Student_p aSTudent = StudentAlloc("000000 Aaaaron");
		StudentLInsertSorted(sorted_students, aSTudent);

		result = result && testMatrSort(sorted_students);
		outputTestResult(DS_LIST, OP_INSERT_SORTED, result, NULL);
	}

	//test extraction of second/first/last/all

	if (result) {
		int lengthBefore = StudentLSize(inputList);

		StudentLP second_element = (*inputList)->next;
		Student_p second_student = second_element->student;

		StudentLP compare_element = StudentLExtractStudent(inputList,
			second_student);

		int lengthAfter = StudentLSize(inputList);

		result = second_element == compare_element
			&& (lengthAfter == lengthBefore - 1);
		outputTestResult(DS_LIST, OP_EXTRACT_SECOND, result, second_student);

		StudentLPFree(compare_element);
	}

	if (result) {
		int lengthBefore = StudentLSize(inputList);

		StudentLP first_element = (*inputList);
		Student_p first_student = first_element->student;

		StudentLP compare_element = StudentLExtractStudent(inputList,
			first_student);

		int lengthAfter = StudentLSize(inputList);

		result = first_element == compare_element
			&& (lengthAfter == lengthBefore - 1);
		outputTestResult(DS_LIST, OP_EXTRACT_FIRST, result, first_student);

		StudentLPFree(compare_element);
	}

	if (result) {
		int lengthBefore = StudentLSize(inputList);

		StudentLP last_element = (*inputList);
		while (last_element->next != NULL) {
			last_element = last_element->next;
		}

		Student_p last_student = last_element->student;

		StudentLP compare_element = StudentLExtractStudent(inputList,
			last_student);

		int lengthAfter = StudentLSize(inputList);

		result = last_element == compare_element
			&& (lengthAfter == lengthBefore - 1);
		outputTestResult(DS_LIST, OP_EXTRACT_LAST, result, last_student);

		StudentLPFree(compare_element);
	}

	if (result) {

		StudentLP current_element = (*inputList);
		Student_p current_student = NULL;
		while (current_element != NULL) {

			int lengthBefore = StudentLSize(inputList);

			current_student = current_element->student;

			StudentLP compare_element = StudentLExtractStudent(inputList,
				current_student);

			int lengthAfter = StudentLSize(inputList);

			result = current_element == compare_element
				&& (lengthAfter == lengthBefore - 1);
			if (!result) {
				break;
			}

			current_element = current_element->next;
			StudentLPFree(compare_element);
		}
		outputTestResult(DS_LIST, OP_EXTRACT_ALL, result, result ? NULL : current_student);

	}

	if (result) {
		printf("%s -> all tests %s\n\n", DS_LIST, TRUETEXT);
	}
	else {
		printf("%s -> test aborted after %s\n\n", DS_LIST, FALSETEXT);
	}

	return result;
}


bool StudentTTest(StudentLP* inputList) {

	bool result = true;

	printf("\n\n%s -> starting tests\n", DS_TREE);

	StudentTP* tree = malloc(sizeof(StudentTP));
	*tree = NULL;

	//test create empty

	if (result) {
		result = StudentTSize(tree) == 0;
		outputTestResult(DS_TREE, OP_EMPTYSIZE, result, NULL);
	}

	if (result) {
		result = StudentTDepth(tree) == 0;
		outputTestResult(DS_TREE, OP_EMPTYDEPTH, result, NULL);
	}

	//test insertion and size

	if (result) {

		int originalSize = 0;

		StudentLP current = *inputList;

		while (current != NULL) {
			Student_p current_element = current->student;
			originalSize++;
			StudentTInsertSorted(tree, deepCopy(current_element));

			if (StudentTSize(tree) != originalSize) {
				result = false;
				break;
			}
			current = current->next;
		}
		outputTestResult(DS_TREE, OP_INSERT_SIZE, result,
			current != NULL ? current->student : NULL);
	}

	//test contains

	if (result) {

		StudentLP current = *inputList;

		while (current != NULL) {
			Student_p current_element = current->student;
			if (!StudentTContainsStudent(tree, current_element)) {
				result = false;
				break;
			}
			current = current->next;
		}
		outputTestResult(DS_TREE, OP_CONTAINS, result,
			current != NULL ? current->student : NULL);
	}

	if (result) {
		//Bielefeld doesn't exist
		Student_p test = StudentAlloc("123456 MrBielefeld404");
		result = !StudentTContainsStudent(tree, test);
		outputTestResult(DS_TREE, OP_CONTAINSNONEXIST, result, test);
	}

	//test finding of existing/nonexisting by matrikel

	if (result) {

		StudentLP current = *inputList;

		while (current != NULL) {
			Student_p current_element = current->student;
			//printf("Looking for..(%d)..", current->student->matrnr);
			StudentTP found_element = StudentTFindByMatr(tree,current_element->matrnr);
			if (found_element == NULL|| !StudentEquals(current_element,found_element->student)) {
				result = false;
				break;
			}
			current = current->next;
		}
		outputTestResult(DS_TREE, OP_FINDMATRIKEL, result,
			current != NULL ? current->student : NULL);
	}

	if (result) {
		//7 digit matrikel never exists
		StudentLP found_element = StudentLFindByMatr(inputList, 1234567);
		result = found_element == NULL;
		outputTestResult(DS_TREE, OP_FINDMATRIKELNONEXIST, result,
			found_element != NULL ? found_element->student : NULL);
	}

	//test finding of existing/nonexisting by name

	if (result) {

		StudentLP current = *inputList;

		while (current != NULL) {
			Student_p current_element = current->student;
			StudentTP found_element = StudentTFindByName(tree,current_element->lastname);
			if (found_element == NULL || !(strcmp(current_element->lastname, found_element->student->lastname) == 0)) {
				result = false;
				break;
			}
			current = current->next;
		}
		outputTestResult(DS_TREE, OP_FINDNAME, result,
			current != NULL ? current->student : NULL);
	}

	if (result) {
		//Bielefeld doesn't exist
		StudentLP found_element = StudentLFindByName(inputList,
			"MrBielefeld404");
		result = found_element == NULL;
		outputTestResult(DS_TREE, OP_FINDNAMENONEXIST, result,
			found_element != NULL ? found_element->student : NULL);
	}

	//test sorted output
	StudentLP* sortedList = NULL;
	if (result) {

		sortedList = StudentTToSortedList(tree);

		result = testMatrSort(sortedList);
		outputTestResult(DS_TREE, OP_SORTED_LIST, result, NULL);
	}

	//test lop-sided insert depth

	if (result) {

		StudentTP* unbalanced_tree = malloc(sizeof(StudentTP));
		*unbalanced_tree = NULL;

		int originalSize = 0;

		StudentLP current = *sortedList;

		while (current != NULL) {
			Student_p current_element = current->student;
			originalSize++;
			StudentTInsertSorted(unbalanced_tree, deepCopy(current_element));

			if (StudentTDepth(unbalanced_tree) != originalSize) {
				result = false;
				break;
			}
			current = current->next;
		}
		outputTestResult(DS_TREE, OP_DEPTH_UNBALANCED, result,
			current != NULL ? current->student : NULL);

		StudentTFree(unbalanced_tree);
	}

	//test balanced insert depth

	if (result) {

		StudentTP* balanced_tree = malloc(sizeof(StudentTP));
		*balanced_tree = NULL;

		int originalSize = 0;

		int balanced_matrs[] = { 444444, 222222, 111111, 666666, 333333, 555555,
				777777 };
		int balanced_matrs_depth = 3;

		for (int i = 0; i < sizeof(balanced_matrs) / sizeof(int); i++) {
			StudentTInsertSorted(balanced_tree,
				generateTestStudent(balanced_matrs[i]));
		}

		result = StudentTDepth(balanced_tree) == balanced_matrs_depth;

		outputTestResult(DS_TREE, OP_DEPTH_BALANCED, result, NULL);

		StudentTFree(balanced_tree);
	}

	StudentLFree(sortedList);
	StudentTFree(tree);


	if (result) {
		printf("%s -> all tests %s\n\n", DS_TREE, TRUETEXT);
	}
	else {
		printf("%s -> test aborted after %s\n\n", DS_TREE, FALSETEXT);
	}

	return result;
}

bool StudentMTest(StudentLP* inputList) {

	bool result = true;

	printf("\n\n%s -> starting tests\n", DS_MAP);

	StudentMP map = StudentMPAlloc(4, dumbHashByMatr);

	//test empty

	if (result) {
		result = StudentMSize(map) == 0;
		outputTestResult(DS_MAP, OP_EMPTYSIZE, result, NULL);
	}

	//test insertion and size

	if (result) {

		int originalSize = 0;
		StudentLP current = *inputList;

		while (current != NULL) {
			Student_p current_element = current->student;
			originalSize++;
			bool insertResult = StudentMInsert(map, deepCopy(current_element));

			if (!insertResult || StudentMSize(map) != originalSize) {
				result = false;
				break;
			}

			current = current->next;

			if (originalSize >= 2) {
				break;
			}

		}
		outputTestResult(DS_MAP, OP_INSERT_SIZE, result,
			current != NULL ? current->student : NULL);

		if (result) {
			int oldsize = map->maxsize;
			int newsize = oldsize * 2;
			StudentMRehash(map, newsize);
			result = (map->maxsize == newsize);
			outputTestResult(DS_MAP, OP_REHASH, result, NULL);
		}

		//insert up to rehash
		if (result) {
			while (current != NULL) {
				Student_p current_element = current->student;
				originalSize++;
				bool insertResult = StudentMInsert(map,
					deepCopy(current_element));

				if (!insertResult || StudentMSize(map) != originalSize) {
					result = false;
					break;
				}

				current = current->next;
			}
			outputTestResult(DS_MAP, OP_INSERT_REHASH, result,
				current != NULL ? current->student : NULL);
		}
	}

	//test finding of existing/nonexisting

	if (result) {

		StudentLP current = *inputList;

		while (current != NULL) {
			Student_p current_element = current->student;
			Student_p found_element = StudentMFind(map, current_element);
			if (found_element == NULL
				|| !StudentEquals(current_element, found_element)) {
				result = false;
				break;
			}
			current = current->next;
		}
		outputTestResult(DS_MAP, OP_FIND, result,
			current != NULL ? current->student : NULL);
	}

	if (result) {
		//should never exist unless you created custom testdata
		Student_p test = StudentAlloc("123456 MrBielefeld404");
		Student_p found_element = StudentMFind(map, test);
		result = found_element == NULL;
		outputTestResult(DS_MAP, OP_FINDNONEXIST, result,
			found_element != NULL ? found_element : NULL);
	}

	//test inserting already isnerted elements again

	if (result) {

		StudentLP current = *inputList;

		int originalsize = StudentMSize(map);

		while (current != NULL) {
			Student_p current_element = current->student;
			bool insertResult = StudentMInsert(map, current_element);

			if (insertResult || StudentMSize(map) != originalsize) {
				result = false;
				break;
			}

			current = current->next;
		}
		outputTestResult(DS_MAP, OP_INSERT_EXISTING, result,
			current != NULL ? current->student : NULL);
	}

	//test list

	if (result) {
		StudentLP* list;
		list = StudentMToList(map);

		result = StudentLSize(list) == StudentLSize(inputList);
		outputTestResult(DS_MAP, OP_LIST, result, NULL);
		StudentLFree(list);
	}

	//test other hash functions

	if (result) {
		free(map);
		map = StudentMPAlloc(4, hashByMatr);

		int originalSize = 0;
		StudentLP current = *inputList;

		while (current != NULL) {
			Student_p current_element = current->student;
			originalSize++;
			bool insertResult = StudentMInsert(map, deepCopy(current_element));

			if (!insertResult || StudentMSize(map) != originalSize) {
				result = false;
				break;
			}

			current = current->next;
		}
		outputTestResult(DS_MAP, OP_INSERT_HASH_MATR, result,
			current != NULL ? current->student : NULL);
	}

	if (result) {
		free(map);
		map = StudentMPAlloc(4, hashByName);

		int originalSize = 0;
		StudentLP current = *inputList;

		while (current != NULL) {
			Student_p current_element = current->student;
			originalSize++;
			bool insertResult = StudentMInsert(map, deepCopy(current_element));

			if (!insertResult || StudentMSize(map) != originalSize) {
				result = false;
				break;
			}

			current = current->next;
		}
		outputTestResult(DS_MAP, OP_INSERT_HASH_NAME, result,
			current != NULL ? current->student : NULL);
	}

	if (result) {
		free(map);
		map = StudentMPAlloc(4, hashByBoth);

		int originalSize = 0;
		StudentLP current = *inputList;

		while (current != NULL) {
			Student_p current_element = current->student;
			originalSize++;
			bool insertResult = StudentMInsert(map, deepCopy(current_element));

			if (!insertResult || StudentMSize(map) != originalSize) {
				result = false;
				break;
			}

			current = current->next;
		}
		outputTestResult(DS_MAP, OP_INSERT_HASH_BOTH, result,
			current != NULL ? current->student : NULL);
	}

	free(map);

	if (result) {
		printf("%s -> all tests %s\n\n", DS_MAP, TRUETEXT);
	}
	else {
		printf("%s -> test aborted after %s\n\n", DS_MAP, FALSETEXT);
	}

	return result;
}



void StudentLBenchmarkBuiltin(StudentLP* inputList) {

	clock_t begin, end;

	//benchmark inserting at beginning
	{
		begin = clock();

		StudentLP list_anchor = NULL;
		StudentLP* benchmark_list = &list_anchor;

		StudentLP current = *inputList;

		while (current != NULL) {
			StudentLInsertFirst(benchmark_list, deepCopy(current->student));
			current = current->next;
		}

		end = clock();
		outputBenchmarkScore(DS_LIST, OP_INSERT_BEGINNING, begin, end);

		StudentLFree(benchmark_list);
	}

	//benchmark inserting at end
	{
		begin = clock();

		StudentLP list_anchor = NULL;
		StudentLP* benchmark_list = &list_anchor;

		StudentLP current = *inputList;

		while (current != NULL) {
			StudentLInsertLast(benchmark_list, deepCopy(current->student));
			current = current->next;
		}

		end = clock();
		outputBenchmarkScore(DS_LIST, OP_INSERT_END, begin, end);

		StudentLFree(benchmark_list);
	}


}


void StudentLBenchmarkTasks(StudentLP* inputList) {

	clock_t begin, end;

	StudentLP list_anchor = NULL;
	StudentLP* benchmark_list = &list_anchor;

	long long tmp = 0;

	//benchmark inserting sorted
	{
		begin = clock();

		StudentLP current = *inputList;

		while (current != NULL) {
			StudentLInsertSorted(benchmark_list, deepCopy(current->student));
			current = current->next;
		}

		end = clock();
		outputBenchmarkScore(DS_LIST, OP_INSERT_SORTED, begin, end);


	}

	//benchmark search by matrikel
	{
		begin = clock();

		StudentLP current = *inputList;


		while (current != NULL) {
			StudentLFindByMatr(benchmark_list, current->student->matrnr);
			current = current->next;
		}


		end = clock();
		outputBenchmarkScore(DS_LIST, OP_FINDMATRIKEL, begin, end);
	}

	//benchmark search by name
	{
		begin = clock();

		StudentLP current = *inputList;

		while (current != NULL) {
			StudentLFindByName(benchmark_list, current->student->lastname);
			current = current->next;
		}

		end = clock();
		outputBenchmarkScore(DS_LIST, OP_FINDNAME, begin, end);
	}
	StudentLFree(benchmark_list);
}



void StudentTBenchmark(StudentLP* inputList) {

	clock_t begin, end;

	StudentLP list_anchor = NULL;
	StudentLP* sorted_list = &list_anchor;


	StudentTP* tree = malloc(sizeof(StudentTP));
	*tree = NULL;

	//benchmark inserting sorted
	{
		begin = clock();

		StudentLP current = *inputList;

		while (current != NULL) {
			StudentTInsertSorted(tree, deepCopy(current->student));
			current = current->next;
		}

		end = clock();
		outputBenchmarkScore(DS_TREE, OP_INSERT_SORTED, begin, end);


	}

	{
		begin = clock();
		sorted_list = StudentTToSortedList(tree);
		end = clock();
		outputBenchmarkScore(DS_TREE, OP_SORTED_LIST, begin, end);
	}


	//benchmark search by matrikel
	{
		begin = clock();

		StudentLP current = *inputList;


		while (current != NULL) {
			StudentTFindByMatr(tree, current->student->matrnr);
			current = current->next;
		}


		end = clock();
		outputBenchmarkScore(DS_TREE, OP_FINDMATRIKEL, begin, end);
	}

	//benchmark search by name
	{
		begin = clock();

		StudentLP current = *inputList;

		while (current != NULL) {
			StudentTFindByName(tree, current->student->lastname);
			current = current->next;
		}

		end = clock();
		outputBenchmarkScore(DS_TREE, OP_FINDNAME, begin, end);
	}

	StudentTP* unbalanced_tree = malloc(sizeof(StudentTP));
	*unbalanced_tree = NULL;

	//benchmark inserting sorted
	{
		begin = clock();

		StudentLP current = NULL;
		if (sorted_list)
		{
			current = *sorted_list;
		}

		while (current != NULL) {
			StudentTInsertSorted(unbalanced_tree, deepCopy(current->student));
			current = current->next;
		}

		end = clock();
		outputBenchmarkScore(DS_TREE, OP_INSERT_UNBALANCED, begin, end);


	}


	//benchmark search by matrikel
	{
		begin = clock();

		StudentLP current = *inputList;


		while (current != NULL) {
			StudentTFindByMatr(unbalanced_tree, current->student->matrnr);
			current = current->next;
		}


		end = clock();
		outputBenchmarkScore(DS_TREE, OP_FINDMATRIKEL_UNBALANCED, begin, end);
	}

	//benchmark search by name
	{
		begin = clock();

		StudentLP current = *inputList;

		while (current != NULL) {
			StudentTFindByName(unbalanced_tree, current->student->lastname);
			current = current->next;
		}

		end = clock();
		outputBenchmarkScore(DS_TREE, OP_FINDNAME_UNBALANCED, begin, end);
	}


	StudentTFree(tree);
	StudentTFree(unbalanced_tree);
	StudentLFree(sorted_list);
}


void StudentMBenchmarkForHash(StudentLP* inputList, const char* hashInsertOPName, const char* hashFindOPName, int (*hashf)(Student_p student, int maxsize)) {

	clock_t begin, end;


	//benchmark inserting
	{
		begin = clock();

		StudentMP map = StudentMPAlloc(64, hashf);

		StudentLP current = *inputList;

		while (current != NULL) {
			bool insertResult = StudentMInsert(map, deepCopy(current->student));
			current = current->next;
		}

		end = clock();
		outputBenchmarkScore(DS_MAP, hashInsertOPName, begin, end);


		begin = clock();

		current = *inputList;

		while (current != NULL) {
			Student_p insertResult = StudentMFind(map, deepCopy(current->student));
			current = current->next;
		}

		end = clock();
		outputBenchmarkScore(DS_MAP, hashFindOPName, begin, end);

		StudentMPFree(map);
	}


}

void StudentMBenchmark(StudentLP* inputList) {

	clock_t begin, end;

	StudentMBenchmarkForHash(inputList, OP_INSERT_HASH_DUMB, OP_FIND_HASH_DUMB, dumbHashByMatr);
	StudentMBenchmarkForHash(inputList, OP_INSERT_HASH_MATR, OP_FIND_HASH_MATR, hashByMatr);
	StudentMBenchmarkForHash(inputList, OP_INSERT_HASH_NAME, OP_FIND_HASH_NAME, hashByName);
	StudentMBenchmarkForHash(inputList, OP_INSERT_HASH_BOTH, OP_FIND_HASH_BOTH, hashByBoth);

}

int main(int argc, char* argv[]) {


	clock_t begin, end;

	begin = clock();

	if (argc != 2) {
		fprintf(stderr, "Usage: %s [<file>|<number of random students>]\n",
			argv[0]);
		exit(EXIT_FAILURE);
	}

	printf("Argument=%s\n", argv[1]);
	int amount = atoi(argv[1]);
	printf("Amount=%d\n", amount);

	StudentLP* inputList;
	if (amount > 0) {
		inputList = generateTestData(amount, true);
	}
	else {
		inputList = StudentsFromFile(argv[1]);
	}

	if (StudentLImplemented()) {
		StudentLP* listForTest = deepLCopy(inputList);
		StudentLTest(listForTest);
		StudentLFree(listForTest);
	}

	if (StudentTImplemented()) {
		StudentLP* listForTest = deepLCopy(inputList);
		StudentTTest(listForTest);
		StudentLFree(listForTest);
	}

	if (StudentMImplemented()) {
		StudentLP* listForTest = deepLCopy(inputList);
		StudentMTest(listForTest);
		StudentLFree(listForTest);
	}

	{//builtin benchmak
		StudentLP* listForTest = deepLCopy(inputList);
		StudentLBenchmarkBuiltin(listForTest);
		StudentLFree(listForTest);
	}

	if (StudentLImplemented()) {
		StudentLP* listForTest = deepLCopy(inputList);
		StudentLBenchmarkTasks(listForTest);
		StudentLFree(listForTest);
	}

	if (StudentTImplemented()) {
		StudentLP* listForTest = deepLCopy(inputList);
		StudentTBenchmark(listForTest);
		StudentLFree(listForTest);
	}

	if (StudentMImplemented()) {
		StudentLP* listForTest = deepLCopy(inputList);
		StudentMBenchmark(listForTest);
		StudentLFree(listForTest);
	}

	end = clock();

	exit(EXIT_SUCCESS);
}
