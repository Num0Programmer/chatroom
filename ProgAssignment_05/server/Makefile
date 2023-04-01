DEBUG = -g
CFLAGS = -Wall -std=c99 -pedantic -c $(DEBUG)
LFLAGS = -Wall -std=c99 -pedantic $(DEBUG)
LIBS = -lpthread

all: client_handler.o main.o
	$(CC) $(LFLAGS) client_handler.o main.o -o chat_server $(LIBS)

client_handler.o: client_handler.c client_handler.h
	$(CC) $(CFLAGS) client_handler.c

main.o: main.c main.h
	$(CC) $(CFLAGS) main.c

clean:
	rm -rf *.o chat_server
