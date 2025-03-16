cmake_minimum_required(VERSION 3.16)
set(PROJ_NAME "OopLab2")
project (${PROJ_NAME} VERSION 3.16 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/code")
set(OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(EXE_OUTPUT_NAME "pr")

set(EXE_SOURCES ${SRC_DIR}/main.cpp)

set(MAINLIB_NAME "my")
set(MAINLIB_SOURCES
        ${SRC_DIR}/dialogue.cpp
        ${SRC_DIR}/job.cpp
)

set(SIMPLE_NAME "simple")
set(SIMPLE_SOURCES ${SRC_DIR}/simple.cpp)

set(COMPLEX_NAME "complex")
set(COMPLEX_SOURCES ${SRC_DIR}/complex.cpp)

add_library(${MAINLIB_NAME} STATIC ${MAINLIB_SOURCES})
add_library(${SIMPLE_NAME} STATIC ${SIMPLE_SOURCES})
add_library(${COMPLEX_NAME} STATIC ${COMPLEX_SOURCES})

target_include_directories(${MAINLIB_NAME} PRIVATE ${SRC_DIR})
target_include_directories(${SIMPLE_NAME} PRIVATE ${SRC_DIR})
target_include_directories(${COMPLEX_NAME} PRIVATE ${SRC_DIR})

target_link_libraries(${COMPLEX_NAME} PRIVATE ${SIMPLE_NAME})
target_link_libraries(${MAINLIB_NAME} PRIVATE ${COMPLEX_NAME})

set(EXE_NAME "MyPrecious")
add_executable(${EXE_NAME} ${EXE_SOURCES})

target_include_directories(${EXE_NAME} PRIVATE ${SRC_DIR})
target_link_libraries(${EXE_NAME} PRIVATE ${MAINLIB_NAME})

set_target_properties(${EXE_NAME} PROPERTIES
        OUTPUT_NAME ${EXE_OUTPUT_NAME}
        RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
)

target_compile_options(${MAINLIB_NAME} PRIVATE -Wall -g)
target_compile_options(${SIMPLE_NAME} PRIVATE -Wall -g)
target_compile_options(${COMPLEX_NAME} PRIVATE -Wall -g)
target_compile_options(${EXE_NAME} PRIVATE -Wall -g)
