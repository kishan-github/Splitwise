#include <stdio.h>
#include <string.h>

#define MAX 10
#define MAX_COL 2
#define MAX_NAME_LENGTH 100

int arr[MAX][MAX_COL];
char userName[MAX][MAX_NAME_LENGTH];
int noOfUsers;

void insertUser();
void updateBalance();
int calculateTotalAmount();
void printAmountToGive();

int main()
{
	// Get user name and amount paid by them.
	insertUser();

	// Update each users give or take amount.
        updateBalance();

	// Print the name of user who have to pay the amount to other user.
        printAmountToGive();

        return 0;
}

// Enter user name and amount paid by them in the respective arrays.
void insertUser()
{
	char name[MAX_NAME_LENGTH];
	int idx = 0;
	int amt = 0;
	int idxAmt = 0;

	printf("\nStart entering name and amount of each user.\n");
	printf("\nEnter exit to stop entering data\n");

	while(1)
	{
		printf("\nEnter name and amount\n");
		scanf("%s", name);
		if(!strcmp(name,"exit"))
			break;
	
		while(scanf("%d", &amt) != 1)
		{
			printf("\nERROR : Only numeric value allowed.\n");
			printf("\nEnter the amount again : ");
			while(getchar() != '\n');
		}
		for(idx = 0; idx < noOfUsers; idx++)
		{
			if(!strcmp(name,userName[idx]))
			{
				arr[idx][idxAmt] += amt;
				break;
			}
		}
	
		if(idx == noOfUsers)
		{
			strcpy(userName[idx], name);
			arr[idx][idxAmt] = amt;
			noOfUsers++;
		}
	}
}

// Update the balance each user have to pay of take.
void updateBalance()
{
        int user_idx = 0;
        int user_amt = 0;
        int user_rem = 1;
        int total_Amount = calculateTotalAmount();
        int amount = total_Amount / noOfUsers;

        while(user_idx < noOfUsers)
        {
                arr[user_idx][user_rem] = arr[user_idx][user_amt] - amount;
                user_idx++;
        }
}

// Calculate the total amount paid by users.
int calculateTotalAmount()
{
        int total = 0;
        int idx = 0;

        while(idx < noOfUsers)
        {
                total = total + arr[idx][0];
                idx++;
        }

        return total;
}

// Print which user have to pay money to which user.
void printAmountToGive()
{
        int idx = 0;
        int maxToGive = 0;
        int maxToTake = 0;
        int idxOfGive = 0;
        int idxOfTake = 0;
        int idxAmt = 1;
        int i = 0;


        for(; i < noOfUsers; i++)
        {
                maxToGive = 0;
                maxToTake = 0;

                for(idx = 0; idx < noOfUsers; idx++)
                {
                        if((maxToGive >= arr[idx][idxAmt]) &&
                           (arr[idx][idxAmt] < 0))
                        {
                                maxToGive = arr[idx][idxAmt];
                                idxOfGive = idx;
                        }

                        if((maxToTake <= arr[idx][idxAmt]) &&
                           (arr[idx][idxAmt] > 0))
                        {
                                maxToTake = arr[idx][idxAmt];
                                idxOfTake = idx;
                        }
                }

                if(maxToGive && maxToTake)
                {
                        arr[idxOfTake][idxAmt] += maxToGive;
                        arr[idxOfGive][idxAmt] -= maxToGive;

                        printf("\n%s -> %s  , Amount = %d\n", userName[idxOfGive], userName[idxOfTake], -maxToGive);
                }
		else
			break;
        }
}
