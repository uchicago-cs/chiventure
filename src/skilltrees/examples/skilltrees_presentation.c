#include <stdio.h>
#include <string.h>
#include "common/ctx.h"
#include "ui/ui.h"
#include "cli/operations.h"
#include "skilltrees/skill.h"
#include "skilltrees/inventory.h"
#include "skilltrees/skilltree.h"

/*
 * This example program runs a complete instance of chiventure to feature skill
 * trees. The context for this chiventure game is software design, represented
 * by three rooms: the Design Room, the Implementation Room, and the Demo Room.
 * In running this game, one begins with just one skill in their inventory, the
 * design skill. The design skill is leveled up with each use, and one can only
 * enter the implementation room after having used (leveled up) the design skill
 * at least 3x. Entry into the implementation room grants the player an
 * additional testing skill. The implementation room models test-driven
 * development: one cannot "LEARN IMPLEMENTATION", until one has used (leveled
 * up) their testing skill at least once. Having both tested at least once and
 * having learned implementation, one can use the implementation skill. The
 * implementation skill must be used at least twice to be granted access to the
 * final room, the demo room.
 *
 * CLI Operations Defined for This Example
 *  - SKILLS, for listing all skills currently in your skill inventory
 *  - DESIGN, for using the design skill
 *  - TEST, for using the testing skill
 *  - LEARN IMPLEMENTATION, for learning the implementation skill
 *  - LOOK IMPLEMENTATION, for inspecting the implementation skill
 *  - IMPLEMENT, for using the implementation skill
 *  - GO NORTH, to progress to the next room in the game sequence
 *  - GO SOUTH, to go back to a previous room in the game sequence
 */

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
        return "Good progress on testing! You can LEARN IMPLEMENTATION now!";
    }

    // Implementation skill struct
    skill_t* implementation_skill;

    // Implementation skill effect
    char* effect_implementation(char* args) {
        return "Good implementation progress! Your users eagerly await in the Demo room!";
    }

    // Implementation skill item
    item_t* implementation_item;

/* Create example chiventure context */
chiventure_ctx_t* create_example_ctx() {
    // Create example game
    game_t* game = game_new("Welcome to the skilltrees team's presentation! "
                            "Room progression is always (GO) NORTHward.");

    // Create example rooms
    room_t* design_room = room_new("Design Room", "", "A software developer "
                                   "devotes ample time to design. DESIGN 3x to "
                                   "move on to Implementation.");
    room_t* implementation_room = room_new("Implementation Room", "", "An "
                                           "exercise in test-driven "
                                           "development. TEST once before all "
                                           "else.");
    room_t* demo_room = room_new("Demo Room", "", "You have 15 minutes to "
                                 "present... Good luck!");

    // Add example rooms to example game
    add_room_to_game(game, design_room);
    add_room_to_game(game, implementation_room);
    add_room_to_game(game, demo_room);

    // Set initial room
    game->curr_room = design_room;

    // Create room items
    implementation_item = item_new("IMPLEMENTATION",
                                   "The software implementation skill",
                                   "IMPLEMENT 2x to move on to Demo.");
    add_item_to_room(implementation_room, implementation_item);

    // Create example chiventure context
    chiventure_ctx_t* ctx = chiventure_ctx_new(game);

    return ctx;
}

/* Wrapper function for leveling up implementation skill */
void implementation_level_up(chiventure_ctx_t* ctx) {
    // Level up Implementation Skill
    skill_level_up(implementation_skill);
    if (implementation_skill->level == 3) {
        // If Implementation Skill is at Level 3, connect to Demo Room
        create_connection(ctx->game, "Implementation Room", "Demo Room",
                          "NORTH");
        create_connection(ctx->game, "Demo Room", "Implementation Room",
                          "SOUTH");
    }
}

/* CLI operation for implementation skill */
char* implementation_operation(char *tokens[TOKEN_LIST_SIZE],
                               chiventure_ctx_t* ctx) {
    // Call wrapper function for leveling up implementation skill
    implementation_level_up(ctx);
    // Execute implementation skill
    return skill_execute(implementation_skill, "");
}

/* CLI operation for LEARNing implementation skill */
char* learn_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx) {
    if (!(tokens[1]))
        return "Learning requires a subject.";
    if ((strcmp(tokens[1], "IMPLEMENTATION"))) {
        return "You cannot learn that.";
    }
    add_entry("IMPLEMENT", implementation_operation, NULL, ctx->table);

    // Acquire skill (add skill to player inventory) if skill is "learned"
    inventory_skill_acquire(skill_tree, inventory, implementation_skill);
    return "You have learned. LOOK IMPLEMENTATION to ascertain your skill/knowledge.";
}

