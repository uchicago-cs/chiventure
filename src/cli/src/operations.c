#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operations.h"
#include "shell.h"
#include "assert.h"

char *quit_operation(char *tokens[TOKEN_LIST_SIZE]){
  return NULL;
}

char *help_operation(char *tokens[TOKEN_LIST_SIZE]){
  help_text();
  return NULL;
}

char *hist_operation(char *tokens[TOKEN_LIST_SIZE]){
  print_history();
  return NULL;
}

char *type1_action_operation(char *tokens[TOKEN_LIST_SIZE]){
  printf("%s\n",tokens[0] );
  return "is an action!";
}

char *type2_action_operation(char *tokens[TOKEN_LIST_SIZE]){
  printf("%s\n",tokens[0] );
  return "is a direction action!";
}

char *type3_action_operation(char *tokens[TOKEN_LIST_SIZE]){
  printf("%s\n",tokens[0] );
  return "is an action!";
}
char *type4_action_operation(char *tokens[TOKEN_LIST_SIZE]){
  printf("%s\n",tokens[0] );
  return "is an action!";
}

char *action_error_operation(char *tokens[TOKEN_LIST_SIZE]){
  return "You cannot perform this action";
}


char *object_error_operation(char *tokens[TOKEN_LIST_SIZE]){
  return "You cannot perform the action on this object";
}

char *prep_error_operation(char *tokens[TOKEN_LIST_SIZE]){
  return "You used the wrong preposition";
}

char *ind_object_error_operation(char *tokens[TOKEN_LIST_SIZE]){
  return "You cant perform this action on specefied object";
}

void create_type1_action(char *tokens[TOKEN_LIST_SIZE]){}

void create_type2_action(char *tokens[TOKEN_LIST_SIZE]){}

void create_type3_action(char *tokens[TOKEN_LIST_SIZE]){}

void create_type4_action(char *tokens[TOKEN_LIST_SIZE]){}
