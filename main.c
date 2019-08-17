#include <stdio.h>
#include <string.h>

#define MAX 10
#define MAX_COL 2

int arr[MAX][MAX_COL];
int noOfUsers;

void updateBalance();
int calculateTotalAmount();
void printAmountToGive();

int main()
{
        int amt = 0;
        int idx = 0;

        while(idx != -1)
        {
                scanf("%d%d", &idx, &amt);
                arr[idx][0] = arr[idx][0] + amt;
		noOfUsers++;
        }
	noOfUsers--;

        updateBalance();

        printAmountToGive();

        idx = 0;
        while(idx < noOfUsers)
        {
                printf("\n%d  %d   %d", idx, arr[idx][0], arr[idx][1]);
                idx++;
        }
        return 0;
}

// Update the balance each user have to pay of take.
void updateBalance()
{
        int user_idx = 0;
        int user_amt = 0;
        int user_rem = 1;
        int total_Amount = calculateTotalAmount();
        int amount = total_Amount / noOfUsers;

        printf("----------------- %d         %d", total_Amount, amount);

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

                        printf("\n %d -> %d  , Amount = %d", idxOfGive, idxOfTake, -maxToGive);
                }
		else
			break;
        }
}
