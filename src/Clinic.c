/*
 ============================================================================
 Name        : Clinic.c
 Author      : Ahmed Ali
 Date        : 14 Aug 2023
 Description : Clinic Management System Project Using C
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* limiting the patient name and slot numbers in clinic */
#define MAX_NAME_LENGTH 20
#define MAX_SLOTS 5

/* define the boolean data type */
typedef enum {
	False = 0, True = 1
} bool;

/* structure for patient data */
typedef struct PatientNode {
	char name[MAX_NAME_LENGTH];
	int age;
	char gender;
	int id;
	struct PatientNode *next;
} PatientNode;

/* structure for reservation slots */
typedef struct ReservationNode {
	int slot;
	int patientId;
	struct ReservationNode *next;
} ReservationNode;

/* global pointer to structure to make the linked-list */
PatientNode *patientList = NULL;
ReservationNode *reservationList = NULL;

/* Function prototypes */
void adminMode();
void userMode();
void addPatient();
void editPatient();
void reserveSlot();
void cancelReservation();
void viewPatientRecord(int id);
void viewReservations();

int main() {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	int modeChoice;
	/* first screen to choose mode */
	while (1) {
		printf("=========Choose mode=========\n");
		printf("1. Admin Mode\n");
		printf("2. User Mode\n");
		printf("3. Exit The system\n\n");
		printf("Enter your choice: ");
		scanf("%d", &modeChoice);
		/* if the user choose 1, the admin mode will activate */
		if (modeChoice == 1) {
			adminMode();
		}
		/* if the user choose 2, the user mode will activate */
		else if (modeChoice == 2) {
			userMode();
		}
		/* if user choose to exit system, the infinite loop will break */
		else if (modeChoice == 3) {
			break;
		}
		/* else statement to input validation from main screen */
		else {
			printf("Invalid choice.\n");
		}
	}
	/* The end of the system */
	printf("\nGoodBye :(\n");
	return 0;
}

/* admin mode function which contain the options for admin */
void adminMode() {
	/* the available password tries for admin mode */
	int passwordTries = 3;
	int password;
	/* the constant password for admin mode */
	const int adminPassword = 1234;
	while (passwordTries > 0) {
		printf("Enter password (remaining tries: %d): ", passwordTries);
		/* take a password form admin to compare it */
		scanf("%d", &password);
		/* if the entered is correct */
		if (password == adminPassword) {
			int adminChoice;
			while (1) {
				/* the menu for admin options */
				printf("\n=========Admin  Mode=========\n");
				printf("1. Add new patient record\n");
				printf("2. Edit patient record\n");
				printf("3. Reserve a slot with the doctor\n");
				printf("4. Cancel reservation\n");
				printf("5. Exit admin mode\n\n");
				printf("Enter your choice: ");
				scanf("%d", &adminChoice);
				switch (adminChoice) {
				case 1:
					/* the admin choose to add new patient */
					addPatient();
					break;
				case 2:
					/* the admin choose to edit patient data */
					editPatient();
					break;
				case 3:
					/* the admin choose to reserve slot for patient */
					reserveSlot();
					break;
				case 4:
					/* the admin choose to cancel reservation for patient */
					cancelReservation();
					break;
				case 5:
					/* the admin choose to exit admin mode */
					return;
				default:
					/* default statement to input validation from admin */
					printf("Invalid choice.\n");
				}
			}
		} else {
			/* if the entered is incorrect, then tries will decrement */
			passwordTries--;
			/* if there are more available tries for password, then admin can try again */
			if (passwordTries > 0) {
				printf("Incorrect password. Try again.\n");
			} else {
				/* if there is not available tries for password, then admin mode
				 will automatically closed */
				printf("Incorrect password. Exiting...\n");
				return;
			}
		}
	}
}

/* user mode function which contain the options for user */
void userMode() {
	int userChoice;
	while (1) {
		/* the menu for user options */
		printf("\n==========User Mode==========\n");
		printf("1. View patient record\n");
		printf("2. View today's reservations\n");
		printf("3. Exit user mode\n\n");
		printf("Enter your choice: ");
		scanf("%d", &userChoice);
		switch (userChoice) {
		case 1:
			/* the user choose to view patient record and will enter the id */
			printf("Enter patient ID: ");
			int patientId;
			scanf("%d", &patientId);
			viewPatientRecord(patientId);
			break;
		case 2:
			/* the user choose to view reservations */
			viewReservations();
			break;
		case 3:
			/* the user choose to exit user mode */
			return;
		default:
			/* default statement to input validation from user */
			printf("Invalid choice.\n");
		}
	}
}

