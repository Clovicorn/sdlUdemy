cmake_minimum_required(VERSION 3.0.0)
project(arcadeApp VERSION 0.1.0)

include(CTest)
enable_testing()
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(arcadeApp 
main.cpp

app/app.cpp

games/breakOut/ball.cpp
games/breakOut/block.cpp
games/breakOut/breakOut.cpp
games/breakOut/breakOutLevel.cpp
games/breakOut/excluder.cpp
games/breakOut/layoutBlock.cpp
games/breakOut/levelBoundary.cpp
games/breakOut/paddle.cpp

graphics/color.cpp
graphics/screenBuffer.cpp
graphics/screen.cpp

input/gameController.cpp
input/inputController.cpp

scenes/arcadeScene.cpp
scenes/gameScene.cpp

shapes/aaRectangle.cpp
shapes/circle.cpp
shapes/line2D.cpp
shapes/triangle.cpp
shapes/shape.cpp

utils/utils.cpp
utils/vec2d.cpp
utils/fileCommandLoader.cpp

)

target_link_libraries(${PROJECT_NAME} SDL2 )
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_definitions(-DSDL_MAIN_HANDLED)