/* Wrapper function for leveling up testing skill */
void test_level_up(chiventure_ctx_t* ctx) {
    // Level up Testing Skill
    skill_level_up(test_skill);
    if (test_skill->level == 2) {
        // If Implementation Skill is at Level 2, allow LEARN action
        print_to_cli(ctx, "FYI, use SKILLS to see your skill inventory.");
        add_entry("LEARN", learn_operation, NULL, ctx->table);
        add_action(implementation_item, "LEARN", "Now that your tests are "
                   "complete, begin implementation!", "Test at least once "
                   "before considering implementation!");
    }
}

/* CLI operation for testing skill */
char* test_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx) {
    // Call wrapper function for leveling up testing skill
    test_level_up(ctx);
    // Execute testing skill
    return skill_execute(test_skill, "");
}

/* Wrapper function for leveling up design skill */
void design_level_up(chiventure_ctx_t* ctx) {
    // Level up Design Skill
    skill_level_up(design_skill);
    if (design_skill->level == 4) {
        // If Design Skill is at Level 4, connect to Implementation Room and
        // add skill (CLI command) TEST to inventory
        print_to_cli(ctx, "You can move on to Implementation now, though feel free to keep designing!");
        create_connection(ctx->game, "Design Room", "Implementation Room",
                          "NORTH");
        create_connection(ctx->game, "Implementation Room", "Design Room",
                          "SOUTH");
        add_entry("TEST", test_operation, NULL, ctx->table);
        inventory_skill_acquire(skill_tree, inventory, test_skill);
    }
}

/* CLI operation for design skill */
char* design_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx) {
    // Call wrapper function for leveling up design skill
    design_level_up(ctx);
    // Execute design skill
    return skill_execute(design_skill, "");
}

/* Prints all skills in inventory to the CLI */
void current_skills_as_strings(chiventure_ctx_t* ctx, skill_inventory_t* inventory) {
    assert(inventory != NULL);

    unsigned int i;
    char description[60];

    print_to_cli(ctx, "-");
    print_to_cli(ctx, "Active Skills:");
    if (!inventory->num_active) {
        print_to_cli(ctx, "You have no active skills.");
    } else {
        for (i = 0; i < inventory->num_active; i++) {
            sprintf(description, "%s: Level %u", inventory->active[i]->name,
                    inventory->active[i]->level);
            print_to_cli(ctx, description);
        }
    }

    print_to_cli(ctx, "-");
    print_to_cli(ctx, "Passive Skills:");
    if (!inventory->num_passive) {
        print_to_cli(ctx, "You have no passive skills.");
    } else {
        for (i = 0; i < inventory->num_passive; i++) {
            sprintf(description, "%s: Level %u", inventory->passive[i]->name,
                    inventory->passive[i]->level);
            print_to_cli(ctx, description);
        }
    }
}

/* CLI operation to list all skills in inventory */
char* skills_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx) {
    current_skills_as_strings(ctx, inventory);
    return "";
}

int main(int argc, char **argv) {
    // Create example chiventure context
    chiventure_ctx_t* ctx = create_example_ctx();

    // Initialize skills
    design_skill = skill_new(0, ACTIVE, "Designing Skill", "Your software "
                             "designing skill", 10, 0, &effect_design);
    test_skill = skill_new(1, ACTIVE, "Testing Skill", "Your software testing "
                           "skill", 10, 0, &effect_test);
    implementation_skill = skill_new(2, ACTIVE, "Implementation Skill",
                                     "Your software implementation skill",
                                     10, 0, &effect_implementation);

    // Initialize skill nodes
    skill_node_t* design_node = skill_node_new(design_skill, 0, 0);
    skill_node_t* test_node = skill_node_new(test_skill, 1, 0);
    node_prereq_add(test_node, design_node);
    skill_node_t* implementation_node = skill_node_new(implementation_skill, 2,
                                                       0);
    node_prereq_add(implementation_node, test_node);

    // Initialize skill tree
    skill_tree = skill_tree_new(0, "Software Development Skill Tree", 3);
    skill_tree_node_add(skill_tree, design_node);
    skill_tree_node_add(skill_tree, test_node);
    skill_tree_node_add(skill_tree, implementation_node);

    // Initialize skill inventory
    inventory = inventory_new(20, 20);
    inventory_skill_acquire(skill_tree, inventory, design_skill);

    // Add DESIGN and SKILLS operation
    add_entry("DESIGN", design_operation, NULL, ctx->table);
    add_entry("SKILLS", skills_operation, NULL, ctx->table);

    // Start UI for example chiventure context
    start_ui(ctx, banner);

    // Free memory
    skill_tree_free(skill_tree);
    skill_node_free(design_node);
    skill_node_free(test_node);
    skill_node_free(implementation_node);
    inventory_free(inventory);
    skill_free(design_skill);
    skill_free(test_skill);
    skill_free(implementation_skill);
    game_free(ctx->game);

    return 0;
}
