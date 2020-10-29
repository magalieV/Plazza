set(PATH_H
        inc/Encapsulation/)
set(PATH_S
        src/Encapsulation/)

set(SOURCES
        ${PATH_S}Mutex.cpp
        ${PATH_S}MessageQueue.cpp
        ${PATH_S}Process.cpp
        ${PATH_S}Procedure.cpp
        ${PATH_S}Shared.cpp
        ${PATH_S}Thead.cpp
        )

set(HEADERS
        ${PATH_H}Mutex.hpp
        ${PATH_H}MessageQueue.hpp
        ${PATH_H}Process.hpp
        ${PATH_H}Procedure.hpp
        ${PATH_H}Shared.hpp
        ${PATH_H}Thread.hpp
        )

set(ENCA_FILES
        ${SOURCES}
        ${HEADERS}
        )