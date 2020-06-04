/* Implementations of the item struct */
#include "common/uthash.h"
#include "game-state/room.h"
#include "openworld/default_items.h"

/* see default_items.h */
item_hash_t *get_default_items()
{

    item_hash_t *hash = NULL;

    item_t *hat = item_new("hat", "a top hat",
                           "A black top hat with monogrammed A. L.");
    HASH_ADD_STR(hash, item_id, hat);

    item_t *apple = item_new("apple", "a red apple",
                             "A juicy Red Delicious apple");
    HASH_ADD_STR(hash, item_id, apple);

    item_t *cow = item_new("cow", "A black and white cow",
                           "A black and white cow called Mavis");
    HASH_ADD_STR(hash, item_id, cow);

    item_t *fruit = item_new("fruit", "a bowl of fruit",
                             "A bowl of fruit resting on a surface");
    HASH_ADD_STR(hash, item_id, fruit);

    item_t *ladder = item_new("ladder", "a wood ladder",
                              "A wooden ladder with 5 rungs resting on a door");
    HASH_ADD_STR(hash, item_id, ladder);

    item_t *yam = item_new("yam", "a rotting yam",
                           "A singular rotting yam with flies flying around");
    HASH_ADD_STR(hash, item_id, yam);

    item_t *ice = item_new("ice", "a bag of ice",
                           "A bag of crunchy ice");
    HASH_ADD_STR(hash, item_id, ice);

    item_t *jug = item_new("jug", "a brown jug",
                           "A brown jug with something inside");
    HASH_ADD_STR(hash, item_id, jug);

    item_t *tray = item_new("tray", "a red plastic tray",
                            "A red plastic tray with some ketchup stains");
    HASH_ADD_STR(hash, item_id, tray);

    item_t *book = item_new("book", "a worn old book",
                            "A green book titled 'Survival Instincts'");
    HASH_ADD_STR(hash, item_id, book);

    item_t *door = item_new("door", "a normal door",
                            "A wooden door with a worn doorknob");
    HASH_ADD_STR(hash, item_id, door);

    item_t *pencil = item_new("pencil", "a no.2 pencil",
                              "A sharpened no.2 yellow pencil");
    HASH_ADD_STR(hash, item_id,pencil);

    item_t *quill = item_new("quill", "a quail quill",
                             "A quail quill in a pot of black ink");
    HASH_ADD_STR(hash, item_id, quill);

    item_t *watercolors = item_new("watercolors",
                                   "a set of watercolors with brush",
                                   "Used watercolors and dusty brush");
    HASH_ADD_STR(hash, item_id, watercolors);

    item_t *nail = item_new("nail", "a normal nail",
                            "A regular metail nail");
    HASH_ADD_STR(hash, item_id, nail);

    item_t *gold = item_new("gold", "three gold coins",
                            "Three shiny gold coins the size of your eye");
    HASH_ADD_STR(hash, item_id, gold);

    item_t *eagle = item_new("eagle", "a bald eagle",
                             "A bald eagle calmly perched on a ledge nearby");
    HASH_ADD_STR(hash, item_id, eagle);

    item_t *umbrella = item_new("umbrella", "a black umbrella",
                                "A black polyester umbrella with M.P. initials");
    HASH_ADD_STR(hash, item_id, umbrella);

    item_t *rabbit = item_new("rabbit", "a white rabbit",
                              "A live, fluffy white rabbit hiding in the corner");
    HASH_ADD_STR(hash, item_id, rabbit);

    item_t *zebra = item_new("zebra", "a small zebra",
                             "A small zebra calmly munching on some grass");
    HASH_ADD_STR(hash, item_id, zebra);

    item_t *mirror = item_new("mirror", "an oval mirror",
                              "A dusty oval mirror with one big crack");
    HASH_ADD_STR(hash, item_id, mirror);

    item_t *kettle = item_new("kettle", "a black kettle",
                              "A black kettle on a stove");
    HASH_ADD_STR(hash, item_id,kettle);

    item_t *olive = item_new("olive", "a black olive",
                             "A singular, unrefrigerated black olive");
    HASH_ADD_STR(hash, item_id, olive);

    item_t *video = item_new("video", "a dvd video",
                             "A DVD video with an illegible label");
    HASH_ADD_STR(hash, item_id, video);

    item_t *xylophone = item_new("xylophone", "a colorful xylophone",
                                 "A children's xylophone with a pair of mallets");
    HASH_ADD_STR(hash, item_id, xylophone);

    return hash;
}
