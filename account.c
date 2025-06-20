#include "account.h"
#include "search.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int generate_account_number() {
    int next = 1;
    FILE* file = fopen(DB_FILE_PATH, "rb");
    if (file) {
        Account_s a = { 0 };
        while (fread(&a, sizeof(a), 1, file) == 1) {
            if (a.account_number >= next)
                next = a.account_number + 1;
        }
        fclose(file);
    }
    return next;	
}

void append_account_to_db(Account_s *acc) {
    FILE* fp = fopen(DB_FILE_PATH, "ab");
    if (!fp) {
        fprintf(stderr,"error while appending new account to data base \n");
        return;
    }
    fwrite(acc, sizeof(*acc), 1, fp);
    fclose(fp);
}

Account_s* load_accounts(int *count) {
    FILE* fp = fopen(DB_FILE_PATH, "rb");
    if (!fp) {
        *count = 0;
        return NULL;
    }
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp); // size in bytes
    rewind(fp); // pointer return to the start of the file
    int n = (int)(size / sizeof(Account_s));
    Account_s* arr = malloc(sizeof(Account_s) * n);
    if (!arr) {
		fprintf(stderr,"Memory allocation error");
        fclose(fp);
        *count = 0;
        return NULL;
    }
    fread(arr, sizeof(Account_s), n, fp);
    fclose(fp);
    *count = n;
    return arr;
}

void rewrite_accounts_in_db(Account_s *accounts, int count) {
    FILE* fp = fopen(DB_FILE_PATH, "wb");
    if (!fp) {
        perror("Rewrite error");
        return;
    }
    fwrite(accounts, sizeof(Account_s), count, fp);
    fclose(fp);
}

void for_each_account(void (*cb)(Account_s *a, Account_search_context_s *ctx),
                      Account_search_context_s *ctx){
    FILE* fp = fopen(DB_FILE_PATH, "rb");
    if (!fp) return;
    Account_s a;
    bool found_any = false;
    while (fread(&a, sizeof(a), 1, fp) == 1) {
        ctx->found = false;
        cb(&a, ctx);

        if (ctx->found) {
            display_account_info(&a);
            found_any = true;
        }
    }
    if (!found_any) {
        printf("No matching accounts found\n");
    }
    fclose(fp);
}
void for_each_account_noctx(void (*cb)(Account_s *a)) {
    FILE *fp = fopen(DB_FILE_PATH, "rb");
    if (!fp) return;
    Account_s a = { 0 };
    while (fread(&a, sizeof(a), 1, fp) == 1) {
        cb(&a);
    }
    fclose(fp);
}


void display_account_info(Account_s *a) {
    printf(
        "#ID:%d | %s %s | %s | PESEL:%s | Balance:%.2f | Loan to pay:%.2f\n",
        a->account_number, a->name, a->surname,
        a->address, a->pesel, a->balance, a->loan_balance
    );
}

