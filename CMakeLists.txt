
cmake_minimum_required(VERSION 3.25)


set_property(GLOBAL PROPERTY USE_FOLDERS ON)


project(CSES
    VERSION 1.0.0   
    LANGUAGES C CXX
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/sources)
