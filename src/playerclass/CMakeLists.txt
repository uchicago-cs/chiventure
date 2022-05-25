add_library(playerclass
        src/class.c
        src/class_item.c
        src/class_prefabs.c
        src/multiclass.c
        )

target_include_directories(playerclass PRIVATE src/)

# EXAMPLES
add_subdirectory(examples
                 EXCLUDE_FROM_ALL)