/* function to add new patient to the patient linked-list and check if the id exists or not */
void addPatient() {
	PatientNode *newPatient = (PatientNode*) malloc(sizeof(PatientNode));
	/* check if there is a free location in heap or not */
	if (newPatient == NULL) {
		/* there is no free location in heap for the new patient */
		printf("Memory allocation error.\n");
		return;
	}
	printf("Enter patient ID: ");
	scanf("%d", &newPatient->id);
	/* check if the ID already exists in the list */
	PatientNode *current = patientList;
	while (current != NULL) {
		if (current->id == newPatient->id) {
			/* the id has found and can't add new patient with this id */
			printf("Patient with ID %d already exists.\n", newPatient->id);
			/* free allocated memory since we're not adding a new patient */
			free(newPatient);
			return;
		}
		current = current->next;
	}
	/* if reach here, there is available place for new patient */
	printf("Enter patient name: ");
	scanf("%s", newPatient->name);
	printf("Enter patient age: ");
	scanf("%d", &newPatient->age);
	printf("Enter patient gender (M/F): ");
	scanf(" %c", &newPatient->gender);
	/* make the head is the next of new record of patient */
	newPatient->next = patientList;
	/* make the new record of patient is the head of linked list */
	patientList = newPatient;
	printf("Patient record added successfully.\n");
}

/* function to edit a data of patient in linked-list and check if the id exists or not */
void editPatient() {
	int patientId;
	printf("Enter patient ID to edit: ");
	scanf("%d", &patientId);
	PatientNode *currentPatient = patientList;
	/* search for the entered id if exists or not */
	while (currentPatient != NULL) {
		if (currentPatient->id == patientId) {
			/* the entered id is exists and ready to edit data */
			printf("Enter new patient name: ");
			scanf("%s", currentPatient->name);
			printf("Enter new patient age: ");
			scanf("%d", &currentPatient->age);
			printf("Enter new patient gender (M/F): ");
			scanf(" %c", &currentPatient->gender);
			printf("Patient data updated successfully.\n");
			return;
		}
		currentPatient = currentPatient->next;
	}
	/* the entered id is not exists */
	printf("Patient with ID %d not found.\n", patientId);
}

