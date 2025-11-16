find_program(XGETTEXT xgettext)
find_program(MSGFMT msgfmt)

if(NOT XGETTEXT OR NOT MSGFMT)
    message(WARNING "Gettext tools not found, translations will not be built")
    return()
endif()

set(DOMAIN "guess")
set(PO_FILE "ru.po")

set(SOURCE_FILE "${CMAKE_SOURCE_DIR}/src/guess.c")

set(MO_DIR "${CMAKE_BINARY_DIR}/share/locale/ru/LC_MESSAGES")
file(MAKE_DIRECTORY "${MO_DIR}")

set(MO_FILE "${MO_DIR}/${DOMAIN}.mo")

add_custom_command(
    OUTPUT "${MO_FILE}"
    COMMAND ${MSGFMT} -o "${MO_FILE}" "${CMAKE_CURRENT_SOURCE_DIR}/${PO_FILE}"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${PO_FILE}"
    COMMENT "Building ${DOMAIN}.mo from ${PO_FILE}"
    VERBATIM
)

add_custom_target(translations ALL DEPENDS "${MO_FILE}")

message(STATUS "MO file will be created at: ${MO_FILE}")