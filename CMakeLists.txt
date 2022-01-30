cmake_minimum_required(VERSION 3.8)

project(idsm_autosar)

set(LIB_SRC
    ./src/lib/idsm_lib.cc)

set(SRC
    ./src/idsm_service.cc)

include_directories(
    ./src/lib/
    ./src/
    )


add_library(idsm_autosar ${LIB_SRC})

add_executable(idsm_service ${SRC})
target_link_libraries(idsm_service idsm_autosar pthread)
