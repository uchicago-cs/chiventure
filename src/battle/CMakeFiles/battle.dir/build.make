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

# Include any dependencies generated for this target.
include src/battle/CMakeFiles/battle.dir/depend.make

# Include the progress variables for this target.
include src/battle/CMakeFiles/battle.dir/progress.make

# Include the compile flags for this target's objects.
include src/battle/CMakeFiles/battle.dir/flags.make

src/battle/CMakeFiles/battle.dir/src/battle_move_maker.c.o: src/battle/CMakeFiles/battle.dir/flags.make
src/battle/CMakeFiles/battle.dir/src/battle_move_maker.c.o: src/battle/src/battle_move_maker.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wellingtj/Desktop/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/battle/CMakeFiles/battle.dir/src/battle_move_maker.c.o"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/battle && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/battle.dir/src/battle_move_maker.c.o   -c /home/wellingtj/Desktop/cs220/chiventure/src/battle/src/battle_move_maker.c

src/battle/CMakeFiles/battle.dir/src/battle_move_maker.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/battle.dir/src/battle_move_maker.c.i"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/battle && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wellingtj/Desktop/cs220/chiventure/src/battle/src/battle_move_maker.c > CMakeFiles/battle.dir/src/battle_move_maker.c.i

src/battle/CMakeFiles/battle.dir/src/battle_move_maker.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/battle.dir/src/battle_move_maker.c.s"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/battle && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wellingtj/Desktop/cs220/chiventure/src/battle/src/battle_move_maker.c -o CMakeFiles/battle.dir/src/battle_move_maker.c.s

src/battle/CMakeFiles/battle.dir/src/battle_ai.c.o: src/battle/CMakeFiles/battle.dir/flags.make
src/battle/CMakeFiles/battle.dir/src/battle_ai.c.o: src/battle/src/battle_ai.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wellingtj/Desktop/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/battle/CMakeFiles/battle.dir/src/battle_ai.c.o"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/battle && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/battle.dir/src/battle_ai.c.o   -c /home/wellingtj/Desktop/cs220/chiventure/src/battle/src/battle_ai.c

src/battle/CMakeFiles/battle.dir/src/battle_ai.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/battle.dir/src/battle_ai.c.i"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/battle && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wellingtj/Desktop/cs220/chiventure/src/battle/src/battle_ai.c > CMakeFiles/battle.dir/src/battle_ai.c.i

src/battle/CMakeFiles/battle.dir/src/battle_ai.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/battle.dir/src/battle_ai.c.s"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/battle && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wellingtj/Desktop/cs220/chiventure/src/battle/src/battle_ai.c -o CMakeFiles/battle.dir/src/battle_ai.c.s

src/battle/CMakeFiles/battle.dir/src/battle_logic.c.o: src/battle/CMakeFiles/battle.dir/flags.make
src/battle/CMakeFiles/battle.dir/src/battle_logic.c.o: src/battle/src/battle_logic.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wellingtj/Desktop/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object src/battle/CMakeFiles/battle.dir/src/battle_logic.c.o"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/battle && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/battle.dir/src/battle_logic.c.o   -c /home/wellingtj/Desktop/cs220/chiventure/src/battle/src/battle_logic.c

src/battle/CMakeFiles/battle.dir/src/battle_logic.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/battle.dir/src/battle_logic.c.i"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/battle && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wellingtj/Desktop/cs220/chiventure/src/battle/src/battle_logic.c > CMakeFiles/battle.dir/src/battle_logic.c.i

src/battle/CMakeFiles/battle.dir/src/battle_logic.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/battle.dir/src/battle_logic.c.s"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/battle && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wellingtj/Desktop/cs220/chiventure/src/battle/src/battle_logic.c -o CMakeFiles/battle.dir/src/battle_logic.c.s

src/battle/CMakeFiles/battle.dir/src/battle_state.c.o: src/battle/CMakeFiles/battle.dir/flags.make
src/battle/CMakeFiles/battle.dir/src/battle_state.c.o: src/battle/src/battle_state.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wellingtj/Desktop/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object src/battle/CMakeFiles/battle.dir/src/battle_state.c.o"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/battle && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/battle.dir/src/battle_state.c.o   -c /home/wellingtj/Desktop/cs220/chiventure/src/battle/src/battle_state.c

src/battle/CMakeFiles/battle.dir/src/battle_state.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/battle.dir/src/battle_state.c.i"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/battle && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wellingtj/Desktop/cs220/chiventure/src/battle/src/battle_state.c > CMakeFiles/battle.dir/src/battle_state.c.i

src/battle/CMakeFiles/battle.dir/src/battle_state.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/battle.dir/src/battle_state.c.s"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/battle && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wellingtj/Desktop/cs220/chiventure/src/battle/src/battle_state.c -o CMakeFiles/battle.dir/src/battle_state.c.s

