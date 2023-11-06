#include "person.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Person* CreatePersonFromInput()
{
	Person* newPerson = (Person*) malloc(sizeof(Person));

	if (newPerson == NULL)
		return NULL;

	printf("Enter the new person's info (<name> <surname> <birth year>): ");

	scanf_s("%s %s %d", 
		newPerson->m_Name, (unsigned int) sizeof(newPerson->m_Name),
		newPerson->m_Surname, (unsigned int) sizeof(newPerson->m_Surname),
		&newPerson->m_BirthYear);

	return newPerson;
}

void PrintPerson(Person* person)
{
	printf("%s %s (%d)\n", person->m_Name, person->m_Surname, person->m_BirthYear);
}

void PrintPersonList(Person* listHead)
{
	Person* currentPerson = listHead->m_Next;

	while (currentPerson != NULL)
	{
		PrintPerson(currentPerson);
		currentPerson = currentPerson->m_Next;
	}
}

void InsertPersonToBack(Person* listHead, Person* newPerson)
{
	Person* currentPerson = listHead;

	while (currentPerson->m_Next != NULL)
		currentPerson = currentPerson->m_Next;

	newPerson->m_Next = NULL;
	currentPerson->m_Next = newPerson;
}

void InsertPersonToFront(Person* listHead, Person* newPerson)
{
	newPerson->m_Next = listHead->m_Next;
	listHead->m_Next = newPerson;
}

Person* FindPersonBySurname(Person* listHead, char* surname)
{
	Person* currentPerson = listHead->m_Next;

	while (currentPerson != NULL)
	{
		// 
		// If the current person's surname matches the given surname, return the current person.
		// 

		if (strcmp(currentPerson->m_Surname, surname) == 0)
			return currentPerson;

		currentPerson = currentPerson->m_Next;
	}

	return NULL;
}

int RemovePerson(Person* listHead, Person* personToRemove)
{
	Person* currentPerson = listHead;

	while (currentPerson->m_Next != NULL)
	{
		// 
		// If the next person is the person to remove, remove it, free the memory, and return 1.
		// 

		if (currentPerson->m_Next == personToRemove)
		{
			currentPerson->m_Next = personToRemove->m_Next;
			free(personToRemove);
			return 1;
		}

		currentPerson = currentPerson->m_Next;
	}

	return 0;
}

int InsertPersonBefore(Person* listHead, Person* targetPerson, Person* personToInsert)
{
	Person* currentPerson = listHead;

	while (currentPerson->m_Next != NULL)
	{
		// 
		// If the next person is the target person, insert the person to insert before it and return 1.
		// 

		if (currentPerson->m_Next == targetPerson)
		{
			personToInsert->m_Next = currentPerson->m_Next;
			currentPerson->m_Next = personToInsert;
			return 1;
		}

		currentPerson = currentPerson->m_Next;
	}

	return 0;
}

int InsertPersonAfter(Person* listHead, Person* targetPerson, Person *personToInsert)
{
	Person* currentPerson = listHead->m_Next;

	while (currentPerson != NULL)
	{
		// 
		// If the current person is the target person, insert the person to insert after it and return 1.
		// 

		if (currentPerson == targetPerson)
		{
			personToInsert->m_Next = currentPerson->m_Next;
			currentPerson->m_Next = personToInsert;
			return 1;
		}

		currentPerson = currentPerson->m_Next;
	}

	return 0;
}

void SortPersonList(Person* listHead)
{
	// 
    // Check if the list is empty or has only one element.
	// 

    if (listHead->m_Next == NULL || listHead->m_Next->m_Next == NULL)
		return;

	// 
	// Bubble sort.
	// 
	// We start from the list head and compare the next person with the next person's next person.
	// This way, we can simply swap the next pointers without walking back the list or keeping track of the previous person.
	// 

	while (1)
	{
		int swapped = 0;
		Person* currentPerson = listHead;

		while (currentPerson->m_Next->m_Next != NULL)
		{
			// 
			// Compare current->m_Next and current->m_Next->m_Next.
			// 

			if (strcmp(currentPerson->m_Next->m_Surname, currentPerson->m_Next->m_Next->m_Surname) > 0)
			{
				// 
				// Swap current->m_Next and current->m_Next->m_Next.
				// 

				Person* firstPerson = currentPerson->m_Next;
				Person* secondPerson = firstPerson->m_Next;

				firstPerson->m_Next = secondPerson->m_Next;
				secondPerson->m_Next = firstPerson;
				currentPerson->m_Next = secondPerson;

				swapped = 1;
			}

			// 
			// Move to the next person.
			// 

			currentPerson = currentPerson->m_Next;
		}

		// 
		// Repeat until no swaps are made (the list is sorted).
		// 

		if (!swapped)
			break;
	}
}

int ExportListToFile(Person* listHead, char* filename)
{
	FILE* file = NULL;
	fopen_s(&file, filename, "w");

	if (file == NULL)
		return 0;
	
	Person* currentPerson = listHead->m_Next;
	
	while (currentPerson != NULL)
	{
		fprintf(file, "%s %s (%d)\n", currentPerson->m_Name, currentPerson->m_Surname, currentPerson->m_BirthYear);
		currentPerson = currentPerson->m_Next;
	}
	
	fclose(file);
	return 1;
}

int ImportListFromFile(Person* listHead, char* filename)
{
	FILE* file = NULL;
	fopen_s(&file, filename, "r");
	
	if (file == NULL)
		return 0;
	
	int succeeded = 1;

	while (1)
	{
		Person* newPerson = (Person*) malloc(sizeof(Person));
		
		if (newPerson == NULL)
		{
			succeeded = 0;
			break;
		}

		if (fscanf_s(file, " %s %s (%d)",
			newPerson->m_Name, (unsigned int) sizeof(newPerson->m_Name),
			newPerson->m_Surname, (unsigned int) sizeof(newPerson->m_Surname),
			&newPerson->m_BirthYear) != 3)
		{
			free(newPerson);
			break;
		}
		
		InsertPersonToBack(listHead, newPerson);
	}
	
	fclose(file);
	return succeeded;
}
