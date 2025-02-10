CC = gcc
#CFLAGS =
LIB = -lncurses

install : mi.c
	$(CC) $(LIB) -o mi mi.c
