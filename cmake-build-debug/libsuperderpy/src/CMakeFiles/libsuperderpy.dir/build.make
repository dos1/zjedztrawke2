# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /home/isaac/clion-2018.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/isaac/clion-2018.3/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/isaac/zjedztrawke2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/isaac/zjedztrawke2/cmake-build-debug

# Include any dependencies generated for this target.
include libsuperderpy/src/CMakeFiles/libsuperderpy.dir/depend.make

# Include the progress variables for this target.
include libsuperderpy/src/CMakeFiles/libsuperderpy.dir/progress.make

# Include the compile flags for this target's objects.
include libsuperderpy/src/CMakeFiles/libsuperderpy.dir/flags.make

libsuperderpy/src/CMakeFiles/libsuperderpy.dir/character.c.o: libsuperderpy/src/CMakeFiles/libsuperderpy.dir/flags.make
libsuperderpy/src/CMakeFiles/libsuperderpy.dir/character.c.o: ../libsuperderpy/src/character.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/isaac/zjedztrawke2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object libsuperderpy/src/CMakeFiles/libsuperderpy.dir/character.c.o"
	cd /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src && $(CMAKE_COMMAND) -E __run_co_compile --tidy="/usr/bin/clang-tidy;-config=Checks: '*,-clang-analyzer-alpha.*,-hicpp-no-assembler,-google-readability-todo,-misc-unused-parameters,-hicpp-signed-bitwise,-cert-msc30-c,-cert-msc50-cpp,-cert-msc32-c,-cert-msc51-cpp'" --source=/home/isaac/zjedztrawke2/libsuperderpy/src/character.c -- /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/libsuperderpy.dir/character.c.o   -c /home/isaac/zjedztrawke2/libsuperderpy/src/character.c

libsuperderpy/src/CMakeFiles/libsuperderpy.dir/character.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/libsuperderpy.dir/character.c.i"
	cd /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/isaac/zjedztrawke2/libsuperderpy/src/character.c > CMakeFiles/libsuperderpy.dir/character.c.i

libsuperderpy/src/CMakeFiles/libsuperderpy.dir/character.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/libsuperderpy.dir/character.c.s"
	cd /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/isaac/zjedztrawke2/libsuperderpy/src/character.c -o CMakeFiles/libsuperderpy.dir/character.c.s

libsuperderpy/src/CMakeFiles/libsuperderpy.dir/config.c.o: libsuperderpy/src/CMakeFiles/libsuperderpy.dir/flags.make
libsuperderpy/src/CMakeFiles/libsuperderpy.dir/config.c.o: ../libsuperderpy/src/config.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/isaac/zjedztrawke2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object libsuperderpy/src/CMakeFiles/libsuperderpy.dir/config.c.o"
	cd /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src && $(CMAKE_COMMAND) -E __run_co_compile --tidy="/usr/bin/clang-tidy;-config=Checks: '*,-clang-analyzer-alpha.*,-hicpp-no-assembler,-google-readability-todo,-misc-unused-parameters,-hicpp-signed-bitwise,-cert-msc30-c,-cert-msc50-cpp,-cert-msc32-c,-cert-msc51-cpp'" --source=/home/isaac/zjedztrawke2/libsuperderpy/src/config.c -- /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/libsuperderpy.dir/config.c.o   -c /home/isaac/zjedztrawke2/libsuperderpy/src/config.c

libsuperderpy/src/CMakeFiles/libsuperderpy.dir/config.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/libsuperderpy.dir/config.c.i"
	cd /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/isaac/zjedztrawke2/libsuperderpy/src/config.c > CMakeFiles/libsuperderpy.dir/config.c.i

libsuperderpy/src/CMakeFiles/libsuperderpy.dir/config.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/libsuperderpy.dir/config.c.s"
	cd /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/isaac/zjedztrawke2/libsuperderpy/src/config.c -o CMakeFiles/libsuperderpy.dir/config.c.s

