# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.26.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.26.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/anthony/CLionProjects/Option_pricer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/anthony/CLionProjects/Option_pricer/build

# Include any dependencies generated for this target.
include tests/unit/CMakeFiles/Unit_tests.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/unit/CMakeFiles/Unit_tests.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/unit/CMakeFiles/Unit_tests.dir/progress.make

# Include the compile flags for this target's objects.
include tests/unit/CMakeFiles/Unit_tests.dir/flags.make

tests/unit/CMakeFiles/Unit_tests.dir/__/test_main.cpp.o: tests/unit/CMakeFiles/Unit_tests.dir/flags.make
tests/unit/CMakeFiles/Unit_tests.dir/__/test_main.cpp.o: /Users/anthony/CLionProjects/Option_pricer/tests/test_main.cpp
tests/unit/CMakeFiles/Unit_tests.dir/__/test_main.cpp.o: tests/unit/CMakeFiles/Unit_tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/anthony/CLionProjects/Option_pricer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/unit/CMakeFiles/Unit_tests.dir/__/test_main.cpp.o"
	cd /Users/anthony/CLionProjects/Option_pricer/build/tests/unit && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/unit/CMakeFiles/Unit_tests.dir/__/test_main.cpp.o -MF CMakeFiles/Unit_tests.dir/__/test_main.cpp.o.d -o CMakeFiles/Unit_tests.dir/__/test_main.cpp.o -c /Users/anthony/CLionProjects/Option_pricer/tests/test_main.cpp

tests/unit/CMakeFiles/Unit_tests.dir/__/test_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Unit_tests.dir/__/test_main.cpp.i"
	cd /Users/anthony/CLionProjects/Option_pricer/build/tests/unit && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/anthony/CLionProjects/Option_pricer/tests/test_main.cpp > CMakeFiles/Unit_tests.dir/__/test_main.cpp.i

tests/unit/CMakeFiles/Unit_tests.dir/__/test_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Unit_tests.dir/__/test_main.cpp.s"
	cd /Users/anthony/CLionProjects/Option_pricer/build/tests/unit && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/anthony/CLionProjects/Option_pricer/tests/test_main.cpp -o CMakeFiles/Unit_tests.dir/__/test_main.cpp.s

tests/unit/CMakeFiles/Unit_tests.dir/test_market_data.cpp.o: tests/unit/CMakeFiles/Unit_tests.dir/flags.make
tests/unit/CMakeFiles/Unit_tests.dir/test_market_data.cpp.o: /Users/anthony/CLionProjects/Option_pricer/tests/unit/test_market_data.cpp
tests/unit/CMakeFiles/Unit_tests.dir/test_market_data.cpp.o: tests/unit/CMakeFiles/Unit_tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/anthony/CLionProjects/Option_pricer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object tests/unit/CMakeFiles/Unit_tests.dir/test_market_data.cpp.o"
	cd /Users/anthony/CLionProjects/Option_pricer/build/tests/unit && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/unit/CMakeFiles/Unit_tests.dir/test_market_data.cpp.o -MF CMakeFiles/Unit_tests.dir/test_market_data.cpp.o.d -o CMakeFiles/Unit_tests.dir/test_market_data.cpp.o -c /Users/anthony/CLionProjects/Option_pricer/tests/unit/test_market_data.cpp

tests/unit/CMakeFiles/Unit_tests.dir/test_market_data.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Unit_tests.dir/test_market_data.cpp.i"
	cd /Users/anthony/CLionProjects/Option_pricer/build/tests/unit && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/anthony/CLionProjects/Option_pricer/tests/unit/test_market_data.cpp > CMakeFiles/Unit_tests.dir/test_market_data.cpp.i

tests/unit/CMakeFiles/Unit_tests.dir/test_market_data.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Unit_tests.dir/test_market_data.cpp.s"
	cd /Users/anthony/CLionProjects/Option_pricer/build/tests/unit && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/anthony/CLionProjects/Option_pricer/tests/unit/test_market_data.cpp -o CMakeFiles/Unit_tests.dir/test_market_data.cpp.s

tests/unit/CMakeFiles/Unit_tests.dir/test_payoff.cpp.o: tests/unit/CMakeFiles/Unit_tests.dir/flags.make
tests/unit/CMakeFiles/Unit_tests.dir/test_payoff.cpp.o: /Users/anthony/CLionProjects/Option_pricer/tests/unit/test_payoff.cpp
tests/unit/CMakeFiles/Unit_tests.dir/test_payoff.cpp.o: tests/unit/CMakeFiles/Unit_tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/anthony/CLionProjects/Option_pricer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object tests/unit/CMakeFiles/Unit_tests.dir/test_payoff.cpp.o"
	cd /Users/anthony/CLionProjects/Option_pricer/build/tests/unit && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/unit/CMakeFiles/Unit_tests.dir/test_payoff.cpp.o -MF CMakeFiles/Unit_tests.dir/test_payoff.cpp.o.d -o CMakeFiles/Unit_tests.dir/test_payoff.cpp.o -c /Users/anthony/CLionProjects/Option_pricer/tests/unit/test_payoff.cpp

