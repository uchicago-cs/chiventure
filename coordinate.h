/*
 * A two-dimensional coordinate data structure
 */

#ifndef INCLUDE_COORDINATE_H_
#define INCLUDE_COORDINATE_H_

#include <stdbool.h>
#include "common.h"

/* A coordinate in two-dimensional space */
typedef struct {
    double x;
    double y;
} coordinate_t;

#endif /* INCLUDE_COORDINATE_H_ */