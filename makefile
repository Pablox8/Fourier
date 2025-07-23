INC_DIR = inc
SRC_DIR = src
OBJ_DIR = build

CC ?= gcc
CFLAGS = -Wall -I$(INC_DIR) -c
LDFLAGS = -lm -lraylib -lGL -lpthread -ldl -lrt -lX11

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

TARGET = epicycles

all: $(OBJ_DIR) $(TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)