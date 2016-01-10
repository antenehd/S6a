SRC=src
OBJ_DIR=OBJECTS
BIN_DIR=bin
TARGET=$(BIN_DIR)/testapp
CFLAGS:= -Wall -Winline $(shell  mysql_config --cflags) 
HEADER:= -I ../inc/ -I ./inc/
LDFLAG:= -L ../bin -lssixa -lfdproto -lfdcore $(shell mysql_config --libs)

SOURCE=$(shell find $(SRC) -name '*.c')
OBJS:=$(patsubst $(SRC)/%.c,$(OBJ_DIR)/%.o,$(SOURCE))

.PHONY: all clean

all: OBJDIR BINDIR $(TARGET)

$(TARGET): $(OBJS)
	gcc $(OBJS) $(LDFLAG) -g -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC)/%.c
	gcc -c $(CFLAGS) -g  $(HEADER) $< -o $@

OBJDIR:
	mkdir -p $(OBJ_DIR)/

BINDIR:
	mkdir -p $(BIN_DIR)/

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) 
