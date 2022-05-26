/*
 * This example program runs a full instance of chiventure with an in-memory game,
 * and where the CLI is monkeypatched to accept functions that model player stats and effects
 * We we unable to completely integrate stats and effect completely into the game, but they
 * are still functional.
 * 
 * Commands created in this example program:
 *
 * - PLYR-STATS: Print player stats
 * - PLYR-EFFECTS: Print player effects
 * - GAME-STATS: Print global stats
 * - GAME-EFFECTS: Print global effects
 * - ADD-EFFECT: Add a specified effect to a player
 * - ADD-STAT: Add a specified stat to a player
 * - ITEM-EFFECT: Print all the effects an item will have
 * - UPGRADE: Increase the max of a specified stat by an arbitrary amount
 *
 */
 
#include <stdio.h>
#include <cli/operations.h>
#include "common/ctx.h"
#include "ui/ui.h"
#include "game-state/stats.h"
#define MIN_STRING_LENGTH 2
#define MAX_NAME_LENGTH 70

const char *banner = "THIS IS AN EXAMPLE PROGRAM";

/* Creates a poison item with an effect */
item_t *create_poison(effects_global_t *p, stats_t *stat)
{
    item_t *poison = item_new("POISON","This is poison.",
                   "This is poison and will harm your health. DO NOT TAKE OR PICKUP.");
    agent_t *agent_poison = malloc(sizeof(agent_t));
    agent_poison->item = poison;
    agent_poison->npc = NULL;
    stat_effect_t *poisoned = stat_effect_new(p);
    stat_mod_t *mod1 = stat_mod_new(stat, 0.5, 50);
    LL_APPEND(poisoned->stat_list, mod1);
    add_effect_to_item(agent_poison->item, poisoned);
    add_action(agent_poison, "TAKE", "The item has been taken.", 
               "The item does not exist in the game.");
    return agent_poison->item;
}

/* Creates a potion item with effect */
item_t *create_potion(effects_global_t *p, stats_t *stat)
{
    item_t *potion = item_new("POTION","This is a health potion.",
                   "This potion will increase your health. Feel free to take it.");
    agent_t *agent_potion = malloc(sizeof(agent_t));
    agent_potion->item = potion;
    agent_potion->npc = NULL;
    stat_effect_t *healed = stat_effect_new(p);
    stat_mod_t *mod = stat_mod_new(stat, 1.25, 25);
    LL_APPEND(healed->stat_list, mod);
    add_effect_to_item(agent_potion->item, healed);
    add_action(agent_potion, "TAKE", "The item has been taken.", 
               "The item does not exist in the game.");
    return agent_potion->item;
}

/* Creates an elixir item with effects */
item_t *create_elixir(effects_global_t *p1, effects_global_t *p2,
                      stats_t *s1, stats_t *s2, stats_t *s3, stats_t *s4)
{
    item_t *elixir = item_new("ELIXIR","This is an elixir.",
                   "This is an elixir. Effects: energize and stun.");
    agent_t *agent_elixir = malloc(sizeof(agent_t));
    agent_elixir->item = elixir;
    agent_elixir->npc = NULL;
    stat_effect_t *stunned = stat_effect_new(p1);
    stat_mod_t *mod1 = stat_mod_new(s1, 0.75, 200);
    stat_mod_t *mod2 = stat_mod_new(s2, 0.9, 200);
    LL_APPEND(stunned->stat_list, mod1);
    LL_APPEND(stunned->stat_list, mod2);
    add_effect_to_item(agent_elixir->item, stunned);

    stat_effect_t *boost = stat_effect_new(p2);
    stat_mod_t *mod3 = stat_mod_new(s3, 1.5, 10);
    stat_mod_t *mod4 = stat_mod_new(s4, 1.25, 10);
    LL_APPEND(boost->stat_list, mod3);
    LL_APPEND(boost->stat_list, mod4);
    add_effect_to_item(agent_elixir->item, boost);
    add_action(agent_elixir, "TAKE", "The item has been taken.", 
               "The item does not exist in the game.");
    return agent_elixir->item;
}
/* Creates a sample in-memory game */
chiventure_ctx_t *create_sample_ctx()
{
    game_t *game = game_new("Welcome to Chiventure!");

    /* Create two rooms (room1 and room2). room1 is the initial room */
    room_t *room1 = room_new("room1", "This is room 1", "Verily, this is the first room.");
    room_t *room2 = room_new("room2", "This is room 2", "Truly, this is the second room.");
    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    game->curr_room = room1;
    create_connection(game, "room1", "room2", "NORTH");

    
    /* Create context */
    chiventure_ctx_t *ctx = chiventure_ctx_new(game);
    game = ctx->game;

    /* Create global effects and add to game */
    effects_global_t *poisoned, *stunned, *healed, *boost;

    poisoned = global_effect_new("POISONED");
    stunned = global_effect_new("STUNNED");
    healed = global_effect_new("HEALED");
    boost = global_effect_new("ENERGIZED");
    add_effect_to_game(game, boost);
    add_effect_to_game(game, stunned);
    add_effect_to_game(game, poisoned);
    add_effect_to_game(game, healed);

    /* Create global stats and add to game */
    stats_global_t *health = stats_global_new("HEALTH", 10000);
    stats_global_t *xp = stats_global_new("XP", 10000);
    add_stat_to_game(game, health);
    add_stat_to_game(game, xp);

    stats_global_t *speed = stats_global_new("SPEED", 10000);
    add_stat_to_game(game, speed);
    stats_global_t *stamina = stats_global_new("STAMINA", 10000);
    add_stat_to_game(game, stamina);

    /* Create player stats */
    stats_t *s1 = stats_new(health, 100);
    stats_t *s2 = stats_new(xp, 100);
    stats_t *s3 = stats_new(speed, 75);
    stats_t *s4 = stats_new(stamina, 100);


    /* Create an elixir item and add it to game and room1*/
    item_t *elixir = create_elixir(stunned, boost, s1, s2, s3, s4);
    add_item_to_game(game, elixir);
    add_item_to_room(room1, elixir);

    /* Create a poison item and add it to game and room1 */
    item_t *poison = create_poison(poisoned, s1);
    add_item_to_game(game, poison);
    add_item_to_room(room1, poison);

    /* Create a potion item and add it to game and room1 */
    item_t *potion = create_potion(healed, s1);
    add_item_to_room(room1, potion);
    add_item_to_game(game, potion);

    /* Add stats to player hash table */
    stats_hash_t *sh = NULL;
    effects_hash_t *eh = NULL;
    add_stat(&sh, s1);
    add_stat(&sh, s2);
    add_stat(&sh, s3);

    class_t *class = class_new("class", "short", "long",
                   NULL, sh, eh);
    game->curr_player->player_class = class;

    return ctx;
}

