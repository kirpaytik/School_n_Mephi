# Если CMakeLists.txt в папке dir
# Весь код хранить в dir/code
# Билдить в dir/build

cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
set(PROJ_NAME "AisdLab2")
project(${PROJ_NAME} VERSION 3.0 LANGUAGES C)

# Collecting all source-files into variables
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/code")
set(EXE_SOURCES ${SRC_DIR}/main.c)
set(MYLIB_SOURCES
	${SRC_DIR}/reception.c
	${SRC_DIR}/task.c
)
# Using a flag to choose a queue implementation (vector/list)
option(USE_VECTOR "Use vector implementation for queue" ON)
if (USE_VECTOR)
	set(QUELIB_SOURCES ${SRC_DIR}/queue-vector.c)
	set(EXE_OUTPUT_NAME "pr-vector")
	message("Using vector implementation for queue")
else()
	set(QUELIB_SOURCES ${SRC_DIR}/queue-list.c)
	set(EXE_OUTPUT_NAME "pr-list")
	message("Using list implementation for queue")
endif()
# Using a flag to choose a type of queue_lib (static/dynamic)
option(QUELIB_USE_STATIC "Build a static queue_lib library" ON)
if (QUELIB_USE_STATIC)
	set(QUELIB_TYPE "STATIC")
	set(EXE_OUTPUT_NAME "${EXE_OUTPUT_NAME}-STATIC")
	message("Building a static queue_lib library")
else()
	set(QUELIB_TYPE "SHARED")
	set(EXE_OUTPUT_NAME "${EXE_OUTPUT_NAME}-SHARED")
	message("Building a dynamic queue_lib library")
endif()

# Adding libraries
set(MYLIB_NAME "my_lib")
set(QUEUELIB_NAME "queue_lib")
add_library(${MYLIB_NAME} STATIC ${MYLIB_SOURCES})
add_library(${QUEUELIB_NAME} ${QUELIB_TYPE} ${QUELIB_SOURCES})
# Adding compile flags to executable
target_compile_options(${MYLIB_NAME} PRIVATE -Wall -g)
target_compile_options(${QUEUELIB_NAME} PRIVATE -Wall -g)
# Linking libraries
target_link_libraries(${MYLIB_NAME} PRIVATE ${QUEUELIB_NAME})
# Including libraries' directories
target_include_directories(${MYLIB_NAME} PRIVATE ${SOURCE_DIR})

# Creating executable
set(EXE_NAME "MyExecutable")
add_executable(${EXE_NAME} ${EXE_SOURCES})
# Linking executable with libraries
target_link_libraries(${EXE_NAME} PRIVATE ${MYLIB_NAME})
# Changing executable's output name
# set(EXE_OUTPUT_NAME "pr") # was already defined in ifs
set_target_properties(${EXE_NAME} PROPERTIES OUTPUT_NAME ${EXE_OUTPUT_NAME})
# Adding compile flags to executable
target_compile_options(${EXE_NAME} PRIVATE -Wall -g)
