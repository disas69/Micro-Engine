project(MicroEngineEditor LANGUAGES CXX)

set(EDITOR_SOURCES
        Source/main.cpp
        Source/EditorApp.cpp
        Source/EditorApp.h
        Source/Core/View/SceneView.cpp
        Source/Core/View/SceneView.h
        Source/pch.cpp
        Source/pch.h
)

add_executable(MicroEditor ${EDITOR_SOURCES})
target_include_directories(MicroEditor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Source)

target_precompile_headers(MicroEditor PRIVATE Source/pch.h)

target_link_libraries(MicroEditor
        PRIVATE
        MicroLib
        imgui
        rlImGui
        tinyfd
)

set_target_properties(MicroEditor PROPERTIES FOLDER "Editor")