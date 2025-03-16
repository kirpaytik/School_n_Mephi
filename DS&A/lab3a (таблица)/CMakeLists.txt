cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
set(PROJ_NAME "AisdLab3a")
project(${PROJ_NAME} VERSION 3.0 LANGUAGES C)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/code")
set(OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(EXE_SOURCES ${SRC_DIR}/main.c)
set(MYLIB_SOURCES
	${SRC_DIR}/dialog.c
	${SRC_DIR}/input.c
	${SRC_DIR}/job.c
)

option(TABLE_USE_ITER "Use iterators to interract with table" OFF)
if (TABLE_USE_ITER)
	set(TABLE_SOURCES ${SRC_DIR}/table-iter.c)
	set(EXE_OUTPUT_NAME "pr-iter")
	message("Common interraction with table")
else()
	set(TABLE_SOURCES ${SRC_DIR}/table.c)
	set(EXE_OUTPUT_NAME "pr")
	message("Interraction with table through iterators")
endif()

option(TABLE_USE_STATIC "Build a static table library" ON)
if (TABLE_USE_STATIC)
	set(TABLE_TYPE "STATIC")
	# set(EXE_OUTPUT_NAME "${EXE_OUTPUT_NAME}-STATIC")
	message("Building a static table library")
else()
	set(TABLE_TYPE "SHARED")
	# set(EXE_OUTPUT_NAME "${EXE_OUTPUT_NAME}-SHARED")
	message("Building a dynamic table library")
endif()

# Adding libraries
set(MYLIB_NAME "my_lib")
set(TABLE_NAME "table_lib")
add_library(${MYLIB_NAME} STATIC ${MYLIB_SOURCES})
add_library(${TABLE_NAME} ${TABLE_TYPE} ${TABLE_SOURCES})

target_compile_options(${MYLIB_NAME} PRIVATE -Wall -g)
target_compile_options(${TABLE_NAME} PRIVATE -Wall -g)

target_link_libraries(${MYLIB_NAME} PRIVATE ${TABLE_NAME})

target_include_directories(${MYLIB_NAME} PRIVATE ${SOURCE_DIR})

# Creating executable
set(EXE_NAME "MyExecutable")
add_executable(${EXE_NAME} ${EXE_SOURCES})

target_link_libraries(${EXE_NAME} PRIVATE ${MYLIB_NAME})

set_target_properties(${EXE_NAME} PROPERTIES
	OUTPUT_NAME ${EXE_OUTPUT_NAME} 
	RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
)

target_compile_options(${EXE_NAME} PRIVATE -Wall -g)
