#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include "structures.c"

#define PORT 5000

#define ERR_EXIT(msg)  do{ perror(msg);} while(0)


#define CUSTOMER_DB "customer_db"
#define ACCOUNT_DB "account_db"
#define TRANSACTION_DB "transaction_db"
/**
 * These 3 functions will help write clean code which is easier to understand.
*/
void sendReadToClient(int desc, char *msg)
{
    struct message communication;
    strcpy(communication.buffer, msg);
    communication.read = 0;
    write(desc, &communication, sizeof(communication));
}

void sendCloseToClient(int desc, char *msg)
{
    struct message communication;
    strcpy(communication.buffer, msg);
    communication.read = 2;
    write(desc, &communication, sizeof(communication));
}

void sendWriteToClient(int desc, char *msg, char *output)
{
    struct message communication;
    strcpy(communication.buffer, msg);
    communication.read = 1;
    write(desc, &communication, sizeof(communication));
    read(desc, output, 1024);
}
/**
 * The functions below will create the files required that will act as database.
*/
void initialSetup()
{
    int fd = open(CUSTOMER_DB, O_CREAT | O_EXCL | O_RDWR, 0755);
    if (fd != -1)
    {
        struct Customer admin;
        strcpy(admin.username, "admin");
        strcpy(admin.password, "admin");
        admin.del_flag = 0;
        admin.type = 1;
        admin.account_number = 5000;
        write(fd, &admin, sizeof(admin));
    }
    close(fd);

    int account_count = 5000;
    fd = open(ACCOUNT_DB, O_CREAT | O_EXCL | O_RDWR, 0755);
    if (fd != -1)
    {
        struct Account account_admin;
        account_admin.account_number = account_count;
        account_admin.balance = 0;
        account_admin.del_flag = 0;

        write(fd, &account_count, sizeof(account_count));
        write(fd, &account_admin, sizeof(account_admin));

        close(fd);
    }
    open(TRANSACTION_DB, O_CREAT | O_EXCL, 0755);
}
/**
 * Helps identify if the username is unique or not - while adding a new account/user
*/
int check_unique_user(char *uname)
{
    int fd = open(CUSTOMER_DB, O_RDONLY);
    struct Customer admin;
    while (read(fd, &admin, sizeof(admin)))
    {
        if (strcmp(uname, admin.username) == 0)
        {
            close(fd);
            return 1;
        }
    }
    close(fd);
    return 0;
}
/**
 * Asks for 2 sets of username and password.
 * The usernames should be unique(i.e. different from each other and there shouldn't be an exisiting customer with the same username).
*/
void add_JointAccount(char *username, char *password, char *username2, char *password2, int socket_desc)
{

    struct Customer cust;
    struct Customer cust2;
    struct Account acc;

    int fd = open(ACCOUNT_DB, O_RDWR);
    int count;

    read(fd, &count, sizeof(count));
    count++;
    lseek(fd, 0, SEEK_SET);
    write(fd, &count, sizeof(count));
    lseek(fd, 0, SEEK_END);
    acc.account_number = count;
    acc.balance = 0;
    acc.del_flag = 0;
    write(fd, &acc, sizeof(acc));
    close(fd);

    fd = open(CUSTOMER_DB, O_WRONLY | O_APPEND);

    strcpy(cust.password, password);
    strcpy(cust.username, username);
    cust.type = 3;
    cust.del_flag = 0;
    cust.account_number = count;
    write(fd, &cust, sizeof(cust));

    strcpy(cust2.password, password2);
    strcpy(cust2.username, username2);
    cust2.type = 3;
    cust2.del_flag = 0;
    cust2.account_number = count;
    write(fd, &cust2, sizeof(cust2));
    close(fd);

    sendReadToClient(socket_desc, "Users Added Succesfully\n");
}
/**
 * If admin wants to add a joint account, then control will go to the above function where it will ask for 2 sets of usernames and passwords.
 * Otherwise, it will create a normal/admin user.
 * Username should be unique.
*/
void add_account(int socket_desc)
{

    char username[1024], password[1024];

    char type[1024];
    char msg_username[1024] = "Enter username: ";
    char msg_password[1024] = "Enter password: ";

    sendWriteToClient(socket_desc, msg_username, username);
    sendWriteToClient(socket_desc, msg_password, password);

    if (check_unique_user(username) == 1)
    {
        sendReadToClient(socket_desc, "Error. Username is not unique.\n");
        return;
    }
    char msg_type[1024] = "Enter type\n\tPress 1 for Admin\n\tPress 2 for Normal User\n\tPress 3 for Joint User\n";
    sendWriteToClient(socket_desc, msg_type, type);
    int intType = atoi(type); //remove
    if (intType == 3)
    {
        char username2[1024], password2[1024];
        char msg_username2[1024] = "Enter username2: ";
        char msg_password2[1024] = "Enter password: ";
        sendWriteToClient(socket_desc, msg_username2, username2);
        sendWriteToClient(socket_desc, msg_password2, password2);
        if (check_unique_user(username2) == 1 || strcmp(username, username2) == 0)
        {
            sendReadToClient(socket_desc, "Error. Username2 is not unique.\n");
        }
        else
        {
            add_JointAccount(username, password, username2, password2, socket_desc);
        }
    }

    else
    {
        struct Customer cust;
        struct Account acc;

        int fd = open(ACCOUNT_DB, O_RDWR);
        int count;

        read(fd, &count, sizeof(count));
        count++;
        lseek(fd, 0, SEEK_SET);
        write(fd, &count, sizeof(count));
        lseek(fd, 0, SEEK_END);
        acc.account_number = count;
        acc.balance = 0;
        acc.del_flag = 0;
        write(fd, &acc, sizeof(acc));
        close(fd);

        fd = open(CUSTOMER_DB, O_WRONLY | O_APPEND);

        strcpy(cust.password, password);
        strcpy(cust.username, username);
        cust.type = intType; //remove
        //cust.type=type;
        cust.del_flag = 0;
        cust.account_number = count;
        write(fd, &cust, sizeof(cust));
        close(fd);

        sendReadToClient(socket_desc, "User Added Succesfully\n");
    }
}
/**
 * using del_flag in account and customer structure
 * If we wish to delete a record, we simply change the value of del_flag from false to true.
 * Also, first implementing a read Lock when checking if the account has any balance remaining.
 * If the admin still wishes to continue with deletion operation even after the prompt that there's balance remaining,
 * then implementing a write lock and changing the values.
 * If an account is deleted, it's corresponding user/users will also be deleted from the customerDB(del_flag=true)
*/
int delete_account(int socket_desc)
{
    int fd, fd2, found = 0;

    struct Customer cust;
    struct Account ac;
    char confirm[1024];
    char accountno[1024];
    char amount[1024];
    struct flock lock;
    sendWriteToClient(socket_desc, "Enter Account number:", accountno);
    int accountnumber = atoi(accountno);

    fd2 = open(ACCOUNT_DB, O_RDWR);
    lseek(fd2, sizeof(int), SEEK_SET);
    while (read(fd2, &ac, sizeof(ac)))
    {
        if (found == 0 && accountnumber == ac.account_number && !ac.del_flag)
        {
            found = 1;

           struct flock lock;
            lock.l_type = F_RDLCK;
            lock.l_whence = SEEK_SET;
            lock.l_start = ((accountnumber - 5000) * sizeof(ac)) + sizeof(int);
            lock.l_len = sizeof(ac);
            lock.l_pid = getpid();
            if (fcntl(fd2, F_SETLKW, &lock) == -1)
                ERR_EXIT("delete_account() account read lock -> fcntl(SETLKW)");
            if (ac.balance > 0)
            {
                sendReadToClient(socket_desc, "\nBalance remaining: ");
                sprintf(amount, "%.2f", ac.balance);
                sendWriteToClient(socket_desc, "\nAre you sure you want to delete account?(Y/N):", confirm);
                if (confirm[0] == 'Y' || confirm[0] == 'y')
                {
                    sendReadToClient(socket_desc, "Deleting account\n");
                }
                else if (confirm[0] == 'N' || confirm[0] == 'n')
                {
                    sendReadToClient(socket_desc, "Stopping delete operation\n");
                    // Unlock
                    lock.l_type = F_UNLCK;
                    if (fcntl(fd2, F_SETLKW, &lock) == -1)
                        ERR_EXIT("delete_account() account unlock-> fcntl()");
                    return -1;
                }
            }
            lock.l_type = F_WRLCK;
            lock.l_whence = SEEK_SET;
            lock.l_start = ((accountnumber - 5000) * sizeof(ac)) + sizeof(int);
            lock.l_len = sizeof(ac);
            lock.l_pid = getpid();
            if (fcntl(fd2, F_SETLKW, &lock) == -1)
                ERR_EXIT("delete_account() account write lock -> fcntl()");
            ac.del_flag = true;
            lseek(fd2, -sizeof(ac), SEEK_CUR);
            write(fd2, &ac, sizeof(ac));
            lock.l_type = F_UNLCK;
            if (fcntl(fd2, F_SETLKW, &lock) == -1)
                ERR_EXIT("delete_account() unlcok account write lock-> fcntl()");
        }
    }
    if (found == 0)
    {
        sendReadToClient(socket_desc, "Account does not exist\n");
        return -1;
    }

    fd = open(CUSTOMER_DB, O_RDWR);
    while (read(fd, &cust, sizeof(cust)))
    {
        if (accountnumber == cust.account_number && !cust.del_flag)
        {
            lock.l_type = F_WRLCK;
            lock.l_whence = SEEK_CUR;
            lock.l_start = -sizeof(cust);
            lock.l_len = sizeof(cust);
            lock.l_pid = getpid();
            if (fcntl(fd, F_SETLKW, &lock) == -1)
                ERR_EXIT("delete_account() cust lock-> fcntl(SETLKW)");
            cust.del_flag = true;
            lseek(fd, -sizeof(cust), SEEK_CUR);
            write(fd, &cust, sizeof(cust));
            lock.l_type = F_UNLCK;
            if (fcntl(fd, F_SETLKW, &lock) == -1)
                ERR_EXIT("delete_account() cust unlock -> fcntl()");
        }
    }

    sendReadToClient(socket_desc, "Successfully deleted the account\n");

    close(fd);
    close(fd2);
    return 0;
}
/**
 * Allows admin to change the 
 * 1. password of an existing user 
 * 2. change an existing normal account to joint account.
*/
void modify_account(int socket_desc)
{
    char choice[1024];
    char username[1024];
    char password[1024];
    struct flock lock;
    sendWriteToClient(socket_desc, "\tPress 1 to change password\n\tPress 2 to change create joint account\n", choice);
    if (choice[0] == '1')
    {
        sendWriteToClient(socket_desc, "Enter username:", username);
        int fd = open(CUSTOMER_DB, O_RDWR);
        int found = 0;
        struct Customer cust;
        while (found == 0 && read(fd, &cust, sizeof(cust)))
        {
            if (strcmp(cust.username, username) == 0 && cust.del_flag == 0)
            {
                found = 1;
            }
        }
        if (found == 1)
        {
            lock.l_type = F_WRLCK;
            lock.l_whence = SEEK_CUR;
            lock.l_start = -sizeof(cust);
            lock.l_len = sizeof(cust);
            lock.l_pid = getpid();
            if (fcntl(fd, F_SETLKW, &lock) == -1)
                ERR_EXIT("modify_account() -> fcntl(SETLKW)");
            lseek(fd, -sizeof(cust), SEEK_CUR);
            sendWriteToClient(socket_desc, "Enter new password:", password);
            strcpy(cust.password, password);
            write(fd, &cust, sizeof(cust));
            // Unlock
            lock.l_type = F_UNLCK;
            if (fcntl(fd, F_SETLKW, &lock) == -1)
                ERR_EXIT("modify_account() -> fcntl()");
            close(fd);
            sendReadToClient(socket_desc, "Password Succesfully Changed\n");
        }
        else
        {
            sendReadToClient(socket_desc, "User not Found\n");
        }
    }
    else if (choice[0] == '2')
    {
        sendWriteToClient(socket_desc, "Enter username:", username);
        int fd = open(CUSTOMER_DB, O_RDWR);
        int found = 0;
        char username2[1024];
        struct Customer cust, cust2;
        while (found == 0 && read(fd, &cust, sizeof(cust)))
        {
            if (strcmp(cust.username, username) == 0 && cust.del_flag == 0)
            {
                found = 1;
            }
        }
        if (found == 1 && cust.type != 3)
        {
            lock.l_type = F_RDLCK;
            lock.l_whence = SEEK_CUR;
            lock.l_start = -sizeof(cust);
            lock.l_len = sizeof(cust);
            lock.l_pid = getpid();
            lseek(fd, -sizeof(cust), SEEK_CUR);
            cust.type = 3; //joint user
            write(fd, &cust, sizeof(cust));

            lseek(fd, 0, SEEK_END);
            sendWriteToClient(socket_desc, "Enter username for 2nd User:", username2);
            sendWriteToClient(socket_desc, "Enter Password for 2nd user:", password);
            strcpy(cust2.username, username2);
            strcpy(cust2.password, password);
            cust2.account_number = cust.account_number;
            cust2.del_flag = 0;
            cust2.type = 3;
            write(fd, &cust2, sizeof(cust2));
            // Unlock
            lock.l_type = F_UNLCK;
            if (fcntl(fd, F_SETLKW, &lock) == -1)
                ERR_EXIT("modify_account() -> fcntl()");
            close(fd);
            sendReadToClient(socket_desc, "Joint account successfully created\n");
        }
        else if (found == 0)
        {
            sendReadToClient(socket_desc, "User not Found\n");
        }
        else
        {
            sendReadToClient(socket_desc, "User already has a joint account\n");
        }
    }
    else
    {
        sendReadToClient(socket_desc, "Invalid Choice\n");
    }
}
/**
 * Used a Read Lock for this function so that written changes from other processes (like deposit/withdraw) don't occur 
 * while retrieving information from the DB file.
*/
void search_account(int socket_desc)
{

    char username[1024], balance[1024], acno[1024];
    int found = 0;
    char username2[1024];
    struct Customer cust;
    struct Account ac;

    int fd = open(CUSTOMER_DB, O_RDONLY);
    sendWriteToClient(socket_desc, "Enter username:", username);

    while (found == 0 && read(fd, &cust, sizeof(cust)))
    {
        if (strcmp(cust.username, username) == 0 && cust.del_flag == 0)
        {
            found = 1;
        }
    }
    close(fd);
    if (found == 0)
    {
        sendReadToClient(socket_desc, "User not found\n");
    }
    else
    {
        fd = open(ACCOUNT_DB, O_RDONLY);
        struct flock lock;
        lock.l_type = F_RDLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = ((cust.account_number - 5000) * sizeof(ac)) + sizeof(int);
        lock.l_len = sizeof(ac);
        lock.l_pid = getpid();
        if (fcntl(fd, F_SETLKW, &lock) == -1)
            ERR_EXIT("search_account() -> fcntl(SETLKW)");

        lseek(fd, sizeof(int), SEEK_SET);
        lseek(fd, sizeof(ac) * (cust.account_number - 5000), SEEK_CUR);
        read(fd, &ac, sizeof(ac));
        // Unlock
        lock.l_type = F_UNLCK;
        if (fcntl(fd, F_SETLKW, &lock) == -1)
            ERR_EXIT("search_account() -> fcntl()");
        close(fd);

        sendReadToClient(socket_desc, "\nUsername: ");
        sendReadToClient(socket_desc, cust.username);
        sendReadToClient(socket_desc, "\nPassword: ");
        sendReadToClient(socket_desc, cust.password);
        sendReadToClient(socket_desc, "\nAccountType: ");
        if (cust.type == 1)
            sendReadToClient(socket_desc, "Admin");
        else if (cust.type == 2)
            sendReadToClient(socket_desc, "Normal Account");
        else
            sendReadToClient(socket_desc, "Joint Account");

        sprintf(acno, "%ld", cust.account_number);
        sendReadToClient(socket_desc, "\nAccount number: ");
        sendReadToClient(socket_desc, acno);

        sprintf(balance, "%.2f", ac.balance);
        sendReadToClient(socket_desc, "\nAccount Balance:");
        sendReadToClient(socket_desc, balance);
    }
}
/**
 * Write Lock for the deposit function and we also check whether the account is still active or not before asking for the deposit amount.
 * For each successful deposit, we also make an entry in the transaction db.
*/
void deposit(int socket_desc, struct Customer record)
{
    struct Account ac;
    struct transaction tran;
    char amount[1024];
    float dep_amount;

    int fd = open(ACCOUNT_DB, O_RDWR);
    int fd2 = open(TRANSACTION_DB, O_WRONLY | O_APPEND);

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = ((record.account_number - 5000) * sizeof(ac)) + sizeof(int);
    lock.l_len = sizeof(ac);
    lock.l_pid = getpid();
    if (fcntl(fd, F_SETLKW, &lock) == -1)
        ERR_EXIT("deposit() -> fcntl(SETLKW)");
    
    //checking if the account is still active or not before writing - just in case admin deleted the account before the write lock could be acquired
    if(ac.del_flag) {
        // Unlock
        lock.l_type = F_UNLCK;
        if (fcntl(fd, F_SETLKW, &lock) == -1)
            ERR_EXIT("deposit() -> fcntl()");
        close(fd);
        sendReadToClient(socket_desc, "\nInvalid account\n");
        return;
    }

    sendWriteToClient(socket_desc, "Enter the deposit amount:", amount);
    dep_amount = atof(amount);

    if (dep_amount <= 0)
    {
        sendReadToClient(socket_desc, "Deposit Amount should be greater than zero.\n");
        return;
    }    

    lseek(fd, sizeof(int), SEEK_SET);
    lseek(fd, sizeof(ac) * (record.account_number - 5000), SEEK_CUR);
    read(fd, &ac, sizeof(ac));
    
    ac.balance = ac.balance + dep_amount;
    lseek(fd, -sizeof(ac), SEEK_CUR);
    write(fd, &ac, sizeof(ac));

    // Unlock
    lock.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLKW, &lock) == -1)
        ERR_EXIT("deposit() -> fcntl()");
    close(fd);

    tran.account_number = ac.account_number;
    tran.amount = dep_amount;
    tran.balance_remaining = ac.balance;

    char text[12];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(text, sizeof(text) - 1, "%d/%m/%Y", t);

    strcpy(tran.date, text);
    write(fd2, &tran, sizeof(tran));

    close(fd);
    close(fd2);

    sendReadToClient(socket_desc, "Successfully Deposited the amount\n");
}
/**
 * Write Lock for the withdraw function and we also check whether the account is still active or not before asking for the withdrawal amount.
 * We also check whether the account has sufficient balance required for the withdrawal.
 * For each successful withdrawal, we also make an entry in the transaction db.
*/
void withdraw(int socket_desc, struct Customer record)
{
    struct Account ac;
    struct transaction tran;
    char amount[1024];
    float withdraw_amount;
   
    int fd = open(ACCOUNT_DB, O_RDWR);
    int fd2 = open(TRANSACTION_DB, O_WRONLY | O_APPEND);

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = ((record.account_number - 5000) * sizeof(ac)) + sizeof(int);
    lock.l_len = sizeof(ac);
    lock.l_pid = getpid();
    if (fcntl(fd, F_SETLKW, &lock) == -1)
        ERR_EXIT("withdraw() -> fcntl(SETLKW)");
    //checking if the account is still active or not before writing - just in case admin deleted the account before the write lock could be acquired
    if(ac.del_flag) {
        // Unlock
        lock.l_type = F_UNLCK;
        if (fcntl(fd, F_SETLKW, &lock) == -1)
            ERR_EXIT("deposit() -> fcntl()");
        close(fd);
        sendReadToClient(socket_desc, "\nInvalid account\n");
        return;
    }

    sendWriteToClient(socket_desc, "Enter the amount to be withdrawn:", amount);
    withdraw_amount = atof(amount);

    lseek(fd, sizeof(int), SEEK_SET);
    lseek(fd, sizeof(ac) * (record.account_number - 5000), SEEK_CUR);
    read(fd, &ac, sizeof(ac));

    if (ac.balance < withdraw_amount)
    {
         // Unlock
        lock.l_type = F_UNLCK;
        if (fcntl(fd, F_SETLKW, &lock) == -1)
            ERR_EXIT("deposit() -> fcntl()");
        close(fd);
        sendReadToClient(socket_desc, "Insufficient balance\n");
        return;
    }
    
    ac.balance = ac.balance - withdraw_amount;
    lseek(fd, -sizeof(ac), SEEK_CUR);
    write(fd, &ac, sizeof(ac));

    // Unlock
    lock.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLKW, &lock) == -1)
        ERR_EXIT("withdraw() -> fcntl()");

    tran.account_number = ac.account_number;
    tran.amount = -withdraw_amount;
    tran.balance_remaining = ac.balance;
    char text[12];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(text, sizeof(text) - 1, "%d/%m/%Y", t);

    strcpy(tran.date, text);
    write(fd2, &tran, sizeof(tran));

    close(fd);
    close(fd2);
    sendReadToClient(socket_desc, "Successfully withdrawn the amount\n");
}
/**
 * When users wish to change their password. Ask for the existing password -> compare it to the password in the DB and if they're the same, then 
 * proceed to update the password.
 * Used a Write Lock for this, in case the admin is also modifying the password for this user concurrently.
*/
void change_password(int socket_desc, struct Customer record)
{
    struct Customer cust;
    char newpass[1024], oldpass[1024];    

    int found = 0;
    int fd = open(CUSTOMER_DB, O_RDWR);
    while (found == 0 && read(fd, &cust, sizeof(cust)))
    {
        if (strcmp(cust.username, record.username) == 0)
        {
            struct flock lock;
            lock.l_type = F_WRLCK;
            lock.l_whence = SEEK_CUR;
            lock.l_start = -sizeof(cust);
            lock.l_len = sizeof(cust);
            lock.l_pid = getpid();
            if (fcntl(fd, F_SETLKW, &lock) == -1)
                ERR_EXIT("change_password() -> fcntl(SETLKW)");
            found = 1;
            sendWriteToClient(socket_desc, "Enter old password:", oldpass);
            if (strcmp(oldpass, record.password) != 0){
                sendReadToClient(socket_desc, "Incorrect Password\n");
                return;
            }
                
            sendWriteToClient(socket_desc, "Enter new password:", newpass);
            lseek(fd, -sizeof(cust), SEEK_CUR);
            strcpy(cust.password, newpass);
            write(fd, &cust, sizeof(cust));

            // Unlock
            lock.l_type = F_UNLCK;
            if (fcntl(fd, F_SETLKW, &lock) == -1)
                ERR_EXIT("change_password() -> fcntl()");
            close(fd);
        }
    }
    sendReadToClient(socket_desc, "Password successfully Changed\n");
}
/**
 * When user wishes to check the balance amount of their account.
 * Read Lock implemented.
*/

