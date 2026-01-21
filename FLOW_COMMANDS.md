# Flow Language Command Reference

Complete guide to all built-in commands, functions, and operators in Flow.

---

## Variables

### `let`
**Description:** Creates or updates a variable. Variables can hold numbers or strings.

**Syntax:**
```flow
let variable_name = value
```

**Examples:**
```flow
let x = 10
let name = "Alice"
let pi = 3.14159
let result = 5 + 3
let greeting = "Hello, " + name
```

**Notes:**
- Variable names can contain letters, numbers, and underscores
- Must start with a letter
- Type is determined by what you assign (number or string)

---

## Input/Output

### `print`
**Description:** Outputs a value to the screen, followed by a newline.

**Syntax:**
```flow
print value
```

**Examples:**
```flow
print "Hello, world!"
print 42
print x
print 5 + 3
print "Your score: " + score
```

**Notes:**
- Always adds a newline after output
- Can print strings, numbers, or variables

### `input()`
**Description:** Gets text input from the user. Returns a string.

**Syntax:**
```flow
let variable = input("prompt")
```

**Examples:**
```flow
let name = input("What is your name? ")
let answer = input("")
```

**Notes:**
- Returns a STRING - use for text input
- Prompt is optional but recommended

### `input_num()`
**Description:** Gets numeric input from the user. Returns a number.

**Syntax:**
```flow
let variable = input_num("prompt")
```

**Examples:**
```flow
let age = input_num("How old are you? ")
let choice = input_num("")
```

**Notes:**
- Returns a NUMBER - use for numeric input
- If user enters non-numeric text, returns 0 and shows error
- Prompt is optional

---

## Conditionals

### `when ... <- otherwise -> ... <-`
**Description:** Executes code based on a condition (if-then-else).

**Syntax:**
```flow
when condition ->
    # code if true
<-

when condition ->
    # code if true
<- otherwise ->
    # code if false
<-
```

**Examples:**
```flow
when x > 10 ->
    print "x is large"
<-

when age >= 18 ->
    print "Adult"
<- otherwise ->
    print "Minor"
<-

# Nested conditionals
when score > 90 ->
    when score == 100 ->
        print "Perfect!"
    <- otherwise ->
        print "Excellent!"
    <-
<- otherwise ->
    print "Keep trying!"
<-
```

**Notes:**
- Condition evaluates to number: 0 = false, anything else = true
- `->` marks start of block, `<-` marks end
- `otherwise` is optional (like "else")

---

## Loops

### `repeat ... times -> ... <-`
**Description:** Executes a block a fixed number of times.

**Syntax:**
```flow
repeat count times ->
    # code to repeat
<-
```

**Examples:**
```flow
repeat 5 times ->
    print "Hello"
<-

let n = 10
repeat n times ->
    print "Counting"
<-
```

**Notes:**
- Count must be a number or expression that evaluates to a number
- Executes 0 times if count is 0 or negative

### `loop while ... -> ... <-`
**Description:** Executes a block while a condition is true.

**Syntax:**
```flow
loop while condition ->
    # code to repeat
<-
```

**Examples:**
```flow
let x = 0
loop while x < 10 ->
    print x
    let x = x + 1
<-

loop while health > 0 ->
    print "Still alive!"
    let health = health - 10
<-
```

**Notes:**
- Condition checked before each iteration
- If condition is false initially, block never executes
- Infinite loop if condition never becomes false

### `loop from ... to ... -> ... <-`
**Description:** Iterates from a start value to an end value (inclusive).

**Syntax:**
```flow
loop from variable = start to end ->
    # code to repeat
<-
```

**Examples:**
```flow
loop from i = 1 to 10 ->
    print i
<-

loop from count = 5 to 15 ->
    print count * 2
<-
```

**Notes:**
- Loop variable is automatically created/updated
- Always increments by 1
- End value is INCLUSIVE
- Only counts upward (start must be ≤ end)

---

## Control Flow

### `label`
**Description:** Marks a location in code that can be jumped to with `goto`.

**Syntax:**
```flow
label label_name
```

**Examples:**
```flow
label start
print "Top of loop"
let x = x + 1
when x < 10 ->
    goto start
<-

label menu
print "Main Menu"
# menu code here
goto menu
```

**Notes:**
- Label names follow same rules as variables
- Labels are discovered before program runs
- Use sparingly - loops are usually better

### `goto`
**Description:** Jumps to a labeled location in the code.

**Syntax:**
```flow
goto label_name
```

**Examples:**
```flow
when lives == 0 ->
    goto game_over
<-

label game_over
print "Game Over!"
```

**Notes:**
- Can only jump to top-level labels (not inside nested blocks)
- Use for menu systems or error handling
- Prefer loops for repetition

---

## Arithmetic Operators

