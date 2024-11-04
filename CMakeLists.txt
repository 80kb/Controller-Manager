cmake_minimum_required(VERSION 3.10)
project(controller-manager)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)

get_filename_component(CMAKE_CURRENT_LIST_DIR "${CMAKE_CURRENT_LIST_FILE}" DIRECTORY)
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

file(GLOB_RECURSE TARGET_H "${SOURCE_DIR}/*.h")
file(GLOB_RECURSE TARGET_CPP "${SOURCE_DIR}/*.cpp")

if ( NOT CMAKE_BUILD_TYPE )
    set( CMAKE_BUILD_TYPE Debug )
endif()

add_executable(${PROJECT_NAME} ${TARGET_CPP} ${TARGET_CPP})
target_link_libraries(${PROJECT_NAME}
	PRIVATE
	$<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
	$<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
	$<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
)

if(MSVC)
	set(BUILD_DIR "${CMAKE_BINARY_DIR}/Debug")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
	set(BUILD_DIR "${CMAKE_BINARY_DIR}")
endif()

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/res/ttf ${BUILD_DIR}/ttf
)