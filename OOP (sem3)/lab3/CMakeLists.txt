cmake_minimum_required(VERSION 3.16)
set(PROJ_NAME "OopLab3")
project(${PROJ_NAME} VERSION 3.16 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Some global info
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cpp")
set(MVC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/mvc")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/hpp")
set(INTERFACE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/interfaces")
set(OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(EXE_OUTPUT_NAME "app")

# SFML configuration
set(SFML_DIR "D:/SFML-2.6.2-sources/build")
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)
include_directories("D:/SFML-2.6.2-sources/include")

# Libraries
set(MODEL_NAME "model")
set(MODEL_SOURCES
	${SRC_DIR}/BuildAttack.cpp
	${SRC_DIR}/Castle.cpp
	${SRC_DIR}/Cell.cpp
	${SRC_DIR}/DefBuild.cpp
	${SRC_DIR}/EffectAttack.cpp
	${SRC_DIR}/Enemy.cpp
	${SRC_DIR}/Field.cpp
	${SRC_DIR}/Lair.cpp
	${SRC_DIR}/Landscape.cpp
	${SRC_DIR}/MagicTower.cpp
	${SRC_DIR}/MagicTrap.cpp
	${SRC_DIR}/PriceTable.cpp
	${SRC_DIR}/Road.cpp
	${SRC_DIR}/Tower.cpp

	${MVC_DIR}/Game.cpp
	${MVC_DIR}/parsing.cpp
)

set(CONTROLLER_NAME "controller")
set(CONTROLLER_SOURCES ${MVC_DIR}/Controller.cpp)

set(VIEW_NAME "view")
set(VIEW_SOURCES ${MVC_DIR}/View.cpp)

add_library(${MODEL_NAME} STATIC ${MODEL_SOURCES})
add_library(${CONTROLLER_NAME} STATIC ${CONTROLLER_SOURCES})
add_library(${VIEW_NAME} STATIC ${VIEW_SOURCES})

target_include_directories(${MODEL_NAME} PRIVATE ${INCLUDE_DIR} ${INTERFACE_DIR} ${MVC_DIR})
target_include_directories(${CONTROLLER_NAME} PRIVATE ${INCLUDE_DIR} ${MVC_DIR})
target_include_directories(${VIEW_NAME} PRIVATE ${INCLUDE_DIR} ${MVC_DIR})

target_link_libraries(${CONTROLLER_NAME} PRIVATE ${MODEL_NAME})
target_link_libraries(${CONTROLLER_NAME} PRIVATE ${VIEW_NAME})

# Exe
set(EXE_NAME "MyPrecious")
set(EXE_SOURCES ${MVC_DIR}/main.cpp)

add_executable(${EXE_NAME} ${EXE_SOURCES})

# target_include_directories(${EXE_NAME} PRIVATE ${INCLUDE_DIR})
target_link_libraries(${EXE_NAME} PRIVATE ${MODEL_NAME})
target_link_libraries(${EXE_NAME} PRIVATE ${CONTROLLER_NAME})
target_link_libraries(${EXE_NAME} PRIVATE ${VIEW_NAME})
target_link_libraries(${EXE_NAME} PRIVATE sfml-graphics sfml-window sfml-system)

set_target_properties(${EXE_NAME} PROPERTIES
	OUTPUT_NAME ${EXE_OUTPUT_NAME}
	RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g -fsanitize=address,undefined")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")

# Supress annoying warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-delete-non-virtual-dtor")
