#ifndef SEARCH_H
#define SEARCH_H

#include "account.h"
#include <stdbool.h>

#define ADDRES_MAX_LEN 100

typedef struct Account_search_context_s {
    char key[ADDRES_MAX_LEN];
    bool found;
} Account_search_context_s;

void search_by_number_callback(Account_s *a, Account_search_context_s *ctx);
void search_by_name_callback  (Account_s *a, Account_search_context_s *ctx);
void search_by_surname_callback(Account_s *a, Account_search_context_s *ctx);
void search_by_address_callback(Account_s *a, Account_search_context_s *ctx);
void search_by_pesel_callback  (Account_s *a, Account_search_context_s *ctx);

#endif // SEARCH_H
