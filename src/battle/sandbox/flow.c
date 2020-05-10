#include "flow.h"
#include "feedback.h"

int start_game(player_t player, enemy_t enemy) {
    announce_game(enemy);    
    char in_progress = 1;
    while(in_progress) {
        battle(player, enemy);
    }
    return 0;
}

int hurt_enemy(int damage, *enemy_t e) {
    return e->stats.hp - damage;
}

int heal_enemy(int heal, *enemy_t *e) {
    return e->stats.hp + heal;
}

int heal_player(int heal, player_t *p) {
    return p->stats.hp - heal;
}

/* Helper function that uses the user's inputted attack
 * PARAMETERS:
 * attack: name of attack
 * enemy: the enemy the player is facing
 * RETURNS:
 * 1 for success
 */
int use_attack(char* attack, enemy_t* enemy) {
    announce_attack(attack, NULL);
    enemy->stats.hp = hurt_enemy(10, enemy); // 10 is the damage the move will do
    announce_damage(10);
    return 1;
}

int hurt_player(int damage, player_t *player) {
    return player->stats.hp - damage; 
}

int enemy_attack(player_t* player, enemy_t* enemy) {
    announce_attack("Poke", enemy);
    player->stats.hp = hurt_player(2, player);
    announce_damage(2);
    return 1;
}

int battle(enemy_t enemy) {
    char* attack;
    while(enemy->stats.hp > 0) {
        printf("Use Attack: ");
        scanf("%s",attack);
        use_attack(attack, enemy);
        enemy_attack(enemy);
    }
    return 0; 
}
