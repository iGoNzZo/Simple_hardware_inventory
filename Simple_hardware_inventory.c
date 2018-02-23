#include <stdio.h>

struct Account {
	unsigned int number; // account number
	char name[30]; // account last name       
	unsigned int Q;
	double balance; // account balance            
};
void textFile(FILE *Ptr);
void newRecord(FILE *Ptr);
void updateRecord(FILE *Ptr);
void updateQuantity(FILE *Ptr);
void deleteRecord(FILE *Ptr);


 main()
{
	FILE *fPtr;
	unsigned int input;

	printf("Enter 1 for adding, 2 for updateing price, 3 for updateing quantity \n4 to delete tool, 5 to put into text file (0 to exit): ");
	scanf("%d", &input);
	if ((fPtr = fopen("hardware.dat", "rb+")) == NULL) {
		if ((fPtr = fopen("hardware.dat", "w")) == NULL) {
			puts("no mem");
		}
		else {
			puts("Just created");
		}
	}
	else {
		while (input != 0)
		{
			if (input == 1)
				newRecord(fPtr);
			else if (input == 2)
				updateRecord(fPtr);
			else if (input == 3)
				;
			else if (input == 4)
				deleteRecord(fPtr);
			else if (input == 5)
				textFile(fPtr);
			else
				puts("Not Valid");

			printf("Enter 1 for adding, 2 for updateing price, 3 for updateing quantity \n4 to delete tool, 5 to put into text file (0 to exit): ");
			scanf("%d", &input);
		}

	}
	fclose(fPtr);
	//system("pause");
}

void textFile(FILE *Ptr)
{
	FILE *wPtr;

	if ((wPtr = fopen("hardware.txt", "w")) == NULL) {
		puts("File could not be opened.");
	}
	else {
		rewind(Ptr);
		fprintf(wPtr, "%-6s%-31s%-8s%10s\n", "Acct", "Name", "Quant", "Balance");

		while (!feof(Ptr)) {
			struct Account account = { 0, "", 0 ,0.0 };
			int result =
				fread(&account, sizeof(struct Account), 1, Ptr);

			// write single record to text file
			if (result != 0 && account.number != 0) {
				fprintf(wPtr, "%-6d%-31s%-8d%10.2f\n", account.number, account.name, account.Q, account.balance);
			}
		}

		fclose(wPtr); // fclose closes the file
	}
}

void updateRecord(FILE *Ptr)
{
	printf("%s", "Enter account to update: ");
	unsigned int num; // account number
	scanf("%d", &num);
	double transaction;
	fseek(Ptr, (num - 1) * sizeof(struct Account),
		SEEK_SET);

	struct Account account = { 0, "", 0 ,0.0 };

	fread(&account, sizeof(struct Account), 1, Ptr);

	if (account.number == 0) {
		printf("Account #%d has no information.\n", account.number);
	}
	else { // update
		printf("%-6d%-31s%-8d%10.2f\n\n", account.number, account.name, account.Q, account.balance);

		printf("%s", "Enter: (+) or (-) funds: ");
		scanf("%lf", &transaction);
		account.balance += transaction;

		printf("%-6d%-31s%-8d%10.2f\n", account.number, account.name, account.Q, account.balance);

		fseek(Ptr, (num - 1) * sizeof(struct Account),
			SEEK_SET);
		fwrite(&account, sizeof(struct Account), 1, Ptr);
	}
}

void updateQuantity(FILE *Ptr)
{
	printf("%s", "Enter account to update: ");
	unsigned int num, change; // account number
	scanf("%d", &num);
	fseek(Ptr, (num - 1) * sizeof(struct Account),
		SEEK_SET);

	struct Account account = { 0, "", 0, 0.0 };

	fread(&account, sizeof(struct Account), 1, Ptr);

	if (account.number == 0) {
		printf("Account #%d has no information.\n", account.number);
	}
	else { // update
		printf("%-6d%-31s%-8d%10.2f\n\n", account.number, account.name, account.Q, account.balance);

		printf("Enter: (+) or (-) quanitiy: ");
		scanf("%d", &change);
		account.Q += change;

		printf("%-6d%-31s%-8d%10.2f\n", account.number, account.name, account.Q, account.balance);

		fseek(Ptr, (num - 1) * sizeof(struct Account),
			SEEK_SET);
		fwrite(&account, sizeof(struct Account), 1, Ptr);
	}
}

void newRecord(FILE *Ptr)
{
	printf("%s", "Enter new account number(1-100): ");
	unsigned int num;
	scanf("%d", &num);

	fseek(Ptr, (num - 1) * sizeof(struct Account),
		SEEK_SET);

	struct Account account = { 0, "", 0,0.0 };

	fread(&account, sizeof(struct Account), 1, Ptr);

	if (account.number != 0)
	{
		printf("Account #%d already contains information.\n", account.number);
	}
	else
	{

		printf("Enter Name(with a - for space), quantity, balance\n!");
		scanf("%31s%d%lf", account.name, &account.Q, &account.balance);

		account.number = num;

		fseek(Ptr, (account.number - 1) *sizeof(struct Account), SEEK_SET);

		fwrite(&account, sizeof(struct Account), 1, Ptr);
	}
}

void deleteRecord(FILE *Ptr)
{
	printf("%s", "Enter account number to delete (1 - 100): ");
	unsigned int accountNum;
	scanf("%d", &accountNum);


	fseek(Ptr, (accountNum - 1) * sizeof(struct Account),
		SEEK_SET);

	struct Account client;
	fread(&client, sizeof(struct Account), 1, Ptr);

	if (client.number == 0) {
		printf("Account %d does not exist.\n", accountNum);
	}
	else {
		fseek(Ptr, (accountNum - 1) * sizeof(struct Account), SEEK_SET);

		struct Account blank = { 0, "", 0,0.0 };
		fwrite(&blank, sizeof(struct Account), 1, Ptr);
	}
}
