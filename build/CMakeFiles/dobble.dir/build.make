# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_SOURCE_DIR = /home/sebastian/dobble

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sebastian/dobble/build

# Include any dependencies generated for this target.
include CMakeFiles/dobble.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/dobble.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/dobble.dir/flags.make

CMakeFiles/dobble.dir/src/graphics.c.o: CMakeFiles/dobble.dir/flags.make
CMakeFiles/dobble.dir/src/graphics.c.o: ../src/graphics.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sebastian/dobble/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/dobble.dir/src/graphics.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/dobble.dir/src/graphics.c.o   -c /home/sebastian/dobble/src/graphics.c

CMakeFiles/dobble.dir/src/graphics.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/dobble.dir/src/graphics.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/sebastian/dobble/src/graphics.c > CMakeFiles/dobble.dir/src/graphics.c.i

CMakeFiles/dobble.dir/src/graphics.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/dobble.dir/src/graphics.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/sebastian/dobble/src/graphics.c -o CMakeFiles/dobble.dir/src/graphics.c.s

CMakeFiles/dobble.dir/src/graphics.c.o.requires:

.PHONY : CMakeFiles/dobble.dir/src/graphics.c.o.requires

CMakeFiles/dobble.dir/src/graphics.c.o.provides: CMakeFiles/dobble.dir/src/graphics.c.o.requires
	$(MAKE) -f CMakeFiles/dobble.dir/build.make CMakeFiles/dobble.dir/src/graphics.c.o.provides.build
.PHONY : CMakeFiles/dobble.dir/src/graphics.c.o.provides

CMakeFiles/dobble.dir/src/graphics.c.o.provides.build: CMakeFiles/dobble.dir/src/graphics.c.o


CMakeFiles/dobble.dir/src/dobble.c.o: CMakeFiles/dobble.dir/flags.make
CMakeFiles/dobble.dir/src/dobble.c.o: ../src/dobble.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sebastian/dobble/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/dobble.dir/src/dobble.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/dobble.dir/src/dobble.c.o   -c /home/sebastian/dobble/src/dobble.c

CMakeFiles/dobble.dir/src/dobble.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/dobble.dir/src/dobble.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/sebastian/dobble/src/dobble.c > CMakeFiles/dobble.dir/src/dobble.c.i

CMakeFiles/dobble.dir/src/dobble.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/dobble.dir/src/dobble.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/sebastian/dobble/src/dobble.c -o CMakeFiles/dobble.dir/src/dobble.c.s

CMakeFiles/dobble.dir/src/dobble.c.o.requires:

.PHONY : CMakeFiles/dobble.dir/src/dobble.c.o.requires

CMakeFiles/dobble.dir/src/dobble.c.o.provides: CMakeFiles/dobble.dir/src/dobble.c.o.requires
	$(MAKE) -f CMakeFiles/dobble.dir/build.make CMakeFiles/dobble.dir/src/dobble.c.o.provides.build
.PHONY : CMakeFiles/dobble.dir/src/dobble.c.o.provides

CMakeFiles/dobble.dir/src/dobble.c.o.provides.build: CMakeFiles/dobble.dir/src/dobble.c.o


# Object files for target dobble
dobble_OBJECTS = \
"CMakeFiles/dobble.dir/src/graphics.c.o" \
"CMakeFiles/dobble.dir/src/dobble.c.o"

# External object files for target dobble
dobble_EXTERNAL_OBJECTS =

dobble: CMakeFiles/dobble.dir/src/graphics.c.o
dobble: CMakeFiles/dobble.dir/src/dobble.c.o
dobble: CMakeFiles/dobble.dir/build.make
dobble: /usr/lib/x86_64-linux-gnu/libSDL2main.a
dobble: /usr/lib/x86_64-linux-gnu/libSDL2.so
dobble: /usr/lib/x86_64-linux-gnu/libSDL2_image.so
dobble: /usr/lib/x86_64-linux-gnu/libSDL2_ttf.so
dobble: CMakeFiles/dobble.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sebastian/dobble/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable dobble"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dobble.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/dobble.dir/build: dobble

.PHONY : CMakeFiles/dobble.dir/build

CMakeFiles/dobble.dir/requires: CMakeFiles/dobble.dir/src/graphics.c.o.requires
CMakeFiles/dobble.dir/requires: CMakeFiles/dobble.dir/src/dobble.c.o.requires

.PHONY : CMakeFiles/dobble.dir/requires

CMakeFiles/dobble.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/dobble.dir/cmake_clean.cmake
.PHONY : CMakeFiles/dobble.dir/clean

CMakeFiles/dobble.dir/depend:
	cd /home/sebastian/dobble/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sebastian/dobble /home/sebastian/dobble /home/sebastian/dobble/build /home/sebastian/dobble/build /home/sebastian/dobble/build/CMakeFiles/dobble.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/dobble.dir/depend

