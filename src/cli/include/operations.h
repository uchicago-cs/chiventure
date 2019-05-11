#ifndef _OPERATIONS_H
#define _OPERATIONS_H
#include "cmd.h"
// Operation data type
//typedef char * operation(char * tokens[TOKEN_LIST_SIZE]);
// The type is listed here for convenience, but for compiler
// niceness, it is in cmd.h.

// We list all demanded operations over here.
// All meta operations must be defined here.
// Later on, we can support other operations
// within similar types, as in a general action operation
// that feeds the right type of command to action management
char *quit_operation(char *tokens[TOKEN_LIST_SIZE]);
// implements the quit command. Due to how quit works,
// this command literally does nothing right now.
// This is completely intended.
char *help_operation(char *tokens[TOKEN_LIST_SIZE]);
// implements the help command
char *hist_operation(char *tokens[TOKEN_LIST_SIZE]);
// implements the history command
char *action_operation(char *tokens[TOKEN_LIST_SIZE]);
// implements a general form for actions, like TAKE
char *state_operation(char *tokens[TOKEN_LIST_SIZE]);
// implements a general form for state actions, like MOVE and LOOK

char *action_error_operation(char *tokens[TOKEN_LIST_SIZE]);
// prints the operation and tells the user that it was not recognised
// Put more operations here!

char *object_error_operation(char *tokens[TOKEN_LIST_SIZE]);

char *prep_error_operation(char *tokens[TOKEN_LIST_SIZE]);

char *ind_object_error_operation(char *tokens[TOKEN_LIST_SIZE]);

#endif /* _OPERATIONS_H */