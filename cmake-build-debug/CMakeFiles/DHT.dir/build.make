# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/anlanyu/CLionProjects/DHT

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/anlanyu/CLionProjects/DHT/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/DHT.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/DHT.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DHT.dir/flags.make

CMakeFiles/DHT.dir/client.cpp.o: CMakeFiles/DHT.dir/flags.make
CMakeFiles/DHT.dir/client.cpp.o: ../client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/anlanyu/CLionProjects/DHT/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DHT.dir/client.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DHT.dir/client.cpp.o -c /Users/anlanyu/CLionProjects/DHT/client.cpp

CMakeFiles/DHT.dir/client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DHT.dir/client.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/anlanyu/CLionProjects/DHT/client.cpp > CMakeFiles/DHT.dir/client.cpp.i

CMakeFiles/DHT.dir/client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DHT.dir/client.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/anlanyu/CLionProjects/DHT/client.cpp -o CMakeFiles/DHT.dir/client.cpp.s

CMakeFiles/DHT.dir/server.cpp.o: CMakeFiles/DHT.dir/flags.make
CMakeFiles/DHT.dir/server.cpp.o: ../server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/anlanyu/CLionProjects/DHT/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/DHT.dir/server.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DHT.dir/server.cpp.o -c /Users/anlanyu/CLionProjects/DHT/server.cpp

CMakeFiles/DHT.dir/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DHT.dir/server.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/anlanyu/CLionProjects/DHT/server.cpp > CMakeFiles/DHT.dir/server.cpp.i

CMakeFiles/DHT.dir/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DHT.dir/server.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/anlanyu/CLionProjects/DHT/server.cpp -o CMakeFiles/DHT.dir/server.cpp.s

# Object files for target DHT
DHT_OBJECTS = \
"CMakeFiles/DHT.dir/client.cpp.o" \
"CMakeFiles/DHT.dir/server.cpp.o"

# External object files for target DHT
DHT_EXTERNAL_OBJECTS =

DHT: CMakeFiles/DHT.dir/client.cpp.o
DHT: CMakeFiles/DHT.dir/server.cpp.o
DHT: CMakeFiles/DHT.dir/build.make
DHT: CMakeFiles/DHT.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/anlanyu/CLionProjects/DHT/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable DHT"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DHT.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DHT.dir/build: DHT

.PHONY : CMakeFiles/DHT.dir/build

CMakeFiles/DHT.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DHT.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DHT.dir/clean

CMakeFiles/DHT.dir/depend:
	cd /Users/anlanyu/CLionProjects/DHT/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/anlanyu/CLionProjects/DHT /Users/anlanyu/CLionProjects/DHT /Users/anlanyu/CLionProjects/DHT/cmake-build-debug /Users/anlanyu/CLionProjects/DHT/cmake-build-debug /Users/anlanyu/CLionProjects/DHT/cmake-build-debug/CMakeFiles/DHT.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DHT.dir/depend

