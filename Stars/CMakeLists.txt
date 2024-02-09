##############################################################################
# General settings
##############################################################################
cmake_minimum_required(VERSION 3.5)

set(ProjectName "v7")
project(${ProjectName})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread -pipe -Wall -fPIC -Werror=return-type")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -pipe -Wall -fPIC -Werror=return-type")

add_executable(Stars 
    main.cpp
)

target_include_directories(Stars PUBLIC
    sources
)
target_link_libraries(Stars
)
