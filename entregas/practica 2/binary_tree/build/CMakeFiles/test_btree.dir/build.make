# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/yabiel/Documents/ED/entregas/practica 2/binary_tree"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/yabiel/Documents/ED/entregas/practica 2/binary_tree/build"

# Include any dependencies generated for this target.
include CMakeFiles/test_btree.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/test_btree.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/test_btree.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_btree.dir/flags.make

CMakeFiles/test_btree.dir/test_btree.cpp.o: CMakeFiles/test_btree.dir/flags.make
CMakeFiles/test_btree.dir/test_btree.cpp.o: ../test_btree.cpp
CMakeFiles/test_btree.dir/test_btree.cpp.o: CMakeFiles/test_btree.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/yabiel/Documents/ED/entregas/practica 2/binary_tree/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_btree.dir/test_btree.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_btree.dir/test_btree.cpp.o -MF CMakeFiles/test_btree.dir/test_btree.cpp.o.d -o CMakeFiles/test_btree.dir/test_btree.cpp.o -c "/home/yabiel/Documents/ED/entregas/practica 2/binary_tree/test_btree.cpp"

CMakeFiles/test_btree.dir/test_btree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_btree.dir/test_btree.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/yabiel/Documents/ED/entregas/practica 2/binary_tree/test_btree.cpp" > CMakeFiles/test_btree.dir/test_btree.cpp.i

CMakeFiles/test_btree.dir/test_btree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_btree.dir/test_btree.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/yabiel/Documents/ED/entregas/practica 2/binary_tree/test_btree.cpp" -o CMakeFiles/test_btree.dir/test_btree.cpp.s

# Object files for target test_btree
test_btree_OBJECTS = \
"CMakeFiles/test_btree.dir/test_btree.cpp.o"

# External object files for target test_btree
test_btree_EXTERNAL_OBJECTS =

test_btree: CMakeFiles/test_btree.dir/test_btree.cpp.o
test_btree: CMakeFiles/test_btree.dir/build.make
test_btree: CMakeFiles/test_btree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/yabiel/Documents/ED/entregas/practica 2/binary_tree/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_btree"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_btree.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_btree.dir/build: test_btree
.PHONY : CMakeFiles/test_btree.dir/build

CMakeFiles/test_btree.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_btree.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_btree.dir/clean

CMakeFiles/test_btree.dir/depend:
	cd "/home/yabiel/Documents/ED/entregas/practica 2/binary_tree/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/yabiel/Documents/ED/entregas/practica 2/binary_tree" "/home/yabiel/Documents/ED/entregas/practica 2/binary_tree" "/home/yabiel/Documents/ED/entregas/practica 2/binary_tree/build" "/home/yabiel/Documents/ED/entregas/practica 2/binary_tree/build" "/home/yabiel/Documents/ED/entregas/practica 2/binary_tree/build/CMakeFiles/test_btree.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/test_btree.dir/depend

