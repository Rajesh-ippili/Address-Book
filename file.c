#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp = fopen("contact.csv", "w");

    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    fprintf(fp, "#%d\n", addressBook->contactCount);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fp);
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp = fopen("contact.csv", "r");

    if (fp == NULL)
    {
        addressBook->contactCount = 0;
        return;
    }

    if (fscanf(fp, "#%d\n", &addressBook->contactCount) != 1)
    {
        addressBook->contactCount = 0;
        fclose(fp);
        return;
    }

    if (addressBook->contactCount > MAX_CONTACTS)
    {
        addressBook->contactCount = MAX_CONTACTS;
    }

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fscanf(fp, "%49[^,],%19[^,],%49[^\n]\n",
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }

    fclose(fp);
}