add_library(playerclass
        src/class.c
        src/class_item_restriction.c
        src/class_prefabs.c
        src/class_skills.c
        )

target_include_directories(playerclass PRIVATE src/)

# EXAMPLES
add_subdirectory(examples
                 EXCLUDE_FROM_ALL)




