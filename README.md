# MiniCompiler

A compiler implementation for a Python-like programming language that generates Three Address Code (3AC) intermediate representation.

## Overview

MiniCompiler is a complete compiler implementation that processes a Python-like language with C-style typing. It performs lexical analysis, syntax parsing, semantic analysis, and generates three-address code as intermediate representation.

## Features

- **Lexical Analysis**: Flex-based tokenizer supporting Python-like syntax
- **Syntax Analysis**: Bison-based parser with comprehensive grammar
- **Semantic Analysis**: Type checking and symbol table management
- **Code Generation**: Three Address Code (3AC) intermediate representation
- **Error Reporting**: Comprehensive syntax and semantic error detection

### Supported Language Features

- **Data Types**: `int`, `float`, `string`, `bool`
- **Literals**: Integer, hexadecimal, float, string, boolean (`True`/`False`)
- **Control Flow**: `if`/`elif`/`else`, `while` loops
- **Functions**: Function definitions with typed parameters and return types
- **Operations**: Arithmetic (`+`, `-`, `*`, `/`, `**`), relational (`==`, `!=`, `<`, `>`, `<=`, `>=`), logical (`and`, `or`, `not`)
- **Built-ins**: `print` statements, `pass` statements
- **Special**: `__main__` function as entry point

## Building

### Prerequisites

- GCC compiler
- Flex (lexical analyzer generator)
- Bison (parser generator)
- Make

### Compilation

```bash
make
```

This will generate the `compiler` executable.

### Clean Build

```bash
make clean
```

## Usage

```bash
./compiler <input_file>
```

### Example

```bash
./compiler test_input.txt
```

## Language Syntax Example

```python
def foo(float x) -> int: {
    int a, b;
    a = 23;
    if a == 23:
        b = 10;
    else:
        b = 19;
    return b + a;
}

def __main__(): {
    int a, b;
    a = 0;
    while a < 10: {
        b = foo(3.14);
        a = a + b;
    }
}
```

## Architecture

### Components

1. **Lexer** (`compiler.l`): Tokenizes input using Flex
2. **Parser** (`compiler.y`): Parses tokens into AST using Bison
3. **AST** (`ast.c`, `ast.h`): Abstract Syntax Tree representation
4. **Symbol Table** (`symbol_table.c`, `symbol_table.h`): Variable and function management
5. **Semantic Analyzer** (`semantic.c`, `semantic.h`): Type checking and validation
6. **3AC Generator** (`3ac_generator.c`, `3ac_generator.h`): Intermediate code generation

### Build Process

1. Bison generates parser from `compiler.y`
2. Flex generates lexer from `compiler.l`
3. All components are compiled and linked together

## Output

On successful compilation, the program outputs:
- "Compilation successful!"
- Generated Three Address Code (3AC)

On failure, it reports syntax or semantic errors with line numbers.

## Testing

A test file (`test_input.txt`) is provided. Run:

```bash
make test
```

## Error Handling

The compiler provides detailed error reporting for:
- **Lexical errors**: Invalid characters or tokens
- **Syntax errors**: Grammar violations
- **Semantic errors**: Type mismatches, undeclared variables, etc.

## License

This project is for educational purposes.