libsuperderpy/src/CMakeFiles/libsuperderpy.dir/gamestate.c.o: libsuperderpy/src/CMakeFiles/libsuperderpy.dir/flags.make
libsuperderpy/src/CMakeFiles/libsuperderpy.dir/gamestate.c.o: ../libsuperderpy/src/gamestate.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/isaac/zjedztrawke2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object libsuperderpy/src/CMakeFiles/libsuperderpy.dir/gamestate.c.o"
	cd /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src && $(CMAKE_COMMAND) -E __run_co_compile --tidy="/usr/bin/clang-tidy;-config=Checks: '*,-clang-analyzer-alpha.*,-hicpp-no-assembler,-google-readability-todo,-misc-unused-parameters,-hicpp-signed-bitwise,-cert-msc30-c,-cert-msc50-cpp,-cert-msc32-c,-cert-msc51-cpp'" --source=/home/isaac/zjedztrawke2/libsuperderpy/src/gamestate.c -- /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/libsuperderpy.dir/gamestate.c.o   -c /home/isaac/zjedztrawke2/libsuperderpy/src/gamestate.c

libsuperderpy/src/CMakeFiles/libsuperderpy.dir/gamestate.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/libsuperderpy.dir/gamestate.c.i"
	cd /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/isaac/zjedztrawke2/libsuperderpy/src/gamestate.c > CMakeFiles/libsuperderpy.dir/gamestate.c.i

libsuperderpy/src/CMakeFiles/libsuperderpy.dir/gamestate.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/libsuperderpy.dir/gamestate.c.s"
	cd /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/isaac/zjedztrawke2/libsuperderpy/src/gamestate.c -o CMakeFiles/libsuperderpy.dir/gamestate.c.s

libsuperderpy/src/CMakeFiles/libsuperderpy.dir/internal.c.o: libsuperderpy/src/CMakeFiles/libsuperderpy.dir/flags.make
libsuperderpy/src/CMakeFiles/libsuperderpy.dir/internal.c.o: ../libsuperderpy/src/internal.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/isaac/zjedztrawke2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object libsuperderpy/src/CMakeFiles/libsuperderpy.dir/internal.c.o"
	cd /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src && $(CMAKE_COMMAND) -E __run_co_compile --tidy="/usr/bin/clang-tidy;-config=Checks: '*,-clang-analyzer-alpha.*,-hicpp-no-assembler,-google-readability-todo,-misc-unused-parameters,-hicpp-signed-bitwise,-cert-msc30-c,-cert-msc50-cpp,-cert-msc32-c,-cert-msc51-cpp'" --source=/home/isaac/zjedztrawke2/libsuperderpy/src/internal.c -- /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/libsuperderpy.dir/internal.c.o   -c /home/isaac/zjedztrawke2/libsuperderpy/src/internal.c

libsuperderpy/src/CMakeFiles/libsuperderpy.dir/internal.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/libsuperderpy.dir/internal.c.i"
	cd /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/isaac/zjedztrawke2/libsuperderpy/src/internal.c > CMakeFiles/libsuperderpy.dir/internal.c.i

libsuperderpy/src/CMakeFiles/libsuperderpy.dir/internal.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/libsuperderpy.dir/internal.c.s"
	cd /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/isaac/zjedztrawke2/libsuperderpy/src/internal.c -o CMakeFiles/libsuperderpy.dir/internal.c.s

libsuperderpy/src/CMakeFiles/libsuperderpy.dir/libsuperderpy.c.o: libsuperderpy/src/CMakeFiles/libsuperderpy.dir/flags.make
libsuperderpy/src/CMakeFiles/libsuperderpy.dir/libsuperderpy.c.o: ../libsuperderpy/src/libsuperderpy.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/isaac/zjedztrawke2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object libsuperderpy/src/CMakeFiles/libsuperderpy.dir/libsuperderpy.c.o"
	cd /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src && $(CMAKE_COMMAND) -E __run_co_compile --tidy="/usr/bin/clang-tidy;-config=Checks: '*,-clang-analyzer-alpha.*,-hicpp-no-assembler,-google-readability-todo,-misc-unused-parameters,-hicpp-signed-bitwise,-cert-msc30-c,-cert-msc50-cpp,-cert-msc32-c,-cert-msc51-cpp'" --source=/home/isaac/zjedztrawke2/libsuperderpy/src/libsuperderpy.c -- /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/libsuperderpy.dir/libsuperderpy.c.o   -c /home/isaac/zjedztrawke2/libsuperderpy/src/libsuperderpy.c

libsuperderpy/src/CMakeFiles/libsuperderpy.dir/libsuperderpy.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/libsuperderpy.dir/libsuperderpy.c.i"
	cd /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/isaac/zjedztrawke2/libsuperderpy/src/libsuperderpy.c > CMakeFiles/libsuperderpy.dir/libsuperderpy.c.i

