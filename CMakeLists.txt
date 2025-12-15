
cmake_minimum_required(VERSION 3.20)
project(TaskManager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# If you add third-party libs later (e.g., nlohmann_json), use find_package here.

file(GLOB_RECURSE SRC_FILES
    CONFIGURE_DEPENDS
    "src/*.cpp"
)

add_executable(task_manager ${SRC_FILES})
target_include_directories(task_manager PRIVATE src)

# Enable warnings
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(task_manager PRIVATE -Wall -Wextra -Wpedantic)
elseif (MSVC)
  target_compile_options(task_manager PRIVATE /W4)
endif()