#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
/*---------------------------------------------------------------*/
/*                    LIST CONTACTS                              */
/*---------------------------------------------------------------*/
void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    int i,j;
     if(addressBook->contactCount==0)
    {
        printf("No contacts available.\n");

        return;
    }
    switch(sortCriteria)
    {
        case 1:
        for(i=0; i<addressBook->contactCount-1; i++)
        {
            for(j=0; j<addressBook->contactCount-i-1; j++)
            {
                if(strcmp(addressBook->contacts[j].name, addressBook->contacts[j+1].name)>0)
                {
                    Contact temp;
                    temp=addressBook->contacts[j];
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                }
            }
        }
        break;

        case 2:
        for(i=0; i<addressBook->contactCount-1; i++)
        {
            for(j=0; j<addressBook->contactCount-i-1; j++)
            {
                if(strcmp(addressBook->contacts[j].phone, addressBook->contacts[j+1].phone)>0)
                {
                    Contact temp;
                    temp=addressBook->contacts[j];
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                }
            }
        }
        break;

        case 3:
        for(i=0; i<addressBook->contactCount-1; i++)
        {
            for(j=0; j<addressBook->contactCount-i-1; j++)
            {
                if(strcmp(addressBook->contacts[j].email, addressBook->contacts[j+1].email)>0)
                {
                    Contact temp;
                    temp=addressBook->contacts[j];
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                }
            }
        }
        break;

        case 4:
        return;

        default:
        printf("Invalid input\n");
        return;
    }
    printf("\n----------------------ALL CONTACT----------------------------\n");

      printf("Index\tName\t\tPhone number\temail\n");

      for(int i=0; i<addressBook->contactCount; i++)
    {
        printf("%-7d %-15s %-15s %-30s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);

    }
    
    //addressBook->contactCount=0;
    //populateAddressBook(addressBook);

}
/*---------------------------------------------------------------------------------------------*/
/*                    INITIALIZE                                                               */
/*---------------------------------------------------------------------------------------------*/
void initialize(AddressBook *addressBook)
 {
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);
    
}
/*----------------------------------------------------------------------------------------------*/
/*                           SVAE AND EXIT                                                      */
/*----------------------------------------------------------------------------------------------*/
void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}
/*----------------------------------------------------------------------------------------------*/
/*                           CREAT CONTACT                                                      */
/*----------------------------------------------------------------------------------------------*/

