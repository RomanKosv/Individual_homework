cmake_minimum_required(VERSION 3.16)

project(DatabaseProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(DatabaseProject main.cpp
    bin_tree.cpp
    data_base.h
    bin_tree.h
)

include(GNUInstallDirs)
install(TARGETS DatabaseProject
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
