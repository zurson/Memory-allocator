# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.21

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\matuj\OneDrive - Politechnika Łódzka\III sem\SO2 - Projekty\Alok"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\matuj\OneDrive - Politechnika Łódzka\III sem\SO2 - Projekty\Alok\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/project1.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/project1.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/project1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/project1.dir/flags.make

CMakeFiles/project1.dir/main.c.obj: CMakeFiles/project1.dir/flags.make
CMakeFiles/project1.dir/main.c.obj: ../main.c
CMakeFiles/project1.dir/main.c.obj: CMakeFiles/project1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\matuj\OneDrive - Politechnika Łódzka\III sem\SO2 - Projekty\Alok\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/project1.dir/main.c.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/project1.dir/main.c.obj -MF CMakeFiles\project1.dir\main.c.obj.d -o CMakeFiles\project1.dir\main.c.obj -c "C:\Users\matuj\OneDrive - Politechnika Łódzka\III sem\SO2 - Projekty\Alok\main.c"

CMakeFiles/project1.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/project1.dir/main.c.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\matuj\OneDrive - Politechnika Łódzka\III sem\SO2 - Projekty\Alok\main.c" > CMakeFiles\project1.dir\main.c.i

CMakeFiles/project1.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/project1.dir/main.c.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\matuj\OneDrive - Politechnika Łódzka\III sem\SO2 - Projekty\Alok\main.c" -o CMakeFiles\project1.dir\main.c.s

CMakeFiles/project1.dir/heap.c.obj: CMakeFiles/project1.dir/flags.make
CMakeFiles/project1.dir/heap.c.obj: ../heap.c
CMakeFiles/project1.dir/heap.c.obj: CMakeFiles/project1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\matuj\OneDrive - Politechnika Łódzka\III sem\SO2 - Projekty\Alok\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/project1.dir/heap.c.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/project1.dir/heap.c.obj -MF CMakeFiles\project1.dir\heap.c.obj.d -o CMakeFiles\project1.dir\heap.c.obj -c "C:\Users\matuj\OneDrive - Politechnika Łódzka\III sem\SO2 - Projekty\Alok\heap.c"

CMakeFiles/project1.dir/heap.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/project1.dir/heap.c.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\matuj\OneDrive - Politechnika Łódzka\III sem\SO2 - Projekty\Alok\heap.c" > CMakeFiles\project1.dir\heap.c.i

CMakeFiles/project1.dir/heap.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/project1.dir/heap.c.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\matuj\OneDrive - Politechnika Łódzka\III sem\SO2 - Projekty\Alok\heap.c" -o CMakeFiles\project1.dir\heap.c.s

CMakeFiles/project1.dir/unit_helper_v2.c.obj: CMakeFiles/project1.dir/flags.make
CMakeFiles/project1.dir/unit_helper_v2.c.obj: ../unit_helper_v2.c
CMakeFiles/project1.dir/unit_helper_v2.c.obj: CMakeFiles/project1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\matuj\OneDrive - Politechnika Łódzka\III sem\SO2 - Projekty\Alok\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/project1.dir/unit_helper_v2.c.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/project1.dir/unit_helper_v2.c.obj -MF CMakeFiles\project1.dir\unit_helper_v2.c.obj.d -o CMakeFiles\project1.dir\unit_helper_v2.c.obj -c "C:\Users\matuj\OneDrive - Politechnika Łódzka\III sem\SO2 - Projekty\Alok\unit_helper_v2.c"

CMakeFiles/project1.dir/unit_helper_v2.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/project1.dir/unit_helper_v2.c.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\matuj\OneDrive - Politechnika Łódzka\III sem\SO2 - Projekty\Alok\unit_helper_v2.c" > CMakeFiles\project1.dir\unit_helper_v2.c.i

CMakeFiles/project1.dir/unit_helper_v2.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/project1.dir/unit_helper_v2.c.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\matuj\OneDrive - Politechnika Łódzka\III sem\SO2 - Projekty\Alok\unit_helper_v2.c" -o CMakeFiles\project1.dir\unit_helper_v2.c.s

CMakeFiles/project1.dir/unit_test_v2.c.obj: CMakeFiles/project1.dir/flags.make
CMakeFiles/project1.dir/unit_test_v2.c.obj: ../unit_test_v2.c
CMakeFiles/project1.dir/unit_test_v2.c.obj: CMakeFiles/project1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\matuj\OneDrive - Politechnika Łódzka\III sem\SO2 - Projekty\Alok\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/project1.dir/unit_test_v2.c.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/project1.dir/unit_test_v2.c.obj -MF CMakeFiles\project1.dir\unit_test_v2.c.obj.d -o CMakeFiles\project1.dir\unit_test_v2.c.obj -c "C:\Users\matuj\OneDrive - Politechnika Łódzka\III sem\SO2 - Projekty\Alok\unit_test_v2.c"

CMakeFiles/project1.dir/unit_test_v2.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/project1.dir/unit_test_v2.c.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\matuj\OneDrive - Politechnika Łódzka\III sem\SO2 - Projekty\Alok\unit_test_v2.c" > CMakeFiles\project1.dir\unit_test_v2.c.i