### `+` Addition
**Examples:**
```flow
let sum = 5 + 3        # 8
let total = x + y + z
```

### `-` Subtraction / Negation
**Examples:**
```flow
let diff = 10 - 4      # 6
let negative = -42     # Negative number
let result = -(5 + 3)  # -8
```

### `*` Multiplication
**Examples:**
```flow
let product = 6 * 7    # 42
let area = width * height
```

### `/` Division
**Examples:**
```flow
let quotient = 20 / 4  # 5
let average = total / count
```

**Notes:**
- Returns decimal result
- Division by zero gives infinity/nan

### `%` Modulo (Remainder)
**Examples:**
```flow
let remainder = 10 % 3  # 1
let is_even = x % 2     # 0 if even, 1 if odd
```

**Notes:**
- Works with integers
- Useful for cycles, patterns, divisibility tests

---

## Comparison Operators

### `==` Equal to
```flow
when x == 10 ->
    print "x is 10"
<-

when name == "Alice" ->
    print "Hello Alice!"
<-
```

### `!=` Not equal to
```flow
when x != 0 ->
    print "x is not zero"
<-
```

### `<` Less than
```flow
when age < 18 ->
    print "Minor"
<-
```

### `>` Greater than
```flow
when score > 100 ->
    print "Bonus!"
<-
```

### `<=` Less than or equal to
```flow
when x <= 10 ->
    print "Ten or less"
<-
```

### `>=` Greater than or equal to
```flow
when age >= 21 ->
    print "Legal drinking age"
<-
```

**Notes:**
- Comparisons return 1 (true) or 0 (false)
- String comparisons only work with `==` and `!=`
- Number comparisons work with all operators

---

## String Operations

### `+` String Concatenation
**Description:** Joins strings together.

**Examples:**
```flow
let greeting = "Hello, " + name
let full_name = first + " " + last
let message = "You scored " + score + " points"
```

**Notes:**
- If one operand is a string, both are converted to strings
- Numbers are automatically converted when concatenating

---

## Mathematical Functions

### `sqrt(x)`
**Description:** Returns the square root of a number.

**Syntax:**
```flow
let result = sqrt(number)
```

**Examples:**
```flow
let side = sqrt(16)           # 4
let hypotenuse = sqrt(a*a + b*b)
let distance = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1))
```

**Notes:**
- Returns decimal result
- Negative numbers will give NaN (not a number)

### `pow(base, exponent)`
**Description:** Raises a number to a power.

**Syntax:**
```flow
let result = pow(base, exponent)
```

**Examples:**
```flow
let squared = pow(5, 2)       # 25
let cubed = pow(3, 3)         # 27
let area = pow(radius, 2) * 3.14159
```

**Notes:**
- Can use fractional exponents: `pow(27, 0.333)` ≈ 3
- Negative exponents work: `pow(2, -1)` = 0.5

### `abs(x)`
**Description:** Returns the absolute value (distance from zero).

**Syntax:**
```flow
let result = abs(number)
```

**Examples:**
```flow
let positive = abs(-42)       # 42
let distance = abs(x - y)
```

### `floor(x)`
**Description:** Rounds down to the nearest integer.

**Syntax:**
```flow
let result = floor(number)
```

**Examples:**
```flow
let down = floor(7.9)         # 7
let down = floor(7.1)         # 7
let down = floor(-3.5)        # -4
```

### `ceil(x)`
**Description:** Rounds up to the nearest integer.

**Syntax:**
```flow
let result = ceil(number)
```

**Examples:**
```flow
let up = ceil(7.1)            # 8
let up = ceil(7.9)            # 8
let up = ceil(-3.5)           # -3
```

### `random(min, max)`
**Description:** Returns a random integer between min and max (inclusive).

**Syntax:**
```flow
let result = random(min, max)
```

**Examples:**
```flow
let dice = random(1, 6)
let coin = random(0, 1)
let big_number = random(1, 100)
```

**Notes:**
- Both min and max are INCLUSIVE
- Returns an integer, not a decimal
- Random seed is set when program starts

---

## Comments

### `#` Comment
**Description:** Adds a comment that is ignored by the interpreter.

**Syntax:**
```flow
# This is a comment
let x = 10  # This is also a comment
```

**Notes:**
- Comments start with `#` and continue to end of line
- Use for documentation and explanations

---

## Block Markers

### `->` Begin Block
**Description:** Marks the start of a code block.

**Usage:**
- After `when` conditions
- After `otherwise`
- After loop declarations
- Must be matched with `<-`

### `<-` End Block
**Description:** Marks the end of a code block.

**Usage:**
- Closes blocks started with `->`
- Required to end all control structures

---

## Operator Precedence

From highest to lowest priority:

