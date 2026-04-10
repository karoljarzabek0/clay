CC=gcc
DEBUGFLAGS=-g -Wall -Wextra
IFLAGS=-I./include/ -lunistring -lm

SRC=src
BUILD=build
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(BUILD)/%.o, $(SRCS))
EXE=play

all: $(EXE)
	time ./play

$(EXE): $(OBJS) $(BUILD)
	$(CC) $(DEBUGFLAGS) $(OBJS) -o $@ $(IFLAGS)

$(BUILD)/%.o: $(SRC)/%.c $(BUILD)
	$(CC) $(DEBUGFLAGS) -c $< -o $@ $(IFLAGS)

$(BUILD):
	mkdir -p $@

trie: $(SRC)/trie.c
	$(CC) $(DEBUGFLAGS) $< -o $@ $(IFLAGS)
	./trie

clean:
	rm -rf $(BUILD)
