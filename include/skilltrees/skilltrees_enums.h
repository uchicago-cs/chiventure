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
    PASSIVE

} skill_type_t;

/* Skill type */
typedef enum complex_skill_type {
    //Denotes combined complex skill
    COMBINED,

    //Denotes sequential complex skill
    SEQUENTIAL,

    //Denotes conditional complex skill
    CONDITIONAL

} complex_skill_type_t;

typedef enum reader_type{
    SINGLE_TARGET,

    WORLD,

    TIME,

    PLAYER_T

} reader_type_t;
#endif /*SKILLTREES_ENUMS_H*/