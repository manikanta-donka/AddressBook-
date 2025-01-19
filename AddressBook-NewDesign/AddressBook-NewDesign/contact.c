#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include <ctype.h>
#include <stdio_ext.h>


void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}
// Validates if the Name contains only alphabetic characters and space.
int validate_name(char *name)  
{
    int i = 0;
    while(name[i] != '\0')
    {
        if(!(isalpha(name[i]) || name[i] == ' ')) // using isalpha function to check alphabets or not
        {
            return 1; // return Invalid Name
        }
        i++;
    }
    return 0; // Return Valid name

}
// Validation if the phone number is exactly 10 digits long and numerics.
int validate_number(char *phone) 
{
    int len = strlen(phone);
    if(len !=10)  
    {
        return 1; // Invalid number length
    }
    int i=0;
    while(phone[i] != '\0')
    {
        if(!(isdigit(phone[i])))
        {
            return 1; // Non-digit character found
        }
        i++;
    }
    return 0; // Valid number
}

// Checks if the phone number is unique in the address book.
int unique_number(AddressBook *addressBook,char *phone)
{
    for(int i = 0;i < addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].phone,phone) == 0)
        {
            return 1; // Phone number already exists
        }
    }
    return 0; // Unique phone number
}

// Validates if the email ends with "gmail.com"
int validate_gmail(char *email)
{
    char check[100] = "@gmail.com";
    if(!(strstr(email,check)))
    {
        return 1; // Invalid email
    }
    return 0; // Valid email
}

// Checks if the email is unique in the address book.
int unique_gmail(AddressBook *addressBook,char *email)
{
    for(int i = 0;i < addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].email,email) == 0)
        return 1; // Email is already exists
    }
    return 0; // Unique email
}

// Creates a new contact and add it to the address book.
void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    // Prompt for create and validate the contact's name 
    char name[20];
    printf("Enter the name : ");
    scanf(" %[^\n]",name);
    while(validate_name(name) == 1) // Function call
    {
        printf("INFO : Name validation not done, Please enter the valid name...\n");
        printf("Enter the name: ");
        scanf(" %[^\n]",name);
    }
    strcpy(addressBook -> contacts[addressBook -> contactCount].name,name); // After validation add name to the address book

    // Prompt for create and validate the contanct's phone number
    char phone[11];
    printf("Enter the mobile number : ");
    scanf(" %[^\n]",phone);
    while((validate_number(phone) == 1) || (unique_number(addressBook,phone) == 1))
    {
        if(validate_number(phone) == 1)
        {
            printf("INFO : Name validation not done, Please enter the valid number...\n");
        }
        else if(unique_number(addressBook,phone) == 1)
        {
            printf("Number is already Existing\n");
        }
        printf("Enter the mobile number :");
        scanf(" %[^\n]",phone);
    }
    strcpy(addressBook -> contacts[addressBook -> contactCount].phone,phone); // After validation add the phone number to the address book

    // Prompt for create and validate the contact's email.
    char email[50];
    printf("Enter the mail address : ");
    scanf(" %[^\n]",email);
    while((validate_gmail(email) == 1) || (unique_gmail(addressBook,email) == 1))
    {
        if(validate_gmail(email) == 1)
        {
            printf("INFO : Mail validation not done, Please enter the valid mail...\n");
        }
        else if(unique_gmail(addressBook,email) == 1)
        {
            printf("Email is already existing\n");
        }
        printf("Enter the mail address :");
        scanf(" %[^\n]",email);

    }
    strcpy(addressBook -> contacts[addressBook -> contactCount].email,email); // After validation add the email to the address book
    addressBook ->contactCount++; // Increment the contact count.

    printf("Contact Created successfully");
}



// Searches for a contact by name, phone number, or email.

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    char searchTerm[50];
    printf("Enter the name, mobile number, or email to search for: ");
    scanf(" %[^\n]", searchTerm);

    int found = 0;

    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        // Compare the search term with the name, mobile number, and email
        if (strcasestr(addressBook -> contacts[i].name, searchTerm) || 
            strcasecmp(addressBook -> contacts[i].name, searchTerm) == 0 ||
            strcasecmp(addressBook -> contacts[i].phone, searchTerm) == 0 ||
            strcasecmp(addressBook -> contacts[i].email, searchTerm) == 0) 
        {
            if(found == 0)
            {
                printf("Contacts Found:\n");
            }
            // Print the matching contact information
            printf("Contact %d:\n",found + 1);
            printf("Name: %s\n", addressBook -> contacts[i].name);
            printf("Mobile Number: %s\n", addressBook -> contacts[i].phone);
            printf("Email: %s\n", addressBook -> contacts[i].email);
            found++;
        }
    }
    if (!found) 
    {
        printf("No contact found with the given information.\n");
    }    
}