char *print_global_stats(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;

    if (tokens[1] != NULL)
    {
        return "I do not know what you mean.";
    }

    stats_global_hash_t *s = game->curr_stats;
    stats_global_t *stat, *tmp;
    int size = MIN_STRING_LENGTH + (MAX_NAME_LENGTH * HASH_COUNT(s));
    char list[size];
    char line[size];

    strcpy(list, "");

    HASH_ITER(hh, s, stat, tmp)
    {
        sprintf(line, "%s [max: %.2f]\n", stat->name, stat->max);
        strcat(list, line);
    }

    char *display = strdup(list);
    return display;
}

char *print_global_effects(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;

    if (tokens[1] != NULL)
    {
        return "I do not know what you mean.";
    }

    effects_global_hash_t *hash = game->all_effects;
    effects_global_t *effect, *tmp;

    int size = MIN_STRING_LENGTH + (MAX_NAME_LENGTH * HASH_COUNT(hash));
    char list[size];
    char line[size];

    strcpy(list, "");

    HASH_ITER(hh, hash, effect, tmp)
    {
        sprintf(line, "%s\n", effect->name);
        strcat(list, line);
    }

    char *display = strdup(list);
    return display;
}

char *print_player_stats(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;

    if (tokens[1] != NULL)
    {
        return "I do not know what you mean.";
    }

    return display_stats(game->curr_player->player_class->base_stats);
}

char *print_player_effects(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;

    if (tokens[1] != NULL)
    {
        return "I do not know what you mean.";
    }

    return display_stat_effects(game->curr_player->player_class->effects);
}

char *print_item_effects(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;

    if (tokens[2] != NULL)
    {
        return "I do not know what you mean.";
    }

    if (tokens[1] == NULL)
    {
        return "You must identify an item\n";
    }

    item_t *item;
    HASH_FIND(hh, game->all_items, tokens[1], strlen(tokens[1]), item);

    if (item == NULL) {
        return "The item is in inventory, so its effect cannot be read.";
    }

    return display_stat_effects(item->stat_effects);
}

char *add_player_stat(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;

    if (tokens[2] != NULL)
    {
        return "I do not know what you mean.";
    }
    if (tokens[1] == NULL)
    {
        return "You must identify a stat to add\n";
    }

    stats_global_t *global;
    HASH_FIND(hh, game->curr_stats, tokens[1], strlen(tokens[1]), global);
    
    if (global == NULL)
    {
        return "This stat does not exist in the game.";
    }

    stats_t *stat = stats_new(global, 100);
    add_stat(&game->curr_player->player_class->base_stats, stat);
    return "The stat has been added.";

}

char *add_player_effect(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;

    if (tokens[2] != NULL)
    {
        return "I do not know what you mean.";
    }
    if (tokens[1] == NULL)
    {
        return "You must identify an effect to add\n";
    }

    effects_global_t *global;
    HASH_FIND(hh, game->all_effects, tokens[1], strlen(tokens[1]), global);
    
    if (global == NULL)
    {
        return "This stat does not exist in the game.";
    }

    stat_effect_t *effect = stat_effect_new(global);
    add_stat_effect(&game->curr_player->player_class->effects, effect);
    return "The effect has been added.";

}

char *upgrade_command(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;

    if (tokens[2] != NULL)
    {
        return "I do not know what you mean.";
    }
    if (tokens[1] == NULL)
    {
        return "You must identify a stat to upgrade\n";
    }

    int rc = change_stat_max(game->curr_player->player_class->base_stats, tokens[1], 100);

    if (rc == FAILURE)
    {
        return "This player does not have this stat.";
    }

    return "The stat has been upgraded.";

}

int main(int argc, char **argv)
{
    chiventure_ctx_t *ctx = create_sample_ctx();

    /* Monkeypatch the CLI to add the new operations */
    add_entry("PLYR-STATS", print_player_stats, NULL, ctx->cli_ctx->table);
    add_entry("PLYR-EFFECTS", print_player_effects, NULL, ctx->cli_ctx->table);
    add_entry("GAME-STATS", print_global_stats, NULL, ctx->cli_ctx->table);
    add_entry("GAME-EFFECTS", print_global_effects, NULL, ctx->cli_ctx->table);
    add_entry("ADD-STAT", add_player_stat, NULL, ctx->cli_ctx->table);
    add_entry("ADD-EFFECT", add_player_effect, NULL, ctx->cli_ctx->table);
    add_entry("ITEM-EFFECT", print_item_effects, NULL, ctx->cli_ctx->table);
    add_entry("UPGRADE", upgrade_command, NULL, ctx->cli_ctx->table);

    /* Start chiventure */
    start_ui(ctx, banner);

    return 0;
}

