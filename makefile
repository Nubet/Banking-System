CC      = gcc
CFLAGS  = -g -Wall -pedantic


SRCS    = main.c account.c user_input.c search.c operations.c
OBJS    = $(SRCS:.c=.o)

TARGET  = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(TARGET) $(OBJS)

