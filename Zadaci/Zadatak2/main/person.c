#include "person.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Person* CreatePersonFromInput()
{
	Person* newPerson = (Person*) malloc(sizeof(Person));

	if (newPerson == NULL)
		return NULL;

	printf("Enter the person's name: ");
	scanf_s("%s", newPerson->m_Name, (unsigned int) sizeof(newPerson->m_Name));

	printf("Enter the person's surname: ");
	scanf_s("%s", newPerson->m_Surname, (unsigned int) sizeof(newPerson->m_Surname));

	printf("Enter the person's birth year: ");
	scanf_s("%d", &newPerson->m_BirthYear);

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