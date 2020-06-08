/*
 * custom-actions-demo.c: Demonstrating custom action execution
 */

#include <stdlib.h>
#include <stdio.h>
#include "game-state/item.h"
#include "../include/action_block.h"
#include "../include/conditional_block.h"


void custom_actions_ex1()
{
    action_block_t *action1, *action2;
    conditional_block_t *cond1, *cond2;
    attribute_t *attr1, *attr2, *attr3, *attr4, *attr5, *attr6;
    attribute_t **args1, **args2;
    attribute_value_t v1, v2, v3, v4, v5, v6;
    int rc1, rc2;

    attr1 = malloc(sizeof(attribute_t));
    attr1->attribute_key = "num_cans";
    attr1->attribute_tag = INTEGER;
    val1.int_val = 0;
    attr1->attribute_value = v1;
    attr2 = malloc(sizeof(attribute_t));
    attr2->attribute_key = "num_cans";
    attr2->attribute_tag = INTEGER;
    val2.int_val = 1;
    attr2->attribute_value = v2;
    cond1 = conditional_block_new(LTGT, attr1, attr2);
    
    attr3 = malloc(sizeof(attribute_t));
    attr3->attribute_key = "flipped";
    attr3->attribute_tag = BOOLE;
    val3.bool_val = false;
    attr3->attribute_value = v3;
    attr4 = malloc(sizeof(attribute_t));
    attr4->attribute_key = "flipped";
    attr4->attribute_tag = BOOLE;
    val4.bool_val = false;
    attr4->attribute_value = v4;
    cond2 = conditional_block_new(EQ, attr3, attr4);
 
    attr5 = malloc(sizeof(attribute_t));
    attr5->attribute_key = "num_cans";
    attr5->attribute_tag = INTEGER;
    val5.int_val = 1;
    attr5->attribute_value = v5;
    attr6 = malloc(sizeof(attribute_t));
    attr6->attribute_key = "num_cans";
    attr6->attribute_tag = INTEGER;
    val6.int_val = 1;
    attr6->attribute_value = v6;
    args1 = (attribute_t**) malloc(sizeof(attribute_t) * 3);
    args1[0] = attr2;
    args1[1] = attr5;
    args1[2] = attr6;
    action1 = action_block_new(SUBTRACT, 3, args);

    attr4->attribute_value.bool_val = true;
    args2 = (attribute_t**) malloc(sizeof(attribute_t) * 2);
    args2[0] = attr3;
    args2[1] = attr4;
    action2 = action_block_new(SET, 2, args2);

    rc1 = do_conditional_block(cond1);
    rc2 = do_conditional_block(cond2);

    if (rc1) {
        printf("You're out of spinach!\n");
    } else if (rc2) {
        printf("The table is already flipped!\n");
    } else {
        
        printf("Initial number of cans of spinach: %d\n",
                attr2->attribute_value.int_val);
        printf("Initial table status: %s\n",
                attr3->attribute_value.bool_val ? "flipped" : "upright");

        rc1 = exec_action_block(action1);
        rc2 = exec_action_block(action2);

        if (rc1 != SUCCESS && rc2 != SUCCESS) {
            printf("Failed to eat spinach and flip table\n");
        } else if (rc1 != SUCCESS) {
            printf("Failed to eat spinach\n");
        } else if (rc2 != SUCCESS) {
            printf("Failed to flip table\n");
        } else {

            printf("Final number of cans of spinach: %d\n",
                    attr6->attribute_value.int_val);
            printf("Final table status: %s\n",
                    attr3->attribute_value.bool_val ? "flipped" : "upright");
        }
    }
}
