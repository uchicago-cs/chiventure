project(chiventure)
cmake_minimum_required(VERSION 3.12)

add_library(playerclass
	    sandbox/player.c)

target_include_directories(playerclass PRIVATE sandbox/)

target_link_libraries(playerclass checkpointing)
target_link_libraries(playerclass action_management)
target_link_libraries(playerclass ui)
target_link_libraries(playerclass game-state)
target_link_libraries(playerclass common)
