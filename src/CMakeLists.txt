cmake_minimum_required(VERSION 3.12)
project(WGA_TASK)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(EXECUTABLE_OUTPUT_PATH  ../build)
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

set(sources Data.cpp
        Data.h
        event.h
        EventHandler.cpp
        EventHandler.h
        Field.cpp
        Field.h
        Game.cpp
        Game.h
        InterfaceDrawer.cpp
        InterfaceDrawer.h
        InterfaceHandler.cpp
        InterfaceHandler.h
        main.cpp)
if(WIN32)
    add_executable(WGA_TASK WIN32 ${sources})
else()
    add_executable(WGA_TASK ${sources})
endif()
target_link_libraries(WGA_TASK sfml-graphics)