#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.pb-c.h"


/* Create a new Logvalueunion struct */
LogValueUnion *logvalueunion_new();

/* Initialize an integer Logvalueunion struct
 * Parameters: 
 * - logvalueunion: a new logvalueunion
 * - value: an integer value
 * Return: a pointer to that Logvalueunion
 */
LogValueUnion *logvalueunion_init_int(LogValueUnion *logvalueunion, int value);

/* Create a new Logvalue struct */
LogValue *logvalue_new();

/* Initialize an integer Logvalue struct
 * Parameters: 
 * - logvalue: a new logvalue
 * - value: an integer value
 * Return: a pointer to that Logvalue
 */
LogValue *logvalue_init_int(LogValue *logvalue, int value);

/* Create a new Log struct */
Log *log_new();

/* Initialize an integer Log struct
 * Parameters: 
 * - log: a new log
 * - level: either "game", "player", "room", "item", etc
 * - level_id : the id of that level string
 * - member : member of the level string
 * - old_value: old value of that member
 * - new_value: new value of that member
 * Return: a pointer to that Log
 */
Log *log_init_int(Log *log, char *level, char *level_id, char *member, int old_value, int new_value);

/* Create a new Log struct and initialize its value*/
Logs *logs_new();

/* Add a Log to the array of Log's
 * Parameters: 
 * - logs: an existing Logs, a.k.a an array of logs
 * - log: the Log to add in
 * Return: a pointer to that Logs
 */
Logs *logs_add(Logs *logs, Log *log);

/* Store a changed value information in our array of logs
 * Parameters: 
 * - logs: the array of logs
 * - level: either "game", "player", "room", "item", etc
 * - player_id : the id of that level string
 * - member : member of the level string
 * - old_value: old value of that member
 * - new_value: new value of that member
 * Return: 0 if SUCCESS, -1 OTHERWISE
 */
int checkpointing_log_int(Logs *logs, char *level, char *level_id, char *member, int old_value, int new_value);
