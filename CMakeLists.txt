cmake_minimum_required(VERSION 3.0.0)
project(arcadeApp VERSION 0.1.0)

include(CTest)
enable_testing()
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(arcadeApp 
main.cpp

app/app.cpp
app/button.cpp

games/highScores.cpp
games/titleScreen.cpp

games/asteroids/asteroids.cpp
games/asteroids/rock.cpp
games/asteroids/ship.cpp

games/breakOut/ball.cpp
games/breakOut/block.cpp
games/breakOut/breakOut.cpp
games/breakOut/breakOutLevel.cpp
games/breakOut/excluder.cpp
games/breakOut/layoutBlock.cpp
games/breakOut/levelBoundary.cpp
games/breakOut/paddle.cpp

games/tetris/tetris.cpp
games/tetris/tetrisBlock.cpp
games/tetris/tetrisShape.cpp

graphics/animatedSprite.cpp
graphics/animation.cpp
graphics/animationPlayer.cpp
graphics/bitmapFont.cpp
graphics/bmpImage.cpp
graphics/color.cpp
graphics/screen.cpp
graphics/screenBuffer.cpp
graphics/spriteSheet.cpp


input/inputController.cpp
input/gameController.cpp

scenes/arcadeScene.cpp
scenes/buttonOptionScene.cpp
scenes/gameScene.cpp
scenes/notImplementedScene.cpp

shapes/aaRectangle.cpp
shapes/circle.cpp
shapes/line2D.cpp
shapes/shape.cpp
shapes/triangle.cpp

utils/fileCommandLoader.cpp
utils/utils.cpp
utils/vec2d.cpp

)
add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)
add_dependencies(${PROJECT_NAME} copy_assets)
target_link_libraries(${PROJECT_NAME} SDL2 )
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_definitions(-DSDL_MAIN_HANDLED)