src/battle/CMakeFiles/battle.dir/src/battle_flow.c.o: src/battle/CMakeFiles/battle.dir/flags.make
src/battle/CMakeFiles/battle.dir/src/battle_flow.c.o: src/battle/src/battle_flow.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wellingtj/Desktop/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object src/battle/CMakeFiles/battle.dir/src/battle_flow.c.o"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/battle && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/battle.dir/src/battle_flow.c.o   -c /home/wellingtj/Desktop/cs220/chiventure/src/battle/src/battle_flow.c

src/battle/CMakeFiles/battle.dir/src/battle_flow.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/battle.dir/src/battle_flow.c.i"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/battle && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wellingtj/Desktop/cs220/chiventure/src/battle/src/battle_flow.c > CMakeFiles/battle.dir/src/battle_flow.c.i

src/battle/CMakeFiles/battle.dir/src/battle_flow.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/battle.dir/src/battle_flow.c.s"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/battle && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wellingtj/Desktop/cs220/chiventure/src/battle/src/battle_flow.c -o CMakeFiles/battle.dir/src/battle_flow.c.s

src/battle/CMakeFiles/battle.dir/src/battle_flow_structs.c.o: src/battle/CMakeFiles/battle.dir/flags.make
src/battle/CMakeFiles/battle.dir/src/battle_flow_structs.c.o: src/battle/src/battle_flow_structs.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wellingtj/Desktop/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object src/battle/CMakeFiles/battle.dir/src/battle_flow_structs.c.o"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/battle && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/battle.dir/src/battle_flow_structs.c.o   -c /home/wellingtj/Desktop/cs220/chiventure/src/battle/src/battle_flow_structs.c

src/battle/CMakeFiles/battle.dir/src/battle_flow_structs.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/battle.dir/src/battle_flow_structs.c.i"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/battle && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wellingtj/Desktop/cs220/chiventure/src/battle/src/battle_flow_structs.c > CMakeFiles/battle.dir/src/battle_flow_structs.c.i

src/battle/CMakeFiles/battle.dir/src/battle_flow_structs.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/battle.dir/src/battle_flow_structs.c.s"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/battle && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wellingtj/Desktop/cs220/chiventure/src/battle/src/battle_flow_structs.c -o CMakeFiles/battle.dir/src/battle_flow_structs.c.s

src/battle/CMakeFiles/battle.dir/src/battle_moves.c.o: src/battle/CMakeFiles/battle.dir/flags.make
src/battle/CMakeFiles/battle.dir/src/battle_moves.c.o: src/battle/src/battle_moves.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wellingtj/Desktop/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object src/battle/CMakeFiles/battle.dir/src/battle_moves.c.o"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/battle && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/battle.dir/src/battle_moves.c.o   -c /home/wellingtj/Desktop/cs220/chiventure/src/battle/src/battle_moves.c

src/battle/CMakeFiles/battle.dir/src/battle_moves.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/battle.dir/src/battle_moves.c.i"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/battle && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wellingtj/Desktop/cs220/chiventure/src/battle/src/battle_moves.c > CMakeFiles/battle.dir/src/battle_moves.c.i

src/battle/CMakeFiles/battle.dir/src/battle_moves.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/battle.dir/src/battle_moves.c.s"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/battle && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wellingtj/Desktop/cs220/chiventure/src/battle/src/battle_moves.c -o CMakeFiles/battle.dir/src/battle_moves.c.s

src/battle/CMakeFiles/battle.dir/__/playerclass/examples/class-list.c.o: src/battle/CMakeFiles/battle.dir/flags.make
src/battle/CMakeFiles/battle.dir/__/playerclass/examples/class-list.c.o: src/playerclass/examples/class-list.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wellingtj/Desktop/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object src/battle/CMakeFiles/battle.dir/__/playerclass/examples/class-list.c.o"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/battle && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/battle.dir/__/playerclass/examples/class-list.c.o   -c /home/wellingtj/Desktop/cs220/chiventure/src/playerclass/examples/class-list.c

src/battle/CMakeFiles/battle.dir/__/playerclass/examples/class-list.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/battle.dir/__/playerclass/examples/class-list.c.i"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/battle && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wellingtj/Desktop/cs220/chiventure/src/playerclass/examples/class-list.c > CMakeFiles/battle.dir/__/playerclass/examples/class-list.c.i

src/battle/CMakeFiles/battle.dir/__/playerclass/examples/class-list.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/battle.dir/__/playerclass/examples/class-list.c.s"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/battle && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wellingtj/Desktop/cs220/chiventure/src/playerclass/examples/class-list.c -o CMakeFiles/battle.dir/__/playerclass/examples/class-list.c.s

src/battle/CMakeFiles/battle.dir/src/battle_print.c.o: src/battle/CMakeFiles/battle.dir/flags.make
src/battle/CMakeFiles/battle.dir/src/battle_print.c.o: src/battle/src/battle_print.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wellingtj/Desktop/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object src/battle/CMakeFiles/battle.dir/src/battle_print.c.o"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/battle && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/battle.dir/src/battle_print.c.o   -c /home/wellingtj/Desktop/cs220/chiventure/src/battle/src/battle_print.c

