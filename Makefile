LIB=inc/
SRC=src
OBJ_DIR=OBJECTS
BIN_DIR=bin
TEST_DIR=test
TARGET=$(BIN_DIR)/libssixa.so
CFLAGS:= -Wall 
LDFLAG:= -L . -lfdproto -lfdcore 

SOURCE=$(shell find $(SRC) -name '*.c')
OBJS:=$(patsubst $(SRC)/%.c,$(OBJ_DIR)/%.o,$(SOURCE))

.PHONY: all test clean

all: OBJDIR BINDIR $(TARGET)

test: MAKETEST

testclean: MAKETESTCLEAN

$(TARGET): $(OBJS)
	gcc $(OBJS) $(LDFLAG) -g -shared -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC)/%.c
	gcc -c $(CFLAGS) -g -I $(LIB) $< -o $@

OBJDIR:
	mkdir -p $(OBJ_DIR)/

BINDIR:
	mkdir -p $(BIN_DIR)/

MAKETEST:
	cd $(TEST_DIR); make

MAKETESTCLEAN:
	cd $(TEST_DIR); make clean

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) 

