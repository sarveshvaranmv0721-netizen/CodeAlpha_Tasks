#include <stdio.h>
#include <string.h>

struct Student {
    int regno;
    char name[100];
    float cgpa;
};

void getdata(struct Student *s) {
    printf("Enter Student Registration Number: ");
    scanf("%d", &s->regno);
    getchar();

    printf("Enter Student Name: ");
    fgets(s->name, sizeof(s->name), stdin);

    printf("Enter Student CGPA: ");
    scanf("%f", &s->cgpa);
}

void filesave(struct Student *s) {
    FILE *fp;
    fp = fopen("student.txt", "a");
    fwrite(s, sizeof(struct Student), 1, fp);
    fclose(fp);
}

void readfile() {
    struct Student s;
    FILE *fp;
    fp = fopen("student.txt", "r");

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        printf("\nReg No : %d", s.regno);
        printf("\nName   : %s", s.name);
        printf("CGPA   : %.2f\n", s.cgpa);
    }
    fclose(fp);
}

void search() {
    struct Student s;
    int reg, found = 0;
    FILE *fp;
    fp = fopen("student.txt", "r");

    printf("Enter Registration Number to Search: ");
    scanf("%d", &reg);

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.regno == reg) {
            printf("\nReg No : %d", s.regno);
            printf("\nName   : %s", s.name);
            printf("CGPA   : %.2f\n", s.cgpa);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student Record Not Found\n");
    }
    fclose(fp);
}

void update() {
    struct Student s;
    int reg, found = 0;
    FILE *fp;
    fp = fopen("student.txt", "r+");

    printf("Enter Registration Number to Update: ");
    scanf("%d", &reg);

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.regno == reg) {
            printf("Enter New Details\n");
            getchar();
            getdata(&s);
            fseek(fp, -sizeof(struct Student), SEEK_CUR);
            fwrite(&s, sizeof(struct Student), 1, fp);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student Record Not Found\n");
    }
    fclose(fp);
}

void deleteStud() {
    struct Student s;
    int reg;
    FILE *fp, *temp;

    fp = fopen("student.txt", "r");
    temp = fopen("temp.txt", "w");

    printf("Enter Registration Number to Delete: ");
    scanf("%d", &reg);

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.regno != reg) {
            fwrite(&s, sizeof(struct Student), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("student.txt");
    rename("temp.txt", "student.txt");

    printf("Record Deleted Successfully\n");
}

int main() {
    struct Student s;
    int ch;

    while (1) {
        printf("\n1. Add Student");
        printf("\n2. Display Students");
        printf("\n3. Search Student");
        printf("\n4. Update Student");
        printf("\n5. Delete Student");
        printf("\n6. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &ch);

        if (ch == 1) {
            getchar();
            getdata(&s);
            filesave(&s);
        } else if (ch == 2) {
            readfile();
        } else if (ch == 3) {
            search();
        } else if (ch == 4) {
            update();
        } else if (ch == 5) {
            deleteStud();
        } else if (ch == 6) {
            printf("Exiting Student Management System.....");
            break;
        }
    }
    return 0;
}