// Edits an existing contact.
void editContact(AddressBook *addressBook)
{
    int n;
    int flag = 1; // Control flag for menu loop

    while (flag)
    {
        // Menu for searching contacts
        printf("Search the contact by:\n1.Name\n2.Mobile number\n3.Email\n4.Exit\n");
        scanf("%d", &n);

        // Exit the loop if user chooses option 4
        if (n == 4)
        {
            flag = 0; // Exit the loop
            break;
        }

        // Variables to hold search criteria
        char name[100];
        char phone[100];
        char email[100];
        int found = 0; // Flag to indicate if a contact was found
        int count = 0; // Count of similar contacts
        int j = -1;  // Index of found contact

        // Switch case to search by different criteria
        switch (n)
        {
            case 1:
                // Search by name
                printf("Enter the current contact name: ");
                scanf(" %[^\n]", name);

                // Loop through the contacts to find matching name
                for (int i = 0; i < addressBook->contactCount; i++)
                {
                    if (strcasestr(addressBook->contacts[i].name, name))
                    {
                        found = 1;
                        j = i;
                        count++;
                    }
                    if (strcasecmp(addressBook->contacts[i].name, name) == 0)
                    {
                        found = 1;
                        j = i;
                        count++;
                    }
                }

                // If multiple contacts with similar names are found
                if (count > 1)
                {
                    printf("Similar names found. Please refine your search.\n");
                    return;
                }

                // If no contact is found
                if (!found)
                {
                    printf("Contact not found.\n");
                    break;
                }

                break;

            case 2:
                // Search by mobile number
                printf("Enter the current contact mobile number: ");
                scanf(" %[^\n]", phone);

                // Loop through the contacts to find matching mobile number
                for (int i = 0; i < addressBook->contactCount; i++)
                {
                    if (strcmp(addressBook->contacts[i].phone, phone) == 0)
                    {
                        found = 1;
                        j = i;
                        break; // Mobile number is unique, so break after finding one
                    }
                }

                // If no contact is found
                if (!found)
                {
                    printf("Contact not found.\n");
                    break;
                }

                break;

            case 3:
                // Search by email
                printf("Enter the current contact email: ");
                scanf(" %[^\n]", email);

                // Loop through the contacts to find matching email
                for (int i = 0; i < addressBook->contactCount; i++)
                {
                    if (strcmp(addressBook->contacts[i].email, email) == 0)
                    {
                        found = 1;
                        j = i;
                        break; // Email is unique, so break after finding one
                    }
                }

                // If no contact is found
                if (!found)
                {
                    printf("Contact not found.\n");
                    break;
                }

                break;

            case 4:
                // Exit the menu
                printf("Exiting menu.\n");
                break;

            default:
                // Handle invalid input
                printf("Invalid choice. Please try again.\n");
                break;
        }

        // If contact was found, proceed to edit
        if (found && j != -1)
        {
            // Display current contact details
            printf("Name: %s\n", addressBook->contacts[j].name);
            printf("Mobile Number: %s\n", addressBook->contacts[j].phone);
            printf("Email: %s\n", addressBook->contacts[j].email);

            int m;
            // Menu to choose which detail to edit
            printf("What do you want to edit?\n1.Name\n2.Mobile number\n3.Email\n4.Exit\n");
            scanf("%d", &m);

            switch (m)
            {
                case 1:
                    // Edit name
                    printf("Enter the new name: ");
                    scanf(" %[^\n]", name);

                    // Validate new name
                    while (validate_name(name) == 1)
                    {
                        printf("INFO: Name validation failed. Please enter a valid name: ");
                        scanf(" %[^\n]", name);
                    }

                    // Update the name in the address book
                    strcpy(addressBook->contacts[j].name, name);
                    printf("Name successfully edited.\n");
                    break;;

                case 2:
                    // Edit mobile number
                    printf("Enter the new mobile number: ");
                    scanf(" %[^\n]", phone);

                    // Validate new mobile number
                    while (validate_number(phone) == 1)
                    {
                        printf("INFO: Mobile number validation failed. Please enter a valid number: ");
                        scanf(" %[^\n]", phone);
                    }

                    // Ensure the new number is unique
                    while (unique_number(addressBook, phone) == 1)
                    {
                        printf("Number already exists. Please enter a unique mobile number: ");
                        scanf(" %[^\n]", phone);
                    }

                    // Update the mobile number in the address book
                    strcpy(addressBook->contacts[j].phone, phone);
                    printf("Mobile number successfully edited.\n");
                    break;;

                case 3:
                    // Edit email
                    printf("Enter the new email: ");
                    scanf(" %[^\n]", email);

                    // Validate new email
                    while (validate_gmail(email) == 1)
                    {
                        printf("INFO: Email validation failed. Please enter a valid email: ");
                        scanf(" %[^\n]", email);
                    }

                    // Ensure the new email is unique
                    while (unique_gmail(addressBook, email) == 1)
                    {
                        printf("Email already exists. Please enter a unique email: ");
                        scanf(" %[^\n]", email);
                    }

                    // Update the email in the address book
                    strcpy(addressBook->contacts[j].email, email);
                    printf("Email successfully edited.\n");
                    break;;

                case 4:
                    // Exit the edit menu
                    printf("Exiting edit menu.\n");
                    break;

                default:
                    // Handle invalid input for the edit menu
                    printf("Invalid choice. Please try again.\n");
                    break;
            }
        }
    }
    printf("Edit contact successfully.");
}


