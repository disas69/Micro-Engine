cmake_minimum_required(VERSION 3.30)

project(MicroGameEngine VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

configure_file(EngineConfig.h.template ${CMAKE_CURRENT_SOURCE_DIR}/Source/EngineConfig.h)

set(ENGINE_SOURCES
        Source/EngineConfig.h
        Source/Core/Engine.cpp
        Source/Core/Engine.h
        Source/pch.cpp
        Source/pch.h
)

add_library(MicroGameEngineLib ${ENGINE_SOURCES})
target_include_directories(MicroGameEngineLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)

target_precompile_headers(MicroGameEngineLib PUBLIC Source/pch.h)

add_executable(MicroGameEngine Source/main.cpp)
target_link_libraries(MicroGameEngine PRIVATE MicroGameEngineLib)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_target_properties(MicroGameEngine PROPERTIES FOLDER "Engine")
set_target_properties(MicroGameEngineLib PROPERTIES FOLDER "Engine")
