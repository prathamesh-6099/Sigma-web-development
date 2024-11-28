#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a contact
struct Contact {
    char name[50];
    char phone[15];
    char email[50];
    char address[100];
};

// File to store contacts
#define FILE_NAME "contacts.dat"

// Function prototypes
void addContact();
void viewContacts();
void searchContact();
void editContact();
void deleteContact();
void clearInputBuffer();

int main() {
    int choice;

    do {
        printf("\n=============================\n");
        printf(" Contact Management System\n");
        printf("=============================\n");
        printf("1. Add Contact\n");
        printf("2. View Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Edit Contact\n");
        printf("5. Delete Contact\n");
        printf("6. Exit\n");
        printf("=============================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                viewContacts();
                break;
            case 3:
                searchContact();
                break;
            case 4:
                editContact();
                break;
            case 5:
                deleteContact();
                break;
            case 6:
                printf("Exiting... Thank you for using the system!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}

// Function to clear the input buffer
void clearInputBuffer() {
    while (getchar() != '\n');
}

// Function to add a contact
void addContact() {
    struct Contact contact;
    FILE *file;

    printf("\nEnter Name: ");
    fgets(contact.name, sizeof(contact.name), stdin);
    strtok(contact.name, "\n"); // Remove newline character

    printf("Enter Phone: ");
    fgets(contact.phone, sizeof(contact.phone), stdin);
    strtok(contact.phone, "\n");

    printf("Enter Email: ");
    fgets(contact.email, sizeof(contact.email), stdin);
    strtok(contact.email, "\n");

    printf("Enter Address: ");
    fgets(contact.address, sizeof(contact.address), stdin);
    strtok(contact.address, "\n");

    file = fopen(FILE_NAME, "ab");
    if (file == NULL) {

        printf("Error opening file!\n");
        return;
    }

    fwrite(&contact, sizeof(contact), 1, file);
    fclose(file);

    printf("Contact added successfully!\n");
}

// Function to view all contacts
void viewContacts() {
    struct Contact contact;
    FILE *file;

    file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("No contacts found!\n");
        return;
    }

    printf("\nList of Contacts:\n");
    printf("===========================================\n");
    while (fread(&contact, sizeof(contact), 1, file)) {
        printf("Name: %s\n", contact.name);
        printf("Phone: %s\n", contact.phone);
        printf("Email: %s\n", contact.email);
        printf("Address: %s\n", contact.address);
        printf("-------------------------------------------\n");
    }
    fclose(file);
}

// Function to search for a contact
void searchContact() {
    struct Contact contact;
    FILE *file;
    char searchName[50];
    int found = 0;

    printf("\nEnter name to search: ");
    fgets(searchName, sizeof(searchName), stdin);
    strtok(searchName, "\n");

    file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("No contacts found!\n");
        return;
    }

    while (fread(&contact, sizeof(contact), 1, file)) {
        if (strcmp(contact.name, searchName) == 0) {
            printf("\nContact Found:\n");
            printf("Name: %s\n", contact.name);
            printf("Phone: %s\n", contact.phone);
            printf("Email: %s\n", contact.email);
            printf("Address: %s\n", contact.address);
            found = 1;
            break;
        }
    }
    fclose(file);

    if (!found) {
        printf("Contact not found!\n");
    }
}

// Function to edit a contact
void editContact() {
    struct Contact contact;
    FILE *file, *tempFile;
    char searchName[50];
    int found = 0;

    printf("\nEnter name of the contact to edit: ");
    fgets(searchName, sizeof(searchName), stdin);
    strtok(searchName, "\n");

    file = fopen(FILE_NAME, "rb");
    tempFile = fopen("temp.dat", "wb");
    if (file == NULL || tempFile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (fread(&contact, sizeof(contact), 1, file)) {
        if (strcmp(contact.name, searchName) == 0) {
            printf("\nEnter new details:\n");
            printf("Enter Name: ");
            fgets(contact.name, sizeof(contact.name), stdin);
            strtok(contact.name, "\n");

            printf("Enter Phone: ");
            fgets(contact.phone, sizeof(contact.phone), stdin);
            strtok(contact.phone, "\n");

            printf("Enter Email: ");
            fgets(contact.email, sizeof(contact.email), stdin);
            strtok(contact.email, "\n");

            printf("Enter Address: ");
            fgets(contact.address, sizeof(contact.address), stdin);
            strtok(contact.address, "\n");

            found = 1;
        }
        fwrite(&contact, sizeof(contact), 1, tempFile);
    }

    fclose(file);
    fclose(tempFile);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (found) {
        printf("Contact updated successfully!\n");
    } else {
        printf("Contact not found!\n");
    }
}

// Function to delete a contact
void deleteContact() {
    struct Contact contact;
    FILE *file, *tempFile;
    char searchName[50];
    int found = 0;

    printf("\nEnter name of the contact to delete: ");
    fgets(searchName, sizeof(searchName), stdin);
    strtok(searchName, "\n");

    file = fopen(FILE_NAME, "rb");
    tempFile = fopen("temp.dat", "wb");
    if (file == NULL || tempFile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (fread(&contact, sizeof(contact), 1, file)) {
        if (strcmp(contact.name, searchName) != 0) {
            fwrite(&contact, sizeof(contact), 1, tempFile);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (found) {
        printf("Contact deleted successfully!\n");
    } else {
        printf("Contact not found!\n");
    }
}
