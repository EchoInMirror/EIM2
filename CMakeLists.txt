cmake_minimum_required(VERSION 3.22)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(EIM VERSION 0.0.0)

set(CEF_VERSION 96.0.18+gfe551e4+chromium-96.0.4664.110)
set(CMAKE_CXX_STANDARD 17)
set(CEF_USE_SANDBOX OFF CACHE BOOL "Force turning off of sandbox")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CEF_CMAKE_OUTPUT_DIR ${CMAKE_BINARY_DIR}/Main)
set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake
    ${CMAKE_CURRENT_SOURCE_DIR}/cef-cmake/cmake
)

include(cef_cmake)
add_subdirectory(cef-cmake)

add_subdirectory(Main)
add_subdirectory(Render)
