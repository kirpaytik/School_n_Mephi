cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(PROJ_NAME "AisdLab4a")
project(${PROJ_NAME} VERSION 3.5 LANGUAGES C)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/code")
set(EXE_OUTPUT_NAME "pr")
set(OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(EXE_SOURCES ${SRC_DIR}/main.c)

option(USE_MYLIB "Use mylib.h instead of dop.h" ON)

if (USE_MYLIB)
	add_definitions(-DUSE_MYLIB)
	set(MAINLIB_SOURCES
		${SRC_DIR}/dialog.c
		${SRC_DIR}/input.c
		${SRC_DIR}/job.c)
	set(MAINLIB_NAME "my")
	set(EXE_OUTPUT_NAME "${EXE_OUTPUT_NAME}1")
	message("Building with mylib.h")
else()
	set(MAINLIB_SOURCES ${SRC_DIR}/dop.c)
	set(MAINLIB_NAME "dop")
	set(EXE_OUTPUT_NAME "${EXE_OUTPUT_NAME}2")
	message("Building with dop.h")
endif()

set(TREE_SOURCES
	${SRC_DIR}/tree.c
	${SRC_DIR}/visual.c
)
set(QUE_SOURCES ${SRC_DIR}/queue.c)

option(TREE_USE_STATIC "Build a static tree library" ON)
if (TREE_USE_STATIC)
	set(TREE_TYPE "STATIC")
	message("Building a static tree library")
else()
	set(TREE_TYPE "SHARED")
	message("Building a dynamic tree library")
endif()

option(QUE_USE_STATIC "Build a static queue library" ON)
if (QUE_USE_STATIC)
	set(QUE_TYPE "STATIC")
	message("Building a static queue library")
else()
	set(QUE_TYPE "SHARED")
	message("Building a dynamic queue library")
endif()

# Adding libraries
# names without "lib" in it, cuz it will be automatically added
set(TREE_NAME "tree")
set(QUE_NAME "queue")
add_library(${MAINLIB_NAME} STATIC ${MAINLIB_SOURCES})
add_library(${TREE_NAME} ${TREE_TYPE} ${TREE_SOURCES})
add_library(${QUE_NAME} ${QUE_TYPE} ${QUE_SOURCES})

target_include_directories(${MAINLIB_NAME} PRIVATE ${SOURCE_DIR})
target_include_directories(${TREE_NAME} PRIVATE ${SOURCE_DIR})
target_include_directories(${QUE_NAME} PRIVATE ${SOURCE_DIR})

target_link_libraries(${MAINLIB_NAME} PRIVATE ${TREE_NAME})
target_link_libraries(${TREE_NAME} PRIVATE ${QUE_NAME})

# Creating executable
set(EXE_NAME "MyExecutable")
add_executable(${EXE_NAME} ${EXE_SOURCES})

target_include_directories(${EXE_NAME} PRIVATE ${SRC_DIR})
target_link_libraries(${EXE_NAME} PRIVATE ${MAINLIB_NAME})

set_target_properties(${EXE_NAME} PROPERTIES
	OUTPUT_NAME ${EXE_OUTPUT_NAME} 
	RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
)

target_compile_options(${MAINLIB_NAME} PRIVATE -Wall -g)
target_compile_options(${TREE_NAME} PRIVATE -Wall -g)
target_compile_options(${QUE_NAME} PRIVATE -Wall -g)
target_compile_options(${EXE_NAME} PRIVATE -Wall -g)
