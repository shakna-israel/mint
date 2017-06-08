# Specification

This is the formal specification for the estoric programming language known as 'mint', version 0.1.0

---

## The Stack

The primary data structure that is to be used by mint's operators, is known as the stack.

The Stack *must* be a mutable array-like structure.

Each cell in the Stack's structure *must* be capable of containing 32bit unsigned integers, as a minimum. Higher-bit types are acceptable.

The Stack *must* have each cell initialised to 0 before being accessed.

The Stack *must* have a minimum length of 1.

The Stack does *not* have a maximum length, though implementations may impose one for practicality's sake.

Exactly 1 cell of the Stack must be selected at all times, so that operators may use it.

---

## The Jumplist

The exact data structure of the Jumplist is left to implementations.

However, the Jumplist must be capable of inserting and removing a sequence of data points.

These data points will be utilised to change execution flow within a mint program.

---

## The Program

A mint program is a mutable series of operators.

As this is the Abstract Syntax Tree of a program, and optimisations may be applied to it by implementations, the exact data structure is left up to implementations.

The Program should be readable by an interpreter in two ways:

* Via arguments
* Via piping

Program data read by pipe should be appended to the program, *after* program data given by arguments.

For example, these two lines are equivalent:

```
echo "---%" | mint +++
mint +++---%
```

Program data may contain symbols that are not operators, those symbols should be skipped. See [Evaluation]().

---

## Standard Library

These are the operators that must be included by an implementation.

Implementations may expand upon them, so long as infinite recursion remains impossible.

For convenience sake, each operator is named, and presented alongside its symbol.

### Increment | +

The + operator increments the value of the current cell in the Stack by 1.

### Decrement | -

The - operator decrements the value of the current cell in the Stack by 1.

### SelectN | >

The > operator changes the selection of the current cell in the Stack, selecting 1 to the right.

If the selected cell was the maximum cell to be selected in the implementation, the cell position should not move.

### SelectP | <

The < operator changes the selection of the current cell in the Stack, selecting 1 to the left.

If the selected cell was the minimum cell to be selected in the implementation, the cell position should not move.

### Clear | ?

The ? operator sets the value of the currently selected cell to 0.

### Store | .

The . operator does two things:

* Adds the current program position to the end of the Jumplist.
* Replaces the current operator with a no-op operator, or something that does nothing.

### JMP | :

The : operator does two things:

* Moves current program execution to the last data point in the Jumplist.
* Removes the last data point from the end of the Jumplist.

### Display | #

Takes the current value of the currently selected cell, and buffers it to stdout as a byte. (i.e. It casts an int to a char, then buffers it to stdout).

### Literal | %

Without attempting to display as a character, buffers the current value of the currently selected cell to stdout.

### Invert | (

The ( operator reverses the directionality of the Stack.

### Reverse | )

The ) operator reverses directionality of the Program.

### Ifskip | !

If the current value of the currently selected cell is 0, skip execution of the next operator in the Program

---

# Evaluation

Each operator of the Program is executed left to right, modifying the Stack or the Program.

Unknown operators are ignored.

e.g. The following are nearly equivalent. (The Program position will move in the latter.)

```
> mint
> mint hhhhhhhhhh
```

If an operator would exceed a minimal or maximal value, it does nothing.

e.g.

```
mint ----%
> 0
```

After the Program is executed to such a stage that the Program's position has reached its maximal value, a newline is buffered to stdout, and stdout is flushed.
