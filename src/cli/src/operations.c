#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operations.h"
#include "shell.h"
#include "assert.h"

char * quit_operation(char * tokens[TOKEN_LIST_SIZE]){
  return NULL;
}

char * help_operation(char * tokens[TOKEN_LIST_SIZE]){
  help_text();
  return NULL;
}

char * hist_operation(char * tokens[TOKEN_LIST_SIZE]){
  print_history();
  return NULL;
}

char * action_operation(char * tokens[TOKEN_LIST_SIZE]){
  printf("%s\n",tokens[0] );
  return "is an action!";
}

char * state_operation(char * tokens[TOKEN_LIST_SIZE]){
  printf("%s\n",tokens[0] );
  return "is a state action!";
}

char * action_error_operation(char * tokens[TOKEN_LIST_SIZE]){
  return "You cannot perform this action";
}