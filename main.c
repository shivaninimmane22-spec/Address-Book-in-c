/*
Project Name : Address Book Management System
File Name    : contact.c
Description  : Contains all contact operations such as
               Create, Search, Edit, Delete, Display,
               Initialize and Save.
Author       : Shivani Nimmane
INPUT=======================================

Address Book Menu

======================================
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Exit

=======================================
Enter your choice:

OUTPUT=======================================

Address Book Menu

======================================
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Exit

=======================================
Enter your choice: 1
Enter name: SHIVI
Enter phone number: 8908765432
Enter email: SHIVI@GMAIL.COM
Invalid character
Enter email: shivi@gmail.com
Contact created successfully.*/


#include <stdio.h>
#include "contact.h"

int main() {
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
        printf("\n======================================\n");
        printf("\nAddress Book Menu\n");
        printf("\n======================================\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Exit\n");
        printf("\n=======================================\n");

        printf("Enter your choice: ");

        if(scanf("%d", &choice) != 1)
        {
        printf("Invalid input! Please enter a number.\n");
        while(getchar() != '\n');   // Clear the invalid input
        continue;   // Go back to the menu
        }
        
        switch (choice) {
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
                printf("Select sort criteria:\n");
                printf("1. Sort by name\n");
                printf("2. Sort by phone\n");
                printf("3. Sort by email\n");
                printf("4.Exit\n");

                printf("Enter your choice: ");
                int sortChoice;
                scanf("%d", &sortChoice);
                listContacts(&addressBook, sortChoice);
                break;
            case 6:
                printf("Saving and Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    saveContactsToFile(&addressBook);

    return 0;
}
