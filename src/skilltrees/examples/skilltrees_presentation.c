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
    //create_connection(game, "Implementation Room", "Demo Room", "NORTH");
    //create_connection(game, "Demo Room", "Implementation Room", "SOUTH");

    // Create room items
    item_t* implementation_item = item_new("IMPLEMENTATION",
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

/* Declare design skill and associated CLI operation */
    // Skill struct
    skill_t* design_skill;

    // Skill effect
    char* effect_design(char* args) {
        return "Good progress on your modules! Keep going!";
    }

    // Wrapper function for leveling up design skill
    void design_level_up(chiventure_ctx_t* ctx) {
        skill_level_up(design_skill);
        if (design_skill->level == 4) {
            create_connection(ctx->game, "Design Room", "Implementation Room", "NORTH");
            create_connection(ctx->game, "Implementation Room", "Design Room", "SOUTH");
        }
    }

    // Skill CLI operation
    char* design_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx) {
        design_level_up(ctx);
        return skill_execute(design_skill, "");
    }

/* Declare test skill and associated CLI operation */
    // Skill struct
    skill_t* test_skill;

    // Skill effect
    char* effect_test(char* args) {
        return "Good progress on testing! Keep going!";
    }

    // Skill CLI operation
    char* test_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx) {
        return skill_execute(test_skill, "");
    }

/* Declare implementation skill and associated CLI operation */
    // Skill struct
    skill_t* implementation_skill;

    // Skill effect
    char* effect_implementation(char* args) {
        return "Good progress implementation progress! Keep going!";
    }

    // Skill CLI operation
    char* implementation_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx) {
        return skill_execute(implementation_skill, "");
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
    inventory_skill_add(inventory, design_skill);

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

    // Start UI for example chiventure context
    start_ui(ctx, banner);

    // Free memory
    skill_free(design_skill);
    game_free(ctx->game);

    return 0;
}
