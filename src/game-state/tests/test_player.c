#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "player.h"
#include "common-player.h"
#include "game_state_common.h"

// NEED TO WRITE ALL THE COMMENTS FOR EACH TEST

void setup(void) {
  player_t *player1 = player_new(100);
  player_t *player2 = player_new(99);
}

void teardown(void) {
  /*TODO*/
  return;
}

Test(player, new)
{
  player_t *player1 = player_new(100);

  cr_assert_not_null(player1, "player_new() failed");
  
  cr_assert_eq(player1->health, 100, "player_new() didn't set player health");
  cr_assert_eq(player1->level, 1, "player_new() didn't properly call player_init()");
  cr_assert_eq(player1->xp, 0, "player_new() didn't properly call player_init()");
}

Test(player, init)
{
  player_t *player1 = player_new(100);

  int res = player_init(player1, 56);

  cr_assert_not_null(player1, "player_new() failed");

  cr_assert_eq(player1->health, 56, "player_init() didn't set player health");
  cr_assert_eq(player1->level, 1, "player_init() didn't set level to 1");
  cr_assert_eq(player1->xp, 0, "player_init() didn't set experience to 0");
  cr_assert_eq(res, SUCCESS, "player_init() failed");
}

// SKIPPED DELETE ALL PLAYERS

Test(player, free)
{
  player_t *player1 = player_new(100);
  
  int res = player_free(player1);

  cr_assert_not_null(player1, "player_new() failed");
  
  cr_assert_eq(res, SUCCESS, "player_free() failed");
}

Test(player, get_health)
{
  player_t *player2 = player_new(99);
  
  int health = get_health(player2);

  cr_assert_not_null(player2, "player_new() failed");

  cr_assert_eq(health, 99, "get_health() returned incorrect health");
}

Test(player, change_health)
{
  player_t *player2 = player_new(99);

  int health = change_health(player2, 2, 100);
  int health2 = change_health(player2, -20, 100);
  int health3 = change_health(player2, 3, 83);
  cr_assert_not_null(player2, "player_new() failed");
  
  cr_assert_eq(health, 100, "change_health() increased health past max");
  cr_assert_eq(health2, 80, "change_health() did not properly reduce health");
  cr_assert_eq(health3, 83, "change_health() did not properly add health");
}
/*
Test(player, change_level)
{
  player_t *player2 = player_new(99);

  int 
  
}

Test(player, get_level)
{
  
}
*/
//same issue—need to figure out way to create defined structs that can be called
/*
Test(player, init) {
    player_t *playerone = malloc(sizeof(player_t));
    player_init(playerone, 100);
    cr_assert_not_null(playerone, "player_init failed");
    cr_assert_eq(playerone->health, 100, "player_init failed: health");
    cr_assert_eq(playerone->level, 1, "player_init failed: level");
    cr_assert_eq(playerone->xp, 0, "player_init failed: xp");
    cr_assert_not_null(playerone->inventory, "player_init failed: inventory");
    cr_assert_not_null(playerone->clothes, "player_init failed: clothes");
}

Test(player, health_change)
{
    player_t *playerone = malloc(sizeof(player_t));
    player_init(playerone, 100);
    health_change(plyr, -50);
    cr_assert_eq(plyr->health, 50, "health change failed");
}
*/
