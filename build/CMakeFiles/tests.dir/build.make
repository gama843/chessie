# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/danielkuchta/kuchtad/project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/danielkuchta/kuchtad/project/build

# Include any dependencies generated for this target.
include CMakeFiles/tests.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/tests.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/tests.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tests.dir/flags.make

CMakeFiles/tests.dir/test/unit_tests.cpp.o: CMakeFiles/tests.dir/flags.make
CMakeFiles/tests.dir/test/unit_tests.cpp.o: /home/danielkuchta/kuchtad/project/test/unit_tests.cpp
CMakeFiles/tests.dir/test/unit_tests.cpp.o: CMakeFiles/tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/danielkuchta/kuchtad/project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tests.dir/test/unit_tests.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tests.dir/test/unit_tests.cpp.o -MF CMakeFiles/tests.dir/test/unit_tests.cpp.o.d -o CMakeFiles/tests.dir/test/unit_tests.cpp.o -c /home/danielkuchta/kuchtad/project/test/unit_tests.cpp

CMakeFiles/tests.dir/test/unit_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/tests.dir/test/unit_tests.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/danielkuchta/kuchtad/project/test/unit_tests.cpp > CMakeFiles/tests.dir/test/unit_tests.cpp.i

CMakeFiles/tests.dir/test/unit_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/tests.dir/test/unit_tests.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/danielkuchta/kuchtad/project/test/unit_tests.cpp -o CMakeFiles/tests.dir/test/unit_tests.cpp.s

CMakeFiles/tests.dir/test/functional_tests.cpp.o: CMakeFiles/tests.dir/flags.make
CMakeFiles/tests.dir/test/functional_tests.cpp.o: /home/danielkuchta/kuchtad/project/test/functional_tests.cpp
CMakeFiles/tests.dir/test/functional_tests.cpp.o: CMakeFiles/tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/danielkuchta/kuchtad/project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/tests.dir/test/functional_tests.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tests.dir/test/functional_tests.cpp.o -MF CMakeFiles/tests.dir/test/functional_tests.cpp.o.d -o CMakeFiles/tests.dir/test/functional_tests.cpp.o -c /home/danielkuchta/kuchtad/project/test/functional_tests.cpp

CMakeFiles/tests.dir/test/functional_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/tests.dir/test/functional_tests.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/danielkuchta/kuchtad/project/test/functional_tests.cpp > CMakeFiles/tests.dir/test/functional_tests.cpp.i

CMakeFiles/tests.dir/test/functional_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/tests.dir/test/functional_tests.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/danielkuchta/kuchtad/project/test/functional_tests.cpp -o CMakeFiles/tests.dir/test/functional_tests.cpp.s

CMakeFiles/tests.dir/test/performance_tests.cpp.o: CMakeFiles/tests.dir/flags.make
CMakeFiles/tests.dir/test/performance_tests.cpp.o: /home/danielkuchta/kuchtad/project/test/performance_tests.cpp
CMakeFiles/tests.dir/test/performance_tests.cpp.o: CMakeFiles/tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/danielkuchta/kuchtad/project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/tests.dir/test/performance_tests.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tests.dir/test/performance_tests.cpp.o -MF CMakeFiles/tests.dir/test/performance_tests.cpp.o.d -o CMakeFiles/tests.dir/test/performance_tests.cpp.o -c /home/danielkuchta/kuchtad/project/test/performance_tests.cpp

CMakeFiles/tests.dir/test/performance_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/tests.dir/test/performance_tests.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/danielkuchta/kuchtad/project/test/performance_tests.cpp > CMakeFiles/tests.dir/test/performance_tests.cpp.i

CMakeFiles/tests.dir/test/performance_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/tests.dir/test/performance_tests.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/danielkuchta/kuchtad/project/test/performance_tests.cpp -o CMakeFiles/tests.dir/test/performance_tests.cpp.s

