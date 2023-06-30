cmake_minimum_required(VERSION 3.10)
project(my_project)

# Set the C++ Standard
set(CMAKE_CXX_STANDARD 17)

# Add the include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2-2.26.5/x86_64-w64-mingw32/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2_image-2.6.3/x86_64-w64-mingw32/include)

# Add the executable target and its source files
add_executable(my_project 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/level/level.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/level/groundTile.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/level/backgroundTile.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/background/background.cpp
    
)

# Link the target executable against SDL2 and SDL2_image
target_link_libraries(my_project
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2-2.26.5/x86_64-w64-mingw32/lib/libSDL2.dll.a
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2_image-2.6.3/x86_64-w64-mingw32/lib/libSDL2_image.dll.a
)

# Copy SDL2.dll to the build folder during configuration
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2-2.26.5/x86_64-w64-mingw32/bin/SDL2.dll
               ${CMAKE_CURRENT_BINARY_DIR}/SDL2.dll
               COPYONLY
)

# Copy libSDL2_image.dll to the build folder during configuration
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2_image-2.6.3/x86_64-w64-mingw32/bin/SDL2_image.dll
               ${CMAKE_CURRENT_BINARY_DIR}/SDL2_image.dll
               COPYONLY
)

