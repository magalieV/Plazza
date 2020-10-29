set(PATH_H
        inc/Reception/)
set(PATH_S
        src/Reception/)

set(SOURCES
        ${PATH_S}Reception.cpp
        ${PATH_S}Order.cpp
        ${PATH_S}Orders.cpp
        )

set(HEADERS
        ${PATH_H}Reception.hpp
        ${PATH_H}Order.hpp
        ${PATH_H}Orders.hpp
        ${PATH_H}CommandParser.hpp
        )

set(RECEPTION_FILES
        ${SOURCES}
        ${HEADERS}
        )