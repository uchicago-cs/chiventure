#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "read_gdl.h"


/* Checks that new_statistics_display_t properly mallocs and inits values
 * for a statistics_display_t struct */
Test(statistics, new)
{
    stats_global_t *global_stat = stats_global_new("Health",10.0);
    stats_t *stat = stats_new(global_stat,10.0);    

    corner c = TOP_LEFT;
    mode m = NUMERICAL;
    unsigned int num_stat = 1;
    
    statistics_display_t *stats;
    stats = new_statistics_display(c,stat,num_stat,m);

    cr_assert_not_null(stats,"new__statistics_display() failed");
    
    cr_assert_eq(stats->corner,TOP_LEFT,
                "new_statistics_display() didn't set corner");
    cr_assert_eq(stats->mode,NUMERICAL,
                "new_statistics_display() didn't set mode");
    cr_assert_eq(stats->num_statistics,1,
                "new_statistics_display() didn't set num_statistics");
    cr_assert_eq(stats->statistics->max,10,
                "new_statistics_display() didn't set stats_t field");
}


/* Checks that init_statistics_display properly inits values for a 
 * statistics_display_t struct */
Test(statistics, init)
{
    stats_global_t *global_stat = stats_global_new("Health", 10.0);
    stats_t *stat = stats_new(global_stat,10.0);

    corner c = TOP_LEFT;
    mode m = NUMERICAL;
    unsigned int num_stat = 1;

    statistics_display_t stats;
    int rc;

    rc = init_statistics_display(&stats,c,stat,num_stat,m);

    cr_assert_eq(rc, SUCCESS,"init_statistics_display() failed");

    cr_assert_eq(stats.corner,TOP_LEFT,
                "init_statistics_display() didn't set corner");
    cr_assert_eq(stats.mode,NUMERICAL,
                "init_statistics_display() didn't set mode");
    cr_assert_eq(stats.num_statistics, 1,
                "init_statistics_display() didn't set num_statistics");
}


/* Checks that free_statistics_display() properly frees memory used for
 * statistics_display_t struct */
Test(statistics, free)
{
    int rc;
    stats_global_t *global_stat = stats_global_new("Health",10.0);              
    stats_t *stat = stats_new(global_stat,10.0);                                
                                                                                 
    corner c = TOP_LEFT;                                                        
    mode m = NUMERICAL;                                                         
    unsigned int num_stat = 1;                                                  
                                                                               
    statistics_display_t *stats;                                                
    stats = new_statistics_display(c,stat,num_stat,m);                         
                                                                                 
    cr_assert_not_null(stats,"new_statistics_display() failed"); 

    rc = free_statistics_display(stats);

    cr_assert_eq(rc,SUCCESS,"free_statistics_display() failed");
}
