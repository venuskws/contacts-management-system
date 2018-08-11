/* ------------------------------------------------------------------
Name: Weisi Kong
Student number: 125400176
Email: wkong10@myseneca.ca
Section: SMM
Date: Dec 10, 2017
----------------------------------------------
Assignment: 2
Milestone:  4
---------------------------------------------- */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

// This source file needs to "know about" the SYSTEM string library functions.
// HINT: The library name is string.h.
//       #include the string.h header file on the next line:
#include <string.h>


// ----------------------------------------------------------
// Include your contactHelpers header file on the next line:
#include "contactHelpers.h"



// ----------------------------------------------------------
// define MAXCONTACTS for sizing contacts array (5):
#define MAXCONTACTS 5

struct Contact contactsArray[MAXCONTACTS] = { { { "Rick",{ '\0' }, "Grimes" },
{ 11, "Trailer Park", 0, "A7A 2J2", "King City" },
{ "4161112222", "4162223333", "4163334444" } },
{
	{ "Maggie", "R.", "Greene" },
	{ 55, "Hightop House", 0, "A9A 3K3", "Bolton" },
	{ "9051112222", "9052223333", "9053334444" } },
	{
		{ "Morgan", "A.", "Jones" },
		{ 77, "Cottage Lane", 0, "C7C 9Q9", "Peterborough" },
		{ "7051112222", "7052223333", "7053334444" } },
		{
			{ "Sasha",{ '\0' }, "Williams" },
			{ 55, "Hightop House", 0, "A9A 3K3", "Bolton" },
			{ "9052223333", "9052223333", "9054445555" } },
};
//------------------------------------------------------
// Function Definitions
//------------------------------------------------------

// +-------------------------------------------------+
// | NOTE:  Copy/Paste your Assignment-2 Milestone-3 |
// |        function definitions below...            |
// +-------------------------------------------------+

// clearKeyboard
void clearKeyboard(void)
{
	while (getchar() != '\n') {
		;
	}
	// empty execution code block on purpose
}


// pause:
void pause(void) {
	printf("(Press Enter to Continue)");
	clearKeyboard();
}


// getInt:
int getInt(void) {
	int vl = 0;
	char NL = 'x';
	scanf("%d%c", &vl, &NL);

	while (NL != '\n') {
		clearKeyboard();
		printf("*** INVALID INTEGER *** <Please enter an integer>: ");
		scanf("%d%c", &vl, &NL);
	}
	return vl;
}

// getIntInRange:
int getIntInRange(int lower, int upper) {
	int value = getInt();
	while (value < lower || value > upper) {
		printf("*** OUT OF RANGE *** <Enter a number between %d and %d>: ", lower, upper);
		value = getInt();
	}
	return value;
}

// yes:
int yes(void) {
	char first, second;
	while (1) {
		scanf(" %c%c", &first, &second);
		if (second == '\n') {
			switch (first) {
			case 'Y':
			case 'y':
				return 1;
			case 'N':
			case 'n':
				return 0;
			default:
				printf("*** INVALID ENTRY *** <Only (Y)es or (N)o are acceptable>: ");
				break;
			}
		}
		else {
			printf("*** INVALID ENTRY *** <Only (Y)es or (N)o are acceptable>: ");
			clearKeyboard();
		}
	}
}

// menu:
int menu(void) {
	int value;
	do {
		printf("Contact Management System\n");
		printf("-------------------------\n");
		printf("1. Display contacts\n");
		printf("2. Add a contact\n");
		printf("3. Update a contact\n");
		printf("4. Delete a contact\n");
		printf("5. Search contacts by cell phone number\n");
		printf("6. Sort contacts by cell phone number\n");
		printf("0. Exit\n\n");
		printf("Select an option:> ");
		value = getIntInRange(0, 6);
		printf("\n");
	} while (value < 0 || value > 6);
	return value;
}

