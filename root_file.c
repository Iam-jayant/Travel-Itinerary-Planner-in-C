#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for each travel stop
typedef struct Stop {
    char location[50];
    char date[15];
    char description[100];
    struct Stop *next;
} Stop;

// Function prototypes
Stop* addStop(Stop *head, char location[], char date[], char description[]);
Stop* deleteStop(Stop *head, char location[]);
void viewItinerary(Stop *head);
void clearScreen();
void pause();

int main() {
    Stop *head = NULL; // Start with an empty itinerary
    int choice;
    char location[50], date[15], description[100];

    // Main menu loop
    while (1) {
        clearScreen();
        printf("\n========= TRAVEL ITINERARY PLANNER =========\n");
        printf("1. Add a New Stop\n");
        printf("2. Delete a Stop\n");
        printf("3. View Itinerary\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline from input buffer

        switch (choice) {
            case 1:
                // Adding a new stop
                printf("\nEnter Location: ");
                fgets(location, 50, stdin);
                location[strcspn(location, "\n")] = 0; // Removes newline

                printf("Enter Date (e.g., 31-10-2024): ");
                fgets(date, 15, stdin);
                date[strcspn(date, "\n")] = 0;

                printf("Enter Description: ");
                fgets(description, 100, stdin);
                description[strcspn(description, "\n")] = 0;

                head = addStop(head, location, date, description);
                printf("\nStop added successfully!\n");
                pause();
                break;

            case 2:
                // Deleting a stop
                printf("\nEnter Location to Delete: ");
                fgets(location, 50, stdin);
                location[strcspn(location, "\n")] = 0;

                head = deleteStop(head, location);
                printf("\nStop deleted (if it existed).\n");
                pause();
                break;

            case 3:
                // Viewing the itinerary
                viewItinerary(head);
                pause();
                break;

            case 4:
                // Exiting the program
                printf("Thank you for using the Itinerary Planner. Safe travels!\n");
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
                pause();
        }
    }

    return 0;
}

// Function to add a new stop to the itinerary
Stop* addStop(Stop *head, char location[], char date[], char description[]) {
    Stop *newStop = (Stop*)malloc(sizeof(Stop));
    strcpy(newStop->location, location);
    strcpy(newStop->date, date);
    strcpy(newStop->description, description);
    newStop->next = NULL;

    if (head == NULL) {
        return newStop;
    }

    Stop *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newStop;
    return head;
}

// Function to delete a stop from the itinerary based on location
Stop* deleteStop(Stop *head, char location[]) {
    if (head == NULL) return NULL;

    Stop *temp = head, *prev = NULL;

    // If the stop to be deleted is the head
    if (strcmp(temp->location, location) == 0) {
        head = temp->next;
        free(temp);
        return head;
    }

    // Traverse the list to find the stop
    while (temp != NULL && strcmp(temp->location, location) != 0) {
        prev = temp;
        temp = temp->next;
    }

    // If the stop is not found
    if (temp == NULL) return head;

    // Remove the stop from the list
    prev->next = temp->next;
    free(temp);
    return head;
}

// Function to display the itinerary
void viewItinerary(Stop *head) {
    if (head == NULL) {
        printf("The itinerary is empty.\n");
        return;
    }

    Stop *temp = head;
    while (temp != NULL) {
        printf("Location: %s\nDate: %s\nDescription: %s\n\n", temp->location, temp->date, temp->description);
        temp = temp->next;
    }
}

// Function to clear the screen (platform dependent)
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Function to pause the program and wait for user input
void pause() {
    printf("Press Enter to continue...");
    getchar();
}