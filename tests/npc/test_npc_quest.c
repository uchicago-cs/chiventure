#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <npc/npc.h>

/* Checks that npc_quest_init() properly inits a new npc_quest struct */
Test(npc_quest, init)
{
    convo_t *c = convo_new();
    npc_quest_t quest;

    int check = npc_quest_init(&quest, "test", c);

    cr_assert_eq(check, SUCCESS, "npc_quest_init() failed to initialize");
    cr_assert_eq(quest.dialogue, c, "npc_quest_init() failed to set dialogue");
    cr_assert_eq(strcmp(quest.id, "test"), 0, "npc_quest_init() failed to set id");
    cr_assert_null(quest.next, "npc_quest_init() failed to make next NULL");
}

/* Checks that npc_quest_new() properly mallocs and inits a new npc_quest struct */
Test(npc_quest, new)
{
    convo_t *c = convo_new();
    npc_quest_t *quest = npc_quest_new("test", c);

    cr_assert_not_null(quest, "npc_quest_new() failed");
    cr_assert_eq(quest->dialogue, c, "npc_quest_new() failed to set dialogue");
    cr_assert_eq(strcmp(quest->id, "test"), 0, "npc_quest_new() failed to set id");
}

/* Checks that npc_quest_free() properly frees a npc_quest struct */
Test(npc_quest, free)
{
    convo_t *c = convo_new();
    npc_quest_t *quest_to_free = npc_quest_new("test", c);
    cr_assert_not_null(quest_to_free, "npc_quest_free() did not properly allocate quest");

    int freed = npc_quest_free(quest_to_free);

    cr_assert_eq(freed, SUCCESS, "npc_quest_free() failed to free");
}

/* Checks that npc_task_init() properly inits a new npc_task struct */
Test(npc_task, init)
{
    convo_t *c = convo_new();
    npc_task_t task;

    int check = npc_task_init(&task, "test", c);

    cr_assert_eq(check, SUCCESS, "npc_task_init() failed to initialize");
    cr_assert_eq(task.dialogue, c, "npc_task_init() failed to set dialogue");
    cr_assert_eq(strcmp(task.id, "test"), 0, "npc_task_init() failed to set id");
    cr_assert_null(task.next, "npc_task_init() failed to make next NULL");
}

/* Checks that npc_task_new() properly mallocs and inits a new npc_task struct */
Test(npc_task, new)
{
    convo_t *c = convo_new();
    npc_task_t *task = npc_task_new("test", c);

    cr_assert_not_null(task, "npc_task_new() failed");
    cr_assert_eq(task->dialogue, c, "npc_task_init() failed to set dialogue");
    cr_assert_eq(strcmp(task->id, "test"), 0, "npc_task_init() failed to set id");
}

/* Checks that npc_task_free() properly frees a npc_task struct */
Test(npc_task, free)
{
    convo_t *c = convo_new();
    npc_task_t *task_to_free = npc_task_new("test", c);
    cr_assert_not_null(task_to_free, "npc_task_free() did not properly allocate quest");

    int freed = npc_task_free(task_to_free);

    cr_assert_eq(freed, SUCCESS, "npc_task_free() failed to free");
}

/* Checks that npc_quest_list_new() properly creates a npc_quest_list struct */
Test(npc_quest_list, new)
{
    npc_quest_list_t *quest_list = npc_quest_list_new();
    cr_assert_not_null(quest_list, "npc_quest_list_new() failed");
    cr_assert_null(quest_list->head, "npc_quest_list_new() failed to make head NULL");
    cr_assert_eq(quest_list->length, 0, "npc_quest_list_new() failed to make length 0");
}

/* Checks that npc_task_list_new() properly creates a npc_task_list struct */
Test(npc_task_list, new)
{
    npc_task_list_t *task_list = npc_task_list_new();
    cr_assert_not_null(task_list, "npc_task_list_new() failed");
    cr_assert_null(task_list->head, "npc_task_list_new() failed to make head NULL");
    cr_assert_eq(task_list->length, 0, "npc_task_list_new() failed to make length 0");
}

// Checks that npc_quest_list_init() properly initializes a npc_quest_list struct
Test(npc_quest_list, init)
{
    npc_quest_list_t *quest_list;
    quest_list = malloc(sizeof(npc_quest_list_t));

    cr_assert_not_null(quest_list, "npc_task_list_new() failed");

    int rc = npc_quest_list_init(quest_list);

    cr_assert_eq(rc, SUCCESS, "npc_quest_list_init() failed to initialize");
    cr_assert_not_null(quest_list, "npc_quest_list_init() failed");
    cr_assert_null(quest_list->head, "npc_quest_list_init() failed to make head NULL");
    cr_assert_eq(quest_list->length, 0, "npc_quest_list_init() failed to make length 0");
}

// Checks that npc_task_list_init() properly initializes a npc_task_list struct
Test(npc_task_list, init)
{
    npc_task_list_t *task_list;
    task_list = malloc(sizeof(npc_task_list_t));

    cr_assert_not_null(task_list, "npc_task_list_new() failed");

    int rc = npc_task_list_init(task_list);

    cr_assert_eq(rc, SUCCESS, "npc_task_list_init() failed to initialize");
    cr_assert_not_null(task_list, "npc_task_list_init() failed");
    cr_assert_null(task_list->head, "npc_task_list_init() failed to make head NULL");
    cr_assert_eq(task_list->length, 0, "npc_task_list_new() failed to make length 0");
}

