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
CMAKE_COMMAND = /home/hkh/clion-2018.1.5/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/hkh/clion-2018.1.5/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hkh/CLionProjects/WebServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hkh/CLionProjects/WebServer/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/WebServer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/WebServer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/WebServer.dir/flags.make

CMakeFiles/WebServer.dir/main.cpp.o: CMakeFiles/WebServer.dir/flags.make
CMakeFiles/WebServer.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hkh/CLionProjects/WebServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/WebServer.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WebServer.dir/main.cpp.o -c /home/hkh/CLionProjects/WebServer/main.cpp

CMakeFiles/WebServer.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WebServer.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hkh/CLionProjects/WebServer/main.cpp > CMakeFiles/WebServer.dir/main.cpp.i

CMakeFiles/WebServer.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WebServer.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hkh/CLionProjects/WebServer/main.cpp -o CMakeFiles/WebServer.dir/main.cpp.s

CMakeFiles/WebServer.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/WebServer.dir/main.cpp.o.requires

CMakeFiles/WebServer.dir/main.cpp.o.provides: CMakeFiles/WebServer.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/WebServer.dir/build.make CMakeFiles/WebServer.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/WebServer.dir/main.cpp.o.provides

CMakeFiles/WebServer.dir/main.cpp.o.provides.build: CMakeFiles/WebServer.dir/main.cpp.o


CMakeFiles/WebServer.dir/src/http_conn.cpp.o: CMakeFiles/WebServer.dir/flags.make
CMakeFiles/WebServer.dir/src/http_conn.cpp.o: ../src/http_conn.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hkh/CLionProjects/WebServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/WebServer.dir/src/http_conn.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WebServer.dir/src/http_conn.cpp.o -c /home/hkh/CLionProjects/WebServer/src/http_conn.cpp

CMakeFiles/WebServer.dir/src/http_conn.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WebServer.dir/src/http_conn.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hkh/CLionProjects/WebServer/src/http_conn.cpp > CMakeFiles/WebServer.dir/src/http_conn.cpp.i

CMakeFiles/WebServer.dir/src/http_conn.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WebServer.dir/src/http_conn.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hkh/CLionProjects/WebServer/src/http_conn.cpp -o CMakeFiles/WebServer.dir/src/http_conn.cpp.s

CMakeFiles/WebServer.dir/src/http_conn.cpp.o.requires:

.PHONY : CMakeFiles/WebServer.dir/src/http_conn.cpp.o.requires

CMakeFiles/WebServer.dir/src/http_conn.cpp.o.provides: CMakeFiles/WebServer.dir/src/http_conn.cpp.o.requires
	$(MAKE) -f CMakeFiles/WebServer.dir/build.make CMakeFiles/WebServer.dir/src/http_conn.cpp.o.provides.build
.PHONY : CMakeFiles/WebServer.dir/src/http_conn.cpp.o.provides

CMakeFiles/WebServer.dir/src/http_conn.cpp.o.provides.build: CMakeFiles/WebServer.dir/src/http_conn.cpp.o


CMakeFiles/WebServer.dir/src/Log.cpp.o: CMakeFiles/WebServer.dir/flags.make
CMakeFiles/WebServer.dir/src/Log.cpp.o: ../src/Log.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hkh/CLionProjects/WebServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/WebServer.dir/src/Log.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WebServer.dir/src/Log.cpp.o -c /home/hkh/CLionProjects/WebServer/src/Log.cpp

CMakeFiles/WebServer.dir/src/Log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WebServer.dir/src/Log.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hkh/CLionProjects/WebServer/src/Log.cpp > CMakeFiles/WebServer.dir/src/Log.cpp.i

CMakeFiles/WebServer.dir/src/Log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WebServer.dir/src/Log.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hkh/CLionProjects/WebServer/src/Log.cpp -o CMakeFiles/WebServer.dir/src/Log.cpp.s

CMakeFiles/WebServer.dir/src/Log.cpp.o.requires:

.PHONY : CMakeFiles/WebServer.dir/src/Log.cpp.o.requires

