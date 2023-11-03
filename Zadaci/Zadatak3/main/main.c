#include "person.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

int main()
{
	// 
	// If the program is run from the Visual Studio debugger, the current directory is the directory of the Visual Studio executable.
	// This function sets the current directory to be the same as the executable directory.
	// 

	if (IsDebuggerPresent())
		FixupCurrentDirectory();

	// 
	// Create a sentinel node (a node that doesn't contain any data) to mark the beginning of the list.
	// 

	Person listHead = { .m_Next = NULL, .m_Name = { '\0' }, .m_Surname = { '\0' }, .m_BirthYear = 0 };

	printf(
		"B - Insert person to the back of the list\n"
		"F - Insert person to the front of the list\n"
		"S - Search for a person\n"
		"D - Delete a person\n"
		"P - Print the list\n"
		"1 - Insert person before a person\n"
		"2 - Insert person after a person\n"
		"3 - Sort the list by surname\n"
		"4 - Print the list to a file\n"
		"5 - Read the list from a file\n"
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

			case '1':
			case '2':
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

				Person* newPerson = CreatePersonFromInput();
				if (newPerson == NULL)
				{
					printf("Failed to create a new person.\n");
					break;
				}

				int insertResult = 0;

				if (command == '1')
					insertResult = InsertPersonBefore(&listHead, foundPerson, newPerson);
				else
					insertResult = InsertPersonAfter(&listHead, foundPerson, newPerson);

				if (insertResult == 0)
					printf("Failed to insert the person.\n");

				break;
			}

			case '3':
			{
				SortPersonList(&listHead);
				break;
			}

			case '4':
			{
				printf("Enter the file name: ");
				
				char fileName[_MAX_PATH];
				scanf_s("%s", fileName, (unsigned int) sizeof(fileName));

				if (!ExportListToFile(&listHead, fileName))
					printf("Failed to print the list to the file.\n");
				
				break;
			}

			case '5':
			{
				printf("Enter the file name: ");

				char fileName[_MAX_PATH];
				scanf_s("%s", fileName, (unsigned int) sizeof(fileName));

				if (!ImportListFromFile(&listHead, fileName))
					printf("Failed to read the list from the file.\n");

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