cmake_minimum_required(VERSION 3.14)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(x264-playground)

add_library(x264 STATIC IMPORTED)

set_property(
  TARGET x264 APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE
)

set_target_properties(x264 PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${X264_ROOT}/lib/libx264.a"
)
  
set_target_properties(x264 PROPERTIES
  MAP_IMPORTED_CONFIG_MINSIZEREL Release
  MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release
)

target_include_directories(x264 INTERFACE "${X264_ROOT}/include")

SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

add_executable(${PROJECT_NAME}
    "src/main.cpp"
)

target_link_libraries(${PROJECT_NAME} x264)