CMakeFiles/WebServer.dir/src/Log.cpp.o.provides: CMakeFiles/WebServer.dir/src/Log.cpp.o.requires
	$(MAKE) -f CMakeFiles/WebServer.dir/build.make CMakeFiles/WebServer.dir/src/Log.cpp.o.provides.build
.PHONY : CMakeFiles/WebServer.dir/src/Log.cpp.o.provides

CMakeFiles/WebServer.dir/src/Log.cpp.o.provides.build: CMakeFiles/WebServer.dir/src/Log.cpp.o


CMakeFiles/WebServer.dir/src/LogStream.cpp.o: CMakeFiles/WebServer.dir/flags.make
CMakeFiles/WebServer.dir/src/LogStream.cpp.o: ../src/LogStream.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hkh/CLionProjects/WebServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/WebServer.dir/src/LogStream.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WebServer.dir/src/LogStream.cpp.o -c /home/hkh/CLionProjects/WebServer/src/LogStream.cpp

CMakeFiles/WebServer.dir/src/LogStream.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WebServer.dir/src/LogStream.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hkh/CLionProjects/WebServer/src/LogStream.cpp > CMakeFiles/WebServer.dir/src/LogStream.cpp.i

CMakeFiles/WebServer.dir/src/LogStream.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WebServer.dir/src/LogStream.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hkh/CLionProjects/WebServer/src/LogStream.cpp -o CMakeFiles/WebServer.dir/src/LogStream.cpp.s

CMakeFiles/WebServer.dir/src/LogStream.cpp.o.requires:

.PHONY : CMakeFiles/WebServer.dir/src/LogStream.cpp.o.requires

CMakeFiles/WebServer.dir/src/LogStream.cpp.o.provides: CMakeFiles/WebServer.dir/src/LogStream.cpp.o.requires
	$(MAKE) -f CMakeFiles/WebServer.dir/build.make CMakeFiles/WebServer.dir/src/LogStream.cpp.o.provides.build
.PHONY : CMakeFiles/WebServer.dir/src/LogStream.cpp.o.provides

CMakeFiles/WebServer.dir/src/LogStream.cpp.o.provides.build: CMakeFiles/WebServer.dir/src/LogStream.cpp.o


CMakeFiles/WebServer.dir/src/AsyncLogging.cpp.o: CMakeFiles/WebServer.dir/flags.make
CMakeFiles/WebServer.dir/src/AsyncLogging.cpp.o: ../src/AsyncLogging.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hkh/CLionProjects/WebServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/WebServer.dir/src/AsyncLogging.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WebServer.dir/src/AsyncLogging.cpp.o -c /home/hkh/CLionProjects/WebServer/src/AsyncLogging.cpp

CMakeFiles/WebServer.dir/src/AsyncLogging.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WebServer.dir/src/AsyncLogging.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hkh/CLionProjects/WebServer/src/AsyncLogging.cpp > CMakeFiles/WebServer.dir/src/AsyncLogging.cpp.i

CMakeFiles/WebServer.dir/src/AsyncLogging.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WebServer.dir/src/AsyncLogging.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hkh/CLionProjects/WebServer/src/AsyncLogging.cpp -o CMakeFiles/WebServer.dir/src/AsyncLogging.cpp.s

CMakeFiles/WebServer.dir/src/AsyncLogging.cpp.o.requires:

.PHONY : CMakeFiles/WebServer.dir/src/AsyncLogging.cpp.o.requires

CMakeFiles/WebServer.dir/src/AsyncLogging.cpp.o.provides: CMakeFiles/WebServer.dir/src/AsyncLogging.cpp.o.requires
	$(MAKE) -f CMakeFiles/WebServer.dir/build.make CMakeFiles/WebServer.dir/src/AsyncLogging.cpp.o.provides.build
.PHONY : CMakeFiles/WebServer.dir/src/AsyncLogging.cpp.o.provides

CMakeFiles/WebServer.dir/src/AsyncLogging.cpp.o.provides.build: CMakeFiles/WebServer.dir/src/AsyncLogging.cpp.o


