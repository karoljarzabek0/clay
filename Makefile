CC=gcc
DEBUGFLAGS=-g -Wall -Wextra
IFLAGS=-I./include/

SRC=src
BUILD=build
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(BUILD)/%.o, $(SRCS))
EXE=clay

all: $(EXE)

$(EXE): $(OBJS) $(BUILD)
	$(CC) $(DEBUGFLAGS) $(OBJS) -o $@ $(IFLAGS)

$(BUILD)/%.o: $(SRC)/%.c $(BUILD)
	$(CC) $(DEBUGFLAGS) -c $< -o $@ $(IFLAGS)

$(BUILD):
	mkdir -p $@

clean:
	rm -rf $(BUILD)