// Checks that npc_quest_list_add() properly adds a npc_quest struct to a npc_quest_list_t
Test(npc_quest_list, add)
{
    convo_t *c1 = convo_new();
    npc_quest_t *quest1 = npc_quest_new("test1", c1);
    cr_assert_not_null(quest1, "npc_quest_new() failed");

    convo_t *c2 = convo_new();
    npc_quest_t *quest2 = npc_quest_new("test2", c2);
    cr_assert_not_null(quest2, "npc_quest_new() failed");

    npc_quest_list_t *quest_list = npc_quest_list_new();
    cr_assert_not_null(quest_list, "npc_quest_list_new() failed");

    int rc = npc_quest_list_init(quest_list);
    cr_assert_eq(rc, SUCCESS, "npc_quest_list_init() failed to initialize");

    int add1 = npc_quest_list_add(quest_list, quest1);
    cr_assert_eq(add1, SUCCESS, "npc_quest_list_add() failed to add a quest");
    cr_assert_eq(quest_list->head, quest1, "npc_quest_list_add() failed to set head->next to quest1");

    int add2 = npc_quest_list_add(quest_list, quest2);
    cr_assert_eq(add2, SUCCESS, "npc_quest_list_add() failed to add a second quest");
    cr_assert_eq(quest_list->head->next, quest2, "npc_quest_list_add() failed to set head->next->next to quest2");
}

// Checks that npc_task_list_add() properly adds a npc_task struct to a npc_task_list_t
Test(npc_task_list, add)
{
    convo_t *c1 = convo_new();
    npc_task_t *task1 = npc_task_new("test1", c1);
    cr_assert_not_null(task1, "npc_task_new() failed");

    convo_t *c2 = convo_new();
    npc_task_t *task2 = npc_task_new("test2", c2);
    cr_assert_not_null(task2, "npc_task_new() failed");

    npc_task_list_t *task_list = npc_task_list_new();
    cr_assert_not_null(task_list, "npc_task_list_new() failed");

    int rc = npc_task_list_init(task_list);
    cr_assert_eq(rc, SUCCESS, "npc_task_list_init() failed to initialize");

    int add1 = npc_task_list_add(task_list, task1);
    cr_assert_eq(add1, SUCCESS, "npc_task_list_add() failed to add a task");
    cr_assert_eq(task_list->head, task1, "npc_task_list_add() failed to set head->next to task1");

    int add2 = npc_task_list_add(task_list, task2);
    cr_assert_eq(add2, SUCCESS, "npc_task_list_add() failed to add a second task");
    cr_assert_eq(task_list->head->next, task2, "npc_task_list_add() failed to set head->next->next to task2");
}

// Checks that npc_task_list_add() properly frees a npc_task_list_t
Test(npc_quest_list, free)
{
    convo_t *c1 = convo_new();
    npc_quest_t *quest1 = npc_quest_new("test1", c1);
    cr_assert_not_null(quest1, "npc_quest_new() failed");

    convo_t *c2 = convo_new();
    npc_quest_t *quest2 = npc_quest_new("test2", c2);
    cr_assert_not_null(quest2, "npc_quest_new() failed");

    npc_quest_list_t *quest_list = npc_quest_list_new();
    cr_assert_not_null(quest_list, "npc_quest_list_new() failed");

    int rc = npc_quest_list_init(quest_list);
    cr_assert_eq(rc, SUCCESS, "npc_quest_list_init() failed to initialize");

    int add1 = npc_quest_list_add(quest_list, quest1);
    cr_assert_eq(add1, SUCCESS, "npc_quest_list_add() failed to add a quest");

    int add2 = npc_quest_list_add(quest_list, quest2);
    cr_assert_eq(add2, SUCCESS, "npc_quest_list_add() failed to add a second quest");

    int free = npc_quest_list_free(quest_list);
    cr_assert_eq(free, SUCCESS, "npc_quest_list_free() failed to free the quest list");
}

// Checks that npc_task_list_free() properly frees a npc_task_list_t
Test(npc_task_list, free)
{
    convo_t *c1 = convo_new();
    npc_task_t *task1 = npc_task_new("test1", c1);
    cr_assert_not_null(task1, "npc_task_new() failed");

    convo_t *c2 = convo_new();
    npc_task_t *task2 = npc_task_new("test2", c2);
    cr_assert_not_null(task2, "npc_task_new() failed");

    npc_task_list_t *task_list = npc_task_list_new();
    cr_assert_not_null(task_list, "npc_task_list_new() failed");

    int rc = npc_task_list_init(task_list);
    cr_assert_eq(rc, SUCCESS, "npc_task_list_init() failed to initialize");

    int add1 = npc_task_list_add(task_list, task1);
    cr_assert_eq(add1, SUCCESS, "npc_task_list_add() failed to add a task");

    int add2 = npc_task_list_add(task_list, task2);
    cr_assert_eq(add2, SUCCESS, "npc_task_list_add() failed to add a second task");

    int free = npc_task_list_free(task_list);
    cr_assert_eq(free, SUCCESS, "npc_task_list_free() failed to free the task list");
}