# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/scionti/CombLayer-Vespa

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/scionti/CombLayer-Vespa

# Include any dependencies generated for this target.
include CMakeFiles/libimat.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/libimat.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/libimat.dir/flags.make

CMakeFiles/libimat.dir/Model/imat/IMatBulkInsert.cxx.o: CMakeFiles/libimat.dir/flags.make
CMakeFiles/libimat.dir/Model/imat/IMatBulkInsert.cxx.o: Model/imat/IMatBulkInsert.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/scionti/CombLayer-Vespa/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/libimat.dir/Model/imat/IMatBulkInsert.cxx.o"
	g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libimat.dir/Model/imat/IMatBulkInsert.cxx.o -c /home/scionti/CombLayer-Vespa/Model/imat/IMatBulkInsert.cxx

CMakeFiles/libimat.dir/Model/imat/IMatBulkInsert.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libimat.dir/Model/imat/IMatBulkInsert.cxx.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/scionti/CombLayer-Vespa/Model/imat/IMatBulkInsert.cxx > CMakeFiles/libimat.dir/Model/imat/IMatBulkInsert.cxx.i

CMakeFiles/libimat.dir/Model/imat/IMatBulkInsert.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libimat.dir/Model/imat/IMatBulkInsert.cxx.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/scionti/CombLayer-Vespa/Model/imat/IMatBulkInsert.cxx -o CMakeFiles/libimat.dir/Model/imat/IMatBulkInsert.cxx.s

CMakeFiles/libimat.dir/Model/imat/IMatBulkInsert.cxx.o.requires:

.PHONY : CMakeFiles/libimat.dir/Model/imat/IMatBulkInsert.cxx.o.requires

CMakeFiles/libimat.dir/Model/imat/IMatBulkInsert.cxx.o.provides: CMakeFiles/libimat.dir/Model/imat/IMatBulkInsert.cxx.o.requires
	$(MAKE) -f CMakeFiles/libimat.dir/build.make CMakeFiles/libimat.dir/Model/imat/IMatBulkInsert.cxx.o.provides.build
.PHONY : CMakeFiles/libimat.dir/Model/imat/IMatBulkInsert.cxx.o.provides

CMakeFiles/libimat.dir/Model/imat/IMatBulkInsert.cxx.o.provides.build: CMakeFiles/libimat.dir/Model/imat/IMatBulkInsert.cxx.o


CMakeFiles/libimat.dir/Model/imat/IMatChopper.cxx.o: CMakeFiles/libimat.dir/flags.make
CMakeFiles/libimat.dir/Model/imat/IMatChopper.cxx.o: Model/imat/IMatChopper.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/scionti/CombLayer-Vespa/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/libimat.dir/Model/imat/IMatChopper.cxx.o"
	g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libimat.dir/Model/imat/IMatChopper.cxx.o -c /home/scionti/CombLayer-Vespa/Model/imat/IMatChopper.cxx

CMakeFiles/libimat.dir/Model/imat/IMatChopper.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libimat.dir/Model/imat/IMatChopper.cxx.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/scionti/CombLayer-Vespa/Model/imat/IMatChopper.cxx > CMakeFiles/libimat.dir/Model/imat/IMatChopper.cxx.i

CMakeFiles/libimat.dir/Model/imat/IMatChopper.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libimat.dir/Model/imat/IMatChopper.cxx.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/scionti/CombLayer-Vespa/Model/imat/IMatChopper.cxx -o CMakeFiles/libimat.dir/Model/imat/IMatChopper.cxx.s

CMakeFiles/libimat.dir/Model/imat/IMatChopper.cxx.o.requires:

.PHONY : CMakeFiles/libimat.dir/Model/imat/IMatChopper.cxx.o.requires

CMakeFiles/libimat.dir/Model/imat/IMatChopper.cxx.o.provides: CMakeFiles/libimat.dir/Model/imat/IMatChopper.cxx.o.requires
	$(MAKE) -f CMakeFiles/libimat.dir/build.make CMakeFiles/libimat.dir/Model/imat/IMatChopper.cxx.o.provides.build
.PHONY : CMakeFiles/libimat.dir/Model/imat/IMatChopper.cxx.o.provides

CMakeFiles/libimat.dir/Model/imat/IMatChopper.cxx.o.provides.build: CMakeFiles/libimat.dir/Model/imat/IMatChopper.cxx.o


