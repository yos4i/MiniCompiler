CC = gcc
CFLAGS = -Wall -g
LEX = flex
YACC = bison

# Target executable
TARGET = compiler

# Source files - ללא main.c
SOURCES = symbol_table.c semantic.c 3ac_generator.c ast.c lex.yy.c compiler.tab.c

# Object files
OBJECTS = $(SOURCES:.c=.o)

# Default target
all: $(TARGET)

# Build the compiler
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) -lfl

# Generate parser - יוצר compiler.tab.c ו-compiler.tab.h
compiler.tab.c compiler.tab.h: compiler.y
	$(YACC) -d compiler.y

# Generate lexer
lex.yy.c: compiler.l compiler.tab.h
	$(LEX) compiler.l

# Compile C files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Dependencies
symbol_table.o: symbol_table.c symbol_table.h
semantic.o: semantic.c semantic.h symbol_table.h
3ac_generator.o: 3ac_generator.c 3ac_generator.h
ast.o: ast.c ast.h
lex.yy.o: lex.yy.c compiler.tab.h
compiler.tab.o: compiler.tab.c symbol_table.h semantic.h 3ac_generator.h ast.h

# Clean build files
clean:
	rm -f $(OBJECTS) $(TARGET) lex.yy.c compiler.tab.c compiler.tab.h

# Test the compiler
test: $(TARGET)
	./$(TARGET) < test_input.txt

.PHONY: all clean test