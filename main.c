#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Color codes */
#define CYAN    "\033[0;36m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[0;33m"
#define RED     "\033[0;31m"
#define RESET   "\033[0m"

struct Complaint {
    int id;
    char name[50];
    char nic[20];
    char phone[15];
    char email[50];
    char faculty[50];
    char degree[50];
    char accusedPerson[50];
    char issue[200];
    char status[20];
    struct Complaint *next;
};

struct Complaint *head = NULL;

/* Function declarations */
struct Complaint* createComplaint();
void insertAtEnd();
void displayComplaints();
void searchComplaint();
void updateStatus();
void deleteComplaint();

/* Create Complaint */
struct Complaint* createComplaint() {
    struct Complaint *newNode = (struct Complaint*)malloc(sizeof(struct Complaint));
    if (!newNode) {
        printf(RED "Memory allocation failed!\n" RESET);
        return NULL;
    }

    printf(CYAN "\n--- Complaint Details ---\n\n" RESET);

    printf(YELLOW "  Enter Complaint ID: " RESET);
    scanf("%d", &newNode->id);

    printf(YELLOW "  Enter Name of the Complainant: " RESET);
    scanf(" %[^\n]", newNode->name);

    printf(YELLOW "  Enter NIC: " RESET);
    scanf(" %[^\n]", newNode->nic);

    printf(YELLOW "  Enter Phone Number: " RESET);
    scanf(" %[^\n]", newNode->phone);

    printf(YELLOW "  Enter Email: " RESET);
    scanf(" %[^\n]", newNode->email);

    printf(YELLOW "  Enter Faculty: " RESET);
    scanf(" %[^\n]", newNode->faculty);

    printf(YELLOW "  Enter Degree Program: " RESET);
    scanf(" %[^\n]", newNode->degree);

    printf(YELLOW "  Enter Name of Alleged Person Responsible: " RESET);
    scanf(" %[^\n]", newNode->accusedPerson);

    printf(YELLOW "  Enter Complaint: " RESET);
    scanf(" %[^\n]", newNode->issue);

    strcpy(newNode->status, "Pending");
    newNode->next = NULL;

    return newNode;
}

/* Insert at end */
void insertAtEnd() {
    struct Complaint *newNode = createComplaint();
    if (!newNode) return;

    if (!head) {
        head = newNode;
    } else {
        struct Complaint *temp = head;
        while (temp->next)
            temp = temp->next;
        temp->next = newNode;
    }

    printf(GREEN "\n  Complaint added successfully.\n" RESET);
}

/* Display complaints */
void displayComplaints() {
    if (!head) {
        printf(RED "\n  No complaints available.\n" RESET);
        return;
    }

    struct Complaint *temp = head;
    int count = 1;

    printf(CYAN "\n=== University Complaint List ===\n" RESET);

    while (temp) {
        printf(GREEN "\nComplaint %d\n" RESET, count++);
        printf(YELLOW "  ID: " RESET "%d\n", temp->id);
        printf(YELLOW "  Name: " RESET "%s\n", temp->name);
        printf(YELLOW "  NIC: " RESET "%s\n", temp->nic);
        printf(YELLOW "  Phone: " RESET "%s\n", temp->phone);
        printf(YELLOW "  Email: " RESET "%s\n", temp->email);
        printf(YELLOW "  Faculty: " RESET "%s\n", temp->faculty);
        printf(YELLOW "  Degree Program: " RESET "%s\n", temp->degree);
        printf(YELLOW "  Accused Person: " RESET "%s\n", temp->accusedPerson);
        printf(YELLOW "  Complaint: " RESET "%s\n", temp->issue);
        printf(GREEN  "  Status: %s\n" RESET, temp->status);
        printf("  --------------------------------------\n");

        temp = temp->next;
    }
}

/* Search complaint */
void searchComplaint() {
    int key;
    struct Complaint *temp = head;

    if (!head) {
        printf(RED "  No complaints to search.\n" RESET);
        return;
    }

    printf(YELLOW "  Enter Complaint ID to search: " RESET);
    scanf("%d", &key);

    while (temp) {
        if (temp->id == key) {
            printf(GREEN "\n  Complaint Found\n" RESET);
            printf(YELLOW "  Name: " RESET "%s\n", temp->name);
            printf(YELLOW "  Faculty: " RESET "%s\n", temp->faculty);
            printf(YELLOW "  Complaint: " RESET "%s\n", temp->issue);
            printf(GREEN  "  Status: %s\n" RESET, temp->status);
            return;
        }
        temp = temp->next;
    }

    printf(RED "  Complaint not found.\n" RESET);
}

/* Update status */
void updateStatus() {
    int key;
    struct Complaint *temp = head;

    if (!head) {
        printf(RED "  No complaints available.\n" RESET);
        return;
    }

    printf(YELLOW "  Enter Complaint ID to update status: " RESET);
    scanf("%d", &key);

    while (temp) {
        if (temp->id == key) {
            printf(YELLOW "  Current Status: " RESET "%s\n", temp->status);
            printf(YELLOW "  Enter New Status: " RESET);
            scanf(" %[^\n]", temp->status);
            printf(GREEN "  Status updated successfully.\n" RESET);
            return;
        }
        temp = temp->next;
    }

    printf(RED "  Complaint not found.\n" RESET);
}

/* Delete complaint */
void deleteComplaint() {
    int key;
    struct Complaint *temp = head, *prev = NULL;

    if (!head) {
        printf(RED "  No complaints to delete.\n" RESET);
        return;
    }

    printf(YELLOW "  Enter Complaint ID to delete: " RESET);
    scanf("%d", &key);

    if (head->id == key) {
        head = head->next;
        free(temp);
        printf(GREEN "  Complaint deleted successfully.\n" RESET);
        return;
    }

    while (temp && temp->id != key) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) {
        printf(RED "  Complaint not found.\n" RESET);
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf(GREEN "  Complaint deleted successfully.\n" RESET);
}

/* Main */
int main() {
    int choice;

    while (1) {
        printf(CYAN "\n=== University Complaint Management System ===\n\n" RESET);
        printf("  1. Add Complaint\n");
        printf("  2. View Complaints\n");
        printf("  3. Search Complaint\n");
        printf("  4. Update Complaint Status\n");
        printf("  5. Delete Complaint\n");
        printf("  6. Exit\n");

        printf(YELLOW "\n  Enter your choice: " RESET);
        scanf("%d", &choice);

        switch (choice) {
            case 1: insertAtEnd(); break;
            case 2: displayComplaints(); break;
            case 3: searchComplaint(); break;
            case 4: updateStatus(); break;
            case 5: deleteComplaint(); break;
            case 6: exit(0);
            default: printf(RED "  Invalid choice!\n" RESET);
        }
    }
    return 0;
}
