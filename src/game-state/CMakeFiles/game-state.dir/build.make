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
CMAKE_SOURCE_DIR = /home/maggiex/cs220/chiventure

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/maggiex/cs220/chiventure

# Include any dependencies generated for this target.
include src/game-state/CMakeFiles/game-state.dir/depend.make

# Include the progress variables for this target.
include src/game-state/CMakeFiles/game-state.dir/progress.make

# Include the compile flags for this target's objects.
include src/game-state/CMakeFiles/game-state.dir/flags.make

src/game-state/CMakeFiles/game-state.dir/src/game.c.o: src/game-state/CMakeFiles/game-state.dir/flags.make
src/game-state/CMakeFiles/game-state.dir/src/game.c.o: src/game-state/src/game.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maggiex/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/game-state/CMakeFiles/game-state.dir/src/game.c.o"
	cd /home/maggiex/cs220/chiventure/src/game-state && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/game-state.dir/src/game.c.o   -c /home/maggiex/cs220/chiventure/src/game-state/src/game.c

src/game-state/CMakeFiles/game-state.dir/src/game.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/game-state.dir/src/game.c.i"
	cd /home/maggiex/cs220/chiventure/src/game-state && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/maggiex/cs220/chiventure/src/game-state/src/game.c > CMakeFiles/game-state.dir/src/game.c.i

src/game-state/CMakeFiles/game-state.dir/src/game.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/game-state.dir/src/game.c.s"
	cd /home/maggiex/cs220/chiventure/src/game-state && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/maggiex/cs220/chiventure/src/game-state/src/game.c -o CMakeFiles/game-state.dir/src/game.c.s

src/game-state/CMakeFiles/game-state.dir/src/game_action.c.o: src/game-state/CMakeFiles/game-state.dir/flags.make
src/game-state/CMakeFiles/game-state.dir/src/game_action.c.o: src/game-state/src/game_action.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maggiex/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/game-state/CMakeFiles/game-state.dir/src/game_action.c.o"
	cd /home/maggiex/cs220/chiventure/src/game-state && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/game-state.dir/src/game_action.c.o   -c /home/maggiex/cs220/chiventure/src/game-state/src/game_action.c

src/game-state/CMakeFiles/game-state.dir/src/game_action.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/game-state.dir/src/game_action.c.i"
	cd /home/maggiex/cs220/chiventure/src/game-state && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/maggiex/cs220/chiventure/src/game-state/src/game_action.c > CMakeFiles/game-state.dir/src/game_action.c.i

src/game-state/CMakeFiles/game-state.dir/src/game_action.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/game-state.dir/src/game_action.c.s"
	cd /home/maggiex/cs220/chiventure/src/game-state && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/maggiex/cs220/chiventure/src/game-state/src/game_action.c -o CMakeFiles/game-state.dir/src/game_action.c.s

src/game-state/CMakeFiles/game-state.dir/src/item.c.o: src/game-state/CMakeFiles/game-state.dir/flags.make
src/game-state/CMakeFiles/game-state.dir/src/item.c.o: src/game-state/src/item.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maggiex/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object src/game-state/CMakeFiles/game-state.dir/src/item.c.o"
	cd /home/maggiex/cs220/chiventure/src/game-state && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/game-state.dir/src/item.c.o   -c /home/maggiex/cs220/chiventure/src/game-state/src/item.c

src/game-state/CMakeFiles/game-state.dir/src/item.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/game-state.dir/src/item.c.i"
	cd /home/maggiex/cs220/chiventure/src/game-state && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/maggiex/cs220/chiventure/src/game-state/src/item.c > CMakeFiles/game-state.dir/src/item.c.i

src/game-state/CMakeFiles/game-state.dir/src/item.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/game-state.dir/src/item.c.s"
	cd /home/maggiex/cs220/chiventure/src/game-state && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/maggiex/cs220/chiventure/src/game-state/src/item.c -o CMakeFiles/game-state.dir/src/item.c.s

src/game-state/CMakeFiles/game-state.dir/src/mode.c.o: src/game-state/CMakeFiles/game-state.dir/flags.make
src/game-state/CMakeFiles/game-state.dir/src/mode.c.o: src/game-state/src/mode.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maggiex/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object src/game-state/CMakeFiles/game-state.dir/src/mode.c.o"
	cd /home/maggiex/cs220/chiventure/src/game-state && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/game-state.dir/src/mode.c.o   -c /home/maggiex/cs220/chiventure/src/game-state/src/mode.c

src/game-state/CMakeFiles/game-state.dir/src/mode.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/game-state.dir/src/mode.c.i"
	cd /home/maggiex/cs220/chiventure/src/game-state && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/maggiex/cs220/chiventure/src/game-state/src/mode.c > CMakeFiles/game-state.dir/src/mode.c.i

