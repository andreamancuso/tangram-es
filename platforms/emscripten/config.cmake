# include(cmake/glfw.cmake)

add_library(tangram STATIC
    platforms/emscripten/src/emscriptenPlatform.cpp
)

target_link_libraries(tangram
  PRIVATE
  tangram-core
)

add_definitions(-w)

set_target_properties(tangram PROPERTIES COMPILE_FLAGS "-O0 -w --use-port=zlib --use-port=libpng")
set_target_properties(tangram PROPERTIES LINK_FLAGS "-O0 --use-port=zlib --use-port=libpng -s USE_GLFW=3 -s USE_WEBGPU=1 -s FULL_ES3=1 -sOFFSCREENCANVAS_SUPPORT -s EXPORT_ALL=1")