tests/unit/CMakeFiles/Unit_tests.dir/test_payoff.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Unit_tests.dir/test_payoff.cpp.i"
	cd /Users/anthony/CLionProjects/Option_pricer/build/tests/unit && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/anthony/CLionProjects/Option_pricer/tests/unit/test_payoff.cpp > CMakeFiles/Unit_tests.dir/test_payoff.cpp.i

tests/unit/CMakeFiles/Unit_tests.dir/test_payoff.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Unit_tests.dir/test_payoff.cpp.s"
	cd /Users/anthony/CLionProjects/Option_pricer/build/tests/unit && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/anthony/CLionProjects/Option_pricer/tests/unit/test_payoff.cpp -o CMakeFiles/Unit_tests.dir/test_payoff.cpp.s

tests/unit/CMakeFiles/Unit_tests.dir/__/__/src/market_data.cpp.o: tests/unit/CMakeFiles/Unit_tests.dir/flags.make
tests/unit/CMakeFiles/Unit_tests.dir/__/__/src/market_data.cpp.o: /Users/anthony/CLionProjects/Option_pricer/src/market_data.cpp
tests/unit/CMakeFiles/Unit_tests.dir/__/__/src/market_data.cpp.o: tests/unit/CMakeFiles/Unit_tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/anthony/CLionProjects/Option_pricer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object tests/unit/CMakeFiles/Unit_tests.dir/__/__/src/market_data.cpp.o"
	cd /Users/anthony/CLionProjects/Option_pricer/build/tests/unit && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/unit/CMakeFiles/Unit_tests.dir/__/__/src/market_data.cpp.o -MF CMakeFiles/Unit_tests.dir/__/__/src/market_data.cpp.o.d -o CMakeFiles/Unit_tests.dir/__/__/src/market_data.cpp.o -c /Users/anthony/CLionProjects/Option_pricer/src/market_data.cpp

tests/unit/CMakeFiles/Unit_tests.dir/__/__/src/market_data.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Unit_tests.dir/__/__/src/market_data.cpp.i"
	cd /Users/anthony/CLionProjects/Option_pricer/build/tests/unit && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/anthony/CLionProjects/Option_pricer/src/market_data.cpp > CMakeFiles/Unit_tests.dir/__/__/src/market_data.cpp.i

tests/unit/CMakeFiles/Unit_tests.dir/__/__/src/market_data.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Unit_tests.dir/__/__/src/market_data.cpp.s"
	cd /Users/anthony/CLionProjects/Option_pricer/build/tests/unit && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/anthony/CLionProjects/Option_pricer/src/market_data.cpp -o CMakeFiles/Unit_tests.dir/__/__/src/market_data.cpp.s

tests/unit/CMakeFiles/Unit_tests.dir/__/__/src/option.cpp.o: tests/unit/CMakeFiles/Unit_tests.dir/flags.make
tests/unit/CMakeFiles/Unit_tests.dir/__/__/src/option.cpp.o: /Users/anthony/CLionProjects/Option_pricer/src/option.cpp
tests/unit/CMakeFiles/Unit_tests.dir/__/__/src/option.cpp.o: tests/unit/CMakeFiles/Unit_tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/anthony/CLionProjects/Option_pricer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object tests/unit/CMakeFiles/Unit_tests.dir/__/__/src/option.cpp.o"
	cd /Users/anthony/CLionProjects/Option_pricer/build/tests/unit && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/unit/CMakeFiles/Unit_tests.dir/__/__/src/option.cpp.o -MF CMakeFiles/Unit_tests.dir/__/__/src/option.cpp.o.d -o CMakeFiles/Unit_tests.dir/__/__/src/option.cpp.o -c /Users/anthony/CLionProjects/Option_pricer/src/option.cpp

tests/unit/CMakeFiles/Unit_tests.dir/__/__/src/option.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Unit_tests.dir/__/__/src/option.cpp.i"
	cd /Users/anthony/CLionProjects/Option_pricer/build/tests/unit && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/anthony/CLionProjects/Option_pricer/src/option.cpp > CMakeFiles/Unit_tests.dir/__/__/src/option.cpp.i

tests/unit/CMakeFiles/Unit_tests.dir/__/__/src/option.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Unit_tests.dir/__/__/src/option.cpp.s"
	cd /Users/anthony/CLionProjects/Option_pricer/build/tests/unit && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/anthony/CLionProjects/Option_pricer/src/option.cpp -o CMakeFiles/Unit_tests.dir/__/__/src/option.cpp.s

