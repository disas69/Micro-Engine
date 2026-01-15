# C++ Micro Game Engine – Features Roadmap

---

## 1. Application & Engine Core

### 1.1 Engine / Application

Responsible for engine lifecycle and high-level flow.

* Engine initialization / shutdown
* Main loop

    * Update
    * FixedUpdate (optional)
    * Render
* Time management

    * Delta time
    * Time scale
* Global engine state
* Runtime vs Editor mode

---

## 2. Scene & World Management

### 2.1 Scene Manager

Controls what world is currently active.

* Load / unload scenes
* Track active scene
* Scene transitions
* Scene stack (menus, overlays)
* Scene serialization (JSON / YAML)
* Editor scene loading (without running game)

Typical scene responsibilities:

* Own entities
* Update & render calls
* Handle scene-specific resources

---

## 3. Entity & Component System

### 3.1 Entity System

Recommended approach: **GameObject + Component** (Unity-style).

* Entity creation / destruction
* Unique entity IDs or handles
* Enable / disable entities
* Name / tag support

### 3.2 Component System

Core component features:

* Add / remove components
* Component lifecycle hooks
* Query components by type

Common components:

* TransformComponent
* SpriteRendererComponent
* MeshRendererComponent
* CameraComponent
* LightComponent
* ScriptComponent

---

## 4. Transform & Hierarchy

### 4.1 Transform System

* Position / Rotation / Scale
* Parent–child hierarchy
* Local ↔ World transforms
* Dirty flag propagation

Used by:

* Cameras
* Child objects
* Editor gizmos

---

## 5. Asset & Resource Management

### 5.1 Asset Manager

* Centralized asset loading
* Asset caching
* Reference counting
* Asset handles

Supported asset types:

* Textures (`Texture2D`)
* Models (`Model`)
* Shaders (`Shader`)
* Sounds / Music
* Fonts

### 5.2 Hot Reloading (Optional)

* File watching
* Reload textures / shaders on change
* Editor productivity feature

---

## 6. Rendering Layer (On Top of raylib)

### 6.1 Render System

* Render queues (opaque / transparent / UI)
* Draw sorting (layer, depth)
* Camera-based rendering
* Render layers / masks

> raylib is immediate-mode; engine should collect draw commands and submit them in order.

---

## 7. Camera System

### 7.1 Camera Manager

* Multiple cameras
* Active camera selection
* 2D (`Camera2D`) and 3D (`Camera3D`)
* Editor camera vs Game camera

Editor camera features:

* Fly camera
* Orbit camera
* Focus on selection

---

## 8. Input System

### 8.1 Input Manager

Wrap raylib input for consistency.

* Keyboard
* Mouse
* Gamepad

### 8.2 Action Mapping

* Logical actions (Jump, Fire, Pause)
* Rebindable controls
* Multiple device support

---

## 9. Physics & Collision

raylib does not include physics.

### 9.1 Collision System

* AABB
* Circle / Sphere
* Raycasts
* Trigger volumes

### 9.2 Physics Simulation

Options:

* Simple custom physics
* Box2D (2D)
* Bullet (3D)

---

## 10. Audio System

### 10.1 Audio Manager

* Load / unload sounds
* Play / stop audio
* Volume groups (master / music / SFX)
* 3D positional audio

---

## 11. UI System

### 11.1 Runtime UI

Options:

* raylib UI
* Custom retained-mode UI
* ImGui (acceptable for tools or debug UI)

### 11.2 Editor UI (ImGui)

Core editor panels:

* Scene Hierarchy
* Inspector
* Asset Browser
* Console / Logs
* Game View
* Scene View

---

## 12. Editor Systems

### 12.1 Editor Core

* Play / Pause / Step
* Edit scenes without running
* Undo / Redo

### 12.2 Gizmos

* Translate / Rotate / Scale
* Bounding boxes
* Camera frustums

---

## 13. Serialization & Prefabs

### 13.1 Serialization

* Scene serialization
* Component data versioning
* Backward compatibility

### 13.2 Prefabs

* Reusable entity templates
* Nested prefabs
* Override system

---

## 14. Scripting (Optional)

### 14.1 Script System

Options:

* Native C++ scripts
* Lua
* C# via Mono

Features:

* Script lifecycle hooks
* Engine API bindings
* Hot reload (optional)

---

## 15. Debugging & Diagnostics

### 15.1 Debug Tools

* Logging system
* Assertions
* On-screen debug info

### 15.2 Debug Rendering

* Collision shapes
* Grid
* FPS / memory stats

---

## 16. Performance & Architecture

### 16.1 Memory Management

* Object pools for components
* Frame allocators
* Minimize per-frame allocations

### 16.2 Multithreading (Optional)

* Async asset loading
* Job system

> Note: raylib rendering must stay on the main thread.

---

## 17. Minimal First-Playable Feature Set

Recommended minimum scope:

1. Engine loop
2. Scene Manager
3. Entity + Transform system
4. Sprite / Model rendering
5. Camera system
6. Input Manager
7. Asset Manager
8. ImGui editor (Hierarchy + Inspector)

---

## 18. Suggested Folder Structure

```
Engine/
  Core/
  Scene/
  Entity/
  Assets/
  Rendering/
  Input/
  Physics/
  Audio/
  UI/
  Editor/
  Serialization/
```
