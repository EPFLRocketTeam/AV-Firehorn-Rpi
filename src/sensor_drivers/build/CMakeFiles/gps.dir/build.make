# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.27.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.27.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/amaurygeorge/Desktop/RocketTeam/2024_C_AV_RPI/src/sensor_drivers

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/amaurygeorge/Desktop/RocketTeam/2024_C_AV_RPI/src/sensor_drivers/build

# Include any dependencies generated for this target.
include CMakeFiles/gps.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/gps.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/gps.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gps.dir/flags.make

CMakeFiles/gps.dir/I2CGPS.o: CMakeFiles/gps.dir/flags.make
CMakeFiles/gps.dir/I2CGPS.o: /Users/amaurygeorge/Desktop/RocketTeam/2024_C_AV_RPI/src/sensor_drivers/I2CGPS.cpp
CMakeFiles/gps.dir/I2CGPS.o: CMakeFiles/gps.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/amaurygeorge/Desktop/RocketTeam/2024_C_AV_RPI/src/sensor_drivers/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/gps.dir/I2CGPS.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/gps.dir/I2CGPS.o -MF CMakeFiles/gps.dir/I2CGPS.o.d -o CMakeFiles/gps.dir/I2CGPS.o -c /Users/amaurygeorge/Desktop/RocketTeam/2024_C_AV_RPI/src/sensor_drivers/I2CGPS.cpp

CMakeFiles/gps.dir/I2CGPS.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/gps.dir/I2CGPS.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/amaurygeorge/Desktop/RocketTeam/2024_C_AV_RPI/src/sensor_drivers/I2CGPS.cpp > CMakeFiles/gps.dir/I2CGPS.i

CMakeFiles/gps.dir/I2CGPS.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/gps.dir/I2CGPS.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/amaurygeorge/Desktop/RocketTeam/2024_C_AV_RPI/src/sensor_drivers/I2CGPS.cpp -o CMakeFiles/gps.dir/I2CGPS.s

CMakeFiles/gps.dir/TinyGPS++.o: CMakeFiles/gps.dir/flags.make
CMakeFiles/gps.dir/TinyGPS++.o: /Users/amaurygeorge/Desktop/RocketTeam/2024_C_AV_RPI/src/sensor_drivers/TinyGPS++.cpp
CMakeFiles/gps.dir/TinyGPS++.o: CMakeFiles/gps.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/amaurygeorge/Desktop/RocketTeam/2024_C_AV_RPI/src/sensor_drivers/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/gps.dir/TinyGPS++.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/gps.dir/TinyGPS++.o -MF CMakeFiles/gps.dir/TinyGPS++.o.d -o CMakeFiles/gps.dir/TinyGPS++.o -c /Users/amaurygeorge/Desktop/RocketTeam/2024_C_AV_RPI/src/sensor_drivers/TinyGPS++.cpp

CMakeFiles/gps.dir/TinyGPS++.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/gps.dir/TinyGPS++.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/amaurygeorge/Desktop/RocketTeam/2024_C_AV_RPI/src/sensor_drivers/TinyGPS++.cpp > CMakeFiles/gps.dir/TinyGPS++.i

CMakeFiles/gps.dir/TinyGPS++.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/gps.dir/TinyGPS++.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/amaurygeorge/Desktop/RocketTeam/2024_C_AV_RPI/src/sensor_drivers/TinyGPS++.cpp -o CMakeFiles/gps.dir/TinyGPS++.s

# Object files for target gps
gps_OBJECTS = \
"CMakeFiles/gps.dir/I2CGPS.o" \
"CMakeFiles/gps.dir/TinyGPS++.o"

# External object files for target gps
gps_EXTERNAL_OBJECTS =

libgps.a: CMakeFiles/gps.dir/I2CGPS.o
libgps.a: CMakeFiles/gps.dir/TinyGPS++.o
libgps.a: CMakeFiles/gps.dir/build.make
libgps.a: CMakeFiles/gps.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/amaurygeorge/Desktop/RocketTeam/2024_C_AV_RPI/src/sensor_drivers/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libgps.a"
	$(CMAKE_COMMAND) -P CMakeFiles/gps.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gps.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gps.dir/build: libgps.a
.PHONY : CMakeFiles/gps.dir/build

CMakeFiles/gps.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gps.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gps.dir/clean

CMakeFiles/gps.dir/depend:
	cd /Users/amaurygeorge/Desktop/RocketTeam/2024_C_AV_RPI/src/sensor_drivers/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/amaurygeorge/Desktop/RocketTeam/2024_C_AV_RPI/src/sensor_drivers /Users/amaurygeorge/Desktop/RocketTeam/2024_C_AV_RPI/src/sensor_drivers /Users/amaurygeorge/Desktop/RocketTeam/2024_C_AV_RPI/src/sensor_drivers/build /Users/amaurygeorge/Desktop/RocketTeam/2024_C_AV_RPI/src/sensor_drivers/build /Users/amaurygeorge/Desktop/RocketTeam/2024_C_AV_RPI/src/sensor_drivers/build/CMakeFiles/gps.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/gps.dir/depend