libsuperderpy/src/CMakeFiles/libsuperderpy.dir/libsuperderpy.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/libsuperderpy.dir/libsuperderpy.c.s"
	cd /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/isaac/zjedztrawke2/libsuperderpy/src/libsuperderpy.c -o CMakeFiles/libsuperderpy.dir/libsuperderpy.c.s

libsuperderpy/src/CMakeFiles/libsuperderpy.dir/mainloop.c.o: libsuperderpy/src/CMakeFiles/libsuperderpy.dir/flags.make
libsuperderpy/src/CMakeFiles/libsuperderpy.dir/mainloop.c.o: ../libsuperderpy/src/mainloop.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/isaac/zjedztrawke2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object libsuperderpy/src/CMakeFiles/libsuperderpy.dir/mainloop.c.o"
	cd /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src && $(CMAKE_COMMAND) -E __run_co_compile --tidy="/usr/bin/clang-tidy;-config=Checks: '*,-clang-analyzer-alpha.*,-hicpp-no-assembler,-google-readability-todo,-misc-unused-parameters,-hicpp-signed-bitwise,-cert-msc30-c,-cert-msc50-cpp,-cert-msc32-c,-cert-msc51-cpp'" --source=/home/isaac/zjedztrawke2/libsuperderpy/src/mainloop.c -- /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/libsuperderpy.dir/mainloop.c.o   -c /home/isaac/zjedztrawke2/libsuperderpy/src/mainloop.c

libsuperderpy/src/CMakeFiles/libsuperderpy.dir/mainloop.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/libsuperderpy.dir/mainloop.c.i"
	cd /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/isaac/zjedztrawke2/libsuperderpy/src/mainloop.c > CMakeFiles/libsuperderpy.dir/mainloop.c.i

libsuperderpy/src/CMakeFiles/libsuperderpy.dir/mainloop.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/libsuperderpy.dir/mainloop.c.s"
	cd /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/isaac/zjedztrawke2/libsuperderpy/src/mainloop.c -o CMakeFiles/libsuperderpy.dir/mainloop.c.s

libsuperderpy/src/CMakeFiles/libsuperderpy.dir/maths.c.o: libsuperderpy/src/CMakeFiles/libsuperderpy.dir/flags.make
libsuperderpy/src/CMakeFiles/libsuperderpy.dir/maths.c.o: ../libsuperderpy/src/maths.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/isaac/zjedztrawke2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object libsuperderpy/src/CMakeFiles/libsuperderpy.dir/maths.c.o"
	cd /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src && $(CMAKE_COMMAND) -E __run_co_compile --tidy="/usr/bin/clang-tidy;-config=Checks: '*,-clang-analyzer-alpha.*,-hicpp-no-assembler,-google-readability-todo,-misc-unused-parameters,-hicpp-signed-bitwise,-cert-msc30-c,-cert-msc50-cpp,-cert-msc32-c,-cert-msc51-cpp'" --source=/home/isaac/zjedztrawke2/libsuperderpy/src/maths.c -- /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/libsuperderpy.dir/maths.c.o   -c /home/isaac/zjedztrawke2/libsuperderpy/src/maths.c

libsuperderpy/src/CMakeFiles/libsuperderpy.dir/maths.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/libsuperderpy.dir/maths.c.i"
	cd /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/isaac/zjedztrawke2/libsuperderpy/src/maths.c > CMakeFiles/libsuperderpy.dir/maths.c.i

libsuperderpy/src/CMakeFiles/libsuperderpy.dir/maths.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/libsuperderpy.dir/maths.c.s"
	cd /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/isaac/zjedztrawke2/libsuperderpy/src/maths.c -o CMakeFiles/libsuperderpy.dir/maths.c.s