CMakeFiles/WebServer.dir/src/LogFile.cpp.o: CMakeFiles/WebServer.dir/flags.make
CMakeFiles/WebServer.dir/src/LogFile.cpp.o: ../src/LogFile.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hkh/CLionProjects/WebServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/WebServer.dir/src/LogFile.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WebServer.dir/src/LogFile.cpp.o -c /home/hkh/CLionProjects/WebServer/src/LogFile.cpp

CMakeFiles/WebServer.dir/src/LogFile.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WebServer.dir/src/LogFile.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hkh/CLionProjects/WebServer/src/LogFile.cpp > CMakeFiles/WebServer.dir/src/LogFile.cpp.i

CMakeFiles/WebServer.dir/src/LogFile.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WebServer.dir/src/LogFile.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hkh/CLionProjects/WebServer/src/LogFile.cpp -o CMakeFiles/WebServer.dir/src/LogFile.cpp.s

CMakeFiles/WebServer.dir/src/LogFile.cpp.o.requires:

.PHONY : CMakeFiles/WebServer.dir/src/LogFile.cpp.o.requires

CMakeFiles/WebServer.dir/src/LogFile.cpp.o.provides: CMakeFiles/WebServer.dir/src/LogFile.cpp.o.requires
	$(MAKE) -f CMakeFiles/WebServer.dir/build.make CMakeFiles/WebServer.dir/src/LogFile.cpp.o.provides.build
.PHONY : CMakeFiles/WebServer.dir/src/LogFile.cpp.o.provides

CMakeFiles/WebServer.dir/src/LogFile.cpp.o.provides.build: CMakeFiles/WebServer.dir/src/LogFile.cpp.o


CMakeFiles/WebServer.dir/src/Thread.cpp.o: CMakeFiles/WebServer.dir/flags.make
CMakeFiles/WebServer.dir/src/Thread.cpp.o: ../src/Thread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hkh/CLionProjects/WebServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/WebServer.dir/src/Thread.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WebServer.dir/src/Thread.cpp.o -c /home/hkh/CLionProjects/WebServer/src/Thread.cpp

CMakeFiles/WebServer.dir/src/Thread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WebServer.dir/src/Thread.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hkh/CLionProjects/WebServer/src/Thread.cpp > CMakeFiles/WebServer.dir/src/Thread.cpp.i

CMakeFiles/WebServer.dir/src/Thread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WebServer.dir/src/Thread.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hkh/CLionProjects/WebServer/src/Thread.cpp -o CMakeFiles/WebServer.dir/src/Thread.cpp.s

CMakeFiles/WebServer.dir/src/Thread.cpp.o.requires:

.PHONY : CMakeFiles/WebServer.dir/src/Thread.cpp.o.requires

CMakeFiles/WebServer.dir/src/Thread.cpp.o.provides: CMakeFiles/WebServer.dir/src/Thread.cpp.o.requires
	$(MAKE) -f CMakeFiles/WebServer.dir/build.make CMakeFiles/WebServer.dir/src/Thread.cpp.o.provides.build
.PHONY : CMakeFiles/WebServer.dir/src/Thread.cpp.o.provides

CMakeFiles/WebServer.dir/src/Thread.cpp.o.provides.build: CMakeFiles/WebServer.dir/src/Thread.cpp.o


CMakeFiles/WebServer.dir/src/Logger.cpp.o: CMakeFiles/WebServer.dir/flags.make
CMakeFiles/WebServer.dir/src/Logger.cpp.o: ../src/Logger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hkh/CLionProjects/WebServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/WebServer.dir/src/Logger.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WebServer.dir/src/Logger.cpp.o -c /home/hkh/CLionProjects/WebServer/src/Logger.cpp

CMakeFiles/WebServer.dir/src/Logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WebServer.dir/src/Logger.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hkh/CLionProjects/WebServer/src/Logger.cpp > CMakeFiles/WebServer.dir/src/Logger.cpp.i

CMakeFiles/WebServer.dir/src/Logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WebServer.dir/src/Logger.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hkh/CLionProjects/WebServer/src/Logger.cpp -o CMakeFiles/WebServer.dir/src/Logger.cpp.s

