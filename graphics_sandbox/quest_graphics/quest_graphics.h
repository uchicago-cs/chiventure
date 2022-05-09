#ifndef QUEST_GRAPHICS_H
#define QUEST_GRAPHICS_H

#include "raylib.h"

typedef struct task_tree_mockup task_tree_mockup_t;

struct task_tree_mockup {
    char* task_name;
    task_tree_mockup_t *parent;
    task_tree_mockup_t *rsibling;
    task_tree_mockup_t *lmostchild;
};


int getTreeMaxWidth(task_tree_mockup_t* taskTree);

int getTreeMaxHeight(task_tree_mockup_t* taskTree);



#endif