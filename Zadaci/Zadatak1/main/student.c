#include "student.h"

int ReadNumRowsInFile(FILE* fileHandle, int* numRows)
{
	// 
	// Go to the beginning of the file.
	// 

	fseek(fileHandle, 0, SEEK_SET);

	// 
	// Read the file character by character.
	// 

	int ch = 0;
	int numLines = 0;

	while ((ch = fgetc(fileHandle)) != EOF) 
	{
		// 
		// If a newline character is encountered, increment the line count.
		// 

		if (ch == '\n') 
			numLines++;
	}

	// 
	// Add 1 to count the last line if the file doesn't end with a newline character.
	// 

	if (ch != '\n' && numLines > 0) {
		numLines++;
	}

	*numRows = numLines;
	return 1;
}

int ReadStudentsFromFile(FILE* fileHandle, int numStudents, Student** outStudents)
{
	// 
	// Go to the beginning of the file.
	// 

	fseek(fileHandle, 0, SEEK_SET);

	// 
	// Allocate memory for the array of students.
	// 

	Student* students = (Student*) malloc(numStudents * sizeof(Student));
	*outStudents = students;

	if (students == NULL)
		return 0;

	int studentIdx = 0;
	
	// 
	// Read the file line by line.
	// 

	while (!feof(fileHandle))
	{
		fscanf_s(fileHandle, " %s %s %lf",
			students[studentIdx].m_Name,
			(unsigned int) sizeof(students[studentIdx].m_Name),
			students[studentIdx].m_Surname,
			(unsigned int) sizeof(students[studentIdx].m_Surname),
			&students[studentIdx].m_Points
		);

		// 
		// If the number of students read is equal to the number of students
		// that should be read, break out of the loop.
		// 

		if (++studentIdx >= numStudents)
			break;
	}

	return 1;
}

int PrintStudents(Student* students, int numStudents)
{
	for (int studentIdx = 0; studentIdx < numStudents; studentIdx++)
	{
		printf("%s %s %.2lf (%.2lf %%)\n",
			students[studentIdx].m_Name,
			students[studentIdx].m_Surname,
			students[studentIdx].m_Points,
			(students[studentIdx].m_Points / STUDENT_MAX_POINTS) * 100.00
		);
	}

	return 1;
}