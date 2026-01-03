project(MicroEngine VERSION 1.0.0)

configure_file(EngineConfig.h.template ${CMAKE_CURRENT_SOURCE_DIR}/Source/EngineConfig.h)

set(ENGINE_SOURCES
        Source/EngineConfig.h
        Source/Core/Engine.cpp
        Source/Core/Engine.h
        Source/Core/Log.cpp
        Source/Core/Log.h
        Source/Core/RenderContext.cpp
        Source/Core/RenderContext.h
        Source/Memory/ArenaAllocator.h
        Source/Game/GameBase.cpp
        Source/Game/GameBase.h
        Source/Gameplay/Component.h
        Source/Gameplay/Component.cpp
        Source/Gameplay/GameObject.h
        Source/Gameplay/GameObject.cpp
        Source/Gameplay/GameObjectPool.h
        Source/Gameplay/Transform2dComponent.cpp
        Source/Gameplay/Transform2dComponent.h
        Source/Gameplay/TransformComponent.cpp
        Source/Gameplay/TransformComponent.h
        Source/Gameplay/GraphicComponent.h
        Source/Gameplay/SpriteComponent.cpp
        Source/Gameplay/SpriteComponent.h
        Source/Gameplay/MeshComponent.cpp
        Source/Gameplay/MeshComponent.h
        Source/Gameplay/TextComponent.cpp
        Source/Gameplay/TextComponent.h
        Source/Gameplay/ImageComponent.cpp
        Source/Gameplay/ImageComponent.h
        Source/Gameplay/ButtonComponent.cpp
        Source/Gameplay/ButtonComponent.h
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