#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "contact.h"
#include "file.h"


void listContacts(AddressBook *addressBook)
{
    Contact temp;

    // Sort contacts alphabetically by name
    for (int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (int j = i + 1; j < addressBook->contactCount; j++)
        {
            if (strcmp(addressBook->contacts[i].name,
                       addressBook->contacts[j].name) > 0)
            {
                temp = addressBook->contacts[i];
                addressBook->contacts[i] =
                    addressBook->contacts[j];
                addressBook->contacts[j] = temp;
            }
        }
    }

    // If no contacts
    if (addressBook->contactCount == 0)
    {
        printf("\n");
        printf("========================================\n");
        printf("          NO CONTACTS AVAILABLE\n");
        printf("========================================\n");
        return;
    }

    // Header
    printf("\n");
    printf("==========================================================================\n");
    printf("                         ADDRESS BOOK CONTACTS\n");
    printf("==========================================================================\n");

    printf("| %-3s | %-20s | %-15s | %-25s |\n",
           "No", "NAME", "PHONE NUMBER", "EMAIL");

    printf("--------------------------------------------------------------------------\n");

    // Print contacts
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("| %-3d | %-20s | %-15s | %-25s |\n",
               i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);

        printf("--------------------------------------------------------------------------\n");
    }

    // Footer
    printf("\n");
    printf("Total Contacts : %d\n", addressBook->contactCount);
    printf("==========================================================================\n");
}


void initialize(AddressBook *addressBook)
{
    loadContactsFromFile(addressBook);
}


void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook);
    exit(EXIT_SUCCESS);
}


void createContact(AddressBook *addressBook)
{
    if (addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("Address Book is full!\n");
        return;
    }

    char name[50];
    char phone[20];
    char email[50];

    int res;


    /* NAME */

    do
    {
        printf("Enter the name: ");
        scanf(" %49[^\n]", name);

        res = validate_name(name);

    } while (res == 0);


    /* PHONE */

    do
    {
        printf("Enter the phone number: ");
        scanf(" %19s", phone);

        res = validate_number(phone);

        if (res == 1)
        {
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].phone, phone) == 0)
                {
                    printf("Error: Number already present.\n");
                    res = 0;
                    break;
                }
            }
        }

    } while (res == 0);


    /* EMAIL */

    do
    {
        printf("Enter the email: ");
        scanf(" %49[^\n]", email);

        res = validate_email(email);

        if (res == 1)
        {
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].email, email) == 0)
                {
                    printf("Error: Email already present.\n");
                    res = 0;
                    break;
                }
            }
        }

    } while (res == 0);


    strcpy(addressBook->contacts[addressBook->contactCount].name, name);

    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);

    strcpy(addressBook->contacts[addressBook->contactCount].email, email);

    addressBook->contactCount++;

    printf("Contact created successfully.\n");
}


/* SEARCH BY PHONE */

int search_by_phone(AddressBook *addressBook)
{
    char phone[20];

    printf("Enter the number to search: ");
    scanf(" %19s", phone);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0)
        {
            printf("\nName : %s\n",
                   addressBook->contacts[i].name);

            printf("Phone: %s\n",
                   addressBook->contacts[i].phone);

            printf("Email: %s\n",
                   addressBook->contacts[i].email);

            return i;
        }
    }

    return -1;
}


/* SEARCH BY NAME */

int search_by_name(AddressBook *addressBook)
{
    char name[50];

    printf("Enter the name to search: ");
    scanf(" %49[^\n]", name);

    int count = 0;
    int result = -1;

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].name, name) == 0)
        {
            printf("\nName : %s\n",
                   addressBook->contacts[i].name);

            printf("Phone: %s\n",
                   addressBook->contacts[i].phone);

            printf("Email: %s\n",
                   addressBook->contacts[i].email);

            count++;
            result = i;
        }
    }

    if (count == 0)
    {
        return -1;
    }

    if (count == 1)
    {
        return result;
    }

    printf("\nMultiple contacts found. Search using phone number.\n");

    return search_by_phone(addressBook);
}


/* SEARCH BY EMAIL */

int search_by_email(AddressBook *addressBook)
{
    char email[50];

    printf("Enter the email to search: ");
    scanf(" %49[^\n]", email);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].email, email) == 0)
        {
            printf("\nName : %s\n",
                   addressBook->contacts[i].name);

            printf("Phone: %s\n",
                   addressBook->contacts[i].phone);

            printf("Email: %s\n",
                   addressBook->contacts[i].email);

            return i;
        }
    }

    return -1;
}


/* SEARCH CONTACT */

void searchContact(AddressBook *addressBook)
{
    int choice;
    int result;

    do
    {
        printf("\nSearch Contact\n");
        printf("1. Search by name\n");
        printf("2. Search by phone\n");
        printf("3. Search by email\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                result = search_by_name(addressBook);
                break;

            case 2:
                result = search_by_phone(addressBook);
                break;

            case 3:
                result = search_by_email(addressBook);
                break;

            default:
                printf("Invalid choice.\n");
                continue;
        }

        if (result == -1)
        {
            printf("CONTACT NOT FOUND\n");
        }

    } while (choice < 1 || choice > 3);
}


/* EDIT CONTACT */

