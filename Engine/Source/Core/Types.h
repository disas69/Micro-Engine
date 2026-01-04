#pragma once

#include <raylib-cpp.hpp>

namespace Micro
{
typedef raylib::Vector2 MVector2;
typedef raylib::Vector3 MVector3;
typedef raylib::Vector4 MVector4;
typedef raylib::Matrix MMatrix;
typedef raylib::Quaternion MQuaternion;
typedef raylib::Rectangle MRectangle;

typedef raylib::Window MWindow;
typedef raylib::Color MColor;
typedef raylib::Camera2D MCamera2D;
typedef raylib::Camera3D MCamera3D;
typedef raylib::Texture MTexture;
typedef raylib::Texture2D MTexture2D;
typedef raylib::Image MImage;
typedef raylib::RenderTexture MRenderTexture;
typedef raylib::RenderTexture2D MRenderTexture2D;

typedef raylib::Material MMaterial;
typedef raylib::Mesh MMesh;
typedef raylib::Model MModel;
typedef raylib::Shader MShader;
}  // namespace Micro
