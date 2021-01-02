CC = gcc
CC_FLAGS = -Wall -Wextra -std=c99 -ggdb

BUILD_DIR = build
SOURCE_DIR = src

_OBJFILES = fileReader.o simulator.o functions.o main.o
OBJFILES = $(patsubst %,$(BUILD_DIR)/%,$(_OBJFILES))

all: gsim

gsim: $(OBJFILES)
	$(CC) $(CC_FLAGS) -o $@ $^

$(BUILD_DIR)/main.o: $(SOURCE_DIR)/main.c
	$(CC) $(CC_FLAGS) -c -o $@ $<

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c $(SOURCE_DIR)/%.h
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CC_FLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)