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
include src/cli/CMakeFiles/cli.dir/depend.make

# Include the progress variables for this target.
include src/cli/CMakeFiles/cli.dir/progress.make

# Include the compile flags for this target's objects.
include src/cli/CMakeFiles/cli.dir/flags.make

src/cli/CMakeFiles/cli.dir/src/util.c.o: src/cli/CMakeFiles/cli.dir/flags.make
src/cli/CMakeFiles/cli.dir/src/util.c.o: src/cli/src/util.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wellingtj/Desktop/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/cli/CMakeFiles/cli.dir/src/util.c.o"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/cli && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cli.dir/src/util.c.o   -c /home/wellingtj/Desktop/cs220/chiventure/src/cli/src/util.c

src/cli/CMakeFiles/cli.dir/src/util.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cli.dir/src/util.c.i"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/cli && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wellingtj/Desktop/cs220/chiventure/src/cli/src/util.c > CMakeFiles/cli.dir/src/util.c.i

src/cli/CMakeFiles/cli.dir/src/util.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cli.dir/src/util.c.s"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/cli && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wellingtj/Desktop/cs220/chiventure/src/cli/src/util.c -o CMakeFiles/cli.dir/src/util.c.s

src/cli/CMakeFiles/cli.dir/src/cmd.c.o: src/cli/CMakeFiles/cli.dir/flags.make
src/cli/CMakeFiles/cli.dir/src/cmd.c.o: src/cli/src/cmd.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wellingtj/Desktop/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/cli/CMakeFiles/cli.dir/src/cmd.c.o"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/cli && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cli.dir/src/cmd.c.o   -c /home/wellingtj/Desktop/cs220/chiventure/src/cli/src/cmd.c

src/cli/CMakeFiles/cli.dir/src/cmd.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cli.dir/src/cmd.c.i"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/cli && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wellingtj/Desktop/cs220/chiventure/src/cli/src/cmd.c > CMakeFiles/cli.dir/src/cmd.c.i

src/cli/CMakeFiles/cli.dir/src/cmd.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cli.dir/src/cmd.c.s"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/cli && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wellingtj/Desktop/cs220/chiventure/src/cli/src/cmd.c -o CMakeFiles/cli.dir/src/cmd.c.s

src/cli/CMakeFiles/cli.dir/src/cmdlist.c.o: src/cli/CMakeFiles/cli.dir/flags.make
src/cli/CMakeFiles/cli.dir/src/cmdlist.c.o: src/cli/src/cmdlist.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wellingtj/Desktop/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object src/cli/CMakeFiles/cli.dir/src/cmdlist.c.o"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/cli && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cli.dir/src/cmdlist.c.o   -c /home/wellingtj/Desktop/cs220/chiventure/src/cli/src/cmdlist.c

src/cli/CMakeFiles/cli.dir/src/cmdlist.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cli.dir/src/cmdlist.c.i"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/cli && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wellingtj/Desktop/cs220/chiventure/src/cli/src/cmdlist.c > CMakeFiles/cli.dir/src/cmdlist.c.i

src/cli/CMakeFiles/cli.dir/src/cmdlist.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cli.dir/src/cmdlist.c.s"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/cli && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wellingtj/Desktop/cs220/chiventure/src/cli/src/cmdlist.c -o CMakeFiles/cli.dir/src/cmdlist.c.s

src/cli/CMakeFiles/cli.dir/src/cli_ctx.c.o: src/cli/CMakeFiles/cli.dir/flags.make
src/cli/CMakeFiles/cli.dir/src/cli_ctx.c.o: src/cli/src/cli_ctx.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wellingtj/Desktop/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object src/cli/CMakeFiles/cli.dir/src/cli_ctx.c.o"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/cli && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cli.dir/src/cli_ctx.c.o   -c /home/wellingtj/Desktop/cs220/chiventure/src/cli/src/cli_ctx.c

src/cli/CMakeFiles/cli.dir/src/cli_ctx.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cli.dir/src/cli_ctx.c.i"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/cli && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wellingtj/Desktop/cs220/chiventure/src/cli/src/cli_ctx.c > CMakeFiles/cli.dir/src/cli_ctx.c.i

src/cli/CMakeFiles/cli.dir/src/cli_ctx.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cli.dir/src/cli_ctx.c.s"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/cli && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wellingtj/Desktop/cs220/chiventure/src/cli/src/cli_ctx.c -o CMakeFiles/cli.dir/src/cli_ctx.c.s

src/cli/CMakeFiles/cli.dir/src/operations.c.o: src/cli/CMakeFiles/cli.dir/flags.make
src/cli/CMakeFiles/cli.dir/src/operations.c.o: src/cli/src/operations.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wellingtj/Desktop/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object src/cli/CMakeFiles/cli.dir/src/operations.c.o"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/cli && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cli.dir/src/operations.c.o   -c /home/wellingtj/Desktop/cs220/chiventure/src/cli/src/operations.c

src/cli/CMakeFiles/cli.dir/src/operations.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cli.dir/src/operations.c.i"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/cli && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wellingtj/Desktop/cs220/chiventure/src/cli/src/operations.c > CMakeFiles/cli.dir/src/operations.c.i

