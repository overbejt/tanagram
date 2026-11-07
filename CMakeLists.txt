cmake_minimum_required(VERSION 3.25.3)
project(Tanam VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB SOURCES "src/*.cpp")
# add_executable(tanam ${SOURCES})

# target_include_directories(tanam PRIVATE include)

# Download and link pybind11
include(FetchContent)
FetchContent_Declare(
  pybind11
  GIT_REPOSITORY "https://github.com/pybind/pybind11.git"
  GIT_TAG v3.1.0
)
FetchContent_MakeAvailable(pybind11)

pybind11_add_module(my_module ${SOURCES})
target_link_libraries(my_module PRIVATE pybind11::module)
target_include_directories(my_module PRIVATE include)

target_compile_options(my_module PRIVATE
    $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra -Wpendantic -Werror>
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Werror>
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
)

# target_compile_options(tanam PRIVATE
#     $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra -Wpendantic -Werror>
#     $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Werror>
#     $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
# )
