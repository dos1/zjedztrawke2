cmake_minimum_required(VERSION 2.8)

project(zjedztrawke2 C)

SET(LIBSUPERDERPY_GAMENAME "zjedztrawke2" CACHE INTERNAL "")
SET(LIBSUPERDERPY_GAMENAME_PRETTY "Zjedz Trawkę 2" CACHE INTERNAL "")

SET(LIBSUPERDERPY_APPID "net.dosowisko.zjedztrawke2" CACHE INTERNAL "")
SET(LIBSUPERDERPY_ORIENTATION "LANDSCAPE" CACHE INTERNAL "")
SET(LIBSUPERDERPY_VERSION "1.0" CACHE INTERNAL "")

set(EMSCRIPTEN_TOTAL_MEMORY "512")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" "${CMAKE_SOURCE_DIR}/libsuperderpy/cmake")

include(libsuperderpy)

add_subdirectory(libsuperderpy)
add_subdirectory(src)
add_subdirectory(data)
