cmake_minimum_required(VERSION 3.10)
project(controller-manager)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

install(DIRECTORY res DESTINATION .)

file(GLOB_RECURSE TARGET_H "${SOURCE_DIR}/*.h")
file(GLOB_RECURSE TARGET_CPP "${SOURCE_DIR}/*.cpp")

add_executable(${PROJECT_NAME} ${TARGET_CPP} ${TARGET_CPP}) 
target_link_libraries(${PROJECT_NAME} SDL2::SDL2 SDL2_ttf::SDL2_ttf)
