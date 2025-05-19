#ifndef SEARCH_H
#define SEARCH_H

#include "account.h"
#include <stdbool.h>

void search_by_number_callback( Account_s *a, void *vctx);
void search_by_name_callback  ( Account_s *a, void *vctx);
void search_by_surname_callback( Account_s *a, void *vctx);
void search_by_address_callback( Account_s *a, void *vctx);
void search_by_pesel_callback( Account_s *a, void *vctx);

typedef struct {
    char key[ADDRES_MAX_LEN];
    bool found;
    Account_s acc;
} Account_search_context_s;

//void account_search_callback(const account_s *a, void *vctx);

#endif // SEARCH_H
