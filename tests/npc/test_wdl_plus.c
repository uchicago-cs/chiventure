#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "libobj/load.h"
#include "../tests/wdl/test_wdl.h"
#include "wdl/load_quests.h"
#include "wdl/load_game.h"
#include "quests/quests_state.h"

#define NPC_WDL_PATH "../../../src/npc/examples/pokemon_plus.wdl"

/* Verifies that the example file, which covers every parsing possibility, is parsed correctly */
Test(quests_wdl, all_encompassing_example) {
    obj_t *doc = __get_doc_obj("DEFAULT.json", NPC_WDL_PATH);

    game_t *game = load_game(doc);
}
