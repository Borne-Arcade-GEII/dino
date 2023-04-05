cmake_minimum_required (VERSION 2.9)
project (dino C)
# The version number.

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

aux_source_directory(src SRC_LIST)
aux_source_directory(headers SRC_LIST)
add_executable(dino ${SRC_LIST})
INCLUDE(FindPkgConfig)
pkg_check_modules(FREETYPE2 REQUIRED freetype2)
pkg_check_modules(HARFBUZZ REQUIRED harfbuzz)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)

include_directories(${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2_MIXER_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
        ${FREETYPE2_INCLUDE_DIRS}
        ${HARFBUZZ_INCLUDE_DIRS})
link_directories (${SDL2_LIBRARY_DIRS}
        ${SDL2_IMAGE_LIBRARY_DIRS}
        ${SDL2_MIXER_LIBRARY_DIRS}
        ${SDL2_TTF_LIBRARY_DIRS}
        ${FREETYPE2_LIBRARY_DIRS}
        ${HARFBUZZ_LIBRARY_DIRS})
target_link_libraries (dino ${SDL2_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${FREETYPE2_LIBRARIES}
        ${HARFBUZZ_LIBRARIES}
        m)