src/cli/CMakeFiles/cli.dir/src/operations.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cli.dir/src/operations.c.s"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/cli && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wellingtj/Desktop/cs220/chiventure/src/cli/src/operations.c -o CMakeFiles/cli.dir/src/operations.c.s

src/cli/CMakeFiles/cli.dir/src/parser.c.o: src/cli/CMakeFiles/cli.dir/flags.make
src/cli/CMakeFiles/cli.dir/src/parser.c.o: src/cli/src/parser.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wellingtj/Desktop/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object src/cli/CMakeFiles/cli.dir/src/parser.c.o"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/cli && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cli.dir/src/parser.c.o   -c /home/wellingtj/Desktop/cs220/chiventure/src/cli/src/parser.c

src/cli/CMakeFiles/cli.dir/src/parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cli.dir/src/parser.c.i"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/cli && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wellingtj/Desktop/cs220/chiventure/src/cli/src/parser.c > CMakeFiles/cli.dir/src/parser.c.i

src/cli/CMakeFiles/cli.dir/src/parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cli.dir/src/parser.c.s"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/cli && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wellingtj/Desktop/cs220/chiventure/src/cli/src/parser.c -o CMakeFiles/cli.dir/src/parser.c.s

src/cli/CMakeFiles/cli.dir/src/shell.c.o: src/cli/CMakeFiles/cli.dir/flags.make
src/cli/CMakeFiles/cli.dir/src/shell.c.o: src/cli/src/shell.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wellingtj/Desktop/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object src/cli/CMakeFiles/cli.dir/src/shell.c.o"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/cli && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cli.dir/src/shell.c.o   -c /home/wellingtj/Desktop/cs220/chiventure/src/cli/src/shell.c

src/cli/CMakeFiles/cli.dir/src/shell.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cli.dir/src/shell.c.i"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/cli && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wellingtj/Desktop/cs220/chiventure/src/cli/src/shell.c > CMakeFiles/cli.dir/src/shell.c.i

src/cli/CMakeFiles/cli.dir/src/shell.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cli.dir/src/shell.c.s"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/cli && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wellingtj/Desktop/cs220/chiventure/src/cli/src/shell.c -o CMakeFiles/cli.dir/src/shell.c.s

# Object files for target cli
cli_OBJECTS = \
"CMakeFiles/cli.dir/src/util.c.o" \
"CMakeFiles/cli.dir/src/cmd.c.o" \
"CMakeFiles/cli.dir/src/cmdlist.c.o" \
"CMakeFiles/cli.dir/src/cli_ctx.c.o" \
"CMakeFiles/cli.dir/src/operations.c.o" \
"CMakeFiles/cli.dir/src/parser.c.o" \
"CMakeFiles/cli.dir/src/shell.c.o"

# External object files for target cli
cli_EXTERNAL_OBJECTS =

src/cli/libcli.a: src/cli/CMakeFiles/cli.dir/src/util.c.o
src/cli/libcli.a: src/cli/CMakeFiles/cli.dir/src/cmd.c.o
src/cli/libcli.a: src/cli/CMakeFiles/cli.dir/src/cmdlist.c.o
src/cli/libcli.a: src/cli/CMakeFiles/cli.dir/src/cli_ctx.c.o
src/cli/libcli.a: src/cli/CMakeFiles/cli.dir/src/operations.c.o
src/cli/libcli.a: src/cli/CMakeFiles/cli.dir/src/parser.c.o
src/cli/libcli.a: src/cli/CMakeFiles/cli.dir/src/shell.c.o
src/cli/libcli.a: src/cli/CMakeFiles/cli.dir/build.make
src/cli/libcli.a: src/cli/CMakeFiles/cli.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wellingtj/Desktop/cs220/chiventure/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking C static library libcli.a"
	cd /home/wellingtj/Desktop/cs220/chiventure/src/cli && $(CMAKE_COMMAND) -P CMakeFiles/cli.dir/cmake_clean_target.cmake
	cd /home/wellingtj/Desktop/cs220/chiventure/src/cli && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cli.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/cli/CMakeFiles/cli.dir/build: src/cli/libcli.a

.PHONY : src/cli/CMakeFiles/cli.dir/build

src/cli/CMakeFiles/cli.dir/clean:
	cd /home/wellingtj/Desktop/cs220/chiventure/src/cli && $(CMAKE_COMMAND) -P CMakeFiles/cli.dir/cmake_clean.cmake
.PHONY : src/cli/CMakeFiles/cli.dir/clean

src/cli/CMakeFiles/cli.dir/depend:
	cd /home/wellingtj/Desktop/cs220/chiventure && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wellingtj/Desktop/cs220/chiventure /home/wellingtj/Desktop/cs220/chiventure/src/cli /home/wellingtj/Desktop/cs220/chiventure /home/wellingtj/Desktop/cs220/chiventure/src/cli /home/wellingtj/Desktop/cs220/chiventure/src/cli/CMakeFiles/cli.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/cli/CMakeFiles/cli.dir/depend

