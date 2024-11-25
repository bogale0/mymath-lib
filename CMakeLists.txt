cmake_minimum_required(VERSION 3.16)

project(mymath LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(mymath main.cpp)# mymath.cpp mymath.h)
target_link_libraries(mymath libmymath.so)

include(GNUInstallDirs)
install(TARGETS mymath
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