CMakeFiles/libimat.dir/Model/imat/IMatGuide.cxx.o: CMakeFiles/libimat.dir/flags.make
CMakeFiles/libimat.dir/Model/imat/IMatGuide.cxx.o: Model/imat/IMatGuide.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/scionti/CombLayer-Vespa/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/libimat.dir/Model/imat/IMatGuide.cxx.o"
	g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libimat.dir/Model/imat/IMatGuide.cxx.o -c /home/scionti/CombLayer-Vespa/Model/imat/IMatGuide.cxx

CMakeFiles/libimat.dir/Model/imat/IMatGuide.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libimat.dir/Model/imat/IMatGuide.cxx.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/scionti/CombLayer-Vespa/Model/imat/IMatGuide.cxx > CMakeFiles/libimat.dir/Model/imat/IMatGuide.cxx.i

CMakeFiles/libimat.dir/Model/imat/IMatGuide.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libimat.dir/Model/imat/IMatGuide.cxx.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/scionti/CombLayer-Vespa/Model/imat/IMatGuide.cxx -o CMakeFiles/libimat.dir/Model/imat/IMatGuide.cxx.s

CMakeFiles/libimat.dir/Model/imat/IMatGuide.cxx.o.requires:

.PHONY : CMakeFiles/libimat.dir/Model/imat/IMatGuide.cxx.o.requires

CMakeFiles/libimat.dir/Model/imat/IMatGuide.cxx.o.provides: CMakeFiles/libimat.dir/Model/imat/IMatGuide.cxx.o.requires
	$(MAKE) -f CMakeFiles/libimat.dir/build.make CMakeFiles/libimat.dir/Model/imat/IMatGuide.cxx.o.provides.build
.PHONY : CMakeFiles/libimat.dir/Model/imat/IMatGuide.cxx.o.provides

CMakeFiles/libimat.dir/Model/imat/IMatGuide.cxx.o.provides.build: CMakeFiles/libimat.dir/Model/imat/IMatGuide.cxx.o


CMakeFiles/libimat.dir/Model/imat/IMatPrimGuide.cxx.o: CMakeFiles/libimat.dir/flags.make
CMakeFiles/libimat.dir/Model/imat/IMatPrimGuide.cxx.o: Model/imat/IMatPrimGuide.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/scionti/CombLayer-Vespa/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/libimat.dir/Model/imat/IMatPrimGuide.cxx.o"
	g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libimat.dir/Model/imat/IMatPrimGuide.cxx.o -c /home/scionti/CombLayer-Vespa/Model/imat/IMatPrimGuide.cxx

CMakeFiles/libimat.dir/Model/imat/IMatPrimGuide.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libimat.dir/Model/imat/IMatPrimGuide.cxx.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/scionti/CombLayer-Vespa/Model/imat/IMatPrimGuide.cxx > CMakeFiles/libimat.dir/Model/imat/IMatPrimGuide.cxx.i

CMakeFiles/libimat.dir/Model/imat/IMatPrimGuide.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libimat.dir/Model/imat/IMatPrimGuide.cxx.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/scionti/CombLayer-Vespa/Model/imat/IMatPrimGuide.cxx -o CMakeFiles/libimat.dir/Model/imat/IMatPrimGuide.cxx.s

CMakeFiles/libimat.dir/Model/imat/IMatPrimGuide.cxx.o.requires:

.PHONY : CMakeFiles/libimat.dir/Model/imat/IMatPrimGuide.cxx.o.requires

CMakeFiles/libimat.dir/Model/imat/IMatPrimGuide.cxx.o.provides: CMakeFiles/libimat.dir/Model/imat/IMatPrimGuide.cxx.o.requires
	$(MAKE) -f CMakeFiles/libimat.dir/build.make CMakeFiles/libimat.dir/Model/imat/IMatPrimGuide.cxx.o.provides.build
.PHONY : CMakeFiles/libimat.dir/Model/imat/IMatPrimGuide.cxx.o.provides

CMakeFiles/libimat.dir/Model/imat/IMatPrimGuide.cxx.o.provides.build: CMakeFiles/libimat.dir/Model/imat/IMatPrimGuide.cxx.o


CMakeFiles/libimat.dir/Model/imat/IMatShutter.cxx.o: CMakeFiles/libimat.dir/flags.make
CMakeFiles/libimat.dir/Model/imat/IMatShutter.cxx.o: Model/imat/IMatShutter.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/scionti/CombLayer-Vespa/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/libimat.dir/Model/imat/IMatShutter.cxx.o"
	g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libimat.dir/Model/imat/IMatShutter.cxx.o -c /home/scionti/CombLayer-Vespa/Model/imat/IMatShutter.cxx

