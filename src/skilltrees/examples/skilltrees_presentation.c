#include <stdio.h>
#include "common/ctx.h"
#include "ui/ui.h"
#include "cli/operations.h"
#include "skilltrees/skill.h"
#include "skilltrees/inventory.h"
#include "skilltrees/skilltree.h"

const char* banner =
    "    ________________________________________________________________________________________\n"
    "  / \\                                                                                       \\\n"
    " |   |                                                                                      |\n"
    "  \\_ |     ███████╗██╗  ██╗██╗██╗     ██╗  ████████╗██████╗ ███████╗███████╗███████╗        |\n"
    "     |      ██╔════╝██║ ██╔╝██║██║     ██║  ╚══██╔══╝██╔══██╗██╔════╝██╔════╝██╔════╝       |\n"
    "     |      ███████╗█████╔╝ ██║██║     ██║     ██║   ██████╔╝█████╗  █████╗  ███████╗       |\n"
    "     |      ╚════██║██╔═██╗ ██║██║     ██║     ██║   ██╔══██╗██╔══╝  ██╔══╝  ╚════██║       |\n"
    "     |      ███████║██║  ██╗██║███████╗███████╗██║   ██║  ██║███████╗███████╗███████║       |\n"
    "     |      ╚══════╝╚═╝  ╚═╝╚═╝╚══════╝╚══════╝╚═╝   ╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝       |\n"
    "     |   ___________________________________________________________________________________|___\n"
    "     |  /                                                                                      /\n"
    "     \\_/______________________________________________________________________________________/\n";

/* Declare item so action can be associated with it on skill acquisition */
item_t* implementation_item;

/* Create example chiventure context */
chiventure_ctx_t* create_example_ctx() {
    // Create example game
    game_t* game = game_new("Welcome to the skilltrees team's presentation!");

    // Create example rooms
    room_t* design_room = room_new("Design Room", "", "A software developer "
                                   "devotes ample time to design. Design 3x to "
                                   "move on to implementation.");
    room_t* implementation_room = room_new("Implementation Room", "", "This "
                                           "room is an exercise in test-driven"
                                           " development.");
    room_t* demo_room = room_new("Demo Room", "", "You have 15 minutes to "
                                 "present. Good luck!");

    // Add example rooms to example game
    add_room_to_game(game, design_room);
    add_room_to_game(game, implementation_room);
    add_room_to_game(game, demo_room);

    // Set initial room
    game->curr_room = design_room;

    // Create room items
    implementation_item = item_new("IMPLEMENTATION",
                                   "The software implementation skill",
                                   "Skill that enables software implementation");
    add_item_to_room(implementation_room, implementation_item);

    // Create example chiventure context
    chiventure_ctx_t* ctx = chiventure_ctx_new(game);

    return ctx;
}

/* Declare skill tree */
skill_tree_t* skill_tree;

/* Declare skill inventory */
skill_inventory_t* inventory;

/* Declare skills and skill effects */
    // Design skill struct
    skill_t* design_skill;

    // Design skill effect
    char* effect_design(char* args) {
        return "Good progress on your modules! Keep going!";
    }

    // Testing skill struct
    skill_t* test_skill;

    // Testing skill effect
    char* effect_test(char* args) {
        return "Good progress on testing! Keep going!";
    }

    // Implementation skill struct
    skill_t* implementation_skill;

    // Implementation skill effect
    char* effect_implementation(char* args) {
        return "Good implementation progress! Keep going!";
    }

/* Wrapper function for leveling up implementation skill */
void implementation_level_up(chiventure_ctx_t* ctx) {
    skill_level_up(implementation_skill);
    if (implementation_skill->level > 2) {
        create_connection(ctx->game, "Implementation Room", "Demo Room", "NORTH");
        create_connection(ctx->game, "Demo Room", "Implementation Room", "SOUTH");
        //inventory_skill_acquire(inventory, test_skill);
    }
}

/* CLI operation for implementation skill */
char* implementation_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx) {
    implementation_level_up(ctx);
    return skill_execute(implementation_skill, "");
}

/* Wrapper function for leveling up testing skill */
void test_level_up(chiventure_ctx_t* ctx) {
    skill_level_up(test_skill);
    if (test_skill->level > 1) {
        add_action(implementation_item, "LEARN", "Now that your tests are complete, begin implementation!", "Test at least once before considering implementation!");
        add_entry("IMPLEMENT", implementation_operation, NULL, ctx->table);
        //inventory_skill_acquire(inventory, implementation_skill);
    }
}

/* CLI operation for testing skill */
char* test_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx) {
    test_level_up(ctx);
    return skill_execute(test_skill, "");
}

/* Wrapper function for leveling up design skill */
void design_level_up(chiventure_ctx_t* ctx) {
    skill_level_up(design_skill);
    if (design_skill->level > 3) {
        create_connection(ctx->game, "Design Room", "Implementation Room", "NORTH");
        create_connection(ctx->game, "Implementation Room", "Design Room", "SOUTH");
        add_entry("TEST", test_operation, NULL, ctx->table);
        //inventory_skill_acquire(inventory, test_skill);
    }
}

/* CLI operation for design skill */
char* design_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx) {
    design_level_up(ctx);
    return skill_execute(design_skill, "");
}

int main(int argc, char **argv) {
    // Create example chiventure context
    chiventure_ctx_t* ctx = create_example_ctx();

    // Initialize skills
    design_skill = skill_new(0, ACTIVE, "Designing Skill", "Your software designing skill", 10, 0, &effect_design);
    test_skill = skill_new(1, ACTIVE, "Testing Skill", "Your software testing skill", 10, 0, &effect_test);
    implementation_skill = skill_new(2, ACTIVE, "Implementation Skill", "Your software implementation skill", 10, 0, &effect_implementation);

    // Initialize inventory
    inventory = inventory_new(10, 0);
    // inventory_skill_acquire(skill_tree, inventory, design_skill);

    // Initialize skill nodes
    skill_node_t* design_node = skill_node_new(design_skill, 0, 0);
    skill_node_t* test_node = skill_node_new(test_skill, 1, 0);
    node_prereq_add(test_node, design_node);
    skill_node_t* implementation_node = skill_node_new(implementation_skill, 2, 0);
    node_prereq_add(implementation_node, design_node);
    node_prereq_add(implementation_node, test_node);

    // Initialize skill tree
    skill_tree = skill_tree_new(0, "Software Development Skill Tree", 3);
    skill_tree_node_add(skill_tree, design_node);
    skill_tree_node_add(skill_tree, test_node);
    skill_tree_node_add(skill_tree, implementation_node);

    // Add DESIGN operation
    add_entry("DESIGN", design_operation, NULL, ctx->table);

    // Define LEARN Kind 1 Action
    action_type_t learn_action = {"LEARN", ITEM};
    add_entry(learn_action.c_name, kind1_action_operation, &learn_action, ctx->table);

    // Start UI for example chiventure context
    start_ui(ctx, banner);

    // Free memory
    skill_free(design_skill);
    game_free(ctx->game);

    return 0;
}
