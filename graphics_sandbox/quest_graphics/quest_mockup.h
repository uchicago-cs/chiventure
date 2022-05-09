#ifndef QUEST_MOCKUP_H
#define QUEST_MOCKUP_H

typedef struct stat_req {
    int hp;
    int level;
} stat_req_t;

typedef struct task {
    char *id;
    bool completed;     //0 is not completed, 1 is completed
} task_t;

typedef struct task_tree {
    task_t *task;
    task_tree_t *parent;
    task_tree_t *rsibling;
    task_tree_t *lmostchild;
} task_tree_t;

typedef struct quest_mockup  {
    char *quest_id;
    task_tree_t *task_tree;
    stat_req_t *stat_req;
} quest_mockup_t;

#endif