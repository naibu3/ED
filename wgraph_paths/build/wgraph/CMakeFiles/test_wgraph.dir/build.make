# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_SOURCE_DIR = /home/naibu3/ingInformatica/ED/wgraph_paths

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/naibu3/ingInformatica/ED/wgraph_paths/build

# Include any dependencies generated for this target.
include wgraph/CMakeFiles/test_wgraph.dir/depend.make

# Include the progress variables for this target.
include wgraph/CMakeFiles/test_wgraph.dir/progress.make

# Include the compile flags for this target's objects.
include wgraph/CMakeFiles/test_wgraph.dir/flags.make

wgraph/CMakeFiles/test_wgraph.dir/test_wgraph.cpp.o: wgraph/CMakeFiles/test_wgraph.dir/flags.make
wgraph/CMakeFiles/test_wgraph.dir/test_wgraph.cpp.o: ../wgraph/test_wgraph.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/naibu3/ingInformatica/ED/wgraph_paths/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object wgraph/CMakeFiles/test_wgraph.dir/test_wgraph.cpp.o"
	cd /home/naibu3/ingInformatica/ED/wgraph_paths/build/wgraph && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_wgraph.dir/test_wgraph.cpp.o -c /home/naibu3/ingInformatica/ED/wgraph_paths/wgraph/test_wgraph.cpp

wgraph/CMakeFiles/test_wgraph.dir/test_wgraph.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_wgraph.dir/test_wgraph.cpp.i"
	cd /home/naibu3/ingInformatica/ED/wgraph_paths/build/wgraph && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/naibu3/ingInformatica/ED/wgraph_paths/wgraph/test_wgraph.cpp > CMakeFiles/test_wgraph.dir/test_wgraph.cpp.i

wgraph/CMakeFiles/test_wgraph.dir/test_wgraph.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_wgraph.dir/test_wgraph.cpp.s"
	cd /home/naibu3/ingInformatica/ED/wgraph_paths/build/wgraph && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/naibu3/ingInformatica/ED/wgraph_paths/wgraph/test_wgraph.cpp -o CMakeFiles/test_wgraph.dir/test_wgraph.cpp.s

# Object files for target test_wgraph
test_wgraph_OBJECTS = \
"CMakeFiles/test_wgraph.dir/test_wgraph.cpp.o"

# External object files for target test_wgraph
test_wgraph_EXTERNAL_OBJECTS =

wgraph/test_wgraph: wgraph/CMakeFiles/test_wgraph.dir/test_wgraph.cpp.o
wgraph/test_wgraph: wgraph/CMakeFiles/test_wgraph.dir/build.make
wgraph/test_wgraph: wgraph/libwgraph.a
wgraph/test_wgraph: wgraph/CMakeFiles/test_wgraph.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/naibu3/ingInformatica/ED/wgraph_paths/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_wgraph"
	cd /home/naibu3/ingInformatica/ED/wgraph_paths/build/wgraph && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_wgraph.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
wgraph/CMakeFiles/test_wgraph.dir/build: wgraph/test_wgraph

.PHONY : wgraph/CMakeFiles/test_wgraph.dir/build

wgraph/CMakeFiles/test_wgraph.dir/clean:
	cd /home/naibu3/ingInformatica/ED/wgraph_paths/build/wgraph && $(CMAKE_COMMAND) -P CMakeFiles/test_wgraph.dir/cmake_clean.cmake
.PHONY : wgraph/CMakeFiles/test_wgraph.dir/clean

wgraph/CMakeFiles/test_wgraph.dir/depend:
	cd /home/naibu3/ingInformatica/ED/wgraph_paths/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/naibu3/ingInformatica/ED/wgraph_paths /home/naibu3/ingInformatica/ED/wgraph_paths/wgraph /home/naibu3/ingInformatica/ED/wgraph_paths/build /home/naibu3/ingInformatica/ED/wgraph_paths/build/wgraph /home/naibu3/ingInformatica/ED/wgraph_paths/build/wgraph/CMakeFiles/test_wgraph.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : wgraph/CMakeFiles/test_wgraph.dir/depend
