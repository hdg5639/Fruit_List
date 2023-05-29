#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char name[100];
} element;

typedef struct ListNode {
    element data;
    struct ListNode* link;
} ListNode;

void error(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

ListNode* insert_first(ListNode* head, element value) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->data = value;
    p->link = head;
    head = p;
    return head;
}

ListNode* insert(ListNode* head, ListNode* pre, element value) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->data = value;

    if (pre == NULL) {
        p->link = head;
        head = p;
    }
    else {
        p->link = pre->link;
        pre->link = p;
    }

    return head;
}

ListNode* insert_last(ListNode* head, element value) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->data = value;
    p->link = NULL;

    if (head == NULL) {
        head = p;
    }
    else {
        ListNode* current = head;
        while (current->link != NULL) {
            current = current->link;
        }
        current->link = p;
    }

    return head;
}

ListNode* delete_first(ListNode* head) {
    ListNode* removed;
    if (head == NULL) return NULL;
    removed = head;
    head = removed->link;
    free(removed);
    return head;
}

ListNode* deleted = NULL;

ListNode* delete_fruit(ListNode* head, char* name) {
    ListNode* current = head;
    ListNode* pre = NULL;

    while (current != NULL) {
        if (strcmp(current->data.name, name) == 0) {
            if (pre == NULL) {
                head = delete_first(head);
            }
            else {
                pre->link = current->link;
                current->link = deleted;
                deleted = current;
            }
            break;
        }
        pre = current;
        current = current->link;
    }

    return head;
}

void print_list(ListNode* head) {
    for (ListNode* p = head; p != NULL; p = p->link)
        printf("%s->", p->data.name);
    printf("NULL\n");
}

int main() {
    ListNode* head = NULL;
    int select;
    element fruits[] = {
        {"Mango"},
        {"Orange"},
        {"Apple"},
        {"Grape"},
        {"Cherry"},
        {"Plum"},
        {"Guava"},
        {"Raspberry"},
        {"Banana"},
        {"Peach"}
    };
    int NF = sizeof(fruits) / sizeof(fruits[0]);
    for (int i = 0; i < NF; i++) {
        head = insert_first(head, fruits[i]);
    }
    for (;;) {
        element data;
        printf("1. Insert new fruit\n2. Delete a fruit\n3. Print the list\n4. Exit\nEnter the menu: ");
        scanf_s("%d", &select);

        switch (select) {
        case 1:
            printf("Enter the fruit name to add: ");
            scanf("%s", data.name);

            size_t len = strlen(data.name);
            if (len > 0 && data.name[len - 1] == '\n') {
                data.name[len - 1] = '\0';
            }

            ListNode* current = head;
            while (current != NULL) {
                if (strcmp(current->data.name, data.name) == 0) {
                    printf("The fruit already exists.\n");
                    break;
                }
                current = current->link;
            }

            if (current == NULL) {
                head = insert_last(head, data);
                printf("%s has been added.\n", data.name);
            }
            printf("\nFruit list:\n");
            print_list(head);
            printf("\n");
            break;

        case 2:
            printf("Enter the fruit name to delete: ");
            scanf("%s", data.name);

            len = strlen(data.name);
            if (len > 0 && data.name[len - 1] == '\n') {
                data.name[len - 1] = '\0';
            }
            current = head;
            ListNode* pre = NULL;
            int found = 0;
            while (current != NULL) {
                if (strcmp(current->data.name, data.name) == 0) {
                    found = 1;
                    break;
                }
                pre = current;
                current = current->link;
            }

            if (found) {
                head = delete_fruit(head, data.name);
                deleted = insert_last(deleted, data);
                printf("%s has been deleted.\n", data.name);
            }
            else {
                printf("%s does not exist.\n", data.name);
            }
            printf("\nFruit list:\n");
            print_list(head);
            printf("\n");
            break;


        case 3:
            printf("List of deleted fruits: ");
            print_list(deleted);
            printf("\nList: ");
            print_list(head);
            printf("\n");
            break;

        case 4:
            printf("Exit the program.\n");
            printf("\n-------------------------------\n");
            exit(0);

        default:
            printf("Invalid Menu. Please select again.\n");
        }
    }
}