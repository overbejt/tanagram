cmake_minimum_required(VERSION 3.25.3)
project(Tanagram VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Download and link pybind11
include(FetchContent)
set(PYBIND11_FINDPYTHON NEW)
FetchContent_Declare(
  pybind11
  GIT_REPOSITORY "https://github.com/pybind/pybind11.git"
  GIT_TAG v3.1.0
)
FetchContent_MakeAvailable(pybind11)

file(GLOB SOURCES "src/*.cpp")
pybind11_add_module(tanagram ${SOURCES})
target_link_libraries(tanagram PRIVATE pybind11::module)
target_include_directories(tanagram PRIVATE include)

target_compile_options(tanagram PRIVATE
    $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra -Wpendantic -Werror>
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Werror>
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
)

# END OF FILE