// ContactManagerSystem:
void ContactManagerSystem(void) {
	int done = 0;
	while (done != 1) {
		int answer = menu();
		switch (answer) {
		case 1:
			displayContacts(contactsArray, MAXCONTACTS);
			pause();
			printf("\n");
			break;
		case 2:
			addContact(contactsArray, MAXCONTACTS);
			pause();
			printf("\n");
			break;
		case 3:
			updateContact(contactsArray, MAXCONTACTS);
			pause();
			printf("\n");
			break;
		case 4:
			deleteContact(contactsArray, MAXCONTACTS);
			pause();
			printf("\n");
			break;
		case 5:
			searchContacts(contactsArray, MAXCONTACTS);
			pause();
			printf("\n");
			break;
		case 6:
			sortContacts(contactsArray, MAXCONTACTS);
			pause();
			printf("\n");
			break;
		case 0:
			printf("Exit the program? (Y)es/(N)o: ");
			int exitNum = yes();
			switch (exitNum) {
			case 1:
				printf("\nContact Management System: terminated\n");
				done = 1;
				break;
			case 0:
				printf("\n");
			}
		}
	}
}

// +-------------------------------------------------+
// | NOTE:  Copy/Paste your Assignment-2 Milestone-3 |
// |        empty function definitions below...      |
// +-------------------------------------------------+

// getTenDigitPhone:
void getTenDigitPhone(char telNum[11])
{
	int needInput = 1;

	while (needInput == 1) {
		scanf("%10s", telNum);
		clearKeyboard();

		// (String Length Function: validate entry of 10 characters)
		if (strlen(telNum) == 10)
			needInput = 0;
		else
			printf("Enter a 10-digit phone number: ");
	}
}


// findContactIndex:
int findContactIndex(const struct Contact contacts[], int size, const char cellNum[])
{
	int i;
	for (i = 0; i < size; i++) {
		if (strcmp(contacts[i].numbers.cell, cellNum) == 0) { //could this work?
			return i;
		}
	}
	return -1;
}


// displayContactHeader
void displayContactHeader(void) {
	printf("+");
	int i;
	for (i = 0; i < 77; i++) {
		printf("-");
	}
	printf("+\n");
	printf("|");
	int j;
	for (j = 0; j < 30; j++) {
		printf(" ");
	}
	printf("Contacts Listing");
	int k;
	for (k = 0; k < 31; k++) {
		printf(" ");
	}
	printf("|\n");
	printf("+");
	int h;
	for (h = 0; h < 77; h++) {
		printf("-");
	}
	printf("+\n");
}


// displayContactFooter
void displayContactFooter(int totalContacts) {
	printf("+");
	int i;
	for (i = 0; i < 77; i++) {
		printf("-");
	}
	printf("+\n");
	printf("Total contacts: %d\n\n", totalContacts);
}


// displayContact:
void displayContact(const struct Contact *contact) {
	if (strlen(contact->name.middleInitial) > 0) {
		printf(" %s %s %s\n", contact->name.firstName, contact->name.middleInitial, contact->name.lastName);

	}
	else {
		printf(" %s %s\n", contact->name.firstName, contact->name.lastName);
	}
	printf("    C: %-10s   H: %-10s   B: %-10s\n", contact->numbers.cell, contact->numbers.home, contact->numbers.business);
	printf("       %d %s, ", contact->address.streetNumber, contact->address.street);
	if (contact->address.apartmentNumber > 0) {
		printf("Apt# %d, ", contact->address.apartmentNumber);
	}
	printf("%s, %s\n", contact->address.city, contact->address.postalCode);
}


// displayContacts:
void displayContacts(const struct Contact contacts[], int size) {
	displayContactHeader();
	int i, totalContacts = 0;
	for (i = 0; i < size; i++) {
		if (strlen(contacts[i].numbers.cell) > 0) { // possibly not working
			displayContact(&contacts[i]);
			totalContacts++;
		}
	}
	displayContactFooter(totalContacts);
}


// searchContacts:
void searchContacts(const struct Contact contacts[], int size) {
	printf("Enter the cell number for the contact: ");
	char contactNumber[11];
	getTenDigitPhone(contactNumber);
	int result = findContactIndex(contacts, size, contactNumber);
	if (result > 0) {
		printf("\n");
		displayContact(&(contacts[result])); //could this work?
		printf("\n");
	}
	else if (result == -1) {
		printf("*** Contact NOT FOUND ***\n");
	}
}


