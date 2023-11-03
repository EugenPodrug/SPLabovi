#pragma once

#define PERSON_MAX_NAME 64

typedef struct _Person
{
	struct _Person* m_Next;
	char m_Name[PERSON_MAX_NAME];
	char m_Surname[PERSON_MAX_NAME];
	int m_BirthYear;
} Person;

/// <summary>
/// Allocates memory for a new person and initializes it with the given values from the standard input.
/// </summary>
/// <returns>A pointer to the newly allocated person, or NULL if the function fails.</returns>
Person* CreatePersonFromInput();

/// <summary>
/// Prints the person information, including name, surname and birth year, to the standard output using printf.
/// </summary>
/// <param name="person">A pointer to the person.</param>
void PrintPerson(Person* person);

/// <summary>
/// Prints the person list to the standard output using printf.
/// </summary>
/// <param name="listHead">A pointer to the head of the person list.</param>
void PrintPersonList(Person* listHead);

/// <summary>
/// Inserts the given person to the back of the person list.
/// </summary>
/// <param name="listHead">A pointer to the head of the person list.</param>
/// <param name="newPerson">A pointer to the person to be inserted.</param>
void InsertPersonToBack(Person* listHead, Person* newPerson);

/// <summary>
/// Inserts the given person to the front of the person list.
/// </summary>
/// <param name="listHead">A pointer to the head of the person list.</param>
/// <param name="newPerson">A pointer to the person to be inserted.</param>
void InsertPersonToFront(Person* listHead, Person* newPerson);

/// <summary>
/// Finds the first person in the person list with the given surname.
/// </summary>
/// <param name="listHead">A pointer to the head of the person list.</param>
/// <param name="surname">A pointer to the surname to be searched for.</param>
/// <returns>A pointer to the first person with the given surname, or NULL if the person is not found.</returns>
Person* FindPersonBySurname(Person* listHead, char* surname);

/// <summary>
/// Removes the given person from the person list.
/// </summary>
/// <param name="listHead">A pointer to the head of the person list.</param>
/// <param name="personToRemove">A pointer to the person to be removed.</param>
/// <returns>If the function succeeds, the return value is nonzero. If the function fails, the return value is zero.</returns>
int RemovePerson(Person* listHead, Person* personToRemove);