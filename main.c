/*
    Name: Ippili Rajesh
    Duration: 02/08/2026 to 09/08/2026
    
    Description:

    Stores contacts with name, phone number and email.
    Validates input names, phone numbers and emails before storing into the file.
    Adds new entries only if the list isn’t full (max 100).
    Prevents duplicates by checking uniqueness of phone numbers and emails.

    Searches contacts by name, phone or email. It also displays contacts with partial matches of name, phone and email.
    Keeps track of matches using a temporary index array for later editing or deleting.
    
    Edits details like name, phone, or email after searching.
    
    Deletes contacts either directly or by selecting anyone from multiple matches.
    
    Lists all contacts in a neat table which was sorted alphabetically by name.

    Can save the made changes before exiting or can exit directly.
    Saves data to a file before exiting, so nothing is lost.
    
    Handles errors gracefully with clear messages for invalid input.
    
    Acts like a mini phonebook, simple yet practical for managing contacts.
    
*/
#include <stdio.h>

#include "contact.h"

int main()
{
    int choice;
    AddressBook addressBook;

    addressBook.contactCount = 0;

    initialize(&addressBook);

    printf("Initializing...\n");

    do
    {
        printf("\n===== ADDRESS BOOK MENU =====\n");

        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Save and Exit\n");

        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                createContact(&addressBook);
                break;

            case 2:
                searchContact(&addressBook);
                break;

            case 3:
                editContact(&addressBook);
                break;

            case 4:
                deleteContact(&addressBook);
                break;

            case 5:
                listContacts(&addressBook);
                break;

            case 6:
                printf("Saving and exiting...\n");
                saveAndExit(&addressBook);
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 6);

    return 0;
}
