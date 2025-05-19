#ifndef USER_INPUT_H
#define USER_INPUT_H

#include <stdbool.h>
#include <stddef.h>

void read_input_line(char *buf, size_t size);
bool confirm_action(const char *prompt);

#endif // USER_INPUT_H
