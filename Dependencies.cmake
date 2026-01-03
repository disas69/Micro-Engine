include(FetchContent)

# raylib
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG        5.5
)
FetchContent_MakeAvailable(raylib)

# ImGui (core library only)
FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG        docking
)
FetchContent_MakeAvailable(imgui)
add_library(imgui STATIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
)
target_include_directories(imgui
        PUBLIC
        ${imgui_SOURCE_DIR}
)
target_compile_definitions(imgui
        PUBLIC
        IMGUI_ENABLE_DOCKING
        # IMGUI_DISABLE_OBSOLETE_FUNCTIONS
)

# rlImGui (ImGui + raylib bridge)
FetchContent_Declare(
        rlimgui
        GIT_REPOSITORY https://github.com/raylib-extras/rlImGui.git
        GIT_TAG        main
)
FetchContent_MakeAvailable(rlimgui)
add_library(rlImGui STATIC
        ${rlimgui_SOURCE_DIR}/rlImGui.cpp
)
target_include_directories(rlImGui
        PUBLIC
        ${rlimgui_SOURCE_DIR}
)
target_link_libraries(rlImGui
        PUBLIC
        raylib
        imgui
)

# raygui (for in-game UI)
FetchContent_Declare(
        raygui
        GIT_REPOSITORY https://github.com/raysan5/raygui.git
        GIT_TAG        master
)
FetchContent_MakeAvailable(raygui)
add_library(raygui STATIC
        ${raygui_SOURCE_DIR}/src/raygui.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Source/External/raygui_impl.cpp
)
target_include_directories(raygui
        PUBLIC
        ${raygui_SOURCE_DIR}/src
)
target_link_libraries(raygui
        PUBLIC
        raylib
)

# raylib-cpp (C++ wrapper for raylib)
FetchContent_Declare(
        raylib_cpp
        GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
        GIT_TAG        master
)
FetchContent_MakeAvailable(raylib_cpp)

# tinyfiledialogs (for file dialogs in editor)
FetchContent_Declare(
        tinyfiledialogs
        GIT_REPOSITORY https://github.com/native-toolkit/tinyfiledialogs.git
        GIT_TAG        master
)
FetchContent_MakeAvailable(tinyfiledialogs)
add_library(tinyfd STATIC
        ${tinyfiledialogs_SOURCE_DIR}/tinyfiledialogs.c
)
target_include_directories(tinyfd
        PUBLIC
        ${tinyfiledialogs_SOURCE_DIR}
)