CMakeFiles/libimat.dir/Model/imat/IMatShutter.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libimat.dir/Model/imat/IMatShutter.cxx.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/scionti/CombLayer-Vespa/Model/imat/IMatShutter.cxx > CMakeFiles/libimat.dir/Model/imat/IMatShutter.cxx.i

CMakeFiles/libimat.dir/Model/imat/IMatShutter.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libimat.dir/Model/imat/IMatShutter.cxx.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/scionti/CombLayer-Vespa/Model/imat/IMatShutter.cxx -o CMakeFiles/libimat.dir/Model/imat/IMatShutter.cxx.s

CMakeFiles/libimat.dir/Model/imat/IMatShutter.cxx.o.requires:

.PHONY : CMakeFiles/libimat.dir/Model/imat/IMatShutter.cxx.o.requires

CMakeFiles/libimat.dir/Model/imat/IMatShutter.cxx.o.provides: CMakeFiles/libimat.dir/Model/imat/IMatShutter.cxx.o.requires
	$(MAKE) -f CMakeFiles/libimat.dir/build.make CMakeFiles/libimat.dir/Model/imat/IMatShutter.cxx.o.provides.build
.PHONY : CMakeFiles/libimat.dir/Model/imat/IMatShutter.cxx.o.provides

CMakeFiles/libimat.dir/Model/imat/IMatShutter.cxx.o.provides.build: CMakeFiles/libimat.dir/Model/imat/IMatShutter.cxx.o


CMakeFiles/libimat.dir/Model/imat/imatVariables.cxx.o: CMakeFiles/libimat.dir/flags.make
CMakeFiles/libimat.dir/Model/imat/imatVariables.cxx.o: Model/imat/imatVariables.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/scionti/CombLayer-Vespa/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/libimat.dir/Model/imat/imatVariables.cxx.o"
	g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libimat.dir/Model/imat/imatVariables.cxx.o -c /home/scionti/CombLayer-Vespa/Model/imat/imatVariables.cxx

CMakeFiles/libimat.dir/Model/imat/imatVariables.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libimat.dir/Model/imat/imatVariables.cxx.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/scionti/CombLayer-Vespa/Model/imat/imatVariables.cxx > CMakeFiles/libimat.dir/Model/imat/imatVariables.cxx.i

CMakeFiles/libimat.dir/Model/imat/imatVariables.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libimat.dir/Model/imat/imatVariables.cxx.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/scionti/CombLayer-Vespa/Model/imat/imatVariables.cxx -o CMakeFiles/libimat.dir/Model/imat/imatVariables.cxx.s

CMakeFiles/libimat.dir/Model/imat/imatVariables.cxx.o.requires:

.PHONY : CMakeFiles/libimat.dir/Model/imat/imatVariables.cxx.o.requires

CMakeFiles/libimat.dir/Model/imat/imatVariables.cxx.o.provides: CMakeFiles/libimat.dir/Model/imat/imatVariables.cxx.o.requires
	$(MAKE) -f CMakeFiles/libimat.dir/build.make CMakeFiles/libimat.dir/Model/imat/imatVariables.cxx.o.provides.build
.PHONY : CMakeFiles/libimat.dir/Model/imat/imatVariables.cxx.o.provides

CMakeFiles/libimat.dir/Model/imat/imatVariables.cxx.o.provides.build: CMakeFiles/libimat.dir/Model/imat/imatVariables.cxx.o


CMakeFiles/libimat.dir/Model/imat/makeIMat.cxx.o: CMakeFiles/libimat.dir/flags.make
CMakeFiles/libimat.dir/Model/imat/makeIMat.cxx.o: Model/imat/makeIMat.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/scionti/CombLayer-Vespa/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/libimat.dir/Model/imat/makeIMat.cxx.o"
	g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libimat.dir/Model/imat/makeIMat.cxx.o -c /home/scionti/CombLayer-Vespa/Model/imat/makeIMat.cxx

CMakeFiles/libimat.dir/Model/imat/makeIMat.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libimat.dir/Model/imat/makeIMat.cxx.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/scionti/CombLayer-Vespa/Model/imat/makeIMat.cxx > CMakeFiles/libimat.dir/Model/imat/makeIMat.cxx.i

