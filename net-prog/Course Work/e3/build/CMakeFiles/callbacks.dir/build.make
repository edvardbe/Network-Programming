# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/edvardeek/Documents/University/V2025 Semester/Network Programming/net-prog/Course Work/e3"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/edvardeek/Documents/University/V2025 Semester/Network Programming/net-prog/Course Work/e3/build"

# Include any dependencies generated for this target.
include CMakeFiles/callbacks.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/callbacks.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/callbacks.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/callbacks.dir/flags.make

CMakeFiles/callbacks.dir/codegen:
.PHONY : CMakeFiles/callbacks.dir/codegen

CMakeFiles/callbacks.dir/callbacks.cpp.o: CMakeFiles/callbacks.dir/flags.make
CMakeFiles/callbacks.dir/callbacks.cpp.o: /Users/edvardeek/Documents/University/V2025\ Semester/Network\ Programming/net-prog/Course\ Work/e3/callbacks.cpp
CMakeFiles/callbacks.dir/callbacks.cpp.o: CMakeFiles/callbacks.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/edvardeek/Documents/University/V2025 Semester/Network Programming/net-prog/Course Work/e3/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/callbacks.dir/callbacks.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/callbacks.dir/callbacks.cpp.o -MF CMakeFiles/callbacks.dir/callbacks.cpp.o.d -o CMakeFiles/callbacks.dir/callbacks.cpp.o -c "/Users/edvardeek/Documents/University/V2025 Semester/Network Programming/net-prog/Course Work/e3/callbacks.cpp"

CMakeFiles/callbacks.dir/callbacks.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/callbacks.dir/callbacks.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/edvardeek/Documents/University/V2025 Semester/Network Programming/net-prog/Course Work/e3/callbacks.cpp" > CMakeFiles/callbacks.dir/callbacks.cpp.i

CMakeFiles/callbacks.dir/callbacks.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/callbacks.dir/callbacks.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/edvardeek/Documents/University/V2025 Semester/Network Programming/net-prog/Course Work/e3/callbacks.cpp" -o CMakeFiles/callbacks.dir/callbacks.cpp.s

# Object files for target callbacks
callbacks_OBJECTS = \
"CMakeFiles/callbacks.dir/callbacks.cpp.o"

# External object files for target callbacks
callbacks_EXTERNAL_OBJECTS =

callbacks: CMakeFiles/callbacks.dir/callbacks.cpp.o
callbacks: CMakeFiles/callbacks.dir/build.make
callbacks: CMakeFiles/callbacks.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/Users/edvardeek/Documents/University/V2025 Semester/Network Programming/net-prog/Course Work/e3/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable callbacks"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/callbacks.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/callbacks.dir/build: callbacks
.PHONY : CMakeFiles/callbacks.dir/build

CMakeFiles/callbacks.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/callbacks.dir/cmake_clean.cmake
.PHONY : CMakeFiles/callbacks.dir/clean

CMakeFiles/callbacks.dir/depend:
	cd "/Users/edvardeek/Documents/University/V2025 Semester/Network Programming/net-prog/Course Work/e3/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/edvardeek/Documents/University/V2025 Semester/Network Programming/net-prog/Course Work/e3" "/Users/edvardeek/Documents/University/V2025 Semester/Network Programming/net-prog/Course Work/e3" "/Users/edvardeek/Documents/University/V2025 Semester/Network Programming/net-prog/Course Work/e3/build" "/Users/edvardeek/Documents/University/V2025 Semester/Network Programming/net-prog/Course Work/e3/build" "/Users/edvardeek/Documents/University/V2025 Semester/Network Programming/net-prog/Course Work/e3/build/CMakeFiles/callbacks.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/callbacks.dir/depend

