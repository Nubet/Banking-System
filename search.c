#include "search.h"
#include <stdlib.h>
#include <string.h>

/*
void account_search_callback(const account_s *a, void* vctx)
{
	account_search_context_s* ctx = vctx;
	if (atoi(ctx->key) == a->account_number || strstr(a->name, ctx->key) ||
		strstr(a->surname, ctx->key) || strstr(a->address, ctx->key) ||
		strstr(a->pesel, ctx->key)) {
		display_account_info(a, NULL);
		ctx->found = true;
	}
}
*/
//move display account info outside the callbacks

void search_by_number_callback(Account_s *a, void *vctx) {
    Account_search_context_s *ctx = vctx;
    int num = atoi(ctx->key);
    if (a->account_number == num) {
        ctx->found = true;
        ctx->acc = *a;
    }
}

void search_by_name_callback(Account_s *a, void *vctx) {
    Account_search_context_s *ctx = vctx;
    if (strstr(a->name, ctx->key)) {
        ctx->found = true;
        ctx->acc = *a;
    }
}

void search_by_surname_callback(Account_s *a, void *vctx) {
    Account_search_context_s *ctx = vctx;
    if (strstr(a->surname, ctx->key)) {
        ctx->found = true;
        ctx->acc = *a;
    }
}

void search_by_address_callback(Account_s *a, void *vctx) {
    Account_search_context_s *ctx = vctx;
    if (strstr(a->address, ctx->key)) {
        ctx->found = true;
        ctx->acc = *a;
    }
}
void search_by_pesel_callback(Account_s *a, void *vctx) {
    Account_search_context_s *ctx = vctx;
    if (strcmp(a->pesel, ctx->key) == 0) {
        ctx->found = true;
        ctx->acc = *a;
    }
}
