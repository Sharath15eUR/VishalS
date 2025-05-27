#include <stdio.h>
#include <string.h>

#define MAX_DAYS 7
#define MAX_TASKS 3
#define MAX_LEN 100

struct Day {
    char dayName[10];
    char tasks[MAX_TASKS][MAX_LEN];
    int taskCount;
};

int main() {
    struct Day week[MAX_DAYS] = {
        {"Monday", {}, 0},
        {"Tuesday", {}, 0},
        {"Wednesday", {}, 0},
        {"Thursday", {}, 0},
        {"Friday", {}, 0},
        {"Saturday", {}, 0},
        {"Sunday", {}, 0}
    };

    int choice, dayIndex, i;
    char task[MAX_LEN];

    while (1) {
        printf("\n1. Add Task\n2. Display Tasks\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter day index (0 for Monday, 6 for Sunday): ");
            scanf("%d", &dayIndex);

            if (dayIndex < 0 || dayIndex >= MAX_DAYS) {
                printf("Invalid day index.\n");
                continue;
            }

            if (week[dayIndex].taskCount >= MAX_TASKS) {
                printf("Task limit reached for %s.\n", week[dayIndex].dayName);
                continue;
            }

            printf("Enter task: ");
            getchar();
            fgets(task, MAX_LEN, stdin);
            task[strcspn(task, "\n")] = '\0';

            strcpy(week[dayIndex].tasks[week[dayIndex].taskCount], task);
            week[dayIndex].taskCount++;

        } else if (choice == 2) {
            for (i = 0; i < MAX_DAYS; i++) {
                printf("\n%s:\n", week[i].dayName);
                if (week[i].taskCount == 0) {
                    printf("  No tasks\n");
                } else {
                    for (int j = 0; j < week[i].taskCount; j++) {
                        printf("  - %s\n", week[i].tasks[j]);
                    }
                }
            }
        } else if (choice == 3) {
            break;
        } else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}
