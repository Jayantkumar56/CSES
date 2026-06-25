

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_executable(cses
    main.cpp
)

target_include_directories(cses PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions(cses PRIVATE CS_RUNNING_LOCALLY)

if(MSVC)
    target_compile_options(cses PRIVATE /W4)
else()
    target_compile_options(cses PRIVATE -Wall -Wextra)
endif()
