cmake_minimum_required(VERSION 3.0)

project(MyProject)

# Define an option for the user to choose the build type
option(USE_VECTOR "Build using queue-vector.c" OFF)

# Add the main executable
add_executable(MyExecutable main.c reception.c)

# Conditionally include the necessary source files based on the user input flag
if(USE_VECTOR)
    target_sources(MyExecutable PRIVATE queue-vector.c)
    set(TARGET_NAME pr_vector)
else()
    target_sources(MyExecutable PRIVATE queue-list.c)
    set(TARGET_NAME pr_list)
endif()

# Set the output executable name
set_target_properties(MyExecutable PROPERTIES OUTPUT_NAME ${TARGET_NAME})
