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
include tests/quests/CMakeFiles/test-quests.dir/depend.make

# Include the progress variables for this target.
include tests/quests/CMakeFiles/test-quests.dir/progress.make

# Include the compile flags for this target's objects.
include tests/quests/CMakeFiles/test-quests.dir/flags.make

tests/quests/CMakeFiles/test-quests.dir/test_quests_state.c.o: tests/quests/CMakeFiles/test-quests.dir/flags.make
tests/quests/CMakeFiles/test-quests.dir/test_quests_state.c.o: tests/quests/test_quests_state.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wellingtj/Desktop/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/quests/CMakeFiles/test-quests.dir/test_quests_state.c.o"
	cd /home/wellingtj/Desktop/cs220/chiventure/tests/quests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test-quests.dir/test_quests_state.c.o   -c /home/wellingtj/Desktop/cs220/chiventure/tests/quests/test_quests_state.c

tests/quests/CMakeFiles/test-quests.dir/test_quests_state.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test-quests.dir/test_quests_state.c.i"
	cd /home/wellingtj/Desktop/cs220/chiventure/tests/quests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wellingtj/Desktop/cs220/chiventure/tests/quests/test_quests_state.c > CMakeFiles/test-quests.dir/test_quests_state.c.i

tests/quests/CMakeFiles/test-quests.dir/test_quests_state.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test-quests.dir/test_quests_state.c.s"
	cd /home/wellingtj/Desktop/cs220/chiventure/tests/quests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wellingtj/Desktop/cs220/chiventure/tests/quests/test_quests_state.c -o CMakeFiles/test-quests.dir/test_quests_state.c.s

tests/quests/CMakeFiles/test-quests.dir/main.c.o: tests/quests/CMakeFiles/test-quests.dir/flags.make
tests/quests/CMakeFiles/test-quests.dir/main.c.o: tests/quests/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wellingtj/Desktop/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object tests/quests/CMakeFiles/test-quests.dir/main.c.o"
	cd /home/wellingtj/Desktop/cs220/chiventure/tests/quests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test-quests.dir/main.c.o   -c /home/wellingtj/Desktop/cs220/chiventure/tests/quests/main.c

tests/quests/CMakeFiles/test-quests.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test-quests.dir/main.c.i"
	cd /home/wellingtj/Desktop/cs220/chiventure/tests/quests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wellingtj/Desktop/cs220/chiventure/tests/quests/main.c > CMakeFiles/test-quests.dir/main.c.i

tests/quests/CMakeFiles/test-quests.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test-quests.dir/main.c.s"
	cd /home/wellingtj/Desktop/cs220/chiventure/tests/quests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wellingtj/Desktop/cs220/chiventure/tests/quests/main.c -o CMakeFiles/test-quests.dir/main.c.s

# Object files for target test-quests
test__quests_OBJECTS = \
"CMakeFiles/test-quests.dir/test_quests_state.c.o" \
"CMakeFiles/test-quests.dir/main.c.o"

# External object files for target test-quests
test__quests_EXTERNAL_OBJECTS =

tests/quests/test-quests: tests/quests/CMakeFiles/test-quests.dir/test_quests_state.c.o
tests/quests/test-quests: tests/quests/CMakeFiles/test-quests.dir/main.c.o
tests/quests/test-quests: tests/quests/CMakeFiles/test-quests.dir/build.make
tests/quests/test-quests: /usr/lib/libcriterion.so
tests/quests/test-quests: src/action_management/libaction_management.a
tests/quests/test-quests: src/battle/libbattle.a
tests/quests/test-quests: src/cli/libcli.a
tests/quests/test-quests: src/common/libcommon.a
tests/quests/test-quests: src/custom-actions/libcustom-actions.a
tests/quests/test-quests: src/game-state/libgame-state.a
tests/quests/test-quests: src/libobj/liblibobj.a
tests/quests/test-quests: src/quests/libquests.a
tests/quests/test-quests: src/sound/libsound.a
tests/quests/test-quests: src/npc/libnpc.a
tests/quests/test-quests: src/openworld/libopenworld.a
tests/quests/test-quests: src/playerclass/libplayerclass.a
tests/quests/test-quests: src/skilltrees/libskilltrees.a
tests/quests/test-quests: src/ui/libui.a
tests/quests/test-quests: src/wdl/libwdl.a
tests/quests/test-quests: src/custom-scripts/libcustom-scripts.a
tests/quests/test-quests: src/cli/libcli.a
tests/quests/test-quests: src/common/libcommon.a
tests/quests/test-quests: src/game-state/libgame-state.a
tests/quests/test-quests: src/cli/libcli.a
tests/quests/test-quests: src/common/libcommon.a
tests/quests/test-quests: src/game-state/libgame-state.a
tests/quests/test-quests: src/action_management/libaction_management.a
tests/quests/test-quests: src/ui/libui.a
tests/quests/test-quests: /usr/lib/x86_64-linux-gnu/libncursesw.so
tests/quests/test-quests: /usr/lib/x86_64-linux-gnu/libformw.so
tests/quests/test-quests: src/quests/libquests.a
tests/quests/test-quests: src/wdl/libwdl.a
tests/quests/test-quests: src/libobj/liblibobj.a
tests/quests/test-quests: src/npc/libnpc.a
tests/quests/test-quests: src/battle/libbattle.a
tests/quests/test-quests: src/playerclass/libplayerclass.a
tests/quests/test-quests: src/skilltrees/libskilltrees.a
tests/quests/test-quests: /usr/lib/x86_64-linux-gnu/libzip.so
tests/quests/test-quests: /usr/lib/x86_64-linux-gnu/libjson-c.so
tests/quests/test-quests: /usr/lib/x86_64-linux-gnu/liblua5.3.so
tests/quests/test-quests: /usr/lib/x86_64-linux-gnu/libm.so
tests/quests/test-quests: tests/quests/CMakeFiles/test-quests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wellingtj/Desktop/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable test-quests"
	cd /home/wellingtj/Desktop/cs220/chiventure/tests/quests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test-quests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/quests/CMakeFiles/test-quests.dir/build: tests/quests/test-quests

.PHONY : tests/quests/CMakeFiles/test-quests.dir/build

tests/quests/CMakeFiles/test-quests.dir/clean:
	cd /home/wellingtj/Desktop/cs220/chiventure/tests/quests && $(CMAKE_COMMAND) -P CMakeFiles/test-quests.dir/cmake_clean.cmake
.PHONY : tests/quests/CMakeFiles/test-quests.dir/clean

tests/quests/CMakeFiles/test-quests.dir/depend:
	cd /home/wellingtj/Desktop/cs220/chiventure && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wellingtj/Desktop/cs220/chiventure /home/wellingtj/Desktop/cs220/chiventure/tests/quests /home/wellingtj/Desktop/cs220/chiventure /home/wellingtj/Desktop/cs220/chiventure/tests/quests /home/wellingtj/Desktop/cs220/chiventure/tests/quests/CMakeFiles/test-quests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/quests/CMakeFiles/test-quests.dir/depend

