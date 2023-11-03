#include "student.h"
#include "util.h"

#include <Windows.h>

#define EXIT_FAILED_TO_OPEN_FILE -1
#define EXIT_FAILED_TO_READ_NUM_STUDENTS -2
#define EXIT_FAILED_TO_READ_STUDENTS -3
#define EXIT_FAILED_TO_PRINT_STUDENTS -4

int main() 
{
	// 
	// If the program is run from the Visual Studio debugger, the current directory is the directory of the Visual Studio executable.
	// This function sets the current directory to be the same as the executable directory.
	// 

	if (IsDebuggerPresent())
		FixupCurrentDirectory();

	FILE* fileHandle = NULL;
	fopen_s(&fileHandle, "students.txt", "r");

	if (fileHandle == NULL) 
	{
		printf("Failed to open the file.\n");
		return EXIT_FAILED_TO_OPEN_FILE;
	}

	int numStudents = 0;
	if (!ReadNumRowsInFile(fileHandle, &numStudents))
	{
		fclose(fileHandle);
		printf("Failed to read the number of students.\n");
		return EXIT_FAILED_TO_READ_NUM_STUDENTS;
	}

	Student* students = NULL;
	if (!ReadStudentsFromFile(fileHandle, numStudents, &students))
	{
		fclose(fileHandle);
		printf("Failed to read the students from the file.\n");
		return EXIT_FAILED_TO_READ_STUDENTS;
	}

	fclose(fileHandle);

	if (!PrintStudents(students, numStudents))
	{
		free(students);
		printf("Failed to print the students.\n");
		return EXIT_FAILED_TO_PRINT_STUDENTS;
	}

	free(students);
	return EXIT_SUCCESS;
}