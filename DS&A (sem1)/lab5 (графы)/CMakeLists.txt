cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
set(PROJ_NAME "AisdLab5")
project (${PROJ_NAME} VERSION 3.0 LANGUAGES C)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/code")
set(OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(EXE_OUTPUT_NAME "pr")

set(EXE_SOURCES ${SRC_DIR}/main.c)

set(MAINLIB_NAME "my")
set(MAINLIB_SOURCES
        ${SRC_DIR}/dialog.c
        ${SRC_DIR}/input.c
        ${SRC_DIR}/job.c
)

set(GRAPHLIB_NAME "graph")
set(GRAPHLIB_SOURCES
        ${SRC_DIR}/graph.c
        ${SRC_DIR}/visual.c
)
option(GRAPHLIB_USE_STATIC "Build a static graph library" ON)
if (GRAPHLIB_USE_STATIC)
        set(GRAPHLIB_TYPE "STATIC")
        message("Building a static graph library")
else()
        set(GRAPHLIB_TYPE "SHARED")
        message("Building a dynamic graph library")
endif()

set(QUELIB_NAME "queue")
set(QUELIB_SOURCES ${SRC_DIR}/queue.c)
option(QUEUELIB_USE_STATIC "Build a static queue library" ON)
if (QUEUELIB_USE_STATIC)
        set(QUELIB_TYPE "STATIC")
        message("Building a static queue library")
else()
        set(QUELIB_TYPE "SHARED")
        message("Building a dynamic queue library")
endif()

add_library(${MAINLIB_NAME} STATIC ${MAINLIB_SOURCES})
add_library(${GRAPHLIB_NAME} ${GRAPHLIB_TYPE} ${GRAPHLIB_SOURCES})
add_library(${QUELIB_NAME} ${QUELIB_TYPE} ${QUELIB_SOURCES})

target_include_directories(${MAINLIB_NAME} PRIVATE ${SRC_DIR})
target_include_directories(${GRAPHLIB_NAME} PRIVATE ${SRC_DIR})
target_include_directories(${QUELIB_NAME} PRIVATE ${SRC_DIR})

target_link_libraries(${MAINLIB_NAME} PRIVATE ${GRAPHLIB_NAME})
target_link_libraries(${GRAPHLIB_NAME} PRIVATE ${QUELIB_NAME})

set(EXE_NAME "MyPrecious")
add_executable(${EXE_NAME} ${EXE_SOURCES})

target_include_directories(${EXE_NAME} PRIVATE ${SRC_DIR})
target_link_libraries(${EXE_NAME} PRIVATE ${MAINLIB_NAME})

set_target_properties(${EXE_NAME} PROPERTIES
        OUTPUT_NAME ${EXE_OUTPUT_NAME}
        RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
)

target_compile_options(${MAINLIB_NAME} PRIVATE -Wall -g)
target_compile_options(${GRAPHLIB_NAME} PRIVATE -Wall -g)
target_compile_options(${QUELIB_NAME} PRIVATE -Wall -g)
target_compile_options(${EXE_NAME} PRIVATE -Wall -g)
