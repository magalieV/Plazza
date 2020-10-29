cmake_minimum_required(VERSION 3.10)
project(CCP_plazza_2019)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3")

include_directories(inc)
include_directories(inc/Arguments)
include_directories(inc/error)
include_directories(inc/Pizza)
include_directories(inc/Tools)
include_directories(inc/Kitchen)

add_subdirectory("src/")
get_directory_property(SRC_FILES DIRECTORY src DEFINITION SRC_FILES)

set(SRCS
        ${SRC_FILES}
    )

add_executable(plazza ${SRCS})
TARGET_LINK_LIBRARIES(plazza PRIVATE pthread)
