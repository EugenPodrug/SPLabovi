#include "person.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
	// 
	// Create a sentinel node (a node that doesn't contain any data) to mark the beginning of the list.
	// 

	Person listHead = { .m_Name = NULL, .m_Name = { '\0' }, .m_Surname = { '\0' }, .m_BirthYear = 0 };

	printf(
		"B - Insert person to the back of the list\n"
		"F - Insert person to the front of the list\n"
		"S - Search for a person\n"
		"D - Delete a person\n"
		"P - Print the list\n"
		"Q - Quit\n"
	);

	while (1)
	{
		printf("Enter a command: ");

		char command = 0;
		scanf_s(" %c", &command, 1);

		switch (command)
		{
			case 'B':
			case 'b':
			case 'F':
			case 'f':
			{
				Person* newPerson = CreatePersonFromInput();

				if (newPerson == NULL)
				{
					printf("Failed to create a new person.\n");
					break;
				}

				if (command == 'B' || command == 'b')
					InsertPersonToBack(&listHead, newPerson);
				else
					InsertPersonToFront(&listHead, newPerson);

				break;
			}

			case 'S':
			case 's':
			{
				printf("Enter the person's surname: ");

				char surname[PERSON_MAX_NAME];
				scanf_s("%s", surname, (unsigned int) sizeof(surname));

				Person* foundPerson = FindPersonBySurname(&listHead, surname);

				if (foundPerson == NULL)
					printf("The person was not found.\n");
				else
					PrintPerson(foundPerson);

				break;
			}

			case 'D':
			case 'd':
			{
				printf("Enter the person's surname: ");

				char surname[PERSON_MAX_NAME];
				scanf_s("%s", surname, (unsigned int) sizeof(surname));

				Person* foundPerson = FindPersonBySurname(&listHead, surname);

				if (foundPerson == NULL)
				{
					printf("The person was not found.\n");
					break;
				}

				if (!RemovePerson(&listHead, foundPerson))
					printf("The person was not found.\n");

				break;
			}

			case 'P':
			case 'p':
			{
				PrintPersonList(&listHead);
				break;
			}

			case 'Q':
			case 'q':
			{
				return EXIT_SUCCESS;
			}

			default:
			{
				printf("Invalid command.\n");
				break;
			}
		}
	}

	return EXIT_SUCCESS;
}