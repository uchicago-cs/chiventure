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
include tests/cli/CMakeFiles/test-cli.dir/depend.make

# Include the progress variables for this target.
include tests/cli/CMakeFiles/test-cli.dir/progress.make

# Include the compile flags for this target's objects.
include tests/cli/CMakeFiles/test-cli.dir/flags.make

tests/cli/CMakeFiles/test-cli.dir/test_cmd.c.o: tests/cli/CMakeFiles/test-cli.dir/flags.make
tests/cli/CMakeFiles/test-cli.dir/test_cmd.c.o: tests/cli/test_cmd.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wellingtj/Desktop/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/cli/CMakeFiles/test-cli.dir/test_cmd.c.o"
	cd /home/wellingtj/Desktop/cs220/chiventure/tests/cli && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test-cli.dir/test_cmd.c.o   -c /home/wellingtj/Desktop/cs220/chiventure/tests/cli/test_cmd.c

tests/cli/CMakeFiles/test-cli.dir/test_cmd.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test-cli.dir/test_cmd.c.i"
	cd /home/wellingtj/Desktop/cs220/chiventure/tests/cli && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wellingtj/Desktop/cs220/chiventure/tests/cli/test_cmd.c > CMakeFiles/test-cli.dir/test_cmd.c.i

tests/cli/CMakeFiles/test-cli.dir/test_cmd.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test-cli.dir/test_cmd.c.s"
	cd /home/wellingtj/Desktop/cs220/chiventure/tests/cli && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wellingtj/Desktop/cs220/chiventure/tests/cli/test_cmd.c -o CMakeFiles/test-cli.dir/test_cmd.c.s

tests/cli/CMakeFiles/test-cli.dir/test_parser.c.o: tests/cli/CMakeFiles/test-cli.dir/flags.make
tests/cli/CMakeFiles/test-cli.dir/test_parser.c.o: tests/cli/test_parser.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wellingtj/Desktop/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object tests/cli/CMakeFiles/test-cli.dir/test_parser.c.o"
	cd /home/wellingtj/Desktop/cs220/chiventure/tests/cli && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test-cli.dir/test_parser.c.o   -c /home/wellingtj/Desktop/cs220/chiventure/tests/cli/test_parser.c

tests/cli/CMakeFiles/test-cli.dir/test_parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test-cli.dir/test_parser.c.i"
	cd /home/wellingtj/Desktop/cs220/chiventure/tests/cli && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wellingtj/Desktop/cs220/chiventure/tests/cli/test_parser.c > CMakeFiles/test-cli.dir/test_parser.c.i

tests/cli/CMakeFiles/test-cli.dir/test_parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test-cli.dir/test_parser.c.s"
	cd /home/wellingtj/Desktop/cs220/chiventure/tests/cli && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wellingtj/Desktop/cs220/chiventure/tests/cli/test_parser.c -o CMakeFiles/test-cli.dir/test_parser.c.s

tests/cli/CMakeFiles/test-cli.dir/test_game.c.o: tests/cli/CMakeFiles/test-cli.dir/flags.make
tests/cli/CMakeFiles/test-cli.dir/test_game.c.o: tests/cli/test_game.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wellingtj/Desktop/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object tests/cli/CMakeFiles/test-cli.dir/test_game.c.o"
	cd /home/wellingtj/Desktop/cs220/chiventure/tests/cli && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test-cli.dir/test_game.c.o   -c /home/wellingtj/Desktop/cs220/chiventure/tests/cli/test_game.c

tests/cli/CMakeFiles/test-cli.dir/test_game.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test-cli.dir/test_game.c.i"
	cd /home/wellingtj/Desktop/cs220/chiventure/tests/cli && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wellingtj/Desktop/cs220/chiventure/tests/cli/test_game.c > CMakeFiles/test-cli.dir/test_game.c.i

tests/cli/CMakeFiles/test-cli.dir/test_game.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test-cli.dir/test_game.c.s"
	cd /home/wellingtj/Desktop/cs220/chiventure/tests/cli && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wellingtj/Desktop/cs220/chiventure/tests/cli/test_game.c -o CMakeFiles/test-cli.dir/test_game.c.s

tests/cli/CMakeFiles/test-cli.dir/main.c.o: tests/cli/CMakeFiles/test-cli.dir/flags.make
tests/cli/CMakeFiles/test-cli.dir/main.c.o: tests/cli/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wellingtj/Desktop/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object tests/cli/CMakeFiles/test-cli.dir/main.c.o"
	cd /home/wellingtj/Desktop/cs220/chiventure/tests/cli && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test-cli.dir/main.c.o   -c /home/wellingtj/Desktop/cs220/chiventure/tests/cli/main.c

tests/cli/CMakeFiles/test-cli.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test-cli.dir/main.c.i"
	cd /home/wellingtj/Desktop/cs220/chiventure/tests/cli && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wellingtj/Desktop/cs220/chiventure/tests/cli/main.c > CMakeFiles/test-cli.dir/main.c.i

