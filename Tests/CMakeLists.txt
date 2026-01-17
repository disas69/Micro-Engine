project(MicroEngineTests LANGUAGES CXX)

# Test framework
include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.12.0
)
FetchContent_MakeAvailable(Catch2)

add_executable(MicroEngineTests
        Source/TransformTests.cpp
)

target_link_libraries(MicroEngineTests
        PRIVATE
        MicroLib
        Catch2::Catch2WithMain
)

target_include_directories(MicroEngineTests
        PRIVATE
        ${CMAKE_SOURCE_DIR}/Source
)

set_target_properties(MicroEngineTests PROPERTIES
        FOLDER "Tests"
)

include(CTest)
include(Catch)

catch_discover_tests(MicroEngineTests)
