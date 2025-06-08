#ifndef ACCOUNT_H
#define ACCOUNT_H

#define DB_FILE_PATH "db.dat"
#define NAME_MAX_LEN 50
#define SURNAME_MAX_LEN 50
#define ADDRES_MAX_LEN 100
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

struct Account_search_context_s;
typedef struct Account_search_context_s Account_search_context_s;

int generate_account_number(void);
void append_account_to_db(Account_s* acc);
Account_s* load_accounts(int* count);
void rewrite_accounts_in_db(Account_s* accounts, int count);

void for_each_account(void (*cb)(Account_s* a, Account_search_context_s* ctx),
					  Account_search_context_s* ctx);
void for_each_account_noctx(void (*cb)(Account_s* a));
void display_account_info(Account_s* a);

#endif // ACCOUNT_H
