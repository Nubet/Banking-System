#include "search.h"
#include "account.h"
#include <stdlib.h>
#include <string.h>

void search_by_number_callback(Account_s *a, Account_search_context_s *ctx) {
    int num = atoi(ctx->key);
    if (a->account_number == num) {
        ctx->found = true;
    }
}

void search_by_name_callback(Account_s *a, Account_search_context_s *ctx) {
    if (strstr(a->name, ctx->key)) {
        ctx->found = true;
    }
}

void search_by_surname_callback(Account_s *a, Account_search_context_s *ctx) {
    if (strstr(a->surname, ctx->key)) {
        ctx->found = true;
    }
}

void search_by_address_callback(Account_s *a, Account_search_context_s *ctx) {
    if (strstr(a->address, ctx->key)) {
        ctx->found = true;
    }
}

void search_by_pesel_callback(Account_s *a, Account_search_context_s *ctx) {
    if (strcmp(a->pesel, ctx->key) == 0) {
        ctx->found = true;
    }
}
