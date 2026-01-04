# AI Agent Coding Guidelines - MicroEngine

This document provides instructions and guidelines for AI agents working on the MicroEngine project. MicroEngine is a custom C++ game engine built on top of [raylib](https://www.raylib.com/), with an editor UI powered by [ImGui](https://github.com/ocornut/imgui).

## Project Overview

- **Engine**: Located in `Engine/Source/`, uses `raylib-cpp`.
- **Editor**: Located in `Editor/Source/`, uses ImGui and `rlImGui`.
- **Games**: Example games are in the `Games/` directory.
- **Dependencies**: Managed via CMake (raylib, imgui, rlImGui, raylib-cpp, tinyfiledialogs, etc.).

## Tech Stack

- **Language**: C++20.
- **Graphics**: raylib (via `raylib-cpp` wrappers where applicable).
- **UI**: ImGui for Editor tools.
- **Build System**: CMake.

## Code Style & Conventions

- **Namespace**: All engine code should reside within the `Micro` namespace.
- **Types**: The engine uses custom typedefs for most types, located in `Engine/Source/Core/Types.h`.
- **Naming Conventions**:
    - **Classes/Structs**: `PascalCase` (e.g., `ArenaAllocator`).
    - **Methods/Functions**: `PascalCase` (e.g., `OnInit`, `OnUpdate`).
    - **Member Variables**: `m_` prefix followed by `camelCase` (e.g., `m_windowTitle`, `m_persistentArena`).
    - **Local Variables**: `camelCase` (e.g., `screenWidth`).
    - **Constants/Macros**: `UPPER_SNAKE_CASE` (e.g., `DEFAULT_EDITOR_SCREEN_WIDTH`).
- **Files**: Use `.h` for headers and `.cpp` for implementations. Use `#pragma once` in headers.
- **Formatting**: Use .clang-format with the following rules.
    - Language: Cpp
    - BasedOnStyle: Microsoft
    - IndentWidth: '4'
    - UseTab: Never
    - TabWidth: '4'
    - BreakBeforeBraces: Allman
    - ColumnLimit: '165'
    - AccessModifierOffset: '-4'
    - SortIncludes: false
    - AllowShortBlocksOnASingleLine: false
    - AlignAfterOpenBracket: DontAlign
    - AllowShortFunctionsOnASingleLine: Inline
    - PointerAlignment: Left
    - AllowShortIfStatementsOnASingleLine: true
    - SpacesBeforeTrailingComments: 2
    - AllowShortCaseLabelsOnASingleLine: true
    - IndentCaseLabels: true
    - AlwaysBreakTemplateDeclarations: Yes
- **Style**: Follow existing code style exactly when adding new code to a file.
    - Prefer explicit nullptr checks over implicit (ptr == null instead of !ptr).
- **Includes**:
    - Prefer `#include "Path/To/Header.h"` for internal engine files.
    - Use `<system_header>` or library headers (e.g., `<raylib.h>`) appropriately.
    - Standard library and raylib includes are placed in pch.h

## Architectural Patterns

### 1. Memory Management
MicroEngine uses smart pointers for dynamic memory management. For special cases and when optimization is needed, ArenaAllocator can be used. For all other cases use stack memory if possible.
Here's the preferred order of memory allocation:
- Stack memory (pass by value or reference)
- Smart pointers (most of the time `std::unique_ptr`, rarely `std::shared_ptr`) with access via raw pointers
- ArenaAllocator for mass allocations with similar lifetimes

### 2. Engine Loop & Game Base
Games should inherit from `Micro::GameBase` and implement:
- `OnInit()`: Initialization logic.
- `OnUpdate(ArenaAllocator& frameArena, float deltaTime)`: Logic updates, using the provided `frameArena` for temporary allocations.
- `OnRender()`: raylib drawing commands.

### 3. Logging
Use the provided logging macros:
- `MICRO_LOG_INFO(msg)`
- `MICRO_LOG_WARNING(msg)`
- `MICRO_LOG_ERROR(msg)`
- `MICRO_LOG_FATAL(msg)`

### 4. Editor Development
- The editor uses a docking layout.
- New editor windows should be added to `EditorApp::DrawMainViewport`.
- Use `rlImGui` functions to bridge raylib and ImGui (e.g., `rlImGuiImageRenderTextureFit`).

## Workflow for Agents

1.  **Analyze**: Before making changes, explore the existing class hierarchy and memory usage patterns.
2.  **Memory First**: When adding new systems, consider how they will be allocated. Prefer `ArenaAllocator`.
3.  **Style Match**: Ensure new code matches the exact style of the file it's being added to.
4.  **CMake**: If adding new files, remember to update the corresponding `CMakeLists.txt`.
5.  **Headers**: Keep headers clean, always consider pch.h. Use forward declarations where possible to reduce compilation times.
6.  **Execution**: Make a complete step-by-step plan, output the plan and ask for confirmation before executing. When confirmed, execute the plan step-by-step, providing code snippets for each step.
