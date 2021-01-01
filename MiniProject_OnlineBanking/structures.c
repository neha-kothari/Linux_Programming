
struct Customer
{
	char username[1024];
	char password[1024];
	long int account_number;
	int type; //1 for admin, 2 for normal and 3 for joint
	bool del_flag; // 0 to active, 1 to inactive
};

struct Account
{
	long int account_number;
	double balance;
	bool del_flag;
};

struct transaction
{
	long int account_number;
	char date[12];
	double amount;
	double balance_remaining;
};

struct message{
	char buffer[1024];
	int read;  // 0 to  read write and 1 to  read, 2 to close
};
