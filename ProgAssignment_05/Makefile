# variables
DEBUG = -g
CFLAGS = -Wall -std=c99 -pedantic -c $(DEBUG)
LFLAGS = -Wall -std=c99 -pedantic $(DEBUG)
LDFLAGS = -lpthread

# remove all
RM_ALL := rm -rf ./*.o ./server/*.o ./client/*.o chat_server chat_client

server: ./server/client_handler.o ./server/main.o
	$(CC) $(LFLAGS) ./server/client_handler.o ./server/main.o -o chat_server $(LDFLAGS)

client_handler.o: ./server/client_handler.c ./server/client_handler.h
	$(CC) $(CFLAGS) ./server/client_handler.c

main.o: ./server/main.c ./server/main.h
	$(CC) $(CFLAGS) ./server/main.c

client: ./client/receiver_handler.o ./client/sender_handler.o ./client/main.o
	$(CC) $(LFLAGS) ./client/receiver_handler.o ./client/sender_handler.o ./client/main.o -o chat_client $(LDFLAGS)

receiver_handler.o: ./client/receiver_handler.c ./client/receiver_handler.h
	$(CC) $(CFLAGS) ./client/receiver_handler.c

sender_handler.o: ./client/sender_handler.c ./client/sender_handler.h
	$(CC) $(CFLAGS) ./client/sender_handler.c

main.o:	./client/main.c ./client/main.h
	$(CC) $(CFLAGS) ./client/main.c

clean:
	$(RM_ALL)
