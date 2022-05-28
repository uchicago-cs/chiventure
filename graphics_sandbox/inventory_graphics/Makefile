test_inventory_graphics: test_inventory_graphics.c inventory_graphics.c
	cc test_inventory_graphics.c ../../src/game-state/src/room.c ../../src/quests/src/quests_state.c ../../src/game-state/src/condition.c inventory_graphics.c ../../src/game-state/src/game.c ../../src/game-state/src/game_action.c ../../src/skilltrees/src/skilltrees_common.c ../../src/cli/src/util.c ../../src/skilltrees/src/inventory.c ../../src/game-state/src/stats.c ../../src/game-state/src/player.c ../../src/game-state/src/item.c -framework IOKit -framework Cocoa -framework OpenGL `pkg-config --libs --cflags raylib` -I../../include/ -I../gdl/read_gdl.h -o test_inventory_graphics -lcriterion

clean:
	rm inventory_graphics test_inventory_graphics
