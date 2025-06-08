#include "operations.h"
#include "user_input.h"
#include "search.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Operations_s Operations[OP_COUNT];

void init_operations(void) {
    Operations[OP_CREATE_ACCOUNT]   = (Operations_s){"Create new account", create_new_account};
    Operations[OP_LIST_ACCOUNTS]    = (Operations_s){"List all accounts",  list_all_accounts};
    Operations[OP_SEARCH_ACCOUNT]   = (Operations_s){"Search account",      search_account};
    Operations[OP_DEPOSIT]          = (Operations_s){"Deposit money",      deposit_money};
    Operations[OP_WITHDRAW]         = (Operations_s){"Withdraw money",     withdraw_money};
    Operations[OP_TRANSFER]         = (Operations_s){"Transfer money between accounts", transfer_money};
    Operations[OP_TAKE_LOAN]        = (Operations_s){"Take a loan",        take_loan};
    Operations[OP_REPAY_LOAN]       = (Operations_s){"Repay loan",         repay_loan};
    Operations[OP_EXIT]             = (Operations_s){"Exit program",       exit_program};
}

void run_menu_loop() {
    while (true) {
        printf("\n\t BANKING SYSTEM \n");
        for (int i = 0; i < OP_COUNT; ++i)
            printf("%d. %s\n", i + 1, Operations[i].description);
        printf("Select (1-%d): ", OP_COUNT);

        int choice;
        if (scanf("%d", &choice) != 1) {
			int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Invalid input\n");
            continue;
        }
        getchar();
        if (choice < 1 || choice > OP_COUNT) {
            printf("Invalid choice\n");
            continue;
        }
        Operations[choice - 1].handler();
    }
}

// HANDLERS

void create_new_account() {
    Account_s a = { 0 };
    a.account_number = generate_account_number();
    printf("\n-- Create an Account (#%d) --\n", a.account_number);
    printf("Name: ");
    read_input_line(a.name, NAME_MAX_LEN);
    printf("Surname: ");
    read_input_line(a.surname, SURNAME_MAX_LEN);
    printf("Address: ");
    read_input_line(a.address, ADDRES_MAX_LEN);
    printf("PESEL: ");
    read_input_line(a.pesel, PESEL_MAX_LEN + 1);
    a.balance = a.loan_balance = 0.0;
    if (confirm_action("Confirm creation?")) {
        append_account_to_db(&a);
        printf("Account created\n");
    } else {
        printf("Operation cancelled\n");
    }
}

void list_all_accounts() {
    printf("\n \t List of All Accounts  \n");
    for_each_account_noctx(display_account_info);
}

void search_account() {
    int choice;
    printf("\n-- Search Account By--\n"); 
    printf(" 1. Account number\n");
    printf(" 2. First name\n");
    printf(" 3. Last name\n");
    printf(" 4. Address\n");
    printf(" 5. PESEL\n");
    printf("Choice (1-5): ");
    
    if (scanf("%d", &choice) != 1) {
        while (getchar() != '\n');
        printf("Invalid input \n");
        return;
    }
    getchar();
    
    void (*cb)(Account_s*, Account_search_context_s*) = NULL;
    switch (choice) {
        case 1: cb = search_by_number_callback;   break;
        case 2: cb = search_by_name_callback;     break;
        case 3: cb = search_by_surname_callback;  break;
        case 4: cb = search_by_address_callback;  break;
        case 5: cb = search_by_pesel_callback;    break; 
        default:
            printf("Invalid choice, enter (1-5)\n");
            return;
    }
    
    char key[ADDRES_MAX_LEN];
    printf("Enter: ");
    read_input_line(key, sizeof(key));

    Account_search_context_s ctx;
    ctx.found = false;
    strncpy(ctx.key, key, sizeof(ctx.key) - 1);
    ctx.key[sizeof(ctx.key) - 1] = '\0';

    for_each_account(cb, &ctx);
}

void deposit_money() {
    int num; 
    double total;
    printf("\n-- Deposit --\nAccount #: ");
    scanf("%d", &num); getchar();
    printf("Amount: ");
    scanf("%lf", &total); getchar();
    if (!confirm_action("Confirm deposit?"))
		return;
    
    int n;
    Account_s *arr = load_accounts(&n);
    if (!arr) { 
		printf("No accounts\n"); 
		return; 
	}
	
    for (int i = 0; i < n; ++i) {
        if (arr[i].account_number == num) {
            arr[i].balance += total;
            printf("Updated balance: %.2f\n", arr[i].balance);
            rewrite_accounts_in_db(arr, n);
            free(arr);
            return;
        }
    }
    free(arr);
    printf("Not found\n");
}

