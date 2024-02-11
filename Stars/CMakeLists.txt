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

##############################################################################################
# Stars
##############################################################################################
add_executable(Stars 
    StarsApp.cpp
    Sources/Common/ConsoleApp.cpp
)

target_include_directories(Stars PUBLIC
    Sources/
    Sources/Common/
)

target_link_libraries(Stars
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
)
##############################################################################################