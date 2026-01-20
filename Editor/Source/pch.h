#pragma once

// std
#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <string>
#include <string_view>
#include <memory>
#include <algorithm>
#include <chrono>
#include <format>
#include <cstdint>
#include <functional>
#include <cmath>
#include <utility>
#include <filesystem>

// raylib
#include <raylib.h>
#include <raylib-cpp.hpp>
#include <raymath.h>
#include <raygui.h>

// custom
#include "Core/Types.h"
#include "Core/Log.h"
#include "Serialization/Reflection/Macros.h"
#include "Serialization/Reflection/TypeDescriptor.h"
#include "Serialization/Reflection/TypeRegistry.h"