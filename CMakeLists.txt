cmake_minimum_required(VERSION 3.15.0)

project(pyramid)

add_executable(${PROJECT_NAME})

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_sources(${PROJECT_NAME}
PRIVATE
    src/main.cpp
)

target_compile_options(${PROJECT_NAME}
PRIVATE
    -Wall
    -Wextra
    -Wuninitialized
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOMOC ON
    # AUTORCC ON
    # AUTOUIC ON
    # AUTOUIC_SEARCH_PATHS src/forms
)

if (NOT CMAKE_BUILD_TYPE)
    set (build_type release)
else()
    string(TOLOWER ${CMAKE_BUILD_TYPE} build_type)
endif()

if (build_type STREQUAL debug)
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG)
    target_compile_options(${PROJECT_NAME} PRIVATE -g3 -O0)
elseif (build_type STREQUAL release)
    target_compile_options(${PROJECT_NAME} PRIVATE -g0 -O3)
endif()


find_package(Qt6 COMPONENTS Widgets REQUIRED)

target_link_libraries(${PROJECT_NAME} Qt6::Widgets)

string(TOLOWER ${CMAKE_SYSTEM_NAME} system_name)
if (NOT system_name STREQUAL windows)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS})
endif()