// addContact:
void addContact(struct Contact contact[], int size) {
	int i, index = -1;
	for (i = 0; i < size; i++) {
		if (strlen(contact[i].numbers.cell) == 0) {
			index = i;
			break;
		}
	}
	if (index == -1) {
		printf("*** ERROR: The contact list is full! ***\n");
	}
	else {
		getContact(&contact[index]); //could this work?
		printf("--- New contact added! ---\n");
	}
}


// updateContact:
void updateContact(struct Contact contact[], int size) {
	printf("Enter the cell number for the contact: ");
	char contactNumber[11];
	getTenDigitPhone(contactNumber);
	int searchResult = findContactIndex(contact, size, contactNumber);
	if (searchResult == -1) {
		printf("*** Contact NOT FOUND ***\n");
	}
	else {
		printf("\nContact found:\n");
		displayContact(&contact[searchResult]); //could this work?
		printf("\n");
		printf("Do you want to update the name? (y or n): ");
		int answer1 = yes();
		if (answer1 == 1) {
			contact[searchResult].name.middleInitial[0] = '\0';
			getName(&(contact[searchResult].name));
		}
		printf("Do you want to update the address? (y or n): ");
		int answer2 = yes();
		if (answer2 == 1) {
			contact[searchResult].address.apartmentNumber = 0;
			getAddress(&(contact[searchResult].address));
		}
		printf("Do you want to update the numbers? (y or n): ");
		int answer3 = yes();
		if (answer3 == 1) {
			contact[searchResult].numbers.business[0] = '\0';
			contact[searchResult].numbers.home[0] = '\0';
			getNumbers(&(contact[searchResult].numbers));
		}
		printf("--- Contact Updated! ---\n");
	}
}


// deleteContact:
void deleteContact(struct Contact contact[], int size) {
	printf("Enter the cell number for the contact: ");
	char contactNumber[11];
	getTenDigitPhone(contactNumber);
	int searchResult = findContactIndex(contact, size, contactNumber);
	if (searchResult == -1) {
		printf("*** Contact NOT FOUND ***\n");
	}
	else {
		printf("\nContact found:\n");
		displayContact(&contact[searchResult]); //could this work?
		printf("\n");
		printf("CONFIRM: Delete this contact? (y or n): ");
		int answer = yes();
		if (answer == 1) {
			contact[searchResult].numbers.cell[0] = '\0';
			contact[searchResult].numbers.business[0] = '\0';
			contact[searchResult].numbers.home[0] = '\0';
			contact[searchResult].name.middleInitial[0] = '\0';
			contact[searchResult].address.apartmentNumber = 0;
			printf("--- Contact deleted! ---\n");
		}
	}
}


// sortContacts:
void swapIndex(struct Contact contact[], int indexA, int indexB) {
	struct Contact temp;
	temp = *(&contact[indexA]);
	*(&contact[indexA]) = *(&contact[indexB]);
	*(&contact[indexB]) = temp;
}

void sortContacts(struct Contact contact[], int size) {
	int i, j, x;
	for (i = 0; i < size - 1; i++) {
		for (j = 0; j < size - 1 - i; j++) {
			for (x = 0; x < 10; x++) {
				if (contact[j].numbers.cell[x] > contact[j + 1].numbers.cell[x]) {
					swapIndex(contact, j + 1, j);
					break;
				}
				else if (contact[j].numbers.cell[x] < contact[j + 1].numbers.cell[x]) {
					break;
				}
			}
		}
	}
	printf("--- Contacts sorted! ---\n");
}

//int addBetween(int i, int j) {
//	if (i > j)
//		return addBetween(j, i);
//	if (i == j)
//		return i;
//	return i + addBetween(i + 1, j);
//}
//
//int addBetween2(int i, int j) {
//	if (i > j)
//		return addBetween2(j, i);
//	int result = i;
//	for (int k = i + 1; k <= j; k++) {
//		result += k;
//	}
//	return result;
//}