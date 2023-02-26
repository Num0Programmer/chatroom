DEBUG = -g
CFLAGS = -Wall -std=c99 -pedantic -c $(DEBUG)
LFLAGS = -Wall -std=c99 -pedantic $(DEBUG)
LIBS = -lm

server: server.o
	$(CC) $(LFLAGS) server.o -o c_server $(LIBS)

client: client.o
	$(CC) $(LFLAGS) client.o -o c_client $(LIBS)

server.o: server.c server.h
	$(CC) $(CFLAGS) server.c

client.o: client.c client.h
	$(CC) $(CFLAGS) client.c

clean:
	rm -rf *.o c_client c_server