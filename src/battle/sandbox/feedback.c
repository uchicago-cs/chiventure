#include "feedback.h"

/* see feedback.h */
int announce_game(enemy_t* e) {
    printf("You have encountered %s\n\n", e->name);
    printf("Let the battle begin!\n");    
    return 1;
}

/* see feedback.h */
int announce_attack(char* attack, enemy_t* e) {
    if(e == NULL) {
        printf("You used %s!\n", attack);
        return 1;
    } else {
        printf("%s used %s", e->name, attack);
        return 1;
    }
    return 0;
}

/* see feedback.h */
int announce_damage(int d) {
    printf("It did %d damage!\n\n", d);
    return 1;
}