CMakeFiles/WebServer.dir/src/Logger.cpp.o.requires:

.PHONY : CMakeFiles/WebServer.dir/src/Logger.cpp.o.requires

CMakeFiles/WebServer.dir/src/Logger.cpp.o.provides: CMakeFiles/WebServer.dir/src/Logger.cpp.o.requires
	$(MAKE) -f CMakeFiles/WebServer.dir/build.make CMakeFiles/WebServer.dir/src/Logger.cpp.o.provides.build
.PHONY : CMakeFiles/WebServer.dir/src/Logger.cpp.o.provides

CMakeFiles/WebServer.dir/src/Logger.cpp.o.provides.build: CMakeFiles/WebServer.dir/src/Logger.cpp.o


# Object files for target WebServer
WebServer_OBJECTS = \
"CMakeFiles/WebServer.dir/main.cpp.o" \
"CMakeFiles/WebServer.dir/src/http_conn.cpp.o" \
"CMakeFiles/WebServer.dir/src/Log.cpp.o" \
"CMakeFiles/WebServer.dir/src/LogStream.cpp.o" \
"CMakeFiles/WebServer.dir/src/AsyncLogging.cpp.o" \
"CMakeFiles/WebServer.dir/src/LogFile.cpp.o" \
"CMakeFiles/WebServer.dir/src/Thread.cpp.o" \
"CMakeFiles/WebServer.dir/src/Logger.cpp.o"

# External object files for target WebServer
WebServer_EXTERNAL_OBJECTS =

WebServer: CMakeFiles/WebServer.dir/main.cpp.o
WebServer: CMakeFiles/WebServer.dir/src/http_conn.cpp.o
WebServer: CMakeFiles/WebServer.dir/src/Log.cpp.o
WebServer: CMakeFiles/WebServer.dir/src/LogStream.cpp.o
WebServer: CMakeFiles/WebServer.dir/src/AsyncLogging.cpp.o
WebServer: CMakeFiles/WebServer.dir/src/LogFile.cpp.o
WebServer: CMakeFiles/WebServer.dir/src/Thread.cpp.o
WebServer: CMakeFiles/WebServer.dir/src/Logger.cpp.o
WebServer: CMakeFiles/WebServer.dir/build.make
WebServer: CMakeFiles/WebServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hkh/CLionProjects/WebServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable WebServer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/WebServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/WebServer.dir/build: WebServer

.PHONY : CMakeFiles/WebServer.dir/build

CMakeFiles/WebServer.dir/requires: CMakeFiles/WebServer.dir/main.cpp.o.requires
CMakeFiles/WebServer.dir/requires: CMakeFiles/WebServer.dir/src/http_conn.cpp.o.requires
CMakeFiles/WebServer.dir/requires: CMakeFiles/WebServer.dir/src/Log.cpp.o.requires
CMakeFiles/WebServer.dir/requires: CMakeFiles/WebServer.dir/src/LogStream.cpp.o.requires
CMakeFiles/WebServer.dir/requires: CMakeFiles/WebServer.dir/src/AsyncLogging.cpp.o.requires
CMakeFiles/WebServer.dir/requires: CMakeFiles/WebServer.dir/src/LogFile.cpp.o.requires
CMakeFiles/WebServer.dir/requires: CMakeFiles/WebServer.dir/src/Thread.cpp.o.requires
CMakeFiles/WebServer.dir/requires: CMakeFiles/WebServer.dir/src/Logger.cpp.o.requires

.PHONY : CMakeFiles/WebServer.dir/requires

CMakeFiles/WebServer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/WebServer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/WebServer.dir/clean

CMakeFiles/WebServer.dir/depend:
	cd /home/hkh/CLionProjects/WebServer/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hkh/CLionProjects/WebServer /home/hkh/CLionProjects/WebServer /home/hkh/CLionProjects/WebServer/cmake-build-debug /home/hkh/CLionProjects/WebServer/cmake-build-debug /home/hkh/CLionProjects/WebServer/cmake-build-debug/CMakeFiles/WebServer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/WebServer.dir/depend

