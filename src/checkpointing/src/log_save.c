#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log_save.h"


/* See log_save.h */
LogValueUnion *logvalueunion_new()
{
    LogValueUnion *logvalueunion = malloc(sizeof(LogValueUnion));
    log_value_union__init(logvalueunion);
    return logvalueunion;
}

/* See log_save.h */
LogValueUnion *logvalueunion_init_int(LogValueUnion *logvalueunion, int value)
{
    if (logvalueunion == NULL)
        fprintf(stderr, "Need to pass in a new Logvalueunion \n");
    return NULL;
    
  logvalueunion->int_val = value;
  return logvalueunion;
}

/* See log_save.h */
LogValue *logvalue_new()
{
    LogValue *logvalue = malloc(sizeof(LogValue));
    log_value__init(logvalue);
    return logvalue;
}

/* See log_save.h */
LogValue *logvalue_init_int(LogValue *logvalue, int value)
{
    if (logvalue == NULL)
    {
        fprintf(stderr, "Need to pass in a new Logvalue \n");
        return NULL;
    }
    logvalue->tag = "int";
    LogValueUnion *logvalueunion = logvalueunion_new();
    logvalueunion = logvalueunion_init_int(logvalueunion, value);
    logvalue->value = logvalueunion;
    return logvalue;
}

/* See log_save.h */
Log *log_new()
{
    Log *log = malloc(sizeof(Log));
    log__init(log);
    return log;
}

/* See log_save.h */
Log *log_init_int(Log *log, char *level, char *level_id, char *member, int old_value, int new_value)
{
    if (log == NULL)
    {
        fprintf(stderr, "Need to pass in a new Log \n");
        return NULL;
    }
    if (level == NULL)
    {
        fprintf(stderr, "Need to pass in a level \n");
        return NULL;
    }
    if (level_id == NULL)
    {
        fprintf(stderr, "Need to pass in a level id \n");
        return NULL;
    }
    if (member == NULL)
    {
        fprintf(stderr, "Need to pass in a struct member \n");
        return NULL;
    }
    log->level = level;
    log->level_id = level_id;
    log->member = member;
    LogValue *old = logvalue_new();
    LogValue *new = logvalue_new();
    old = logvalue_init_int(old, old_value);
    new = logvalue_init_int(new, new_value);
    log->old_value = old;
    log->new_value = new;
    return log;
}

/* See log_save.h */
Logs *logs_new()
{
    Logs *logs = malloc(sizeof(Logs));
    logs__init(logs);
    logs->logs_len = 0;
    logs->n_logs = 0;
    logs->logs = malloc(sizeof(Log*) * 100); // 100 logs before dumping
    return logs;
}

/* See log_save.h */
Logs *logs_add(Logs *l, Log *log)
{
    if (l == NULL)
    {
        fprintf(stderr, "Need to pass in an initialized Logs \n");
        return NULL;
    }
    if (log == NULL)
    {
        fprintf(stderr, "Need to pass in an initialized Log \n");
        return NULL;
    }
    if (l->logs_len == 100)
    {
        fprintf(stderr, "Logs excedding 100 Log, dump game state\n");
        return NULL;
    }
    l->logs_len += 1;
    l->n_logs += 1;
    l->logs[l->logs_len - 1] = log;
    return l;
}

/* See log_save.h */
int checkpointing_log_int(Logs *logs, char *level, char *level_id, char *member, int old_value, int new_value)
{
    if (logs == NULL)
    {
        fprintf(stderr, "Need to pass in a new Logs \n");
        return -1;
    }
    if (level == NULL)
    {
        fprintf(stderr, "Need to pass in a level \n");
        return -1;
    }
    if (level_id == NULL)
    {
        fprintf(stderr, "Need to pass in a level id \n");
        return -1;
    }
    if (member == NULL)
    {
        fprintf(stderr, "Need to pass in a struct member \n");
        return -1;
    }
    Log *log = log_new();
    log = log_init_int(log, level, level_id, member, old_value, new_value);
    logs = logs_add(logs, log);
    return 0;
}