src/game-state/CMakeFiles/game-state.dir/src/mode.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/game-state.dir/src/mode.c.s"
	cd /home/maggiex/cs220/chiventure/src/game-state && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/maggiex/cs220/chiventure/src/game-state/src/mode.c -o CMakeFiles/game-state.dir/src/mode.c.s

src/game-state/CMakeFiles/game-state.dir/src/path.c.o: src/game-state/CMakeFiles/game-state.dir/flags.make
src/game-state/CMakeFiles/game-state.dir/src/path.c.o: src/game-state/src/path.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maggiex/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object src/game-state/CMakeFiles/game-state.dir/src/path.c.o"
	cd /home/maggiex/cs220/chiventure/src/game-state && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/game-state.dir/src/path.c.o   -c /home/maggiex/cs220/chiventure/src/game-state/src/path.c

src/game-state/CMakeFiles/game-state.dir/src/path.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/game-state.dir/src/path.c.i"
	cd /home/maggiex/cs220/chiventure/src/game-state && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/maggiex/cs220/chiventure/src/game-state/src/path.c > CMakeFiles/game-state.dir/src/path.c.i

src/game-state/CMakeFiles/game-state.dir/src/path.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/game-state.dir/src/path.c.s"
	cd /home/maggiex/cs220/chiventure/src/game-state && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/maggiex/cs220/chiventure/src/game-state/src/path.c -o CMakeFiles/game-state.dir/src/path.c.s

src/game-state/CMakeFiles/game-state.dir/src/player.c.o: src/game-state/CMakeFiles/game-state.dir/flags.make
src/game-state/CMakeFiles/game-state.dir/src/player.c.o: src/game-state/src/player.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maggiex/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object src/game-state/CMakeFiles/game-state.dir/src/player.c.o"
	cd /home/maggiex/cs220/chiventure/src/game-state && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/game-state.dir/src/player.c.o   -c /home/maggiex/cs220/chiventure/src/game-state/src/player.c

src/game-state/CMakeFiles/game-state.dir/src/player.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/game-state.dir/src/player.c.i"
	cd /home/maggiex/cs220/chiventure/src/game-state && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/maggiex/cs220/chiventure/src/game-state/src/player.c > CMakeFiles/game-state.dir/src/player.c.i

src/game-state/CMakeFiles/game-state.dir/src/player.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/game-state.dir/src/player.c.s"
	cd /home/maggiex/cs220/chiventure/src/game-state && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/maggiex/cs220/chiventure/src/game-state/src/player.c -o CMakeFiles/game-state.dir/src/player.c.s

src/game-state/CMakeFiles/game-state.dir/src/room.c.o: src/game-state/CMakeFiles/game-state.dir/flags.make
src/game-state/CMakeFiles/game-state.dir/src/room.c.o: src/game-state/src/room.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maggiex/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object src/game-state/CMakeFiles/game-state.dir/src/room.c.o"
	cd /home/maggiex/cs220/chiventure/src/game-state && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/game-state.dir/src/room.c.o   -c /home/maggiex/cs220/chiventure/src/game-state/src/room.c

src/game-state/CMakeFiles/game-state.dir/src/room.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/game-state.dir/src/room.c.i"
	cd /home/maggiex/cs220/chiventure/src/game-state && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/maggiex/cs220/chiventure/src/game-state/src/room.c > CMakeFiles/game-state.dir/src/room.c.i

src/game-state/CMakeFiles/game-state.dir/src/room.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/game-state.dir/src/room.c.s"
	cd /home/maggiex/cs220/chiventure/src/game-state && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/maggiex/cs220/chiventure/src/game-state/src/room.c -o CMakeFiles/game-state.dir/src/room.c.s

src/game-state/CMakeFiles/game-state.dir/src/stats.c.o: src/game-state/CMakeFiles/game-state.dir/flags.make
src/game-state/CMakeFiles/game-state.dir/src/stats.c.o: src/game-state/src/stats.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maggiex/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object src/game-state/CMakeFiles/game-state.dir/src/stats.c.o"
	cd /home/maggiex/cs220/chiventure/src/game-state && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/game-state.dir/src/stats.c.o   -c /home/maggiex/cs220/chiventure/src/game-state/src/stats.c

src/game-state/CMakeFiles/game-state.dir/src/stats.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/game-state.dir/src/stats.c.i"
	cd /home/maggiex/cs220/chiventure/src/game-state && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/maggiex/cs220/chiventure/src/game-state/src/stats.c > CMakeFiles/game-state.dir/src/stats.c.i