1. **Parentheses** `( )`
2. **Unary minus** `-x`
3. **Function calls** `sqrt()`, `pow()`, etc.
4. **Multiplication, Division, Modulo** `*`, `/`, `%`
5. **Addition, Subtraction** `+`, `-`
6. **Comparisons** `<`, `>`, `<=`, `>=`
7. **Equality** `==`, `!=`

**Examples:**
```flow
let x = 2 + 3 * 4        # 14 (not 20)
let y = (2 + 3) * 4      # 20
let z = -5 + 3           # -2
let a = 10 / 2 + 3       # 8 (not 2)
```

---

## Type System

Flow has two types:

### Numbers
- Stored as double-precision floating point
- Can be integers or decimals
- Default value: 0

### Strings
- Sequences of characters
- Enclosed in double quotes `"..."`
- Can be concatenated with `+`
- Default value: empty string `""`

### Type Rules
- Variables can change type by reassignment
- Math operations require numbers
- String concatenation converts numbers to strings
- Comparisons work within same type
- `==` and `!=` work across types (but usually return false)

---

## Program Structure

Every Flow program is a sequence of statements:

```flow
# Comments and variable initialization
let score = 0
let lives = 3

# Main program logic
label game_loop

print "What do you do?"
let choice = input_num("")

when choice == 1 ->
    print "You fight!"
    let score = score + 10
<- otherwise ->
    print "You run!"
<-

when lives > 0 ->
    goto game_loop
<-

print "Game Over!"
print "Final score: " + score
```

---

## Common Patterns

### Menu System
```flow
label menu
print "1 = Option A"
print "2 = Option B"
print "3 = Exit"

let choice = input_num("")

when choice == 1 ->
    # Option A code
    goto menu
<-
when choice == 2 ->
    # Option B code
    goto menu
<-
when choice == 3 ->
    print "Goodbye!"
<-
```

### Input Validation
```flow
label get_input
print "Enter a number 1-10:"
let num = input_num("")

when num < 1 ->
    print "Too small!"
    goto get_input
<-
when num > 10 ->
    print "Too large!"
    goto get_input
<-

print "Valid input!"
```

### Accumulator Pattern
```flow
let total = 0
loop from i = 1 to 10 ->
    let total = total + i
<-
print "Sum: " + total
```

### Counter Pattern
```flow
let count = 0
loop while count < 100 ->
    print count
    let count = count + 1
<-
```

---

## Limitations

### Current Limitations
- No arrays or lists
- No user-defined functions
- No `print` without newline (all output adds newline)
- No string manipulation functions (substring, length, etc.)
- No logical operators (AND, OR, NOT)
- No `break` or `continue` in loops
- No file I/O
- For loops only increment by 1
- For loops only count upward

### Workarounds
- Use multiple variables instead of arrays
- Use goto for complex control flow
- Build strings before printing entire lines
- Use modulo (%) for cyclic patterns
- Nest conditionals for AND/OR logic

---

## Best Practices

1. **Use descriptive variable names**
   ```flow
   let player_health = 100    # Good
   let h = 100                # Less clear
   ```

2. **Comment your code**
   ```flow
   # Calculate distance using Pythagorean theorem
   let distance = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1))
   ```

3. **Prefer loops over goto**
   ```flow
   # Good
   loop from i = 1 to 10 ->
       print i
   <-
   
   # Less ideal
   let i = 1
   label loop_start
   print i
   let i = i + 1
   when i <= 10 ->
       goto loop_start
   <-
   ```

4. **Use input_num() for numbers**
   ```flow
   let age = input_num("Age? ")    # Correct for numbers
   let name = input("Name? ")       # Correct for text
   ```

5. **Initialize variables before use**
   ```flow
   let score = 0
   let lives = 3
   # Now they're ready to use
   ```

---

## Quick Reference Table

| Command | Category | Purpose |
|---------|----------|---------|
| `let` | Variables | Create/update variable |
| `print` | I/O | Output to screen |
| `input()` | I/O | Get text input |
| `input_num()` | I/O | Get numeric input |
| `when...otherwise` | Control | Conditional execution |
| `repeat...times` | Loops | Fixed repetition |
| `loop while` | Loops | Conditional repetition |
| `loop from...to` | Loops | Counted iteration |
| `label` | Control | Mark jump location |
| `goto` | Control | Jump to label |
| `+` `-` `*` `/` `%` | Math | Arithmetic |
| `==` `!=` `<` `>` `<=` `>=` | Comparison | Comparisons |
| `sqrt()` | Math | Square root |
| `pow()` | Math | Exponentiation |
| `abs()` | Math | Absolute value |
| `floor()` | Math | Round down |
| `ceil()` | Math | Round up |
| `random()` | Math | Random integer |
| `#` | Misc | Comment |

---

This is the complete reference for Flow as it currently exists!