libsuperderpy/src/CMakeFiles/libsuperderpy.dir/particle.c.o: libsuperderpy/src/CMakeFiles/libsuperderpy.dir/flags.make
libsuperderpy/src/CMakeFiles/libsuperderpy.dir/particle.c.o: ../libsuperderpy/src/particle.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/isaac/zjedztrawke2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object libsuperderpy/src/CMakeFiles/libsuperderpy.dir/particle.c.o"
	cd /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src && $(CMAKE_COMMAND) -E __run_co_compile --tidy="/usr/bin/clang-tidy;-config=Checks: '*,-clang-analyzer-alpha.*,-hicpp-no-assembler,-google-readability-todo,-misc-unused-parameters,-hicpp-signed-bitwise,-cert-msc30-c,-cert-msc50-cpp,-cert-msc32-c,-cert-msc51-cpp'" --source=/home/isaac/zjedztrawke2/libsuperderpy/src/particle.c -- /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/libsuperderpy.dir/particle.c.o   -c /home/isaac/zjedztrawke2/libsuperderpy/src/particle.c

libsuperderpy/src/CMakeFiles/libsuperderpy.dir/particle.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/libsuperderpy.dir/particle.c.i"
	cd /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/isaac/zjedztrawke2/libsuperderpy/src/particle.c > CMakeFiles/libsuperderpy.dir/particle.c.i

libsuperderpy/src/CMakeFiles/libsuperderpy.dir/particle.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/libsuperderpy.dir/particle.c.s"
	cd /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/isaac/zjedztrawke2/libsuperderpy/src/particle.c -o CMakeFiles/libsuperderpy.dir/particle.c.s

libsuperderpy/src/CMakeFiles/libsuperderpy.dir/shader.c.o: libsuperderpy/src/CMakeFiles/libsuperderpy.dir/flags.make
libsuperderpy/src/CMakeFiles/libsuperderpy.dir/shader.c.o: ../libsuperderpy/src/shader.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/isaac/zjedztrawke2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object libsuperderpy/src/CMakeFiles/libsuperderpy.dir/shader.c.o"
	cd /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src && $(CMAKE_COMMAND) -E __run_co_compile --tidy="/usr/bin/clang-tidy;-config=Checks: '*,-clang-analyzer-alpha.*,-hicpp-no-assembler,-google-readability-todo,-misc-unused-parameters,-hicpp-signed-bitwise,-cert-msc30-c,-cert-msc50-cpp,-cert-msc32-c,-cert-msc51-cpp'" --source=/home/isaac/zjedztrawke2/libsuperderpy/src/shader.c -- /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/libsuperderpy.dir/shader.c.o   -c /home/isaac/zjedztrawke2/libsuperderpy/src/shader.c

libsuperderpy/src/CMakeFiles/libsuperderpy.dir/shader.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/libsuperderpy.dir/shader.c.i"
	cd /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/isaac/zjedztrawke2/libsuperderpy/src/shader.c > CMakeFiles/libsuperderpy.dir/shader.c.i

libsuperderpy/src/CMakeFiles/libsuperderpy.dir/shader.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/libsuperderpy.dir/shader.c.s"
	cd /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/isaac/zjedztrawke2/libsuperderpy/src/shader.c -o CMakeFiles/libsuperderpy.dir/shader.c.s

libsuperderpy/src/CMakeFiles/libsuperderpy.dir/timeline.c.o: libsuperderpy/src/CMakeFiles/libsuperderpy.dir/flags.make
libsuperderpy/src/CMakeFiles/libsuperderpy.dir/timeline.c.o: ../libsuperderpy/src/timeline.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/isaac/zjedztrawke2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object libsuperderpy/src/CMakeFiles/libsuperderpy.dir/timeline.c.o"
	cd /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src && $(CMAKE_COMMAND) -E __run_co_compile --tidy="/usr/bin/clang-tidy;-config=Checks: '*,-clang-analyzer-alpha.*,-hicpp-no-assembler,-google-readability-todo,-misc-unused-parameters,-hicpp-signed-bitwise,-cert-msc30-c,-cert-msc50-cpp,-cert-msc32-c,-cert-msc51-cpp'" --source=/home/isaac/zjedztrawke2/libsuperderpy/src/timeline.c -- /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/libsuperderpy.dir/timeline.c.o   -c /home/isaac/zjedztrawke2/libsuperderpy/src/timeline.c

libsuperderpy/src/CMakeFiles/libsuperderpy.dir/timeline.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/libsuperderpy.dir/timeline.c.i"
	cd /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/isaac/zjedztrawke2/libsuperderpy/src/timeline.c > CMakeFiles/libsuperderpy.dir/timeline.c.i

