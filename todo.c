				#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_LEN 100
#define FILE_NAME "tasks.txt"

char tasks[MAX_TASKS][MAX_LEN];
int taskCount = 0;

// ✅ ফাইল থেকে কাজ লোড করা
void loadTasks() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) return;  // ফাইল না থাকলে কিছু করবে না

    while (taskCount < MAX_TASKS && fgets(tasks[taskCount], MAX_LEN, file)) {
        tasks[taskCount][strcspn(tasks[taskCount], "\n")] = '\0'; // newline remove
        taskCount++;
    }
    fclose(file);
}

// ✅ কাজগুলো ফাইলে সেভ করা
void saveTasks() {
    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("❌ ফাইল খুলতে সমস্যা হয়েছে!\n");
        return;
    }
    for (int i = 0; i < taskCount; i++) {
        fprintf(file, "%s\n", tasks[i]);
    }
    fclose(file);
}

// ✅ নতুন কাজ যোগ করা
void addTask() {
    if (taskCount < MAX_TASKS) {
        printf("নতুন কাজ লিখুন: ");
        fgets(tasks[taskCount], MAX_LEN, stdin);
        tasks[taskCount][strcspn(tasks[taskCount], "\n")] = '\0';
        taskCount++;
        saveTasks();
        printf("✅ কাজ যোগ হয়েছে!\n");
    } else {
        printf("❌ কাজের লিস্ট পূর্ণ!\n");
    }
}

// ✅ কাজগুলো দেখা
void viewTasks() {
    if (taskCount == 0) {
        printf("📭 কোনো কাজ নেই!\n");
    } else {
        printf("\n=== আপনার টু-ডু লিস্ট ===\n");
        for (int i = 0; i < taskCount; i++) {
            printf("%d. %s\n", i + 1, tasks[i]);
        }
    }
} printf("")

// ✅ কাজ মুছে ফেলা
void deleteTask() {
    char input[10];
    int index;

    viewTasks();
    if (taskCount == 0) return;

    printf("কোন নাম্বারের কাজ মুছতে চান? ");
    fgets(input, sizeof(input), stdin);
    index = atoi(input);

    if (index < 1 || index > taskCount) {
        printf("❌ ভুল নাম্বার!\n");
    } else {
        for (int i = index - 1; i < taskCount - 1; i++) {
            strcpy(tasks[i], tasks[i + 1]);
        }
        taskCount--;
        saveTasks();
        printf("🗑️ কাজ ডিলিট করা হয়েছে!\n");
    }
}

int main() {
    char input[10];
    int choice;

    loadTasks();  // অ্যাপ চালু হলে আগের কাজগুলো লোড হবে

    while (1) {
        printf("\n==== To-Do List App ====\n");
        printf("1. কাজ যোগ করুন\n");
        printf("2. সব কাজ দেখুন\n");
        printf("3. কাজ মুছুন\n");
        printf("4. প্রস্থান\n");
        printf("আপনার পছন্দ দিন: ");

        fgets(input, sizeof(input), stdin);
        choice = atoi(input);

        switch (choice) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: deleteTask(); break;
            case 4:
                printf("👋 ধন্যবাদ! প্রোগ্রাম বন্ধ হচ্ছে...\n");
                exit(0);
            default:
                printf("❌ ভুল ইনপুট! আবার চেষ্টা করুন।\n");
        }
    }

    return 0;
} 