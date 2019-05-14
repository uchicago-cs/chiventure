Version 1.0

Besides this README, this directory includes the following files:

- a Makefile for the project

- shell.h and shell.c, shell actions (to be merged with operations.h/.c)

- cmd.c and cmd.h that introduces a data structure for commands, and navigates between them.

- parser.c and parser.h that parses a input string

- validate.c and validate.h that check a function's validity

- operations.c and operations.h that will link the operations to actual actions.

- example/testshell.c runs an example shell that is used for demonstration and testing\
  To run the example shell, do
  ```bash
  make test
  ./example/testshell
  ```
