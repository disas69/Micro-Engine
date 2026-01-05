project(MicroEngine VERSION 1.0.0)

configure_file(EngineConfig.h.template ${CMAKE_CURRENT_SOURCE_DIR}/Source/EngineConfig.h)

set(ENGINE_SOURCES
        Source/EngineConfig.h
        Source/Core/Types.h
        Source/Core/GUID.cpp
        Source/Core/GUID.h
        Source/Core/Engine.cpp
        Source/Core/Engine.h
        Source/Core/Log.cpp
        Source/Core/Log.h
        Source/Memory/ArenaAllocator.h
        Source/Game/GameBase.cpp
        Source/Game/GameBase.h
        Source/Gameplay/Components/Component.h
        Source/Gameplay/GameObject.h
        Source/Gameplay/GameObject.cpp
        Source/Gameplay/Components/CameraComponent.h
        Source/Gameplay/Components/TransformComponent.cpp
        Source/Gameplay/Components/TransformComponent.h
        Source/Gameplay/Components/MeshComponent.h
        Source/Gameplay/Components/SpriteComponent.h
        Source/Gameplay/Components/ImageComponent.h
        Source/Gameplay/Components/TextComponent.h
        Source/Gameplay/Scene.cpp
        Source/Gameplay/Scene.h
        Source/Gameplay/Systems/RenderSystem.cpp
        Source/Gameplay/Systems/RenderSystem.h
        Source/Gameplay/Systems/TransformSystem.cpp
        Source/Gameplay/Systems/TransformSystem.h
        Source/Gameplay/Systems/TransformUtils.h
        Source/Game/DefaultGame.cpp
        Source/Game/DefaultGame.h
        Source/External/raygui_impl.cpp
        Source/pch.cpp
        Source/pch.h
)

add_library(MicroLib ${ENGINE_SOURCES})
target_include_directories(MicroLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)

target_precompile_headers(MicroLib PUBLIC Source/pch.h)

target_link_libraries(MicroLib
        PUBLIC
        raylib
        raylib_cpp
        raygui
        # other engine-level deps…
)

add_executable(MicroEngine Source/main.cpp)
target_link_libraries(MicroEngine PRIVATE MicroLib)

set_target_properties(MicroEngine PROPERTIES FOLDER "Engine")
set_target_properties(MicroLib PROPERTIES FOLDER "Engine")