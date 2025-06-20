# Banking System - Console Application

Portable C11 program for managing bank accounts via a file-based database, demonstrating modular design, safe I/O, and transaction consistency.

## Features

* **Account CRUD**: auto‑generated IDs, store name, address, PESEL, balances.
* **Persistent Storage**: direct read/write to `db.dat` after each change; no in‑memory cache.
* **Search**: query by account number, name, surname, address, or PESEL.
* **Transactions**: deposits, withdrawals, transfers, loan issuance (with interest), loan repayment.
* **Validation & Safety**: bounds‑checked input, balance checks, confirmation prompts.

## Repository Layout

```plaintext
├── main.c           # program entry and starting point
├── account.c/.h     # account struct and file I/O implementations
├── operations.c/.h  # all operations logic
├── search.c/.h      # search filters and callbacks
├── user_input.c/.h  # safe input and confirmation from user
└── Makefile         # linking and building 
```

## Build & Run

```bash
git clone https://github.com/Nubet/banking-system.git
cd banking-system
make          # builds main
./main        # starts programm
```

## Usage

1. **New account**: enter personal data -> confirm.
2. **List**: view all accounts.
3. **Search**: select field -> enter query.
4. **Deposit/Withdraw**: provide account ID and amount.
5. **Transfer**: source ID -> target ID -> amount.
6. **Loan**: amount + interest rate -> funds to balance.
7. **Repay**: payment amount -> deduct from loan balance.

---

## Design & Implementation Details

* **`Account_s` Struct**: defined in `account.h` with fields:

  * `int account_number`
  * `char name[NAME_MAX_LEN]`, `surname[SURNAME_MAX_LEN]`, `address[ADDRES_MAX_LEN]`, `pesel[PESEL_MAX_LEN+1]`
  * `double balance`, `loan_balance`
* **Binary File Database (`db.dat`)**:

  * Each `Account_s` record written/read sequentially.
  * `generate_account_number()` scans file to find the highest existing ID.
  * `append_account_to_db()` uses `fwrite`, `rewrite_accounts_in_db()` rewrites entire file.
* **Search System**:

  * Uses `for_each_account()` with context pointer `Account_search_context_s`.
  * Field-specific callbacks (`search_by_number_callback`, etc.) compare `ctx.key` and set `ctx.found`.
* **Menu & Operations Dispatch**:

  * `Operations_s` array in `operations.c` pairs description strings with handlers via `op_function`.
  * `run_menu_loop()` presents options and invokes the correct callback.
* **Transactions & Loans**:

  * `deposit_money()`, `withdraw_money()`, `transfer_money()`, `take_loan()`, `repay_loan()` implement read-modify-write:

    1. Read all accounts into memory via `load_accounts()`
    2. Modify target `Account_s` entries
    3. Persist changes with `rewrite_accounts_in_db()`
  * Interest calculation: `loan_balance += amount * rate / 100.0`.
* **Input Handling**:

  * `read_input_line(char *buf, size_t size)`: safe `fgets` wrapper trimming newline.
  * `confirm_action(const char *prompt)`: prompts user (`y/n`), loops until valid response.
* **Error & Boundary Checks**:

  * All file operations (`fopen`, `fread`, `fwrite`, `fseek`) checked for errors.
  * String inputs limited by `NAME_MAX_LEN`, etc., to prevent overflow.
  * Balance operations ensure non-negative results before applying.
* **Build**:

  * `Makefile` compiles with `gcc -std=c11 -Wall -Werror -o main *.c`.
