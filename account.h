#ifndef ACCOUNT_H
#define ACCOUNT_H

#define DB_FILE_PATH	"db.dat"
#define NAME_MAX_LEN	50
#define SURNAME_MAX_LEN	50
#define ADDRES_MAX_LEN	100
#define PESEL_MAX_LEN 11

typedef struct {
    int account_number;
    char name[NAME_MAX_LEN];
    char surname[SURNAME_MAX_LEN];
    char address[ADDRES_MAX_LEN];
    char pesel[PESEL_MAX_LEN + 1];
    double balance;
    double loan_balance;
} Account_s;

// FILE OPERATIONS
int generate_account_number();
void append_account_to_db(const Account_s *acc);
Account_s* load_accounts(int *count);
void rewrite_accounts_in_db(Account_s *accounts, int count);

// DISPLAYING AND ITERATION
void for_each_account(void (*cb)(const Account_s*, void*), void *ctx);
void for_each_account_noctx(void (*cb)(const Account_s*));
void display_account_info(const Account_s *a);

#endif // ACCOUNT_H
