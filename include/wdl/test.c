#include "objstore.h"

int main() {
    objstore_t *test = NULL;
    obj_t item1 = { .id = "villager", .type = 6, .attrs = NULL };
    objstore_t *new = new_objstore(&item1);
    printf("%s\n", new->key.id);
    add_objstore(&test, &item1);
    if (test == NULL)
    {
        printf("oof\n");
    }
    else
    {
        printf("test success\n");
    }
    free(new);
    free(test);
}