/* function enable the patient to reserve a slot if it is available */
void reserveSlot() {
	bool found = False, slot1, slot2, slot3, slot4, slot5;
	printf("\n=======Available slots=======\n");
	/* check every slot if it is available or not */
	ReservationNode *checkSlot = reservationList;
	/* suppose at first that all slots are available */
	slot1 = slot2 = slot3 = slot4 = slot5 = True;
	while (checkSlot != NULL) {
		/* check if the slot 1 is not reserved */
		if (checkSlot->slot != 1 && slot1) {
			/* the slot 1 is not reserved so remain true */
			slot1 = True;
		} else {
			/* the slot 1 is not available so it will not appears for user */
			slot1 = False;
		}
		/* check if the slot 2 is not reserved */
		if (checkSlot->slot != 2 && slot2) {
			/* the slot 2 is not reserved so remain true */
			slot2 = True;
		} else {
			/* the slot 2 is not available so it will not appears for user */
			slot2 = False;
		}
		/* check if the slot 3 is not reserved */
		if (checkSlot->slot != 3 && slot3) {
			/* the slot 3 is not reserved so remain true */
			slot3 = True;
		} else {
			/* the slot 3 is not available so it will not appears for user */
			slot3 = False;
		}
		/* check if the slot 4 is not reserved */
		if (checkSlot->slot != 4 && slot4) {
			/* the slot 4 is not reserved so remain true */
			slot4 = True;
		} else {
			/* the slot 4 is not available so it will not appears for user */
			slot4 = False;
		}
		/* check if the slot 5 is not reserved */
		if (checkSlot->slot != 5 && slot5) {
			/* the slot 5 is not reserved so remain true */
			slot5 = True;
		} else {
			/* the slot 5 is not available so it will not appears for user */
			slot5 = False;
		}
		checkSlot = checkSlot->next;
	}
	/* if slot number is available, then print it for user */
	if (slot1) {
		printf("1. 2:00pm - 2:30pm\n");
	}
	if (slot2) {
		printf("2. 2:30pm - 3:00pm\n");
	}
	if (slot3) {
		printf("3. 3:00pm - 3:30pm\n");
	}
	if (slot4) {
		printf("4. 4:00pm - 4:30pm\n");
	}
	if (slot5) {
		printf("5. 4:30pm - 5:00pm\n");
	}
	/* take user id and slot choice to reserve it */
	int slotChoice, patientId;
	printf("Enter patient ID: ");
	scanf("%d", &patientId);
	/* check if the ID already exists in the list */
	PatientNode *current = patientList;
	while (current != NULL) {
		if (current->id == patientId) {
			/* the entered id is exists and ready to reserve a slot */
			found = True;
			break;
		}
		current = current->next;
	}
	/* check if the id is found or not */
	if (!found) {
		printf("Patient with ID %d not found.\n", patientId);
		return;
	}
	printf("Enter slot choice: ");
	scanf("%d", &slotChoice);
	/* if incorrect slot choice is entered */
	if (slotChoice < 1 || slotChoice > MAX_SLOTS) {
		printf("Invalid slot choice.\n");
		return;
	}
	/* Check if the slot is already reserved */
	ReservationNode *currentReservation = reservationList;
	while (currentReservation != NULL) {
		if (currentReservation->slot == slotChoice) {
			/* if reach here, that mean the chosen slot is reserved */
			printf("Slot is already reserved.\n");
			return;
		}
		currentReservation = currentReservation->next;
	}
	ReservationNode *newReservation = (ReservationNode*) malloc(
			sizeof(ReservationNode));
	/* check if there is a free location in heap or not */
	if (newReservation == NULL) {
		/* there is no free location in heap for the new reservation */
		printf("Memory allocation error.\n");
		return;
	}
	/* if reach here, that mean the chosen slot is not reserved and start to reserve it */
	newReservation->slot = slotChoice;
	newReservation->patientId = patientId;
	newReservation->next = reservationList;
	reservationList = newReservation;
	printf("Slot reserved successfully.\n");
}

/* function enable the patient to cancel a reservation if it exits with his id*/
void cancelReservation() {
	int patientId;
	printf("Enter patient ID to cancel reservation: ");
	scanf("%d", &patientId);
	ReservationNode *currentReservation = reservationList;
	ReservationNode *prevReservation = NULL;
	/* search in the reservation slots in the clinic */
	while (currentReservation != NULL) {
		/* if the entered id has been found in the reservations */
		if (currentReservation->patientId == patientId) {
			if (prevReservation == NULL) {
				/* The reservation to cancel is the first node */
				reservationList = currentReservation->next;
			} else {
				/* connect between previous node and the next of current node */
				prevReservation->next = currentReservation->next;
			}
			/* free the allocation of the cancelled reservation */
			free(currentReservation);
			printf("Reservation cancelled.\n");
			return;
		}
		/* continue the search operation of the patient id */
		/* make the previous has address of current node */
		prevReservation = currentReservation;
		/* make the current node has address of the next of it */
		currentReservation = currentReservation->next;
	}
	/* if reach here, that is mean the patient id is not found in the linked-list */
	printf("No reservation found for the given patient ID.\n");
}

/* function to show data of patient in the linked-list by searching with his id */
void viewPatientRecord(int id) {
	PatientNode *currentPatient = patientList;
	/* search for the given id if found or not */
	while (currentPatient != NULL) {
		if (currentPatient->id == id) {
			/* the given id is found and print its data */
			printf("Patient Name: %s\n", currentPatient->name);
			printf("Age: %d\n", currentPatient->age);
			printf("Gender: %c\n", currentPatient->gender);
			printf("ID: %d\n", currentPatient->id);
			return;
		}
		currentPatient = currentPatient->next;
	}
	/* the given id is not found */
	printf("Patient not found.\n");
}

/* function to show data of reservation for today */
void viewReservations() {
	/* if there is no reservations and no patient reserve a slot */
	if (reservationList == NULL) {
		printf("No reservations for today.\n");
		return;
	}
	/* there is a reservations and start to print it with the patient id */
	printf("\n====Today's  reservations====\n");
	ReservationNode *currentReservation = reservationList;
	while (currentReservation != NULL) {
		printf("Slot %d: Patient ID %d\n", currentReservation->slot,
				currentReservation->patientId);
		currentReservation = currentReservation->next;
	}
}