void check_balance(int socket_desc, struct Customer record)
{
    struct Account ac;
    char balance[1024];
    int fd = open(ACCOUNT_DB, O_RDWR);
    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = ((record.account_number - 5000) * sizeof(ac)) + sizeof(int);
    lock.l_len = sizeof(ac);
    lock.l_pid = getpid();
    if (fcntl(fd, F_SETLKW, &lock) == -1)
        ERR_EXIT("check_balance() -> fcntl(SETLKW)");
    lseek(fd, sizeof(int), SEEK_SET);
    lseek(fd, sizeof(ac) * (record.account_number - 5000), SEEK_CUR);
    read(fd, &ac, sizeof(ac));

    // Unlock
    lock.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLKW, &lock) == -1)
        ERR_EXIT("check_balance() -> fcntl()");
    close(fd);

    sendReadToClient(socket_desc, "Your current balance is: Rs");
    sprintf(balance, "%.2f", ac.balance);
    sendReadToClient(socket_desc, balance);
}
/**
 * Fetches the details from transactionDB for Customer's account.
 * Read Lock Implemented on the entire file.
*/
void view_details(int socket_desc, struct Customer record)
{
    struct transaction tran;
    char balance[1024], amount[1024], acno[1024];
    int fd = open("transaction_db", O_RDONLY);
    int found = 0;
    struct flock lock;
    lock.l_type = F_RDLCK;
    if (fcntl(fd, F_SETLKW, &lock) == -1)
        ERR_EXIT("view_details() -> fcntl(SETLKW)");
    while (read(fd, &tran, sizeof(tran)))
    {
        if (tran.account_number == record.account_number)
        {
            found = 1;
            sendReadToClient(socket_desc, "\nAccount number: ");
            sprintf(acno, "%ld", tran.account_number);
            sendReadToClient(socket_desc, acno);
            sendReadToClient(socket_desc, "\nDate: ");
            sendReadToClient(socket_desc, tran.date);
            sendReadToClient(socket_desc, "\nAmount transferred: ");
            sprintf(amount, "%.2f", tran.amount);
            sendReadToClient(socket_desc, amount);
            sendReadToClient(socket_desc, "\nRemaining Balance: ");
            sprintf(balance, "%.2f", tran.balance_remaining);
            sendReadToClient(socket_desc, balance);
            sendReadToClient(socket_desc, "\n----------------------\n");
        }
    }
    // Unlock
    lock.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLKW, &lock) == -1)
        ERR_EXIT("view_details() -> fcntl()");
    close(fd);
    if (found == 0)
        sendReadToClient(socket_desc, "\nNo Transactions made yet\n");
}
/**
 * Displays the different options available for - admin and normal/joint user.
*/
void display_menu(int socket_desc, struct Customer record)
{
    char choice[10];
    if (record.type == 1)
    {

        char welcome_msg[1024] = "---------------WELCOME ADMIN----------------------\n";
        sendReadToClient(socket_desc, welcome_msg);
        char menu[1024] = "Press 1 to add an account\nPress 2 to delete an account\nPress 3 to modify an account\nPress 4 to search an account\n";
        sendWriteToClient(socket_desc, menu, choice);
        switch (choice[0])
        {
        case '1':
            sendReadToClient(socket_desc, "Add Account\n\n");
            add_account(socket_desc);
            break;
        case '2':
            sendReadToClient(socket_desc, "Delete Account\n");
            //sendWriteToClient(socket_desc,"Press 1 to delete user\nPress 2 to delete account\n");
            delete_account(socket_desc);
            break;
        case '3':
            sendReadToClient(socket_desc, "Modify Account\n");
            modify_account(socket_desc);
            break;
        case '4':
            sendReadToClient(socket_desc, "Search account\n");
            search_account(socket_desc);
            break;
        default:
            sendReadToClient(socket_desc, "Invalid option");
        }
    }
    else
    {
        char welcome_msg[1024] = "---------------WELCOME USER----------------------\n";
        sendReadToClient(socket_desc, welcome_msg);
        char menu[1024] = "Press 1 to deposit\nPress 2 to withdraw\nPress 3 to check balance\nPress 4 to change password\nPress 5 to view details\nPress 6 to Exit\n";
        sendWriteToClient(socket_desc, menu, choice);
        switch (choice[0])
        {
        case '1':
            sendReadToClient(socket_desc, "------------------Deposit---------------\n");
            deposit(socket_desc, record);
            break;
        case '2':
            sendReadToClient(socket_desc, "-----------------Withdraw----------------\n");
            withdraw(socket_desc, record);
            break;
        case '3':
            sendReadToClient(socket_desc, "------------------Check Balance-------------\n");
            check_balance(socket_desc, record);
            break;
        case '4':
            sendReadToClient(socket_desc, "------------------Change Password-------------\n");
            change_password(socket_desc, record);
            break;
        case '5':
            sendReadToClient(socket_desc, "------------------View Details------------\n");
            view_details(socket_desc, record);
            break;
        }
    }
}
/**
 * Checks during login if the username and password match and whether the account is active or not.
*/
void validate_credentials(int socket_desc)
{
    char welcome_msg[1024] = "------------------WELCOME BANK------------------\n";
    sendReadToClient(socket_desc, welcome_msg); //reconnecting
    char username[1024], password[1024];
    char msg_username[1024] = "Enter username: ";
    char msg_password[1024] = "Enter password: ";
    sendWriteToClient(socket_desc, msg_username, username);
    sendWriteToClient(socket_desc, msg_password, password);
    struct Customer record;
    int fd = open("customer_db", O_RDONLY);
    bool flag = false;
    while (read(fd, &record, sizeof(record)))
    {
        if (strcmp(record.username, username) == 0 && strcmp(record.password, password) == 0 && !record.del_flag)
        {

            display_menu(socket_desc, record);
            flag = true;
            break;
        }
    }
    if (!flag)
    {
        sendReadToClient(socket_desc, "Invalid username/password. Logging out.\n");
        return;
    }
}

void main()
{
    struct sockaddr_in serverad, clientad;
    int sfd, nsd, clientLen, client_socket;
    char buff[50];

    sfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    initialSetup();

    serverad.sin_family = AF_INET;
    serverad.sin_addr.s_addr = INADDR_ANY;
    serverad.sin_port = htons(PORT); //convers 5555 from host byte order to network byte order

    bind(sfd, (struct sockaddr *)&serverad, sizeof(serverad)); //binds a name to socket

    listen(sfd, 2); //coverts socket to passive, used to accept connections

    printf("Waiting for client...\n");
    while (1)
    {
        clientLen = sizeof(clientad);
        client_socket = accept(sfd, (struct sockaddr *)&clientad, &clientLen); //accepting connection
        printf("\n");
        write(1, "Connected to client...\n", sizeof("Connected to client...\n"));
        if (!fork())
        {
            validate_credentials(client_socket);
            char close_message[1024] = "\nShutting down";
            sendCloseToClient(client_socket, close_message);
        }
        else
        {
            close(nsd);
        }
    }
    close(sfd);
}
