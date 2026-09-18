#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fptr=fopen("contacts.csv", "w");

    if(fptr==NULL)
    {
        printf("Error: could not open file.\n");

        return;
    }
    
    for(int i=0; i<addressBook->contactCount; i++)
    {

        fprintf(fptr, "%s,%s,%s\n", 
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
    }

    fclose(fptr);

}

void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fptr=fopen("contacts.csv", "r");

    if(fptr==NULL)
    {
        printf("No existing contacts file found.\n");

        return;
    }
    while(addressBook->contactCount < MAX_CONTACTS &&
          fscanf(fptr,
                 " %49[^,],%14[^,],%49[^\n]",

                 addressBook->contacts[addressBook->contactCount].name,
                 addressBook->contacts[addressBook->contactCount].phone,
                 addressBook->contacts[addressBook->contactCount].email) == 3)
    {
        addressBook->contactCount++;
    }                         

    fclose(fptr);
}
