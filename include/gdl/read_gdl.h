/*
 * This is a Graphics Description Language
 * reading device
 *
 * Authors can describe preferred graphical
 * styles and features by writing a "GDL"
 * file in JSON format according to a set
 * of just a few rules
 */


/* The set of background colors availible for the inventory */
typedef enum color {
    WHITE,
    GRAY,
    BLACK,
    RED,
    BLUE,
    GREEN,
    YELLOW,
    ORANGE,
    PURPLE,
    PINK,
} color;


/* 
 * This display struct contains the custom inventory 
 * represenation specified by the game developer with 
 * a set of rows and columns and a background color
 */
typedef struct inventory_display {
    unsigned int rows;
    unsigned int columns;
    color color;
} inventory_display_t;


/* 
 * Defines a large struct that contains all of the information
 * specified by the game developer in the GDL file by category
 */
typedef struct graphics {
    inventory_display_t
} graphics_t;


inventory_display_t init_inventory_display(graphics_t *graphics);


void free_inventory_display(inventory_display_t *inventory_display);
