set(PATH_H
        inc/error/)
set(PATH_S
        src/error/)

set(SOURCES
        ${PATH_S}GlobalError.cpp
        ${PATH_S}PizzaError.cpp
        )

set(HEADERS
        ${PATH_H}GlobalError.hpp
        ${PATH_H}PizzaError.hpp
        )

set(ERRORS_FILES
        ${SOURCES}
        ${HEADERS}
        )