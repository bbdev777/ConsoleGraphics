cmake_minimum_required(VERSION 3.5)

set(ProjectName "SfmlTest")
project(${ProjectName})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)


##############################################################################
# HelloWorld
##############################################################################
add_executable(${ProjectName}.Main
	"src/main.cpp"
)

target_link_libraries(${ProjectName}.Main
    sfml-graphics
    sfml-window
    sfml-system
)
##############################################################################
