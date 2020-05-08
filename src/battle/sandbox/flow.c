#include "flow.h"
#include "feedback.h"

/* see flow.h */
int start_game(player_t player, enemy_t enemy) {
    announce_game(enemy);    
    battle(player, enemy);
    return 0;
}
/* Helper function that hurts the enemy the player is facing
 * PARAMETERS:
 * - damage: the amount of damage an attack does
 * - e: enemy player data
 * RETURNS:
 *   Value of the enemy's remaining hp
 */
int hurt_enemy(int damage, enemy_t e) {
    return e->stats.hp - damage;
}

/* Helper function that uses the user's inputted attack to damage enemy
 * PARAMETERS:
 *  - attack: name of attack
 *  - enemy: the enemy the player is facing
 * RETURNS:
 *   1 for success
 */
int use_attack(char* attack, enemy_t* enemy) {
    announce_attack(attack, NULL);
    enemy->stats.hp = hurt_enemy(10, enemy); // 10 is the damage the move will do
    announce_damage(10);
    return 1;
}

/* Helper function that uses enemy's attack to damage the player
 * PARAMETERS:
 *  - damage: amount of damage an attack does
 *  - player: player's data
 * RETURNS:
 *    Value of player's remaining HP
 */
int hurt_player(int damage, player_t player) {
    return player->stats.hp - damage; 
}

/* Conducts the enemy's attack
 * PARAMETERS:
 *  - player: player data
 *  - enemy: enemy data
 * RETURNS:
 *    1 for success
 */
int enemy_attack(player_t* player, enemy_t* enemy) {
    announce_attack("Poke", enemy);
    player->stats.hp = hurt_player(2, player);
    announce_damage(2);
    return 1;
}

/* see flow.h */
int battle(player_t player, enemy_t enemy) {
    char* attack;
    while(enemy->stats.hp > 0) {
        printf("Use Attack: ");
        scanf("%s",attack);
        use_attack(attack, enemy);
        enemy_attack(enemy);
    }
    return 0; 
}

