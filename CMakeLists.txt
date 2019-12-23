cmake_minimum_required(VERSION 3.10)

# set the project name
project(GroupCounter_proj)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#set the source and include lists
set(IncludeList "./source/group_counter" "./source/types")
set(SourceList "./source/main/main.cpp")

# add the executable
add_executable(GroupCounter ${SourceList})

#set the include directories
target_include_directories(GroupCounter PRIVATE ${IncludeList})