void editContact(AddressBook *addressBook)
{
    int choice;
    int result = -1;

    do
    {
        printf("\nSearch contact to edit:\n");
        printf("1. Search by name\n");
        printf("2. Search by phone\n");
        printf("3. Search by email\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                result = search_by_name(addressBook);
                break;

            case 2:
                result = search_by_phone(addressBook);
                break;

            case 3:
                result = search_by_email(addressBook);
                break;

            case 4:
                return;

            default:
                printf("Invalid choice.\n");
                continue;
        }

        if (result == -1)
        {
            printf("CONTACT NOT FOUND\n");
        }

    } while (result == -1);


    int option;

    do
    {
        printf("\nWhat do you want to change?\n");
        printf("1. Change name\n");
        printf("2. Change phone number\n");
        printf("3. Change email\n");
        printf("Enter your choice: ");

        scanf("%d", &option);

    } while (option < 1 || option > 3);


    char name[50];
    char phone[20];
    char email[50];

    int res;


    switch (option)
    {
        case 1:

            do
            {
                printf("Enter new name: ");
                scanf(" %49[^\n]", name);

                res = validate_name(name);

            } while (res == 0);

            strcpy(addressBook->contacts[result].name, name);

            printf("Name changed successfully.\n");

            break;


        case 2:

            do
            {
                printf("Enter new phone number: ");
                scanf(" %19s", phone);

                res = validate_number(phone);

                if (res == 1)
                {
                    for (int i = 0;
                         i < addressBook->contactCount;
                         i++)
                    {
                        if (i != result &&
                            strcmp(addressBook->contacts[i].phone,
                                   phone) == 0)
                        {
                            printf("Phone number already exists.\n");
                            res = 0;
                            break;
                        }
                    }
                }

            } while (res == 0);

            strcpy(addressBook->contacts[result].phone, phone);

            printf("Phone number changed successfully.\n");

            break;


        case 3:

            do
            {
                printf("Enter new email: ");
                scanf(" %49[^\n]", email);

                res = validate_email(email);

                if (res == 1)
                {
                    for (int i = 0;
                         i < addressBook->contactCount;
                         i++)
                    {
                        if (i != result &&
                            strcmp(addressBook->contacts[i].email,
                                   email) == 0)
                        {
                            printf("Email already exists.\n");
                            res = 0;
                            break;
                        }
                    }
                }

            } while (res == 0);

            strcpy(addressBook->contacts[result].email, email);

            printf("Email changed successfully.\n");

            break;
    }
}


/* DELETE CONTACT */

void deleteContact(AddressBook *addressBook)
{
    int choice;
    int result = -1;

    do
    {
        printf("\nSearch contact to delete:\n");
        printf("1. Search by name\n");
        printf("2. Search by phone\n");
        printf("3. Search by email\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

    } while (choice < 1 || choice > 3);


    switch (choice)
    {
        case 1:
            result = search_by_name(addressBook);
            break;

        case 2:
            result = search_by_phone(addressBook);
            break;

        case 3:
            result = search_by_email(addressBook);
            break;
    }


    if (result == -1)
    {
        printf("CONTACT NOT FOUND\n");
        return;
    }


    for (int i = result;
         i < addressBook->contactCount - 1;
         i++)
    {
        addressBook->contacts[i] =
            addressBook->contacts[i + 1];
    }


    addressBook->contactCount--;

    printf("Contact deleted successfully.\n");
}


/* VALIDATE NAME */

int validate_name(char *str)
{
    if (str[0] == '\0')
    {
        printf("Invalid name\n");
        return 0;
    }

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!((str[i] >= 'A' && str[i] <= 'Z') ||
              (str[i] >= 'a' && str[i] <= 'z') ||
              str[i] == '.' ||
              str[i] == ' '))
        {
            printf("Invalid name\n");
            return 0;
        }
    }

    return 1;
}


/* VALIDATE PHONE */

int validate_number(char *str)
{
    if (strlen(str) != 10)
    {
        printf("Invalid phone number\n");
        return 0;
    }

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] < '0' || str[i] > '9')
        {
            printf("Invalid phone number\n");
            return 0;
        }
    }

    return 1;
}


/* VALIDATE EMAIL */

int validate_email(char *str)
{
    int length = strlen(str);

    if (length < 6)
    {
        printf("Invalid email\n");
        return 0;
    }

    if ((str[0] >= '0' && str[0] <= '9') ||
        str[0] == '.' ||
        str[0] == '@')
    {
        printf("Invalid email\n");
        return 0;
    }


    int atCount = 0;
    int atPosition = -1;


    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '@')
        {
            atCount++;
            atPosition = i;
        }
    }


    if (atCount != 1)
    {
        printf("Invalid email\n");
        return 0;
    }


    if (atPosition == 0 ||
        atPosition == length - 1)
    {
        printf("Invalid email\n");
        return 0;
    }


    for (int i = 0; i < atPosition; i++)
    {
        if (!((str[i] >= 'a' && str[i] <= 'z') ||
              (str[i] >= 'A' && str[i] <= 'Z') ||
              (str[i] >= '0' && str[i] <= '9') ||
              str[i] == '.' ||
              str[i] == '_' ||
              str[i] == '-' ||
              str[i] == '+'))
        {
            printf("Invalid email\n");
            return 0;
        }

        if (str[i] == '.' && str[i + 1] == '.')
        {
            printf("Invalid email\n");
            return 0;
        }
    }


    if (str[atPosition - 1] == '.')
    {
        printf("Invalid email\n");
        return 0;
    }


    for (int i = atPosition + 1;
         str[i] != '\0';
         i++)
    {
        if (!((str[i] >= 'a' && str[i] <= 'z') ||
              (str[i] >= 'A' && str[i] <= 'Z') ||
              (str[i] >= '0' && str[i] <= '9') ||
              str[i] == '.' ||
              str[i] == '-'))
        {
            printf("Invalid email\n");
            return 0;
        }

        if (str[i] == '.' && str[i + 1] == '.')
        {
            printf("Invalid email\n");
            return 0;
        }
    }


    if (length < 4 ||
        strcmp(&str[length - 4], ".com") != 0)
    {
        printf("Invalid email\n");
        return 0;
    }

    return 1;
}