void createContact(AddressBook *addressBook)
{
	int index=addressBook->contactCount;
    int i;
    
    int atcount=0;
    int dotcount=0;
    int atposition=-1;
    int dotposition =-1;

    int valid;

    if(addressBook->contactCount>=MAX_CONTACTS)
    {
        printf("Address Book is full.\n");
        return;
    }

    /*-------------------NAME--------------------------------------------*/
    while(1)
    {
        int alphabetCount=0;
        int invalid=0;
        printf("Enter name: ");

        scanf(" %49[^\n]",addressBook->contacts[index].name);

    for(i=0; addressBook->contacts[index].name[i]!='\0'; i++)
    {
        if(isalpha(addressBook->contacts[index].name[i]))
        {
            alphabetCount++;
        }
        else if(addressBook->contacts[index].name[i]==' ')
        {
            //space is allowed
        }
        else
        {
            invalid=1;
            break;
        }
    }
    if(invalid==1)
    {
        printf("Name should contain only alphabets and spaces.\n");
        continue;
    }
    if(alphabetCount<4)
    {
        printf("The alphabet contain atleast 4 character\n");
        continue;
    }
    break;
  }
  /*------------------------------------------------PHONE NUMBER--------------------------*/
  while(1)
  {
    int valid =1;

    printf("Enter phone number: ");

    scanf("%14s",addressBook->contacts[index].phone);

    for(i=0; addressBook->contacts[index].phone[i]!='\0'; i++)
    {
        if(!isdigit(addressBook->contacts[index].phone[i]))
        {
            printf("Error: Other than digits, any other character is not allowed in phone number.\n");
            valid = 0;
            break;
        }
    }
        if(valid==0)
        {
            continue;
        }
        if(strlen(addressBook->contacts[index].phone)!=10)
        {
            printf("Error: phone number must contain exactly 10 digits.\n");
            continue;
        }
        if(addressBook->contacts[index].phone[0]<'6' || addressBook->contacts[index].phone[0]>'9')
        {
            printf("Error: first digit must be between 6 and 9.\n");
            continue;
        }
        for(i=0;i<addressBook->contactCount; i++)
        {
            if(strcmp(addressBook->contacts[i].phone, addressBook->contacts[index].phone)==0)
            {
                printf("Error: phone number already exists.\n");
                valid=0;
                break;
            }
        }
        if(valid==0)
        {
            continue;
        }
        else
        break;
}

/*----------------------------------EMAIL----------------------------------------------*/
  while(1)
  {
    atcount=0;
    dotcount=0;
    atposition=-1;
    dotposition=-1;
    valid=1;

    printf("Enter email: ");

    scanf("%49s",addressBook->contacts[index].email);

    for(i=0; addressBook->contacts[index].email[i]!='\0'; i++)
    {
        if(islower(addressBook->contacts[index].email[i] )|| isdigit(addressBook->contacts[index].email[i]))
        {
            //valid character
        }
        else if(addressBook->contacts[index].email[i]=='@')
        {
            atcount++;
            atposition=i;
        }
        else if(addressBook->contacts[index].email[i]=='.')
        {
            dotcount++;
            dotposition=i;
        }
        else
        {
            printf("Invalid character\n");
            valid=0;
            break;
        }
    }
    if(valid==0)
    {
        continue;
    }
    //exactly one @
    if(atcount==0)
    {
        printf("Error: missing @.\n");
        continue;
    }
    if(atcount>1)
    {
        printf("Error: multiple @ symbols are not allowed.\n");
        continue;
    }
    //exactly one dot
    if(dotcount==0)
    {
        printf("Error: missing dot.\n");
        continue;
    }
    if(dotcount>1)
    {
        printf("Error: multiple dots are not allowed.\n");
        continue;
    }
    //dot must come after @
    if(dotposition<atposition)
    {
        printf("Error: dot must appear after @.\n");
        continue;
    }
    //atleast one character between @ and dot
    if(dotposition==atposition+1)
    {
        printf("Error: at least one character is required between @ and dot.\n");
        continue;
    }
    //no extra characters after .com
    if(strcmp(&addressBook->contacts[index].email[dotposition],
                  ".com") != 0)
    {
        printf("Error: Extra characters after the domain.\n");
        continue;
    }
    //check uniqueness
    for(i=0; i<addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].email,addressBook->contacts[index].email)==0)
        {
            printf("Error: email already exists.\n");
            valid=0;
            break;
        }
    }
    if(valid==0)
    {
        continue;
    }
    break;
  }

    addressBook->contactCount++;

    printf("Contact created successfully.\n");
    
}
/*-------------------------------------------------------------------------------------*/
/*                          SEARCH CONTACT                                             */
/*-------------------------------------------------------------------------------------*/
void searchContact(AddressBook *addressBook) 
{
    int choice;
    char searchvalue[50];
    int found=0;

    printf("Search by:\n");

    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");

    printf("Enter choice: ");

    if(scanf("%d", &choice) != 1)
    {
    printf("Invalid input!\n");

    while(getchar() != '\n');

    return;
    }

    if(choice < 1 || choice > 3)
    {
        printf("Invalid choice.\n");

        return;
    }

    printf("Enter search value: ");

    if(choice==1)
    {
        scanf(" %[^\n]",searchvalue);
    }
    else
    {
        scanf("%s", searchvalue);
    }
    
    for(int i=0; i<addressBook->contactCount; i++)
   {
        int match=0;

    if(choice == 1 && strstr(addressBook->contacts[i].name,searchvalue)!=NULL)
    {
        match=1;
    }
    if(choice == 2 && strstr(addressBook->contacts[i].phone,searchvalue)!=NULL)
    {
        match=1;
    }    
    if(choice == 3 && strstr(addressBook->contacts[i].email,searchvalue)!=NULL)
    {
        match=1;        
    }
    if(match)
   {
    if(found == 0)
    {
        printf("\n-------------------- Matching Contacts --------------------\n");
        printf("S.No\tName\t\tPhone Number\tEmail\n");
        printf("-----------------------------------------------------------\n");
    }

    printf("%d\t%-15s %-15s %s\n",
           found + 1,
           addressBook->contacts[i].name,
           addressBook->contacts[i].phone,
           addressBook->contacts[i].email);

    found++;
   }
  }
    if(found==0)
    {
    printf("Contact not found.\n");
    }
    else 
    {
    printf("-----------------------------------------------------------\n");
    }
}
/*-------------------------------------------------------------------------------------*/
/*                            EDIT CONTACT                                           */
/*-------------------------------------------------------------------------------------*/
void editContact(AddressBook *addressBook)
{
    int index;
    int choice;

    printf("Enter contact index to edit: ");

    if(scanf("%d", &index) != 1)
    {
    printf("Invalid input!\n");

    while(getchar() != '\n');

    return;
    }

    if(index<1 ||index>addressBook->contactCount)
    {
        printf("Invalid index.\n");
        return;
    }
    index--;
    printf("\nWhat do you want to edit?\n");

    printf("1.Name\n");
    printf("2.phone\n");
    printf("3.Email\n");
    
    printf("Enter your choice: ");

    if(scanf("%d", &choice) != 1)
    {
    printf("Invalid input!\n");

    while(getchar() != '\n');

    return;
    }

    switch(choice)
    {
        case 1:
        {
           while(1)
           {
               int alphabetCount=0;
               int invalid=0;

               printf("Enter new name: ");
               scanf(" %49[^\n]", addressBook->contacts[index].name);

               for(int i=0; addressBook->contacts[index].name[i]!='\0'; i++)
               {
                if(isalpha(addressBook->contacts[index].name[i]))
                {
                    alphabetCount++;
                }
                else if(addressBook->contacts[index].name[i]==' ')
                {
                    /*space allowed*/
                }
                else
                {
                    invalid=1;
                    break;
                }
            }
            if(invalid)
            {
                printf("Error: Name must contain only alphabets and spaces.\n");

                continue;
            }

            if(alphabetCount < 4)
            {
                printf("Error: Name must contain at least 4 alphabets.\n");

                continue;
            }
            break;
        }
         break;
    }
            

        case 2:
        {
           while(1)
           {
            int valid=1;

            printf("Enter new phone: ");

            scanf("%14s", addressBook->contacts[index].phone);
            
            for(int i=0; addressBook->contacts[index].phone[i]!='\0'; i++)
            {
                if(!isdigit(addressBook->contacts[index].phone[i]))
                {
                    printf("Error: phone number must contain only digits.\n");

                    valid=0;

                    break;
                }
            }
            if(!valid)
            {
                continue;
            }
            
            if(strlen(addressBook->contacts[index].phone)!=10)
            {
                printf("Erroe: phone number must contain exactly 10 digits.\n");

                continue;
            }
            if (addressBook->contacts[index].phone[0] < '6' || addressBook->contacts[index].phone[0] > '9')
                {
                    printf("Error: First digit must be between 6 and 9.\n");

                    continue;
                }


                for (int i = 0; i < addressBook->contactCount; i++)
                {
                    if (i != index &&
                        strcmp(addressBook->contacts[i].phone, addressBook->contacts[index].phone) == 0)
                    {
                        printf("Error: Phone number already exists.\n");

                        valid = 0;

                        break;
                    }
                }
                 if (!valid)
                {
                    continue;
                }
                break;
            }
            break;
        }


        case 3:
        {
          while(1)
          {
            char email[50];

            int atCount = 0;
            int dotCount = 0;

            int atPosition = -1;
            int dotPosition = -1;

            int valid = 1;
            printf("Enter new email: ");
            scanf("%49s", email);

            for(int i=0; email[i]!='\0'; i++)
            {
                if(islower(email[i]) || isdigit(email[i]))
                {
                    /*valid*/
                }
                else if (email[i]=='@')
                {
                    atCount++;

                    atPosition=i;
                }
                else if(email[i] == '.')
                {
                    dotCount++;

                    dotPosition = i;
                }
                else
                {
                    printf("Error: email contains invalid character.\n");

                    valid=0;

                    break;
                }
            }
            if(!valid)
            {
                continue;
            }

            if(atCount != 1)
            {
                printf("Error: email must contain exactly one @ symbole.\n");

                continue;
            }

            if(atPosition==0)
            {
                printf("Error: character are required before @.\n");

                continue;
            }
            if(dotCount != 1)
            {

            printf("Error: Email must contain exactly one dot.\n");

            continue;

            }

            if(dotPosition <= atPosition+1)
            {
                printf("Error: characters are required between @ and dot.\n");

                continue;
            }

            if(strcmp(&email[dotPosition],".com")!=0)
            {
                printf("Error: email must end with .com.\n");

                continue;
            }
            for(int i=0; i<addressBook->contactCount; i++)
            {
                if(i != index && strcmp(addressBook->contacts[i].email, email)==0)
                {
                    printf("Error: email already exist.\n");

                    valid=0;

                    break;
                }
            }
            if(!valid)
            {
                continue;
            }
            strcpy(addressBook->contacts[index].email, email);
            break;
          }

            break;
        }
        default:
        {

            printf("Invalid choice.\n");

            return;
        }
    }

    printf("contact updated successfully.\n");
}
/*-------------------------------------------------------------------------------------*/
/*                        DELETE CONTACT                                               */
/*-------------------------------------------------------------------------------------*/
void deleteContact(AddressBook *addressBook)
{
	int index;

    printf("Enter contact index to delet: ");

    if(scanf("%d", &index) != 1)
    {
    printf("Invalid input!\n");

    while(getchar() != '\n');

    return;
    }

    if(index<1|| index>addressBook->contactCount)
    {
        printf("Invalid index.\n");
        return ;
    }
    index--;

    for(int i=index; i<addressBook->contactCount-1; i++)
    
    {
        addressBook->contacts[i]=addressBook->contacts[i+1];
    }

    addressBook->contactCount--;

    printf("Contact deletede successfully.\n");
   
}