tests/unit/CMakeFiles/Unit_tests.dir/__/__/src/payoff.cpp.o: tests/unit/CMakeFiles/Unit_tests.dir/flags.make
tests/unit/CMakeFiles/Unit_tests.dir/__/__/src/payoff.cpp.o: /Users/anthony/CLionProjects/Option_pricer/src/payoff.cpp
tests/unit/CMakeFiles/Unit_tests.dir/__/__/src/payoff.cpp.o: tests/unit/CMakeFiles/Unit_tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/anthony/CLionProjects/Option_pricer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object tests/unit/CMakeFiles/Unit_tests.dir/__/__/src/payoff.cpp.o"
	cd /Users/anthony/CLionProjects/Option_pricer/build/tests/unit && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/unit/CMakeFiles/Unit_tests.dir/__/__/src/payoff.cpp.o -MF CMakeFiles/Unit_tests.dir/__/__/src/payoff.cpp.o.d -o CMakeFiles/Unit_tests.dir/__/__/src/payoff.cpp.o -c /Users/anthony/CLionProjects/Option_pricer/src/payoff.cpp

tests/unit/CMakeFiles/Unit_tests.dir/__/__/src/payoff.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Unit_tests.dir/__/__/src/payoff.cpp.i"
	cd /Users/anthony/CLionProjects/Option_pricer/build/tests/unit && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/anthony/CLionProjects/Option_pricer/src/payoff.cpp > CMakeFiles/Unit_tests.dir/__/__/src/payoff.cpp.i

tests/unit/CMakeFiles/Unit_tests.dir/__/__/src/payoff.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Unit_tests.dir/__/__/src/payoff.cpp.s"
	cd /Users/anthony/CLionProjects/Option_pricer/build/tests/unit && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/anthony/CLionProjects/Option_pricer/src/payoff.cpp -o CMakeFiles/Unit_tests.dir/__/__/src/payoff.cpp.s

# Object files for target Unit_tests
Unit_tests_OBJECTS = \
"CMakeFiles/Unit_tests.dir/__/test_main.cpp.o" \
"CMakeFiles/Unit_tests.dir/test_market_data.cpp.o" \
"CMakeFiles/Unit_tests.dir/test_payoff.cpp.o" \
"CMakeFiles/Unit_tests.dir/__/__/src/market_data.cpp.o" \
"CMakeFiles/Unit_tests.dir/__/__/src/option.cpp.o" \
"CMakeFiles/Unit_tests.dir/__/__/src/payoff.cpp.o"

# External object files for target Unit_tests
Unit_tests_EXTERNAL_OBJECTS =

tests/unit/Unit_tests: tests/unit/CMakeFiles/Unit_tests.dir/__/test_main.cpp.o
tests/unit/Unit_tests: tests/unit/CMakeFiles/Unit_tests.dir/test_market_data.cpp.o
tests/unit/Unit_tests: tests/unit/CMakeFiles/Unit_tests.dir/test_payoff.cpp.o
tests/unit/Unit_tests: tests/unit/CMakeFiles/Unit_tests.dir/__/__/src/market_data.cpp.o
tests/unit/Unit_tests: tests/unit/CMakeFiles/Unit_tests.dir/__/__/src/option.cpp.o
tests/unit/Unit_tests: tests/unit/CMakeFiles/Unit_tests.dir/__/__/src/payoff.cpp.o
tests/unit/Unit_tests: tests/unit/CMakeFiles/Unit_tests.dir/build.make
tests/unit/Unit_tests: /usr/local/lib/libgmock_main.a
tests/unit/Unit_tests: /usr/local/lib/libgtest_main.a
tests/unit/Unit_tests: /usr/local/lib/libgmock.a
tests/unit/Unit_tests: /usr/local/lib/libgtest.a
tests/unit/Unit_tests: tests/unit/CMakeFiles/Unit_tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/anthony/CLionProjects/Option_pricer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable Unit_tests"
	cd /Users/anthony/CLionProjects/Option_pricer/build/tests/unit && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Unit_tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/unit/CMakeFiles/Unit_tests.dir/build: tests/unit/Unit_tests
.PHONY : tests/unit/CMakeFiles/Unit_tests.dir/build

tests/unit/CMakeFiles/Unit_tests.dir/clean:
	cd /Users/anthony/CLionProjects/Option_pricer/build/tests/unit && $(CMAKE_COMMAND) -P CMakeFiles/Unit_tests.dir/cmake_clean.cmake
.PHONY : tests/unit/CMakeFiles/Unit_tests.dir/clean

tests/unit/CMakeFiles/Unit_tests.dir/depend:
	cd /Users/anthony/CLionProjects/Option_pricer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/anthony/CLionProjects/Option_pricer /Users/anthony/CLionProjects/Option_pricer/tests/unit /Users/anthony/CLionProjects/Option_pricer/build /Users/anthony/CLionProjects/Option_pricer/build/tests/unit /Users/anthony/CLionProjects/Option_pricer/build/tests/unit/CMakeFiles/Unit_tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/unit/CMakeFiles/Unit_tests.dir/depend