src/battle/CMakeFiles/battle.dir/src/battle_print.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/battle.dir/src/battle_print.c.i"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/battle && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wellingtj/Desktop/cs220/chiventure/src/battle/src/battle_print.c > CMakeFiles/battle.dir/src/battle_print.c.i

src/battle/CMakeFiles/battle.dir/src/battle_print.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/battle.dir/src/battle_print.c.s"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/battle && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wellingtj/Desktop/cs220/chiventure/src/battle/src/battle_print.c -o CMakeFiles/battle.dir/src/battle_print.c.s

src/battle/CMakeFiles/battle.dir/src/battle_default_objects.c.o: src/battle/CMakeFiles/battle.dir/flags.make
src/battle/CMakeFiles/battle.dir/src/battle_default_objects.c.o: src/battle/src/battle_default_objects.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wellingtj/Desktop/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object src/battle/CMakeFiles/battle.dir/src/battle_default_objects.c.o"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/battle && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/battle.dir/src/battle_default_objects.c.o   -c /home/wellingtj/Desktop/cs220/chiventure/src/battle/src/battle_default_objects.c

src/battle/CMakeFiles/battle.dir/src/battle_default_objects.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/battle.dir/src/battle_default_objects.c.i"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/battle && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wellingtj/Desktop/cs220/chiventure/src/battle/src/battle_default_objects.c > CMakeFiles/battle.dir/src/battle_default_objects.c.i

src/battle/CMakeFiles/battle.dir/src/battle_default_objects.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/battle.dir/src/battle_default_objects.c.s"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/battle && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wellingtj/Desktop/cs220/chiventure/src/battle/src/battle_default_objects.c -o CMakeFiles/battle.dir/src/battle_default_objects.c.s

# Object files for target battle
battle_OBJECTS = \
"CMakeFiles/battle.dir/src/battle_move_maker.c.o" \
"CMakeFiles/battle.dir/src/battle_ai.c.o" \
"CMakeFiles/battle.dir/src/battle_logic.c.o" \
"CMakeFiles/battle.dir/src/battle_state.c.o" \
"CMakeFiles/battle.dir/src/battle_flow.c.o" \
"CMakeFiles/battle.dir/src/battle_flow_structs.c.o" \
"CMakeFiles/battle.dir/src/battle_moves.c.o" \
"CMakeFiles/battle.dir/__/playerclass/examples/class-list.c.o" \
"CMakeFiles/battle.dir/src/battle_print.c.o" \
"CMakeFiles/battle.dir/src/battle_default_objects.c.o"

# External object files for target battle
battle_EXTERNAL_OBJECTS =

src/battle/libbattle.a: src/battle/CMakeFiles/battle.dir/src/battle_move_maker.c.o
src/battle/libbattle.a: src/battle/CMakeFiles/battle.dir/src/battle_ai.c.o
src/battle/libbattle.a: src/battle/CMakeFiles/battle.dir/src/battle_logic.c.o
src/battle/libbattle.a: src/battle/CMakeFiles/battle.dir/src/battle_state.c.o
src/battle/libbattle.a: src/battle/CMakeFiles/battle.dir/src/battle_flow.c.o
src/battle/libbattle.a: src/battle/CMakeFiles/battle.dir/src/battle_flow_structs.c.o
src/battle/libbattle.a: src/battle/CMakeFiles/battle.dir/src/battle_moves.c.o
src/battle/libbattle.a: src/battle/CMakeFiles/battle.dir/__/playerclass/examples/class-list.c.o
src/battle/libbattle.a: src/battle/CMakeFiles/battle.dir/src/battle_print.c.o
src/battle/libbattle.a: src/battle/CMakeFiles/battle.dir/src/battle_default_objects.c.o
src/battle/libbattle.a: src/battle/CMakeFiles/battle.dir/build.make
src/battle/libbattle.a: src/battle/CMakeFiles/battle.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wellingtj/Desktop/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking C static library libbattle.a"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/battle && $(CMAKE_COMMAND) -P CMakeFiles/battle.dir/cmake_clean_target.cmake
	cd /home/wellingtj/Desktop/cs220/chiventure/src/battle && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/battle.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/battle/CMakeFiles/battle.dir/build: src/battle/libbattle.a

.PHONY : src/battle/CMakeFiles/battle.dir/build

src/battle/CMakeFiles/battle.dir/clean:
	cd /home/wellingtj/Desktop/cs220/chiventure/src/battle && $(CMAKE_COMMAND) -P CMakeFiles/battle.dir/cmake_clean.cmake
.PHONY : src/battle/CMakeFiles/battle.dir/clean

src/battle/CMakeFiles/battle.dir/depend:
	cd /home/wellingtj/Desktop/cs220/chiventure && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wellingtj/Desktop/cs220/chiventure /home/wellingtj/Desktop/cs220/chiventure/src/battle /home/wellingtj/Desktop/cs220/chiventure /home/wellingtj/Desktop/cs220/chiventure/src/battle /home/wellingtj/Desktop/cs220/chiventure/src/battle/CMakeFiles/battle.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/battle/CMakeFiles/battle.dir/depend

