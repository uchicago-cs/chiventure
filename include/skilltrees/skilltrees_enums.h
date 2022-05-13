/* This file holds enums for skilltrees */
#ifndef INCLUDE_ENUMS_H_
#define INCLUDE_ENUMS_H_
typedef enum sid {
    // Example 1
    UNLOCK_DOOR = 1000,

    // Example 2
    DEFUSE_BOMB = 1001,

    // Example 3
    CHOP_TREE = 1002,

    // Example 4
    INNER_PEACE = 1003,
} sid_t;

/* Skill type */
typedef enum skill_type {
    // Denotes active skill
    ACTIVE,

    // Denotes passive skill
    PASSIVE,

} skill_type_t;

typedef enum reader_location{
    PLAYER,

    SINGLE_TARGET,

    WORLD
} reader_location_t;

//Enums for stat reader and comparisons
typedef enum comparison {
    EQUALS,

    NOT,

    GREATER,

    LESSER,

    GREATER_EQUAL,

    LESSER_EQUAL
} comparison_t;

#endif /*SKILLTREES_ENUMS_H*/