CMakeFiles/tests.dir/src/chessengine.cpp.o: CMakeFiles/tests.dir/flags.make
CMakeFiles/tests.dir/src/chessengine.cpp.o: /home/danielkuchta/kuchtad/project/src/chessengine.cpp
CMakeFiles/tests.dir/src/chessengine.cpp.o: CMakeFiles/tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/danielkuchta/kuchtad/project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/tests.dir/src/chessengine.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tests.dir/src/chessengine.cpp.o -MF CMakeFiles/tests.dir/src/chessengine.cpp.o.d -o CMakeFiles/tests.dir/src/chessengine.cpp.o -c /home/danielkuchta/kuchtad/project/src/chessengine.cpp

CMakeFiles/tests.dir/src/chessengine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/tests.dir/src/chessengine.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/danielkuchta/kuchtad/project/src/chessengine.cpp > CMakeFiles/tests.dir/src/chessengine.cpp.i

CMakeFiles/tests.dir/src/chessengine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/tests.dir/src/chessengine.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/danielkuchta/kuchtad/project/src/chessengine.cpp -o CMakeFiles/tests.dir/src/chessengine.cpp.s

CMakeFiles/tests.dir/src/moveexecutor.cpp.o: CMakeFiles/tests.dir/flags.make
CMakeFiles/tests.dir/src/moveexecutor.cpp.o: /home/danielkuchta/kuchtad/project/src/moveexecutor.cpp
CMakeFiles/tests.dir/src/moveexecutor.cpp.o: CMakeFiles/tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/danielkuchta/kuchtad/project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/tests.dir/src/moveexecutor.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tests.dir/src/moveexecutor.cpp.o -MF CMakeFiles/tests.dir/src/moveexecutor.cpp.o.d -o CMakeFiles/tests.dir/src/moveexecutor.cpp.o -c /home/danielkuchta/kuchtad/project/src/moveexecutor.cpp

CMakeFiles/tests.dir/src/moveexecutor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/tests.dir/src/moveexecutor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/danielkuchta/kuchtad/project/src/moveexecutor.cpp > CMakeFiles/tests.dir/src/moveexecutor.cpp.i

CMakeFiles/tests.dir/src/moveexecutor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/tests.dir/src/moveexecutor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/danielkuchta/kuchtad/project/src/moveexecutor.cpp -o CMakeFiles/tests.dir/src/moveexecutor.cpp.s

CMakeFiles/tests.dir/src/movegenerator.cpp.o: CMakeFiles/tests.dir/flags.make
CMakeFiles/tests.dir/src/movegenerator.cpp.o: /home/danielkuchta/kuchtad/project/src/movegenerator.cpp
CMakeFiles/tests.dir/src/movegenerator.cpp.o: CMakeFiles/tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/danielkuchta/kuchtad/project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/tests.dir/src/movegenerator.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tests.dir/src/movegenerator.cpp.o -MF CMakeFiles/tests.dir/src/movegenerator.cpp.o.d -o CMakeFiles/tests.dir/src/movegenerator.cpp.o -c /home/danielkuchta/kuchtad/project/src/movegenerator.cpp

CMakeFiles/tests.dir/src/movegenerator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/tests.dir/src/movegenerator.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/danielkuchta/kuchtad/project/src/movegenerator.cpp > CMakeFiles/tests.dir/src/movegenerator.cpp.i

CMakeFiles/tests.dir/src/movegenerator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/tests.dir/src/movegenerator.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/danielkuchta/kuchtad/project/src/movegenerator.cpp -o CMakeFiles/tests.dir/src/movegenerator.cpp.s

CMakeFiles/tests.dir/src/movevalidator.cpp.o: CMakeFiles/tests.dir/flags.make
CMakeFiles/tests.dir/src/movevalidator.cpp.o: /home/danielkuchta/kuchtad/project/src/movevalidator.cpp
CMakeFiles/tests.dir/src/movevalidator.cpp.o: CMakeFiles/tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/danielkuchta/kuchtad/project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/tests.dir/src/movevalidator.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tests.dir/src/movevalidator.cpp.o -MF CMakeFiles/tests.dir/src/movevalidator.cpp.o.d -o CMakeFiles/tests.dir/src/movevalidator.cpp.o -c /home/danielkuchta/kuchtad/project/src/movevalidator.cpp

