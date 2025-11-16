cmake_minimum_required(VERSION 3.10)

project(guess C)

set(LOCALE_DIR "${CMAKE_BINARY_DIR}/share/locale")
message(STATUS "Locale directory: ${LOCALE_DIR}")

add_subdirectory(po)

add_executable(guess src/guess.c)

target_compile_definitions(guess PRIVATE
    LOCALE_PATH="${LOCALE_DIR}"
)

set_target_properties(guess PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)