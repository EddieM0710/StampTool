# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /sandbox/Development/AlbumGenerator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /sandbox/Development/AlbumGenerator/build

# Include any dependencies generated for this target.
include src/CMakeFiles/StampTool.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/StampTool.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/StampTool.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/StampTool.dir/flags.make

src/CMakeFiles/StampTool.dir/StampToolApp.cpp.o: src/CMakeFiles/StampTool.dir/flags.make
src/CMakeFiles/StampTool.dir/StampToolApp.cpp.o: /sandbox/Development/AlbumGenerator/src/StampToolApp.cpp
src/CMakeFiles/StampTool.dir/StampToolApp.cpp.o: src/CMakeFiles/StampTool.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/sandbox/Development/AlbumGenerator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/StampTool.dir/StampToolApp.cpp.o"
	cd /sandbox/Development/AlbumGenerator/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/StampTool.dir/StampToolApp.cpp.o -MF CMakeFiles/StampTool.dir/StampToolApp.cpp.o.d -o CMakeFiles/StampTool.dir/StampToolApp.cpp.o -c /sandbox/Development/AlbumGenerator/src/StampToolApp.cpp

src/CMakeFiles/StampTool.dir/StampToolApp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/StampTool.dir/StampToolApp.cpp.i"
	cd /sandbox/Development/AlbumGenerator/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /sandbox/Development/AlbumGenerator/src/StampToolApp.cpp > CMakeFiles/StampTool.dir/StampToolApp.cpp.i

src/CMakeFiles/StampTool.dir/StampToolApp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/StampTool.dir/StampToolApp.cpp.s"
	cd /sandbox/Development/AlbumGenerator/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /sandbox/Development/AlbumGenerator/src/StampToolApp.cpp -o CMakeFiles/StampTool.dir/StampToolApp.cpp.s

src/CMakeFiles/StampTool.dir/Defs.cpp.o: src/CMakeFiles/StampTool.dir/flags.make
src/CMakeFiles/StampTool.dir/Defs.cpp.o: /sandbox/Development/AlbumGenerator/src/Defs.cpp
src/CMakeFiles/StampTool.dir/Defs.cpp.o: src/CMakeFiles/StampTool.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/sandbox/Development/AlbumGenerator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/StampTool.dir/Defs.cpp.o"
	cd /sandbox/Development/AlbumGenerator/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/StampTool.dir/Defs.cpp.o -MF CMakeFiles/StampTool.dir/Defs.cpp.o.d -o CMakeFiles/StampTool.dir/Defs.cpp.o -c /sandbox/Development/AlbumGenerator/src/Defs.cpp

src/CMakeFiles/StampTool.dir/Defs.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/StampTool.dir/Defs.cpp.i"
	cd /sandbox/Development/AlbumGenerator/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /sandbox/Development/AlbumGenerator/src/Defs.cpp > CMakeFiles/StampTool.dir/Defs.cpp.i

src/CMakeFiles/StampTool.dir/Defs.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/StampTool.dir/Defs.cpp.s"
	cd /sandbox/Development/AlbumGenerator/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /sandbox/Development/AlbumGenerator/src/Defs.cpp -o CMakeFiles/StampTool.dir/Defs.cpp.s

# Object files for target StampTool
StampTool_OBJECTS = \
"CMakeFiles/StampTool.dir/StampToolApp.cpp.o" \
"CMakeFiles/StampTool.dir/Defs.cpp.o"

# External object files for target StampTool
StampTool_EXTERNAL_OBJECTS =

StampTool: src/CMakeFiles/StampTool.dir/StampToolApp.cpp.o
StampTool: src/CMakeFiles/StampTool.dir/Defs.cpp.o
StampTool: src/CMakeFiles/StampTool.dir/build.make
StampTool: src/gui/libGuiFiles.so
StampTool: src/design/libDesignFiles.so
StampTool: src/catalog/libCatalogFiles.so
StampTool: src/utils/libUtils.so
StampTool: src/CMakeFiles/StampTool.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/sandbox/Development/AlbumGenerator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ../StampTool"
	cd /sandbox/Development/AlbumGenerator/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/StampTool.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/StampTool.dir/build: StampTool
.PHONY : src/CMakeFiles/StampTool.dir/build

src/CMakeFiles/StampTool.dir/clean:
	cd /sandbox/Development/AlbumGenerator/build/src && $(CMAKE_COMMAND) -P CMakeFiles/StampTool.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/StampTool.dir/clean

src/CMakeFiles/StampTool.dir/depend:
	cd /sandbox/Development/AlbumGenerator/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /sandbox/Development/AlbumGenerator /sandbox/Development/AlbumGenerator/src /sandbox/Development/AlbumGenerator/build /sandbox/Development/AlbumGenerator/build/src /sandbox/Development/AlbumGenerator/build/src/CMakeFiles/StampTool.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/StampTool.dir/depend