// Delete Existing cintact
void deleteContact(AddressBook *addressBook)
{
    // Initialize flag to control the loop and variable for user input
    int flag = 1;
    int n;

    while (flag)
    {
        // Display menu options for user to choose a deletion method
        printf("Enter the choice:\n1.Name\n2.Mobile number\n3.Email\n4.Exit\n");
        scanf("%d", &n);

        // If user chooses to exit, break the loop
        if (n == 4)
        {
            flag = 0;
            break;
        }

        // Variables to hold contact details
        char name[200];
        char phone[200];
        char email[200];
        int i = 0;
        int j; // Store the index of the contact to be deleted
        int found = 0; // Flag to check if the contact was found
        int count = 0; // Count similar contacts

        // Switch case to handle deletion by name, mobile number, or email
        switch (n)
        {
        case 1:
            // Delete contact by name
            printf("Enter the name:");
            scanf(" %[^\n]", name);

            // Search for the contact by name
            for (i = 0; i < addressBook->contactCount; i++)
            {
                if (strcasestr(addressBook->contacts[i].name, name))
                {
                    found = 1;
                    j = i;
                    count++;
                }
                if (strcasecmp(addressBook->contacts[i].name, name) == 0)
                {
                    found = 1;
                    j = i; // Store index of the found contact
                    count++;
                }
            }

            // If exactly one contact found, delete it
            if (count == 1)
            {
                for (i = j; i < addressBook->contactCount; i++)
                {
                    addressBook->contacts[i] = addressBook->contacts[i + 1];
                }
                addressBook->contactCount--; // Decrease contact count
                printf("Contact is deleted\n");
            }

            // If multiple similar contacts found, prompt for refinement
            if (count > 1)
            {
                printf("Similar contacts found\n");
            }

            // If no contact found, display message
            if (!found)
            {
                printf("Contact not found\n");
                flag = 1; // Continue loop
            }
            break;
            
        case 2:
            // Delete contact by mobile number
            printf("Enter the mobile number:");
            scanf(" %[^\n]", phone);

            // Search for the contact by mobile number
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].phone, phone) == 0)
                {
                    found = 1;
                    j = i;
                    break;
                }
            }

            // If contact found, delete it
            if (found == 1)
            {
                for (i = j; i < addressBook->contactCount; i++)
                {
                    addressBook->contacts[i] = addressBook->contacts[i + 1];
                }
                addressBook->contactCount--; // Decrease contact count
                printf("Contact is deleted\n");
            }

            // If no contact found, display message
            if (!found)
            {
                printf("Contact not found\n");
                flag = 1; // Continue loop
            }
            break;

        case 3:
            // Delete contact by email
            printf("Enter the email:");
            scanf(" %[^\n]", email);

            // Search for the contact by email
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].email, email) == 0)
                {
                    found = 1;
                    j = i;
                    break;
                }
            }

            // If contact found, delete it
            if (found == 1)
            {
                for (i = j; i < addressBook->contactCount; i++)
                {
                    addressBook->contacts[i] = addressBook->contacts[i + 1];
                }
                addressBook->contactCount--; // Decrease contact count
                printf("Contact is deleted\n");
            }

            // If no contact found, display message
            if (!found)
            {
                printf("Contact not found\n");
                flag = 1; // Continue loop
            }
            break;

        case 4:
            // Exit menu
            printf("Exiting menu.\n");
            break;

        default:
            // Handle invalid input
            printf("Invalid choice. Please try again.\n");
            break;
        }
    }
}


// Display all created contacts 
void listContacts(AddressBook *addressBook) 
{
    // Sort contacts alphabetically by name using bubble sort
    for (int i = 0; i < addressBook->contactCount - 1; i++) 
    {
        for (int j = 0; j < addressBook->contactCount - i - 1; j++) 
        {
            // Compare adjacent contacts' names and swap if out of order
            if (strcmp(addressBook->contacts[j].name, addressBook->contacts[j + 1].name) > 0) 
            {
                // Swap the contacts
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }

    // Print table headers for contacts list
    printf("Name\t\t\t Phone\t\t\t Email\n");

    // Loop through all contacts and print their details
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        // Print each contact's name, phone, and email in a formatted manner
        printf("%-20s\t %-20s\t %-20s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
}

