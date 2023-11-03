#pragma once

#include <stdio.h>
#include <stdlib.h>

#define STUDENT_MAX_NAME 64
#define STUDENT_MAX_POINTS 30

typedef struct _Student 
{
	char m_Name[STUDENT_MAX_NAME];
	char m_Surname[STUDENT_MAX_POINTS];
	double m_Points;
} Student;

/// <summary>
/// Reads the number of rows in file.
/// </summary>
/// <param name="fileHandle">A handle to the file.</param>
/// <param name="numRows">A pointer to an integer that receives the number of rows in the file.</param>
/// <returns>If the function succeeds, the return value is nonzero. If the function fails, the return value is zero.</returns>
int ReadNumRowsInFile(FILE* fileHandle, int* numRows);

/// <summary>
/// Reads the students from file.
/// </summary>
/// <param name="fileHandle">A handle to the file.</param>
/// <param name="numStudents">The number of students.</param>
/// <param name="outStudents">A pointer to a pointer that receives the address of the array of students.</param>
/// <returns>If the function succeeds, the return value is nonzero. If the function fails, the return value is zero.</returns>
/// <remarks>The caller is responsible for freeing the memory allocated for the array of students.</remarks>
int ReadStudentsFromFile(FILE* fileHandle, int numStudents, Student** outStudents);

/// <summary>
/// Prints student information, including names and points, to the standard output using printf.
/// </summary>
/// <param name="students">A pointer to the array of students.</param>
/// <param name="numStudents">The number of students.</param>
/// <returns>If the function succeeds, the return value is nonzero. If the function fails, the return value is zero.</returns>
int PrintStudents(Student* students, int numStudents);