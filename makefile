#makefile for FCBank.

CC = gcc
CFLAGS = -Wall -Werror -ansi -o

bank.out: bank.c linked_list_implementation.c
	$(CC) $(CFLAGS) bank.out bank.c linked_list_implementation.c -lm