CMakeFiles/project1.dir/unit_test_v2.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/project1.dir/unit_test_v2.c.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\matuj\OneDrive - Politechnika Łódzka\III sem\SO2 - Projekty\Alok\unit_test_v2.c" -o CMakeFiles\project1.dir\unit_test_v2.c.s

CMakeFiles/project1.dir/rdebug.c.obj: CMakeFiles/project1.dir/flags.make
CMakeFiles/project1.dir/rdebug.c.obj: ../rdebug.c
CMakeFiles/project1.dir/rdebug.c.obj: CMakeFiles/project1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\matuj\OneDrive - Politechnika Łódzka\III sem\SO2 - Projekty\Alok\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/project1.dir/rdebug.c.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/project1.dir/rdebug.c.obj -MF CMakeFiles\project1.dir\rdebug.c.obj.d -o CMakeFiles\project1.dir\rdebug.c.obj -c "C:\Users\matuj\OneDrive - Politechnika Łódzka\III sem\SO2 - Projekty\Alok\rdebug.c"

CMakeFiles/project1.dir/rdebug.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/project1.dir/rdebug.c.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\matuj\OneDrive - Politechnika Łódzka\III sem\SO2 - Projekty\Alok\rdebug.c" > CMakeFiles\project1.dir\rdebug.c.i

CMakeFiles/project1.dir/rdebug.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/project1.dir/rdebug.c.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\matuj\OneDrive - Politechnika Łódzka\III sem\SO2 - Projekty\Alok\rdebug.c" -o CMakeFiles\project1.dir\rdebug.c.s

CMakeFiles/project1.dir/memmanager.c.obj: CMakeFiles/project1.dir/flags.make
CMakeFiles/project1.dir/memmanager.c.obj: ../memmanager.c
CMakeFiles/project1.dir/memmanager.c.obj: CMakeFiles/project1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\matuj\OneDrive - Politechnika Łódzka\III sem\SO2 - Projekty\Alok\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/project1.dir/memmanager.c.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/project1.dir/memmanager.c.obj -MF CMakeFiles\project1.dir\memmanager.c.obj.d -o CMakeFiles\project1.dir\memmanager.c.obj -c "C:\Users\matuj\OneDrive - Politechnika Łódzka\III sem\SO2 - Projekty\Alok\memmanager.c"

CMakeFiles/project1.dir/memmanager.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/project1.dir/memmanager.c.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\matuj\OneDrive - Politechnika Łódzka\III sem\SO2 - Projekty\Alok\memmanager.c" > CMakeFiles\project1.dir\memmanager.c.i

CMakeFiles/project1.dir/memmanager.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/project1.dir/memmanager.c.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\matuj\OneDrive - Politechnika Łódzka\III sem\SO2 - Projekty\Alok\memmanager.c" -o CMakeFiles\project1.dir\memmanager.c.s

# Object files for target project1
project1_OBJECTS = \
"CMakeFiles/project1.dir/main.c.obj" \
"CMakeFiles/project1.dir/heap.c.obj" \
"CMakeFiles/project1.dir/unit_helper_v2.c.obj" \
"CMakeFiles/project1.dir/unit_test_v2.c.obj" \
"CMakeFiles/project1.dir/rdebug.c.obj" \
"CMakeFiles/project1.dir/memmanager.c.obj"

# External object files for target project1
project1_EXTERNAL_OBJECTS =

project1.exe: CMakeFiles/project1.dir/main.c.obj
project1.exe: CMakeFiles/project1.dir/heap.c.obj
project1.exe: CMakeFiles/project1.dir/unit_helper_v2.c.obj
project1.exe: CMakeFiles/project1.dir/unit_test_v2.c.obj
project1.exe: CMakeFiles/project1.dir/rdebug.c.obj
project1.exe: CMakeFiles/project1.dir/memmanager.c.obj
project1.exe: CMakeFiles/project1.dir/build.make
project1.exe: CMakeFiles/project1.dir/linklibs.rsp
project1.exe: CMakeFiles/project1.dir/objects1.rsp
project1.exe: CMakeFiles/project1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\matuj\OneDrive - Politechnika Łódzka\III sem\SO2 - Projekty\Alok\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Linking C executable project1.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\project1.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/project1.dir/build: project1.exe
.PHONY : CMakeFiles/project1.dir/build

CMakeFiles/project1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\project1.dir\cmake_clean.cmake
.PHONY : CMakeFiles/project1.dir/clean

CMakeFiles/project1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\matuj\OneDrive - Politechnika Łódzka\III sem\SO2 - Projekty\Alok" "C:\Users\matuj\OneDrive - Politechnika Łódzka\III sem\SO2 - Projekty\Alok" "C:\Users\matuj\OneDrive - Politechnika Łódzka\III sem\SO2 - Projekty\Alok\cmake-build-debug" "C:\Users\matuj\OneDrive - Politechnika Łódzka\III sem\SO2 - Projekty\Alok\cmake-build-debug" "C:\Users\matuj\OneDrive - Politechnika Łódzka\III sem\SO2 - Projekty\Alok\cmake-build-debug\CMakeFiles\project1.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/project1.dir/depend

