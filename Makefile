BIN:=test
SRC:=$(wildcard *.c)
OBJ:=$(SRC:.c=.o)
CC:=gcc
CPPFLAGS:=-I$(CURDIR)
LDLIBS:=\
	-lserialport

.PHONY: all clean $(BIN)

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)
clean:
	$(RM) $(OBJ) $(BIN) example.txt