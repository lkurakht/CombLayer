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
include CMakeFiles/sns.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sns.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sns.dir/flags.make

CMakeFiles/sns.dir/Main/sns.cxx.o: CMakeFiles/sns.dir/flags.make
CMakeFiles/sns.dir/Main/sns.cxx.o: Main/sns.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/scionti/CombLayer-Vespa/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sns.dir/Main/sns.cxx.o"
	g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sns.dir/Main/sns.cxx.o -c /home/scionti/CombLayer-Vespa/Main/sns.cxx

CMakeFiles/sns.dir/Main/sns.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sns.dir/Main/sns.cxx.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/scionti/CombLayer-Vespa/Main/sns.cxx > CMakeFiles/sns.dir/Main/sns.cxx.i

CMakeFiles/sns.dir/Main/sns.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sns.dir/Main/sns.cxx.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/scionti/CombLayer-Vespa/Main/sns.cxx -o CMakeFiles/sns.dir/Main/sns.cxx.s

CMakeFiles/sns.dir/Main/sns.cxx.o.requires:

.PHONY : CMakeFiles/sns.dir/Main/sns.cxx.o.requires

CMakeFiles/sns.dir/Main/sns.cxx.o.provides: CMakeFiles/sns.dir/Main/sns.cxx.o.requires
	$(MAKE) -f CMakeFiles/sns.dir/build.make CMakeFiles/sns.dir/Main/sns.cxx.o.provides.build
.PHONY : CMakeFiles/sns.dir/Main/sns.cxx.o.provides

CMakeFiles/sns.dir/Main/sns.cxx.o.provides.build: CMakeFiles/sns.dir/Main/sns.cxx.o


# Object files for target sns
sns_OBJECTS = \
"CMakeFiles/sns.dir/Main/sns.cxx.o"

# External object files for target sns
sns_EXTERNAL_OBJECTS =

sns: CMakeFiles/sns.dir/Main/sns.cxx.o
sns: CMakeFiles/sns.dir/build.make
sns: lib/liblibsnsBuild.so
sns: lib/liblibinput.so
sns: lib/liblibfuncBase.so
sns: lib/libliblog.so
sns: lib/liblibconstruct.so
sns: lib/liblibmd5.so
sns: lib/liblibprocess.so
sns: lib/liblibworld.so
sns: lib/liblibmonte.so
sns: lib/liblibgeometry.so
sns: lib/liblibmersenne.so
sns: lib/liblibsrc.so
sns: lib/liblibxml.so
sns: lib/liblibpoly.so
sns: lib/liblibsupport.so
sns: lib/liblibweights.so
sns: lib/liblibglobal.so
sns: lib/liblibattachComp.so
sns: lib/liblibphysics.so
sns: lib/liblibsimMC.so
sns: lib/liblibtransport.so
sns: lib/liblibscatMat.so
sns: lib/liblibsource.so
sns: lib/liblibtally.so
sns: lib/liblibflukaProcess.so
sns: lib/liblibflukaPhysics.so
sns: lib/liblibflukaTally.so
sns: lib/liblibphitsProcess.so
sns: lib/liblibphitsPhysics.so
sns: lib/liblibphitsTally.so
sns: lib/liblibphitsSupport.so
sns: lib/liblibwork.so
sns: lib/liblibendf.so
sns: lib/liblibcrystal.so
sns: lib/liblibinsertUnit.so
sns: lib/liblibvisit.so
sns: CMakeFiles/sns.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/scionti/CombLayer-Vespa/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable sns"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sns.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sns.dir/build: sns

.PHONY : CMakeFiles/sns.dir/build

CMakeFiles/sns.dir/requires: CMakeFiles/sns.dir/Main/sns.cxx.o.requires

.PHONY : CMakeFiles/sns.dir/requires

CMakeFiles/sns.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sns.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sns.dir/clean

CMakeFiles/sns.dir/depend:
	cd /home/scionti/CombLayer-Vespa && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/scionti/CombLayer-Vespa /home/scionti/CombLayer-Vespa /home/scionti/CombLayer-Vespa /home/scionti/CombLayer-Vespa /home/scionti/CombLayer-Vespa/CMakeFiles/sns.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sns.dir/depend
