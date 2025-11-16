project(MicroEngine VERSION 1.0.0)

configure_file(EngineConfig.h.template ${CMAKE_CURRENT_SOURCE_DIR}/Source/EngineConfig.h)

set(ENGINE_SOURCES
        Source/EngineConfig.h
        Source/Core/Engine.cpp
        Source/Core/Engine.h
        Source/pch.cpp
        Source/pch.h
)

add_library(MicroEngineLib ${ENGINE_SOURCES})
target_include_directories(MicroEngineLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)

target_precompile_headers(MicroEngineLib PUBLIC Source/pch.h)

add_executable(MicroEngine Source/main.cpp)
target_link_libraries(MicroEngine PRIVATE MicroEngineLib)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_target_properties(MicroEngine PROPERTIES FOLDER "Engine")
set_target_properties(MicroEngineLib PROPERTIES FOLDER "Engine")