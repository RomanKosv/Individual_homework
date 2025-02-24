cmake_minimum_required(VERSION 3.16)

project(DatabaseProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(DatabaseProject main.cpp
    bintree.h
    utils.h

    array_utils.h
    linkedlist.h
    tasks.h

)

include(GNUInstallDirs)
install(TARGETS DatabaseProject
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