CMakeFiles/tests.dir/src/movevalidator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/tests.dir/src/movevalidator.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/danielkuchta/kuchtad/project/src/movevalidator.cpp > CMakeFiles/tests.dir/src/movevalidator.cpp.i

CMakeFiles/tests.dir/src/movevalidator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/tests.dir/src/movevalidator.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/danielkuchta/kuchtad/project/src/movevalidator.cpp -o CMakeFiles/tests.dir/src/movevalidator.cpp.s

CMakeFiles/tests.dir/src/utils.cpp.o: CMakeFiles/tests.dir/flags.make
CMakeFiles/tests.dir/src/utils.cpp.o: /home/danielkuchta/kuchtad/project/src/utils.cpp
CMakeFiles/tests.dir/src/utils.cpp.o: CMakeFiles/tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/danielkuchta/kuchtad/project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/tests.dir/src/utils.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tests.dir/src/utils.cpp.o -MF CMakeFiles/tests.dir/src/utils.cpp.o.d -o CMakeFiles/tests.dir/src/utils.cpp.o -c /home/danielkuchta/kuchtad/project/src/utils.cpp

CMakeFiles/tests.dir/src/utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/tests.dir/src/utils.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/danielkuchta/kuchtad/project/src/utils.cpp > CMakeFiles/tests.dir/src/utils.cpp.i

CMakeFiles/tests.dir/src/utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/tests.dir/src/utils.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/danielkuchta/kuchtad/project/src/utils.cpp -o CMakeFiles/tests.dir/src/utils.cpp.s

# Object files for target tests
tests_OBJECTS = \
"CMakeFiles/tests.dir/test/unit_tests.cpp.o" \
"CMakeFiles/tests.dir/test/functional_tests.cpp.o" \
"CMakeFiles/tests.dir/test/performance_tests.cpp.o" \
"CMakeFiles/tests.dir/src/chessengine.cpp.o" \
"CMakeFiles/tests.dir/src/moveexecutor.cpp.o" \
"CMakeFiles/tests.dir/src/movegenerator.cpp.o" \
"CMakeFiles/tests.dir/src/movevalidator.cpp.o" \
"CMakeFiles/tests.dir/src/utils.cpp.o"

# External object files for target tests
tests_EXTERNAL_OBJECTS =

tests: CMakeFiles/tests.dir/test/unit_tests.cpp.o
tests: CMakeFiles/tests.dir/test/functional_tests.cpp.o
tests: CMakeFiles/tests.dir/test/performance_tests.cpp.o
tests: CMakeFiles/tests.dir/src/chessengine.cpp.o
tests: CMakeFiles/tests.dir/src/moveexecutor.cpp.o
tests: CMakeFiles/tests.dir/src/movegenerator.cpp.o
tests: CMakeFiles/tests.dir/src/movevalidator.cpp.o
tests: CMakeFiles/tests.dir/src/utils.cpp.o
tests: CMakeFiles/tests.dir/build.make
tests: lib/libgtest.a
tests: lib/libgtest_main.a
tests: lib/libgtest.a
tests: CMakeFiles/tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/danielkuchta/kuchtad/project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable tests"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tests.dir/build: tests
.PHONY : CMakeFiles/tests.dir/build

CMakeFiles/tests.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tests.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tests.dir/clean

CMakeFiles/tests.dir/depend:
	cd /home/danielkuchta/kuchtad/project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/danielkuchta/kuchtad/project /home/danielkuchta/kuchtad/project /home/danielkuchta/kuchtad/project/build /home/danielkuchta/kuchtad/project/build /home/danielkuchta/kuchtad/project/build/CMakeFiles/tests.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/tests.dir/depend