void withdraw_money() {
    int num; 
    double total;
    printf("\n-- Withdraw --\n For Account #: ");
    scanf("%d", &num); getchar();
    printf("Amount:    ");
    scanf("%lf", &total); getchar();
    if (!confirm_action("Confirm withdrawal?")) return;
    
    int n; 
    Account_s *arr = load_accounts(&n);
    if (!arr) { 
		printf("No accounts\n"); 
		return; 
	}
    for (int i = 0; i < n; ++i) {
        if (arr[i].account_number == num) {
            if (arr[i].balance < total) {
                printf("You are trying to withdraw more money that you obatain! Lack of funds\n");
            } else {
                arr[i].balance -= total;
                printf("Updated balance: %.2f\n", arr[i].balance);
                rewrite_accounts_in_db(arr, n);
            }
            free(arr);
            return;
        }
    }
    free(arr);
    printf("Not found\n");
}

void transfer_money() {
    int src, dst; 
    double total;
    printf("\n-- Transfering --\nSource #: ");
    scanf("%d", &src); getchar();
    printf("Destination #: ");
    scanf("%d", &dst); getchar();
    printf("Amount: ");
    scanf("%lf", &total); getchar();
    if (!confirm_action("Confirm transfer?")) return;
    
    int n;
    Account_s *arr = load_accounts(&n);
    if (!arr) {
		printf("No accounts \n"); 
		return; 
	
	}
    Account_s *a = NULL;
    Account_s *b = NULL;
 
    for (int i = 0; i < n; ++i) {
        if (arr[i].account_number == src) a = &arr[i];
        if (arr[i].account_number == dst) b = &arr[i];
    }
	if (NULL == a ||  NULL == b) {
        printf("Invalid account(s)\n");
    }
    else if (a->balance < total) {
        printf("Not enough funds\n");
    }
    else {
        a->balance -= total;
        b->balance += total;
        rewrite_accounts_in_db(arr, n);
        printf("Transfer done\n");
    }
    free(arr);
}

void take_loan() {
    int num; 
    double total, rate;
    printf("\n-- Take a Loan --\nAccount #: ");
    scanf("%d", &num); getchar();
    printf("Amount: ");
    scanf("%lf", &total); getchar();
    printf("Interest rate %%: ");
    scanf("%lf", &rate); getchar();
    if (!confirm_action("Confirm loan?")) return;
    
    int n; 
    Account_s *arr = load_accounts(&n);
    if (!arr) { 
		printf("No accounts \n"); 
		return; 
	}
	
    for (int i = 0; i < n; ++i) {
        if (arr[i].account_number == num) {
            double debt = total * (1 + rate/100.0);
            arr[i].balance += total;
            arr[i].loan_balance += debt;
            printf("Balance:%.2f Debt:%.2f\n", arr[i].balance, arr[i].loan_balance);
            rewrite_accounts_in_db(arr, n);
            free(arr);
            return;
        }
    }
    free(arr);
    printf("Not found\n");
}

void repay_loan() {
    int num; double total;
    printf("\n-- Repay Loan --\nAccount #: ");
    scanf("%d", &num); getchar();
    printf("Amount: ");
    scanf("%lf", &total); getchar();
    if (!confirm_action("Confirm repayment?")) return;
    
    int n;
    Account_s *arr = load_accounts(&n);
    
    if (!arr) { 
		printf("No accounts were found\n"); 
		return; 
	
	}
    for (int i = 0; i < n; ++i) {
        if (arr[i].account_number == num) {
            if (arr[i].loan_balance <= 0) {
                printf("No debt to pay\n");
            } else if (arr[i].balance < total) {
                printf("Lack of funds\n");
            } else {
                arr[i].balance -= total;
                arr[i].loan_balance -= total;
                if (arr[i].loan_balance < 0) {
					arr[i].balance += abs(arr[i].loan_balance);
					arr[i].loan_balance = 0;
				}
					
                printf("Balance:%.2f Debt:%.2f\n",
                       arr[i].balance,
                       arr[i].loan_balance);
                rewrite_accounts_in_db(arr, n);
            }
            free(arr);
            return;
        }
    }
    free(arr);
    printf("Account not found\n");
}

void exit_program(void) {
    printf("EXITING BANKING SYSTEM!\n");
    exit(0);
}

