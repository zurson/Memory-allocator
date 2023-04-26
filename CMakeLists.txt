#
# DANTE :: System Automatycznych Testów Jednostkowych oraz Akceptacyjnych
# Tomasz Jaworski, 2018-2020
#
# Plik wygenerowany automatycznie
# Znacznik czasowy: 2022-12-11 14:00:11.487471
#

cmake_minimum_required(VERSION 3.17)
project(project1 C)

# Przyjmij standard C11
set(CMAKE_C_STANDARD 11)

# Ustaw opcje kompilatora (z raportu Dante)
add_compile_options(
      "-Werror"
      "-xc"
      "-Wno-error=parentheses"
      "-Wno-error=implicit-fallthrough"
      "-Wall"
      "-D_ANSI_OUTPUT"
      "-ggdb3"
      "-std=c11"
      "-Werror=vla"
      "-fmax-errors=5"
      "-DINSIDE_DANTE"
      "-Wextra"
      "-Wno-parentheses"
      "-fdiagnostics-color"
      "-D_GNU_SOURCE"
      "-Wno-error=unused-parameter"
      "-pedantic"

)

# Ustaw opcje konsolidatora (z raportu Dante)
add_link_options(
        "-Wl,-Map=main.map"
        "-Wl,-wrap,main"
        "-Wl,-cref"
        "-ggdb3"
)

# Utwórz target 'project1' i dodaj do niego pliki źródlowe:
add_executable(project1
        "main.c"
        "heap.c"
        "unit_helper_v2.c"
        "unit_test_v2.c"
        "rdebug.c"
        "memmanager.c"
)

# Dołącz niezbędne biblioteki
target_link_libraries(project1
        "m"
        "pthread"
)