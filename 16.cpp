#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "employee.dat"

struct employee {
    int id;
    char name[30];
    float salary;
};

int main() {
    FILE *fp;
    struct employee e;
    int choice, emp_id, found = 0;

    while (1) {
        printf("\n1. Add employee\n");
        printf("2. Search employee\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                fp = fopen(FILE_NAME, "ab");
                printf("Enter employee ID: ");
                scanf("%d", &e.id);
                printf("Enter employee name: ");
                scanf("%s", e.name);
                printf("Enter employee salary: ");
                scanf("%f", &e.salary);
                fwrite(&e, sizeof(struct employee), 1, fp);
                fclose(fp);
                break;
            case 2:
                fp = fopen(FILE_NAME, "rb");
                printf("Enter employee ID: ");
                scanf("%d", &emp_id);
                while (fread(&e, sizeof(struct employee), 1, fp) == 1) {
                    if (e.id == emp_id) {
                        printf("\nEmployee details:\n");
                        printf("ID: %d\n", e.id);
                        printf("Name: %s\n", e.name);
                        printf("Salary: %.2f\n", e.salary);
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    printf("\nEmployee not found.\n");
                }
                fclose(fp);
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice.\n");
                break;
        }
    }

    return 0;
}

