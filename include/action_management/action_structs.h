#ifndef _ACTION_STRUCTS_H_
#define _ACTION_STRUCTS_H_

/* File consisting of all action structs created by action management
   =========================================================================== */

/* An enumeration of all supported actions.
 * KIND 1 ACTIONS - ACTION <item>
 * KIND 2 ACTIONS - ACTION <path>
 * KIND 3 ACTIONS - ACTION <item> <item>
 */
enum actions {
    // KIND 1 ACTIONS - ACTION <item>
    OPEN,
    CLOSE,
    PUSH,
    PULL,
    TURNON,
    TURNOFF,
    TAKE,
    PICKUP,
    DROP,
    CONSUME,
    USE,
    DRINK,
    EAT,

    // KIND 2 ACTIONS - ACTION <path>
    GO,
    WALK,

    /* KIND 3 ACTIONS - ACTION <item_item> */
    USE_ON,
    PUT,

    /* KIND 4 ACTIONS - ACTION <self> */ 
    VIEW,
};

// Each enum corresponds to a different "KIND" of action
enum action_kind {
    ITEM = 1, // ACTION <item> i.e. Action Type 1
    PATH = 2, // ACTION <path i.e. Action Type 2
    ITEM_ITEM = 3, // ACTION <item> <item> i.e. Action Type 3
    SELF = 4 //// ACTION <self> i.e. Action Type 4
};

/* Forward room declaration */
typedef struct room room_t;


/* An action struct that contains the following:
 * - c_name: the 'canonical' string that should call the enum
 * - kind: an enumeration of the kind of action
 * - room: the room that requires the action to be done before entry.
 * - direction: direction of path.
 */
typedef struct {
    char *c_name; // e.g. "eat"
    enum action_kind kind; // e.g. KIND_1
    room_t *room;
    char *direction;
} action_type_t;


/* A linked list struct that contains two components
 * - act: the data component
 * - next: the next item in the linked list
 * - trigger: room_id of the room that requires this aciton as a condition
 * This struct is primarily used in the get_supported_actions function.
*/
typedef struct list_act {
    action_type_t *act;
    struct list_act *next;
} list_action_type_t;

#endif
