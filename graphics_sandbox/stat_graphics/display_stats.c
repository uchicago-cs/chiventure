#include "ui/display_stats.h"
#include "raylib.h"

/* See display_stats.h for details */
screen_stats_t* new_screen_stats(int ulx, int uly, int lrx, int lry, int num_stats, on-screen_stat *stats)
{
    screen_stats_t *screen;
    int rc;

    screen = malloc(sizeof(screen_stats_t));
    
    if (screen == NULL){
        fprintf(stderr, "Could not allocate memory");
        return NULL;
    }

    rc = init_screen_stats(screen,ulx,uly,lrx,lry,num_stats,stats);
    
    if (rc != SUCCESS){
        fprintf(stderr, "Could not initialize screen_stats_t");
        return NULL;
    }
    
    return screen;
}

/* See display_stats.h for details */
int init_screen_stats(screen_stats_t *screen, int ulx, int uly, int lrx, 
                      int lry, int num_stats, on_screen_stat *stats)
{
    assert(screen != NULL);
    
    screen->ulx = ulx;
    screen->uly = uly;
    screen->lrx = lrx;
    screen->lry = lry;

    screen->num_stats = num_stats;
    
    screen->screen_stats = stats;

    return SUCCESS;
}


/* See display_stats.h for details */
int free_screen_stats(screen_stats_t *screen);

/* See display_stats.h for details */
int draw_screen_stats(screen_stats_t *screen_stats);

/* See display_stats.h for details */
screen_stats_t* update_screen_stats(player_t *player, screen_stats_t *screen_stats);

/* See display_stats.h for details */
pop-up_t* new_pop-up(int ulx, int uly, int lrx, int lry,
                      pop-up_type type, player_t *player)
{
    pop_up_t *pop_up;
    int rc;

    pop_up = malloc(sizeof(pop_up_t));

    if (pop_up == NULL){
        fprintf(stderr, "Could not allocate memory");
        return NULL;
    }

    rc = init_pop_up(pop_up, ulx,uly,lrx,lry,type,player);  

    if (rc != SUCCESS){
        fprintf(stderr, "Could not initialize slot_t");
        return NULL;
    }
    
    return pop_up;
}
 
/* See display_stats.h for details */
int init_pop_up(pop_up_t *pop_up, int ulx, int uly, int lrx, int lry, 
                pop_up_type type, player_t *player)
{
    assert(pop_up != NULL);
    
    pop_up->ulx = ulx;
    pop_up->uly = uly;
    pop_up->lrx = lrx;
    pop_up->lry = lry;

    pop_up->type = type;

    pop_up->player = player;
    
    return SUCCESS;
}

/* See display_stats.h for details */
int free_pop_up(pop_up_t *pop_up)
{
    free(pop_up->player);
    free(pop_up);

    return SUCCESS;
}

/* See display_stats.h for details */
int open_pop-up(pop-up_t pop-up);

/* See display_stats.h for details */
int close_pop-up();
