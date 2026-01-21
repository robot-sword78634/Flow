FLOW — Friendly Language Of Wonder

Flow is a small, friendly, educational programming language inspired by
classic 1970s and early 1980s computing. It is designed to encourage
curiosity, experimentation, and learning through play.

Flow focuses on clarity and approachability rather than performance or
complexity. Programs are meant to be read, typed, modified, and
explored.

  ----------
  FEATURES
  ----------

-   Simple, readable syntax inspired by classic BASIC-style languages
-   Support for numbers and strings
-   Interactive input from the user
-   Built-in math functions
-   Random number generation
-   Conditional logic
-   Loops for repetition
-   Designed for games, simulations, and demos

  -------------
  HELLO WORLD
  -------------

print “Hello, world!”

  -----------
  VARIABLES
  -----------

Use let to create or update variables.

let x = 10 let name = “Flow”

  -------
  INPUT
  -------

Flow supports numeric and string input.

let age = input_num(“Enter your age:”) let name = input(“What is your
name?”)

  --------
  OUTPUT
  --------

Use print to display values.

print “Hello” print x print “Your name is” + name

  --------------
  CONDITIONALS
  --------------

Flow uses when blocks for conditional logic.

when x == 10 -> print “x is ten” <- otherwise -> print “x is not ten” <-

  -------
  LOOPS
  -------

Repeat a block a fixed number of times:

repeat 5 times -> print “Hello” <-

Loop while a condition is true:

loop while x < 10 -> let x = x + 1 <-

  ----------------
  MATH FUNCTIONS
  ----------------

Flow includes common math functions:

pow(a, b) # exponentiation sqrt(x) # square root abs(x) # absolute value
random(a, b) # random integer between a and b

  ---------------------------
  EXAMPLE: GUESS THE NUMBER
  ---------------------------

print “Guess a number between 1 and 10”

let secret = random(1, 10) let guess = 0

loop while guess != secret -> let guess = input_num(“Your guess:”)

    when guess < secret ->
        print "Too low"
    <-
    when guess > secret ->
        print "Too high"
    <-

<-

print “Correct!”

  ------------
  PHILOSOPHY
  ------------

Flow is intentionally limited.

The goal is not to be fast or feature-complete, but to be: - Friendly -
Understandable - Approachable - Fun

Flow encourages learning by experimentation and discovery.

  -----------------
  GETTING STARTED
  -----------------

1.  Install or build the Flow interpreter
2.  Write a .flow file
3.  Run it using the Flow interpreter
4.  Modify the program and experiment

  -------------
  INSPIRATION
  -------------

Flow is inspired by: - Early BASIC interpreters - Educational
programming languages - Classic computer games - Interactive terminal
software

  ---------
  LICENSE
  ---------

This project is provided for educational and experimental purposes. See
the LICENSE file for details.

  -----------------
  WELCOME TO FLOW
  -----------------

Have fun exploring, learning, and creating.

FLOW — Friendly Language Of Wonder