src/game-state/CMakeFiles/game-state.dir/src/stats.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/game-state.dir/src/stats.c.s"
	cd /home/maggiex/cs220/chiventure/src/game-state && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/maggiex/cs220/chiventure/src/game-state/src/stats.c -o CMakeFiles/game-state.dir/src/stats.c.s

src/game-state/CMakeFiles/game-state.dir/src/condition.c.o: src/game-state/CMakeFiles/game-state.dir/flags.make
src/game-state/CMakeFiles/game-state.dir/src/condition.c.o: src/game-state/src/condition.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maggiex/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object src/game-state/CMakeFiles/game-state.dir/src/condition.c.o"
	cd /home/maggiex/cs220/chiventure/src/game-state && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/game-state.dir/src/condition.c.o   -c /home/maggiex/cs220/chiventure/src/game-state/src/condition.c

src/game-state/CMakeFiles/game-state.dir/src/condition.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/game-state.dir/src/condition.c.i"
	cd /home/maggiex/cs220/chiventure/src/game-state && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/maggiex/cs220/chiventure/src/game-state/src/condition.c > CMakeFiles/game-state.dir/src/condition.c.i

src/game-state/CMakeFiles/game-state.dir/src/condition.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/game-state.dir/src/condition.c.s"
	cd /home/maggiex/cs220/chiventure/src/game-state && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/maggiex/cs220/chiventure/src/game-state/src/condition.c -o CMakeFiles/game-state.dir/src/condition.c.s

# Object files for target game-state
game__state_OBJECTS = \
"CMakeFiles/game-state.dir/src/game.c.o" \
"CMakeFiles/game-state.dir/src/game_action.c.o" \
"CMakeFiles/game-state.dir/src/item.c.o" \
"CMakeFiles/game-state.dir/src/mode.c.o" \
"CMakeFiles/game-state.dir/src/path.c.o" \
"CMakeFiles/game-state.dir/src/player.c.o" \
"CMakeFiles/game-state.dir/src/room.c.o" \
"CMakeFiles/game-state.dir/src/stats.c.o" \
"CMakeFiles/game-state.dir/src/condition.c.o"

# External object files for target game-state
game__state_EXTERNAL_OBJECTS =

src/game-state/libgame-state.a: src/game-state/CMakeFiles/game-state.dir/src/game.c.o
src/game-state/libgame-state.a: src/game-state/CMakeFiles/game-state.dir/src/game_action.c.o
src/game-state/libgame-state.a: src/game-state/CMakeFiles/game-state.dir/src/item.c.o
src/game-state/libgame-state.a: src/game-state/CMakeFiles/game-state.dir/src/mode.c.o
src/game-state/libgame-state.a: src/game-state/CMakeFiles/game-state.dir/src/path.c.o
src/game-state/libgame-state.a: src/game-state/CMakeFiles/game-state.dir/src/player.c.o
src/game-state/libgame-state.a: src/game-state/CMakeFiles/game-state.dir/src/room.c.o
src/game-state/libgame-state.a: src/game-state/CMakeFiles/game-state.dir/src/stats.c.o
src/game-state/libgame-state.a: src/game-state/CMakeFiles/game-state.dir/src/condition.c.o
src/game-state/libgame-state.a: src/game-state/CMakeFiles/game-state.dir/build.make
src/game-state/libgame-state.a: src/game-state/CMakeFiles/game-state.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/maggiex/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking C static library libgame-state.a"
	cd /home/maggiex/cs220/chiventure/src/game-state && $(CMAKE_COMMAND) -P CMakeFiles/game-state.dir/cmake_clean_target.cmake
	cd /home/maggiex/cs220/chiventure/src/game-state && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/game-state.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/game-state/CMakeFiles/game-state.dir/build: src/game-state/libgame-state.a

.PHONY : src/game-state/CMakeFiles/game-state.dir/build

src/game-state/CMakeFiles/game-state.dir/clean:
	cd /home/maggiex/cs220/chiventure/src/game-state && $(CMAKE_COMMAND) -P CMakeFiles/game-state.dir/cmake_clean.cmake
.PHONY : src/game-state/CMakeFiles/game-state.dir/clean

src/game-state/CMakeFiles/game-state.dir/depend:
	cd /home/maggiex/cs220/chiventure && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/maggiex/cs220/chiventure /home/maggiex/cs220/chiventure/src/game-state /home/maggiex/cs220/chiventure /home/maggiex/cs220/chiventure/src/game-state /home/maggiex/cs220/chiventure/src/game-state/CMakeFiles/game-state.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/game-state/CMakeFiles/game-state.dir/depend

