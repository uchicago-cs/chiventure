// A developer tool for creating and testing custom actions 
// without the need to run the whole game.

#include "custom-actions/custom_actions_common.h"
#include "custom-actions/interface.h"

#include "game-state/game_state_common.h"
#include "game-state/player.h"
#include "game-state/game.h"

/* Creates a player given a name and health */
player_t* createPlayer(char *name, int health) {
    player_t* player = player_new(name,health);
    int x = player_init(player,name,health);
    if (x == SUCCESS) 
        printf("Player \"%s\" with %d health initialized\n", name, health);
    if (x == FAILURE) 
        printf("Error in creating player requested. Try again or contact game-state team.\n");
    return player;
}

/* Creates an empty game with 1 player given as input */
game_t *createSandboxGame(player_t *player) {
    game_t* game = game_new("Welcome to the sandbox");
    int x = add_player_to_game(game, player);
    if (x == SUCCESS) printf("Empty game with 1 player successfully created\n");
    if (x == FAILURE) printf("Error in producing empty game with one player. Try again or contact game-state team.\n");
    return game;
}

// called with ./sandbox or ./sandbox Steve 10
int main(int argc, char *argv[]) {

    /* sandbox game initilization start */
    char *name = "Alex"; // default name
    int health = 10; // default health
    int level;
    int xp;
    int maxWordsInput = 10;
    int maxWordsLength = 10;

    // changes player name and health if provided
    if (argc >= 3) {
        name = argv[1];
        health = atoi(argv[2]);
    }

    game_t *game;
    player_t *player = createPlayer(name, health);
    game = createSandboxGame(player);
    /* sandbox game initilization end */


    /* dealing with input start */
    char *input = (char*)malloc(100*sizeof(char)); // stdin goes here
    char *token = (char*)malloc(maxWordsLength*sizeof(char)); // used for strtok();
    char **input2 = (char**)malloc(maxWordsInput*sizeof(char*)); // stdin split at spaces into words for processing
    for(int chungus = 0; chungus < maxWordsInput; chungus++) {
            input2[chungus] = (char*)malloc(maxWordsLength*sizeof(char));
        }
    
    int i;
    /* dealing with input end */


    /* main loop start */
    while (true) {
        // sets our input separated by word to contain all empty strings //
        for(int jupiter = 0; jupiter < maxWordsLength; jupiter++) {
            input2[jupiter] = "";
        }

        scanf("%s", input);

        /* turns input int a list of words, stored in input2 */
        char *token = strtok(input, " ");
        i = 0;
        while (token != NULL) {
            input2[i] = token;
            token = strtok(NULL, " ");
            i++;
        }

        /* input processing begins */

        // input: load actions <filename>
        if((strcmp(input2[0],"load") == 0) && (strcmp(input2[1],"actions") == 0)) {
            printf("There is currently no functionality to load a json file, or at least none implemented through WDL's interface. Thanks for trying though.\n");
        }

        // input:search action <action name>
        else if((strcmp(input2[0],"search") == 0) && (strcmp(input2[1],"action") == 0)) {
            custom_action_t *customaction = search_for_custom_action(input2[2],game);
            if(customaction == NULL) {
                printf("Custom action %s not found\n", input2[2]);
            } else {
                printf("Custom action %s found\n", input2[2]);
            }
        }

        // input: get player <level/xp/health/stats>
        else if((strcmp(input2[0],"get") == 0) && (strcmp(input2[1],"player") == 0)) {
            level = get_level(player);
            xp = get_xp(player);
            health = get_health(player);
            if(strcmp(input2[2],"stats") == 0) 
                printf("%s (Level %d) has %d health and %d xp\n", name, level, health, xp);
            else if(strcmp(input2[2],"health") == 0) printf("%s has %d health\n", name, health);
            else if(strcmp(input2[2],"xp") == 0) printf("%s has %d xp\n", name, xp);
            else if(strcmp(input2[2],"level") == 0) printf("%s is level %d\n", name, level);
            else printf("Request get player understood, but parameter was not. Please reread sandbox.txt and try again.\n");
        }

        // input: exit
        else if(strcmp(input2[0],"exit") == 0) {
            printf("Exiting sandbox\n");
            break;
        }
        
        // input: anything not listed above
        else printf("Input not understood. Please reread sandbox.txt and try again.\n");
    }
    /* main loop end */
    
    return 0;
}
