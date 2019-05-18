#include <stdlib.h>
#include <string.h>
#include "lookup.h"
#include "uthash.h"
#include "operations.h"
lookup_t * table = NULL;

void add_entry(char * command_name, operation * associated_operation){
  lookup_t * t = malloc(sizeof(lookup_t));
  t->name = command_name;
  t->operation_type = associated_operation;
  HASH_ADD_KEYPTR( hh, table, t->name, strlen(t->name), t);

}

//void add_action_entries(action_t * action_value, lookup_t * table){
  // To be filled with a while loop that adds each synonym,
  // and maps the enum in the action value to the proper operation.
//}

lookup_t * find_entry(char * command_name){
  lookup_t * t;
  HASH_FIND_STR(table, command_name, t);
  return t;
}

operation * find_operation(char * command_name){
  return find_entry(command_name)->operation_type;
}

// operation * find_action(char * command_name, lookup_t * table){
//   return find_entry(command_name)->action_type;
// }


void delete_entry(char * command_name){
  lookup_t * t = find_entry(command_name);
  HASH_DEL(table, t);
  free(t);
}
void delete_entries(){
  lookup_t * tmp;
  lookup_t * current_user;
  HASH_ITER(hh, table, current_user, tmp) {
      HASH_DEL(table, current_user);
      free(current_user);
    }
}

void initialize_lookup(){
  add_entry("QUIT", quit_operation);
  add_entry("HELP", help_operation);
  add_entry("HIST", hist_operation);
}
// int main(int argc, char const *argv[]) {
//   /* code */
//   return 0;
// }