tests/cli/CMakeFiles/test-cli.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test-cli.dir/main.c.s"
	cd /home/wellingtj/Desktop/cs220/chiventure/tests/cli && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wellingtj/Desktop/cs220/chiventure/tests/cli/main.c -o CMakeFiles/test-cli.dir/main.c.s

# Object files for target test-cli
test__cli_OBJECTS = \
"CMakeFiles/test-cli.dir/test_cmd.c.o" \
"CMakeFiles/test-cli.dir/test_parser.c.o" \
"CMakeFiles/test-cli.dir/test_game.c.o" \
"CMakeFiles/test-cli.dir/main.c.o"

# External object files for target test-cli
test__cli_EXTERNAL_OBJECTS =

tests/cli/test-cli: tests/cli/CMakeFiles/test-cli.dir/test_cmd.c.o
tests/cli/test-cli: tests/cli/CMakeFiles/test-cli.dir/test_parser.c.o
tests/cli/test-cli: tests/cli/CMakeFiles/test-cli.dir/test_game.c.o
tests/cli/test-cli: tests/cli/CMakeFiles/test-cli.dir/main.c.o
tests/cli/test-cli: tests/cli/CMakeFiles/test-cli.dir/build.make
tests/cli/test-cli: /usr/lib/libcriterion.so
tests/cli/test-cli: src/action_management/libaction_management.a
tests/cli/test-cli: src/battle/libbattle.a
tests/cli/test-cli: src/cli/libcli.a
tests/cli/test-cli: src/common/libcommon.a
tests/cli/test-cli: src/custom-actions/libcustom-actions.a
tests/cli/test-cli: src/game-state/libgame-state.a
tests/cli/test-cli: src/libobj/liblibobj.a
tests/cli/test-cli: src/quests/libquests.a
tests/cli/test-cli: src/sound/libsound.a
tests/cli/test-cli: src/npc/libnpc.a
tests/cli/test-cli: src/openworld/libopenworld.a
tests/cli/test-cli: src/playerclass/libplayerclass.a
tests/cli/test-cli: src/skilltrees/libskilltrees.a
tests/cli/test-cli: src/ui/libui.a
tests/cli/test-cli: src/wdl/libwdl.a
tests/cli/test-cli: src/custom-scripts/libcustom-scripts.a
tests/cli/test-cli: src/cli/libcli.a
tests/cli/test-cli: src/common/libcommon.a
tests/cli/test-cli: src/game-state/libgame-state.a
tests/cli/test-cli: src/cli/libcli.a
tests/cli/test-cli: src/common/libcommon.a
tests/cli/test-cli: src/game-state/libgame-state.a
tests/cli/test-cli: src/action_management/libaction_management.a
tests/cli/test-cli: src/ui/libui.a
tests/cli/test-cli: /usr/lib/x86_64-linux-gnu/libncursesw.so
tests/cli/test-cli: /usr/lib/x86_64-linux-gnu/libformw.so
tests/cli/test-cli: src/quests/libquests.a
tests/cli/test-cli: src/wdl/libwdl.a
tests/cli/test-cli: src/libobj/liblibobj.a
tests/cli/test-cli: src/npc/libnpc.a
tests/cli/test-cli: src/battle/libbattle.a
tests/cli/test-cli: src/playerclass/libplayerclass.a
tests/cli/test-cli: src/skilltrees/libskilltrees.a
tests/cli/test-cli: /usr/lib/x86_64-linux-gnu/libzip.so
tests/cli/test-cli: /usr/lib/x86_64-linux-gnu/libjson-c.so
tests/cli/test-cli: /usr/lib/x86_64-linux-gnu/liblua5.3.so
tests/cli/test-cli: /usr/lib/x86_64-linux-gnu/libm.so
tests/cli/test-cli: tests/cli/CMakeFiles/test-cli.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wellingtj/Desktop/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable test-cli"
	cd /home/wellingtj/Desktop/cs220/chiventure/tests/cli && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test-cli.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/cli/CMakeFiles/test-cli.dir/build: tests/cli/test-cli

.PHONY : tests/cli/CMakeFiles/test-cli.dir/build

tests/cli/CMakeFiles/test-cli.dir/clean:
	cd /home/wellingtj/Desktop/cs220/chiventure/tests/cli && $(CMAKE_COMMAND) -P CMakeFiles/test-cli.dir/cmake_clean.cmake
.PHONY : tests/cli/CMakeFiles/test-cli.dir/clean

tests/cli/CMakeFiles/test-cli.dir/depend:
	cd /home/wellingtj/Desktop/cs220/chiventure && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wellingtj/Desktop/cs220/chiventure /home/wellingtj/Desktop/cs220/chiventure/tests/cli /home/wellingtj/Desktop/cs220/chiventure /home/wellingtj/Desktop/cs220/chiventure/tests/cli /home/wellingtj/Desktop/cs220/chiventure/tests/cli/CMakeFiles/test-cli.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/cli/CMakeFiles/test-cli.dir/depend

