#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define TABLE_SIZE 50

struct task
{
    char name[50];
    char description[100];
    char deadline[20];
    int priority;
    int status;
};

struct task_manager
{
    struct task tasks[MAX_TASKS];
    int count;
};

struct task_node
{
    struct task task;
    struct task_node *next;
};

struct hash_table
{
    struct task_node *table[TABLE_SIZE];
};

// Hash function to calculate the index of the hash table
int hash(char *str)
{
    int hash = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        hash += str[i];
    }
    return hash % TABLE_SIZE;
}

// Function to add a task to the task manager
void add_task(struct task_manager *manager, struct hash_table *table)
{
    struct task t;
    printf("Enter task name: ");
    scanf("%s", t.name);
    printf("Enter task description: ");
    scanf("%s", t.description);
    printf("Enter task deadline: ");
    scanf("%s", t.deadline);
    printf("Enter task priority: ");
    scanf("%d", &t.priority);
    printf("Enter task status (1 for complete, 0 for incomplete): ");
    scanf("%d", &t.status);
    // Add task to the task manager
    manager->tasks[manager->count] = t;
    manager->count++;
    // Add task to the hash table
    int index = hash(t.name);
    struct task_node *node = (struct task_node *)malloc(sizeof(struct task_node));
    node->task = t;
    node->next = table->table[index];
    table->table[index] = node;
    printf("Task added successfully\n");
}

// Function to delete a task from the task manager
void delete_task(struct task_manager *manager, struct hash_table *table)
{
    char name[50];
    printf("Enter task name: ");
    scanf("%s", name);
    // Find the task in the task manager
    for (int i = 0; i < manager->count; i++)
    {
        if (strcmp(manager->tasks[i].name, name) == 0)
        {
            // Remove the task from the task manager
            for (int j = i; j < manager->count - 1; j++)
            {
                manager->tasks[j] = manager->tasks[j + 1];
            }
            manager->count--;
            // Remove the task from the hash table
            int index = hash(name);
            struct task_node *prev = NULL;
            struct task_node *node = table->table[index];
            while (node != NULL)
            {
                if (strcmp(node->task.name, name) == 0)
                {
                    if (prev == NULL)
                    {
                        table->table[index] = node->next;
                    }
                    else
                    {
                        prev->next = node->next;
                    }
                    free(node);
                    printf("Task deleted successfully\n");
                    return;
                }
                prev = node;
                node = node->next;
            } then we can do it by using we can do it by using so much we can do it by using
            return;
        }
    }
    printf("Task not found\n");
}

// Function to display all the tasks in the task manager
void display_tasks(struct task_manager *manager)
{
    for (int i = 0; i < manager->count; i++)
    {
        printf("%s\n", manager->tasks[i].name);
    }
}

// Function to display all the tasks with a given name from the
void display_tasks_by_name(struct hash_table *table)
{
    char name[50];
    printf("Enter task name: ");
    scanf("%s", name);
    int index = hash(name);
    struct task_node *node = table->table[index];
    int count = 0;
    while (node != NULL)
    {
        if (strcmp(node->task.name, name) == 0)
        {
            printf("Task name: %s\n", node->task.name);
            printf("Task description: %s\n", node->task.description);
            printf("Task deadline: %s\n", node->task.deadline);
            printf("Task priority: %d\n", node->task.priority);
            printf("Task status: %s\n", node->task.status ? "Complete" : "Incomplete");
            count++;
        }
        node = node->next;
    }
    if (count == 0)
    {
        printf("No tasks found with name %s\n", name);
    }
}

int main()
{
    struct task_manager manager;
    manager.count = 0;
    struct hash_table table;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        table.table[i] = NULL;
    }
    int choice;
    do
    {
        printf("1. Add Task\n");
        printf("2. Delete Task\n");
        printf("3. Display All Tasks\n");
        printf("4. Display Tasks by Name\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            add_task(&manager, &table);
            break;
        case 2:
            delete_task(&manager, &table);
            break;
        case 3:
            display_tasks(&manager);
            break;
        case 4:
            display_tasks_by_name(&table);
            break;
        case 5:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice\n");
            break;
        }
    } while (choice != 5);
    return 0;
}
