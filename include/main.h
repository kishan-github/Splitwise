#ifndef MAIN_H
#define MAIN_H

#define MAX_NAME_LENGTH 100

typedef struct user_details
{
	char *name;			// Name of the user
	int amount_paid;		// Amount paid by user.
	int remaining_balance;		// Amount user have to pay or take
	struct user_details *next;	// next element in the list
}user_details_t;

void insertUser();
void updateBalance();
int calculateTotalAmount();
void printAmountToGive();
user_details_t* create_node(char *name, int amount);
user_details_t* get_user_handle_in_list(char *name);
#endif
