# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/wellingtj/Desktop/cs220/chiventure

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wellingtj/Desktop/cs220/chiventure

# Utility rule file for npc-examples.

# Include the progress variables for this target.
include src/npc/examples/CMakeFiles/npc-examples.dir/progress.make

src/npc/examples/CMakeFiles/npc-examples: src/npc/examples/dialogue_example
src/npc/examples/CMakeFiles/npc-examples: src/npc/examples/npc_example
src/npc/examples/CMakeFiles/npc-examples: src/npc/examples/conversation_mode_example
src/npc/examples/CMakeFiles/npc-examples: src/npc/examples/battle_move_example_2021


npc-examples: src/npc/examples/CMakeFiles/npc-examples
npc-examples: src/npc/examples/CMakeFiles/npc-examples.dir/build.make

.PHONY : npc-examples

# Rule to build all files generated by this target.
src/npc/examples/CMakeFiles/npc-examples.dir/build: npc-examples

.PHONY : src/npc/examples/CMakeFiles/npc-examples.dir/build

src/npc/examples/CMakeFiles/npc-examples.dir/clean:
	cd /home/wellingtj/Desktop/cs220/chiventure/src/npc/examples && $(CMAKE_COMMAND) -P CMakeFiles/npc-examples.dir/cmake_clean.cmake
.PHONY : src/npc/examples/CMakeFiles/npc-examples.dir/clean

src/npc/examples/CMakeFiles/npc-examples.dir/depend:
	cd /home/wellingtj/Desktop/cs220/chiventure && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wellingtj/Desktop/cs220/chiventure /home/wellingtj/Desktop/cs220/chiventure/src/npc/examples /home/wellingtj/Desktop/cs220/chiventure /home/wellingtj/Desktop/cs220/chiventure/src/npc/examples /home/wellingtj/Desktop/cs220/chiventure/src/npc/examples/CMakeFiles/npc-examples.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/npc/examples/CMakeFiles/npc-examples.dir/depend