CMakeFiles/libimat.dir/Model/imat/makeIMat.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libimat.dir/Model/imat/makeIMat.cxx.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/scionti/CombLayer-Vespa/Model/imat/makeIMat.cxx -o CMakeFiles/libimat.dir/Model/imat/makeIMat.cxx.s

CMakeFiles/libimat.dir/Model/imat/makeIMat.cxx.o.requires:

.PHONY : CMakeFiles/libimat.dir/Model/imat/makeIMat.cxx.o.requires

CMakeFiles/libimat.dir/Model/imat/makeIMat.cxx.o.provides: CMakeFiles/libimat.dir/Model/imat/makeIMat.cxx.o.requires
	$(MAKE) -f CMakeFiles/libimat.dir/build.make CMakeFiles/libimat.dir/Model/imat/makeIMat.cxx.o.provides.build
.PHONY : CMakeFiles/libimat.dir/Model/imat/makeIMat.cxx.o.provides

CMakeFiles/libimat.dir/Model/imat/makeIMat.cxx.o.provides.build: CMakeFiles/libimat.dir/Model/imat/makeIMat.cxx.o


# Object files for target libimat
libimat_OBJECTS = \
"CMakeFiles/libimat.dir/Model/imat/IMatBulkInsert.cxx.o" \
"CMakeFiles/libimat.dir/Model/imat/IMatChopper.cxx.o" \
"CMakeFiles/libimat.dir/Model/imat/IMatGuide.cxx.o" \
"CMakeFiles/libimat.dir/Model/imat/IMatPrimGuide.cxx.o" \
"CMakeFiles/libimat.dir/Model/imat/IMatShutter.cxx.o" \
"CMakeFiles/libimat.dir/Model/imat/imatVariables.cxx.o" \
"CMakeFiles/libimat.dir/Model/imat/makeIMat.cxx.o"

# External object files for target libimat
libimat_EXTERNAL_OBJECTS =

lib/liblibimat.so: CMakeFiles/libimat.dir/Model/imat/IMatBulkInsert.cxx.o
lib/liblibimat.so: CMakeFiles/libimat.dir/Model/imat/IMatChopper.cxx.o
lib/liblibimat.so: CMakeFiles/libimat.dir/Model/imat/IMatGuide.cxx.o
lib/liblibimat.so: CMakeFiles/libimat.dir/Model/imat/IMatPrimGuide.cxx.o
lib/liblibimat.so: CMakeFiles/libimat.dir/Model/imat/IMatShutter.cxx.o
lib/liblibimat.so: CMakeFiles/libimat.dir/Model/imat/imatVariables.cxx.o
lib/liblibimat.so: CMakeFiles/libimat.dir/Model/imat/makeIMat.cxx.o
lib/liblibimat.so: CMakeFiles/libimat.dir/build.make
lib/liblibimat.so: CMakeFiles/libimat.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/scionti/CombLayer-Vespa/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX shared library lib/liblibimat.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/libimat.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/libimat.dir/build: lib/liblibimat.so

.PHONY : CMakeFiles/libimat.dir/build

CMakeFiles/libimat.dir/requires: CMakeFiles/libimat.dir/Model/imat/IMatBulkInsert.cxx.o.requires
CMakeFiles/libimat.dir/requires: CMakeFiles/libimat.dir/Model/imat/IMatChopper.cxx.o.requires
CMakeFiles/libimat.dir/requires: CMakeFiles/libimat.dir/Model/imat/IMatGuide.cxx.o.requires
CMakeFiles/libimat.dir/requires: CMakeFiles/libimat.dir/Model/imat/IMatPrimGuide.cxx.o.requires
CMakeFiles/libimat.dir/requires: CMakeFiles/libimat.dir/Model/imat/IMatShutter.cxx.o.requires
CMakeFiles/libimat.dir/requires: CMakeFiles/libimat.dir/Model/imat/imatVariables.cxx.o.requires
CMakeFiles/libimat.dir/requires: CMakeFiles/libimat.dir/Model/imat/makeIMat.cxx.o.requires

.PHONY : CMakeFiles/libimat.dir/requires

CMakeFiles/libimat.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/libimat.dir/cmake_clean.cmake
.PHONY : CMakeFiles/libimat.dir/clean

CMakeFiles/libimat.dir/depend:
	cd /home/scionti/CombLayer-Vespa && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/scionti/CombLayer-Vespa /home/scionti/CombLayer-Vespa /home/scionti/CombLayer-Vespa /home/scionti/CombLayer-Vespa /home/scionti/CombLayer-Vespa/CMakeFiles/libimat.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/libimat.dir/depend
