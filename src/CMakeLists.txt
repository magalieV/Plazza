set(PATH_H
        inc/)
set(PATH_S
        src/)

add_subdirectory("Pizza/")
add_subdirectory("error/")
add_subdirectory("Arguments/")
add_subdirectory("Reception/")
add_subdirectory("Tools/")
add_subdirectory("Kitchen/")
add_subdirectory("Encapsulation/")

get_directory_property(ARGS_FILES DIRECTORY Arguments DEFINITION ARGS_FILES)
get_directory_property(ERRORS_FILES DIRECTORY error DEFINITION ERRORS_FILES)
get_directory_property(PIZZA_FILES DIRECTORY Pizza DEFINITION PIZZA_FILES)
get_directory_property(TOOLS_FILES DIRECTORY Tools DEFINITION TOOLS_FILES)
get_directory_property(RECEPTION_FILES DIRECTORY Reception DEFINITION RECEPTION_FILES)
get_directory_property(KITCHEN_FILES DIRECTORY Kitchen DEFINITION KITCHEN_FILES)
get_directory_property(ENCA_FILES DIRECTORY Encapsulation DEFINITION ENCA_FILES)

set(SOURCES
        ${PATH_S}main.cpp
        )

set(HEADERS
        ${PATH_H}plazza_header.hpp
        )

set(SRC_FILES
        ${SOURCES}
        ${HEADERS}
        ${ARGS_FILES}
        ${ERRORS_FILES}
        ${PIZZA_FILES}
        ${RECEPTION_FILES}
        ${TOOLS_FILES}
        ${KITCHEN_FILES}
        ${ENCA_FILES}
        )