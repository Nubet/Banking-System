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

void search_by_number_callback(const Account_s *a, void *vctx) {
    Account_search_context_s *ctx = vctx;
    int num = atoi(ctx->key);
    if (a->account_number == num) {
        display_account_info(a);
        ctx->found = true;
    }
}

void search_by_name_callback(const Account_s *a, void *vctx) {
    Account_search_context_s *ctx = vctx;
    if (strstr(a->name, ctx->key)) {
		display_account_info(a);
        ctx->found = true;
    }
}

void search_by_surname_callback(const Account_s *a, void *vctx) {
    Account_search_context_s *ctx = vctx;
    if (strstr(a->surname, ctx->key)) {
		display_account_info(a);
        ctx->found = true;
    }
}

void search_by_address_callback(const Account_s *a, void *vctx) {
    Account_search_context_s *ctx = vctx;
    if (strstr(a->address, ctx->key)) {
		        display_account_info(a);
        ctx->found = true;
    }
}
void search_by_pesel_callback(const Account_s *a, void *vctx) {
    Account_search_context_s *ctx = vctx;
    if (strcmp(a->pesel, ctx->key) == 0) {
		        display_account_info(a);
        ctx->found = true;
    }
}
