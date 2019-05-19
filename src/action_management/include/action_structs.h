#ifndef _ACTION_STRUCTS_H_
#define _ACTION_STRUCTS_H_


/* File consisting of all action structs created by action management
   =========================================================================== */


/* forward declaration of a list struct used for synonoyms
 * will be implemented in a later sprint */
typedef struct list list_t;


/* An enumeration of all supported actions.
 * KIND 1 ACTIONS - ACTION <item>
 * KIND 2 ACTIONS - ACTION <direction>
 * KIND 3 ACTIONS - ACTION <npc>
 * KIND 4 ACTIONS - ACTION <item> <npc>
 * KIND 5 ACTIONS - ACTION <item> <item>
 */
enum actions {

    // KIND 1 ACTIONS - ACTION <item>
    OPEN,
    CLOSE,
    PUSH,
    PULL,
    EXAMINE,
    TURN_ON,
    TURN_OFF,
    TAKE,    // synonyms: "pick up"
    DROP,
    CONSUME, // synonyms: "use" "drink" "eat"

    // KIND 2 ACTIONS - ACTION <direction>
    GO,      // synonyms: "walk"
    ENTER,

    // KIND 3 ACTIONS - ACTION <npc>
    TALK_TO,

    // KIND 4 ACTIONS - ACTION <item_npc>
    GIVE_TO,

    // KIND 5 ACTIONS - ACTION <item_item>
    USE_ON,
    PUT_ON
};


// Each enum corresponds to a different "KIND" of action
enum action_kind {
    ITEM = 1, // ACTION <item> i.e. Action Type 1
    DIRECTION = 2, // ACTION <direction i.e. Action Type 2
    NPC = 3, // ACTION <npc> i.e. Action Type 3
    ITEM_NPC = 4, // ACTION <item> <npc> i.e. Action Type 4
    ITEM_ITEM = 5 // ACTION <item> <item> i.e. Action Type 5
};


/* An action struct that contains the following:
 * - act: the encoded enum name for this action
 * - c_name: the 'canonical' string that should call the enum
 * - synonyms: the synonyms that would also be allowed to call action
 * - kind: an enumeration of the kind of action
*/
typedef struct {
    enum actions act;   // e.g. CONSUME
    char *c_name;  // e.g. "eat"
    list_t *synonyms;   // e.g. "drink" -> "use"
    enum action_kind kind; // e.g. KIND_1
} action_t;


#endif
