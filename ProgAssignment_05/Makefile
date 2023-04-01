# executables
SERVER_EXEC := chat_server
CLIENT_EXEC := chat_client

# source directories
SERVER_DIR := ./server
CLIENT_DIR := ./client

# source files
SERVER_SRC := $(shell find $(SERVER_DIR) -name "*.c")
CLIENT_SRC := $(shell find $(CLIENT_DIR) -name "*.c")

# variables
DEBUG := -g
CFLAGS := -Wall -std=c99 -pedantic -c $(DEBUG)
LFLAGS := -Wall -std=c99 -pedantic $(DEBUG)
LDFLAGS := -pthread -lpthread

# remove all
RM_ALL := rm -rf ./*.o $(SERVER_DIR)/*.o $(CLIENT_DIR)/*.o $(SERVER_EXEC) $(CLIENT_EXEC)

all: $(SERVER_DIR)/%.o $(CLIENT_DIR)/%.o
	$(CC) $(LFLAGS) $(SERVER_SRC)/%.o -o $(SERVER_EXEC) $(LDFLAGS)
	$(CC) $(LFLAGS) $(CLIENT_SRC)/%.o -o $(CLIENT_EXEC) $(LDFLAGS)

$(SERVER_SRC)/%.o: %.c %.h
	$(CC) $(CFLAGS) $(SERVER_SRC)/$(SRCS)

$(CLIENT_SRC)/%.o: %.c %.h
	$(CC) $(CFLAGS) $(CLIENT_SRC)/$(SRCS)

clean:
	$(RM_ALL)
