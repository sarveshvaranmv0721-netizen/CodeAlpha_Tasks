#include <stdio.h>
#include <string.h>

struct Account {
    int accno;
    char name[100];
    float balance;
};

void getdata(struct Account *a) {
    printf("Enter Account Number: ");
    scanf("%d", &a->accno);
    getchar();

    printf("Enter Account holder name: ");
    fgets(a->name, sizeof(a->name), stdin);

    printf("Enter Initial Balance: ");
    scanf("%f", &a->balance);
}

void filesave(struct Account *a) {
    FILE *fp;
    fp = fopen("bank.txt", "a");
    fwrite(a, sizeof(struct Account), 1, fp);
    fclose(fp);
}

void deposit() {
    struct Account a;
    int acc;
    float amt;
    FILE *fp;

    fp = fopen("bank.txt", "r+");

    printf("Enter Account Number: ");
    scanf("%d", &acc);

    while (fread(&a, sizeof(struct Account), 1, fp)) {
        if (a.accno == acc) {
            printf("Enter Amount to Deposit: ");
            scanf("%f", &amt);
            a.balance += amt;
            fseek(fp, -sizeof(struct Account), SEEK_CUR);
            fwrite(&a, sizeof(struct Account), 1, fp);
            printf("Amount Deposited Successfully\n");
            break;
        }
    }
    fclose(fp);
}

void withdrawal() {
    struct Account a;
    int acc;
    float amt;
    FILE *fp;

    fp = fopen("bank.txt", "r+");

    printf("Enter Account Number: ");
    scanf("%d", &acc);

    while (fread(&a, sizeof(struct Account), 1, fp)) {
        if (a.accno == acc) {
            printf("Enter Amount to Withdraw: ");
            scanf("%f", &amt);
            if (a.balance >= amt) {
                a.balance -= amt;
                fseek(fp, -sizeof(struct Account), SEEK_CUR);
                fwrite(&a, sizeof(struct Account), 1, fp);
                printf("Withdrawal Successful\n");
            } else {
                printf("Insufficient Balance\n");
            }
            break;
        }
    }
    fclose(fp);
}

void enquiry() {
    struct Account a;
    int acc;
    FILE *fp;

    fp = fopen("bank.txt", "r");

    printf("Enter Account Number: ");
    scanf("%d", &acc);

    while (fread(&a, sizeof(struct Account), 1, fp)) {
        if (a.accno == acc) {
            printf("\nAccount Number : %d", a.accno);
            printf("\nName           : %s", a.name);
            printf("Balance        : %.2f\n", a.balance);
            break;
        }
    }
    fclose(fp);
}

int main() {
    struct Account a;
    int ch;

    while (1) {
        printf("\n1. Create Account");
        printf("\n2. Deposit");
        printf("\n3. Withdrawal");
        printf("\n4. Balance Enquiry");
        printf("\n5. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &ch);

        if (ch == 1) {
            getchar();
            getdata(&a);
            filesave(&a);
        } else if (ch == 2) {
            deposit();
        } else if (ch == 3) {
            withdrawal();
        } else if (ch == 4) {
            enquiry();
        } else if (ch == 5) {
            printf("Exiting Banking Management system......\n");
            break;
        }
    }
    return 0;
}
