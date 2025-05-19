#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "account.h"

typedef void (*op_function)(void);

typedef struct {
    const char *description;
    op_function handler;
} Operations_s;

typedef enum {
    OP_CREATE_ACCOUNT,
    OP_LIST_ACCOUNTS,
    OP_SEARCH_ACCOUNT,
    OP_DEPOSIT,
    OP_WITHDRAW,
    OP_TRANSFER,
    OP_TAKE_LOAN,
    OP_REPAY_LOAN,
    OP_EXIT,
    OP_COUNT
} Operation_code_s;

void init_operations();
void run_menu_loop();

// HANDLERS
void create_new_account();
void list_all_accounts();
void search_account();
void deposit_money();
void withdraw_money();
void transfer_money();
void take_loan();
void repay_loan();
void exit_program();

#endif // OPERATIONS_H