libsuperderpy/src/CMakeFiles/libsuperderpy.dir/timeline.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/libsuperderpy.dir/timeline.c.s"
	cd /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/isaac/zjedztrawke2/libsuperderpy/src/timeline.c -o CMakeFiles/libsuperderpy.dir/timeline.c.s

libsuperderpy/src/CMakeFiles/libsuperderpy.dir/tween.c.o: libsuperderpy/src/CMakeFiles/libsuperderpy.dir/flags.make
libsuperderpy/src/CMakeFiles/libsuperderpy.dir/tween.c.o: ../libsuperderpy/src/tween.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/isaac/zjedztrawke2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object libsuperderpy/src/CMakeFiles/libsuperderpy.dir/tween.c.o"
	cd /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src && $(CMAKE_COMMAND) -E __run_co_compile --tidy="/usr/bin/clang-tidy;-config=Checks: '*,-clang-analyzer-alpha.*,-hicpp-no-assembler,-google-readability-todo,-misc-unused-parameters,-hicpp-signed-bitwise,-cert-msc30-c,-cert-msc50-cpp,-cert-msc32-c,-cert-msc51-cpp'" --source=/home/isaac/zjedztrawke2/libsuperderpy/src/tween.c -- /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/libsuperderpy.dir/tween.c.o   -c /home/isaac/zjedztrawke2/libsuperderpy/src/tween.c

libsuperderpy/src/CMakeFiles/libsuperderpy.dir/tween.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/libsuperderpy.dir/tween.c.i"
	cd /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/isaac/zjedztrawke2/libsuperderpy/src/tween.c > CMakeFiles/libsuperderpy.dir/tween.c.i

libsuperderpy/src/CMakeFiles/libsuperderpy.dir/tween.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/libsuperderpy.dir/tween.c.s"
	cd /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/isaac/zjedztrawke2/libsuperderpy/src/tween.c -o CMakeFiles/libsuperderpy.dir/tween.c.s

libsuperderpy/src/CMakeFiles/libsuperderpy.dir/utils.c.o: libsuperderpy/src/CMakeFiles/libsuperderpy.dir/flags.make
libsuperderpy/src/CMakeFiles/libsuperderpy.dir/utils.c.o: ../libsuperderpy/src/utils.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/isaac/zjedztrawke2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object libsuperderpy/src/CMakeFiles/libsuperderpy.dir/utils.c.o"
	cd /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src && $(CMAKE_COMMAND) -E __run_co_compile --tidy="/usr/bin/clang-tidy;-config=Checks: '*,-clang-analyzer-alpha.*,-hicpp-no-assembler,-google-readability-todo,-misc-unused-parameters,-hicpp-signed-bitwise,-cert-msc30-c,-cert-msc50-cpp,-cert-msc32-c,-cert-msc51-cpp'" --source=/home/isaac/zjedztrawke2/libsuperderpy/src/utils.c -- /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/libsuperderpy.dir/utils.c.o   -c /home/isaac/zjedztrawke2/libsuperderpy/src/utils.c

libsuperderpy/src/CMakeFiles/libsuperderpy.dir/utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/libsuperderpy.dir/utils.c.i"
	cd /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/isaac/zjedztrawke2/libsuperderpy/src/utils.c > CMakeFiles/libsuperderpy.dir/utils.c.i

libsuperderpy/src/CMakeFiles/libsuperderpy.dir/utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/libsuperderpy.dir/utils.c.s"
	cd /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/isaac/zjedztrawke2/libsuperderpy/src/utils.c -o CMakeFiles/libsuperderpy.dir/utils.c.s

# Object files for target libsuperderpy
libsuperderpy_OBJECTS = \
"CMakeFiles/libsuperderpy.dir/character.c.o" \
"CMakeFiles/libsuperderpy.dir/config.c.o" \
"CMakeFiles/libsuperderpy.dir/gamestate.c.o" \
"CMakeFiles/libsuperderpy.dir/internal.c.o" \
"CMakeFiles/libsuperderpy.dir/libsuperderpy.c.o" \
"CMakeFiles/libsuperderpy.dir/mainloop.c.o" \
"CMakeFiles/libsuperderpy.dir/maths.c.o" \
"CMakeFiles/libsuperderpy.dir/particle.c.o" \
"CMakeFiles/libsuperderpy.dir/shader.c.o" \
"CMakeFiles/libsuperderpy.dir/timeline.c.o" \
"CMakeFiles/libsuperderpy.dir/tween.c.o" \
"CMakeFiles/libsuperderpy.dir/utils.c.o"

