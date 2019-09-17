#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <main.h>
#include <stdbool.h>


int noOfUsers;		// Total no of user in the list
user_details_t *head;	// Head node of the list containing details of users.

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
	int amount = 0;
	user_details_t *user = NULL;

	printf("\nStart entering name and amount of each user.\n");
	printf("\nEnter exit to stop entering data\n");

	while(1)
	{
		printf("\nEnter name and amount\n");
		scanf("%s", name);
		if(!strcmp(name,"exit"))	// Exit the loop when user finished entering user.
			break;
	
		while(scanf("%d", &amount) != 1)	// Check if non numeric value is entered.
		{
			printf("\nERROR : Only numeric value allowed.\n");
			printf("\nEnter the amount again : ");
			while(getchar() != '\n');
		}

		user = get_user_handle_in_list(name);	// Get node address of the user.
		if(user)				// If user already in the list then just update the amount paid.
		{
			user->amount_paid = user->amount_paid + amount;
		}
		else					// If user not available in the list the create a entry in the list.
		{
			user = create_node(name, amount);
			user->next = head;
			head = user;			// Update the head node.
			noOfUsers++;			// Update number of users.
		}
	}
}

// Update the balance each user have to pay of take.
void updateBalance()
{
        int total_amount = 0;
        int amount = 0;
	user_details_t *user = head;

	total_amount = calculateTotalAmount();
	amount = total_amount / noOfUsers;

        while(user)
        {
                user->remaining_balance = user->amount_paid - amount;	// Update remaining balance for each user that he have to take or give.
                user = user->next;
        }
}

// Calculate the total amount paid by users.
int calculateTotalAmount()
{
	int total = 0;
        user_details_t *user = head;

        while(user)

        {
                total = total + user->amount_paid;
                user = user->next;
        }

        return total;
}

// Print which user have to pay money to which user.
void printAmountToGive()
{
        int maxToGive = 0;
        int maxToTake = 0;
	user_details_t *user = NULL;		// Used for iterating over the list.
	user_details_t *user_of_give = NULL;	// Used to store the address of the node that have to give money.
	user_details_t *user_of_take = NULL;	// Used to store the address of the node that have to take money.

        while(true)
        {
                maxToGive = 0;
                maxToTake = 0;

                for(user = head; user; user = user->next)
                {
                        if((maxToGive >= user->remaining_balance) &&
                           (user->remaining_balance < 0))
                        {
                                maxToGive = user->remaining_balance;	// Get the user who have to pay max amount.
                                user_of_give = user;
                        }

                        if((maxToTake <= user->remaining_balance) &&
                           (user->remaining_balance > 0))
                        {
                                maxToTake = user->remaining_balance;	// Get user who have to take max amount.
                                user_of_take = user;
                        }
                }

                if(maxToGive && maxToTake)
                {
			if( -maxToGive >= maxToTake )
			{
				user_of_give->remaining_balance += maxToTake;	// Update the reamining balance after taking money from payer.
				maxToGive = -maxToTake;
				user_of_take->remaining_balance = 0;
			}
			else
			{
				user_of_take->remaining_balance += maxToGive;	// Update the remaining balance after giving money.
				user_of_give->remaining_balance = 0;
			}

                        printf("\n%s -> %s  , Amount = %d\n", user_of_give->name, user_of_take->name, -maxToGive);
                }
		else
			break;
        }
}

// Create a node to add new entry in the list.
user_details_t* create_node(char *name, int amount)
{
	user_details_t *user = NULL;

	MEM_ALLOC(user, sizeof(user_details_t));

	MEM_ALLOC(user->name, sizeof(char) * (strlen(name) + 1));

	strcpy(user->name, name);
	user->amount_paid = amount;
	user->next = NULL;

	return user;
}

// Get the address of the node having name same as argument name.
user_details_t* get_user_handle_in_list(char *name)
{
	user_details_t *user = head;

	while(user)
	{
		if(!strcmp(user->name, name))
			return user;
		user = user->next;
	}

	return NULL;
}
