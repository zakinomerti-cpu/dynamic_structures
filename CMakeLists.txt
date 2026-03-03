cmake_minimum_required(VERSION 4.0)

add_executable(main main.c hashArray.c funcArray.c dataArray.c stringTools.c)
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

set_property(TARGET main PROPERTY C_STANDARD 90)
set_property(TARGET main PROPERTY C_STANDARD_REQUIRED ON)
set_property(TARGET main PROPERTY C_EXTENSIONS OFF)
