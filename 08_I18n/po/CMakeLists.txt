# po/CMakeLists.txt

# Ищем утилиты gettext
find_program(XGETTEXT xgettext)
find_program(MSGFMT msgfmt)

if(NOT XGETTEXT OR NOT MSGFMT)
    message(WARNING "Gettext tools not found, translations will not be built")
    return()
endif()

set(DOMAIN "guess")
set(PO_FILE "ru.po")

# Полный путь к исходнику
set(SOURCE_FILE "${CMAKE_SOURCE_DIR}/src/guess.c")

# Создаем папку для .mo файлов
set(MO_DIR "${CMAKE_BINARY_DIR}/share/locale/ru/LC_MESSAGES")
file(MAKE_DIRECTORY "${MO_DIR}")

# Полный путь к .mo файлу
set(MO_FILE "${MO_DIR}/${DOMAIN}.mo")

# Команда для создания .mo файла
add_custom_command(
    OUTPUT "${MO_FILE}"
    COMMAND ${MSGFMT} -o "${MO_FILE}" "${CMAKE_CURRENT_SOURCE_DIR}/${PO_FILE}"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${PO_FILE}"
    COMMENT "Building ${DOMAIN}.mo from ${PO_FILE}"
    VERBATIM
)

# Добавляем цель для сборки переводов
add_custom_target(translations ALL DEPENDS "${MO_FILE}")

# Показываем информацию о созданном файле
message(STATUS "MO file will be created at: ${MO_FILE}")