#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256
#define TODO_FILE "TO-DO LIST.txt"

void viewTasks() {
    FILE *file = fopen(TODO_FILE, "r");
    if (!file) {
        printf("Nothing yet\n");
        return;
    }

    char line[MAX_LINE];
    int count = 1;
    printf("\n--- Your To-Do List ---\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%d. %s", count++, line);
    }
    fclose(file);
    printf("-----------------------\n");
}

void addTask() {
    char task[MAX_LINE];
    printf("What you want to add ra?: ");
    getchar();
    fgets(task, sizeof(task), stdin);

    size_t len = strlen(task);
    if (len > 0 && task[len - 1] == '\n') task[len - 1] = '\0';

    FILE *file = fopen(TODO_FILE, "a");
    if (!file) {
        perror("Can't open file");
        return;
    }
    fprintf(file, "%s\n", task);
    fclose(file);
    printf("Added\n");
}

void removeTask() {
    FILE *file = fopen(TODO_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!file || !temp) {
        perror("Can't open file");
        return;
    }

    char line[MAX_LINE];
    char taskToRemove[MAX_LINE];
    printf("What you want to remove ra sudeep: ");
    getchar(); 
    fgets(taskToRemove, sizeof(taskToRemove), stdin);


    size_t len = strlen(taskToRemove);
    if (len > 0 && taskToRemove[len - 1] == '\n') taskToRemove[len - 1] = '\0';

    int removed = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, taskToRemove) == NULL) {
            fputs(line, temp);
        } else {
            removed = 1;
        }
    }

    fclose(file);
    fclose(temp);

    remove(TODO_FILE);
    rename("temp.txt", TODO_FILE);

    if (removed)
        printf("Removed\n");
    else
        printf("Not found\n");
}

int main() {
    int choice;

    do {
        printf("\nTo-Do List Manager\n");
        printf("1. View stuff\n");
        printf("2. Add stuff\n");
        printf("3. Remove stuff\n");
        printf("4. Exit stuff\n");
        printf("Choose stuff re: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: viewTasks(); break;
            case 2: addTask(); break;
            case 3: removeTask(); break;
            case 4: printf("Get outta here\n"); break;
            default: printf("Invalid you are ra\n");
        }
    } while (choice != 4);

    return 0;
}
