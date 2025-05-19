#include "user_input.h"
#include <stdio.h>
#include <string.h>

void read_input_line(char *buffer, size_t size) {
    if (fgets(buffer, (int)size, stdin) == NULL) {
		//EOF
        buffer[0] = '\0';
        return;
    }
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
}

bool confirm_action(const char *prompt) {
    int ch;
    int c;
    
    printf("%s (1=Yes,0=No): ", prompt);
    if (scanf("%d", &ch) != 1) {
		// clear buffer
        while ((c = getchar()) != '\n' && c != EOF) {}
        return false;
    }
	while ((c = getchar()) != '\n' && c != EOF) {}
    return ch == 1;
}

