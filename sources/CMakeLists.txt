

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

    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(cses PRIVATE 
            /fsanitize=address
        )

    endif()
else()
    target_compile_options(cses PRIVATE -Wall -Wextra)

    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(cses PRIVATE
            -fsanitize=address,
            undefined
        )
        target_link_options(cses PRIVATE
            -fsanitize=address,
            undefined
        )
    endif()
endif()