# External object files for target libsuperderpy
libsuperderpy_EXTERNAL_OBJECTS =

libsuperderpy/src/libsuperderpy.so: libsuperderpy/src/CMakeFiles/libsuperderpy.dir/character.c.o
libsuperderpy/src/libsuperderpy.so: libsuperderpy/src/CMakeFiles/libsuperderpy.dir/config.c.o
libsuperderpy/src/libsuperderpy.so: libsuperderpy/src/CMakeFiles/libsuperderpy.dir/gamestate.c.o
libsuperderpy/src/libsuperderpy.so: libsuperderpy/src/CMakeFiles/libsuperderpy.dir/internal.c.o
libsuperderpy/src/libsuperderpy.so: libsuperderpy/src/CMakeFiles/libsuperderpy.dir/libsuperderpy.c.o
libsuperderpy/src/libsuperderpy.so: libsuperderpy/src/CMakeFiles/libsuperderpy.dir/mainloop.c.o
libsuperderpy/src/libsuperderpy.so: libsuperderpy/src/CMakeFiles/libsuperderpy.dir/maths.c.o
libsuperderpy/src/libsuperderpy.so: libsuperderpy/src/CMakeFiles/libsuperderpy.dir/particle.c.o
libsuperderpy/src/libsuperderpy.so: libsuperderpy/src/CMakeFiles/libsuperderpy.dir/shader.c.o
libsuperderpy/src/libsuperderpy.so: libsuperderpy/src/CMakeFiles/libsuperderpy.dir/timeline.c.o
libsuperderpy/src/libsuperderpy.so: libsuperderpy/src/CMakeFiles/libsuperderpy.dir/tween.c.o
libsuperderpy/src/libsuperderpy.so: libsuperderpy/src/CMakeFiles/libsuperderpy.dir/utils.c.o
libsuperderpy/src/libsuperderpy.so: libsuperderpy/src/CMakeFiles/libsuperderpy.dir/build.make
libsuperderpy/src/libsuperderpy.so: /usr/lib/x86_64-linux-gnu/liballegro.so
libsuperderpy/src/libsuperderpy.so: /usr/lib/x86_64-linux-gnu/liballegro_font.so
libsuperderpy/src/libsuperderpy.so: /usr/lib/x86_64-linux-gnu/liballegro_ttf.so
libsuperderpy/src/libsuperderpy.so: /usr/lib/x86_64-linux-gnu/liballegro_primitives.so
libsuperderpy/src/libsuperderpy.so: /usr/lib/x86_64-linux-gnu/liballegro_audio.so
libsuperderpy/src/libsuperderpy.so: /usr/lib/x86_64-linux-gnu/liballegro_acodec.so
libsuperderpy/src/libsuperderpy.so: /usr/lib/x86_64-linux-gnu/liballegro_video.so
libsuperderpy/src/libsuperderpy.so: /usr/lib/x86_64-linux-gnu/liballegro_image.so
libsuperderpy/src/libsuperderpy.so: libsuperderpy/src/CMakeFiles/libsuperderpy.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/isaac/zjedztrawke2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking C shared library libsuperderpy.so"
	cd /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/libsuperderpy.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libsuperderpy/src/CMakeFiles/libsuperderpy.dir/build: libsuperderpy/src/libsuperderpy.so

.PHONY : libsuperderpy/src/CMakeFiles/libsuperderpy.dir/build

libsuperderpy/src/CMakeFiles/libsuperderpy.dir/clean:
	cd /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src && $(CMAKE_COMMAND) -P CMakeFiles/libsuperderpy.dir/cmake_clean.cmake
.PHONY : libsuperderpy/src/CMakeFiles/libsuperderpy.dir/clean

libsuperderpy/src/CMakeFiles/libsuperderpy.dir/depend:
	cd /home/isaac/zjedztrawke2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/isaac/zjedztrawke2 /home/isaac/zjedztrawke2/libsuperderpy/src /home/isaac/zjedztrawke2/cmake-build-debug /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src /home/isaac/zjedztrawke2/cmake-build-debug/libsuperderpy/src/CMakeFiles/libsuperderpy.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libsuperderpy/src/CMakeFiles/libsuperderpy.dir/depend

