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
include src/battle/examples/CMakeFiles/battle_command_example.dir/depend.make

# Include the progress variables for this target.
include src/battle/examples/CMakeFiles/battle_command_example.dir/progress.make

# Include the compile flags for this target's objects.
include src/battle/examples/CMakeFiles/battle_command_example.dir/flags.make

src/battle/examples/CMakeFiles/battle_command_example.dir/battle_command_example.c.o: src/battle/examples/CMakeFiles/battle_command_example.dir/flags.make
src/battle/examples/CMakeFiles/battle_command_example.dir/battle_command_example.c.o: src/battle/examples/battle_command_example.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wellingtj/Desktop/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/battle/examples/CMakeFiles/battle_command_example.dir/battle_command_example.c.o"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/battle/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/battle_command_example.dir/battle_command_example.c.o   -c /home/wellingtj/Desktop/cs220/chiventure/src/battle/examples/battle_command_example.c

src/battle/examples/CMakeFiles/battle_command_example.dir/battle_command_example.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/battle_command_example.dir/battle_command_example.c.i"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/battle/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wellingtj/Desktop/cs220/chiventure/src/battle/examples/battle_command_example.c > CMakeFiles/battle_command_example.dir/battle_command_example.c.i

src/battle/examples/CMakeFiles/battle_command_example.dir/battle_command_example.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/battle_command_example.dir/battle_command_example.c.s"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/battle/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wellingtj/Desktop/cs220/chiventure/src/battle/examples/battle_command_example.c -o CMakeFiles/battle_command_example.dir/battle_command_example.c.s

# Object files for target battle_command_example
battle_command_example_OBJECTS = \
"CMakeFiles/battle_command_example.dir/battle_command_example.c.o"

# External object files for target battle_command_example
battle_command_example_EXTERNAL_OBJECTS =

src/battle/examples/battle_command_example: src/battle/examples/CMakeFiles/battle_command_example.dir/battle_command_example.c.o
src/battle/examples/battle_command_example: src/battle/examples/CMakeFiles/battle_command_example.dir/build.make
src/battle/examples/battle_command_example: src/action_management/libaction_management.a
src/battle/examples/battle_command_example: src/battle/libbattle.a
src/battle/examples/battle_command_example: src/cli/libcli.a
src/battle/examples/battle_command_example: src/common/libcommon.a
src/battle/examples/battle_command_example: src/custom-actions/libcustom-actions.a
src/battle/examples/battle_command_example: src/game-state/libgame-state.a
src/battle/examples/battle_command_example: src/libobj/liblibobj.a
src/battle/examples/battle_command_example: src/quests/libquests.a
src/battle/examples/battle_command_example: src/sound/libsound.a
src/battle/examples/battle_command_example: src/npc/libnpc.a
src/battle/examples/battle_command_example: src/openworld/libopenworld.a
src/battle/examples/battle_command_example: src/playerclass/libplayerclass.a
src/battle/examples/battle_command_example: src/skilltrees/libskilltrees.a
src/battle/examples/battle_command_example: src/ui/libui.a
src/battle/examples/battle_command_example: src/wdl/libwdl.a
src/battle/examples/battle_command_example: src/custom-scripts/libcustom-scripts.a
src/battle/examples/battle_command_example: src/cli/libcli.a
src/battle/examples/battle_command_example: src/common/libcommon.a
src/battle/examples/battle_command_example: src/game-state/libgame-state.a
src/battle/examples/battle_command_example: src/cli/libcli.a
src/battle/examples/battle_command_example: src/common/libcommon.a
src/battle/examples/battle_command_example: src/game-state/libgame-state.a
src/battle/examples/battle_command_example: src/action_management/libaction_management.a
src/battle/examples/battle_command_example: src/ui/libui.a
src/battle/examples/battle_command_example: /usr/lib/x86_64-linux-gnu/libncursesw.so
src/battle/examples/battle_command_example: /usr/lib/x86_64-linux-gnu/libformw.so
src/battle/examples/battle_command_example: src/quests/libquests.a
src/battle/examples/battle_command_example: src/wdl/libwdl.a
src/battle/examples/battle_command_example: src/libobj/liblibobj.a
src/battle/examples/battle_command_example: src/npc/libnpc.a
src/battle/examples/battle_command_example: src/battle/libbattle.a
src/battle/examples/battle_command_example: src/playerclass/libplayerclass.a
src/battle/examples/battle_command_example: src/skilltrees/libskilltrees.a
src/battle/examples/battle_command_example: /usr/lib/x86_64-linux-gnu/libzip.so
src/battle/examples/battle_command_example: /usr/lib/x86_64-linux-gnu/libjson-c.so
src/battle/examples/battle_command_example: /usr/lib/x86_64-linux-gnu/liblua5.3.so
src/battle/examples/battle_command_example: /usr/lib/x86_64-linux-gnu/libm.so
src/battle/examples/battle_command_example: src/battle/examples/CMakeFiles/battle_command_example.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wellingtj/Desktop/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable battle_command_example"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/battle/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/battle_command_example.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/battle/examples/CMakeFiles/battle_command_example.dir/build: src/battle/examples/battle_command_example

.PHONY : src/battle/examples/CMakeFiles/battle_command_example.dir/build

src/battle/examples/CMakeFiles/battle_command_example.dir/clean:
	cd /home/wellingtj/Desktop/cs220/chiventure/src/battle/examples && $(CMAKE_COMMAND) -P CMakeFiles/battle_command_example.dir/cmake_clean.cmake
.PHONY : src/battle/examples/CMakeFiles/battle_command_example.dir/clean

src/battle/examples/CMakeFiles/battle_command_example.dir/depend:
	cd /home/wellingtj/Desktop/cs220/chiventure && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wellingtj/Desktop/cs220/chiventure /home/wellingtj/Desktop/cs220/chiventure/src/battle/examples /home/wellingtj/Desktop/cs220/chiventure /home/wellingtj/Desktop/cs220/chiventure/src/battle/examples /home/wellingtj/Desktop/cs220/chiventure/src/battle/examples/CMakeFiles/battle_command_example.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/battle/examples/CMakeFiles/battle_command_example.dir/depend

