#############################################################################################
# General settings
#############################################################################################
cmake_minimum_required(VERSION 3.5)

set(ProjectName "ConsoleGraphics")
project(${ProjectName})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread -pipe -Wall -fPIC -Werror=return-type")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -pipe -Wall -fPIC -Werror=return-type")

find_package(glm CONFIG REQUIRED)
#target_link_libraries(main PRIVATE glm::glm-header-only) #example

##############################################################################################
# 3d objects
##############################################################################################
add_executable(3dObjects 
    3dObjects.cpp
    Sources/Common/ConsoleApp.cpp
    Sources/3d/Triangle.cpp
)

target_include_directories(3dObjects PUBLIC
    Sources/
    Sources/Common/
    Sources/3d/
)

target_link_libraries(3dObjects
    ncurses
    glm::glm
)
##############################################################################################

##############################################################################################
# Stars
##############################################################################################
add_executable(Stars 
    Stars.cpp
    Sources/Common/ConsoleApp.cpp
)

target_include_directories(Stars PUBLIC
    Sources/
    Sources/Common/
)

target_link_libraries(Stars
    ncurses
)
##############################################################################################

##############################################################################################
# MatrixColumns
##############################################################################################
add_executable(MatrixColumns 
    MatrixColumns.cpp
    Sources/Common/ConsoleApp.cpp
)

target_include_directories(MatrixColumns PUBLIC
    Sources/
    Sources/Common/
)

target_link_libraries(MatrixColumns
    ncurses
)
##############################################################################################

##############################################################################################
# Flame
##############################################################################################
add_executable(Flame 
    Flame.cpp
    Sources/Common/ConsoleApp.cpp
)

target_include_directories(Flame PUBLIC
    Sources/
    Sources/Common/
)

target_link_libraries(Flame
    ncurses
)
##############################################################################################

##############################################################################################
# Fireballs
##############################################################################################
add_executable(Fireballs
    Fireballs.cpp
    Sources/Common/ConsoleApp.cpp
)

target_include_directories(Fireballs PUBLIC
    Sources/
    Sources/Common/
)

target_link_libraries(Fireballs
    ncurses
    glm::glm
)
##############################################################################################
