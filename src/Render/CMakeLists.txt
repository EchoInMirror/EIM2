cmake_minimum_required(VERSION 3.22)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(EIM VERSION 0.0.0)

set(CEF_VERSION 96.0.18+gfe551e4+chromium-96.0.4664.110)
set(CMAKE_CXX_STANDARD 17)
set(CEF_USE_SANDBOX OFF CACHE BOOL "Force turning off of sandbox")

set(CEF_CMAKE_OUTPUT_DIR ${CMAKE_BINARY_DIR}/EIM_artefacts)
set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake
    ${CMAKE_CURRENT_SOURCE_DIR}/cef-cmake/cmake
)

add_definitions(-DJUCE_PLUGINHOST_VST3)

add_subdirectory(JUCE)

include(cef_cmake)
add_subdirectory(cef-cmake)
set_property(TARGET cefdll_wrapper PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

file(GLOB MAIN_SRC_FILES "src/Main/*.cpp" "src/Main/*.h")
file(GLOB SRC_FILES "src/*.cpp" "src/*.h")
target_sources(EIMMain PRIVATE ${MAIN_SRC_FILES})
add_executable(EIMMain WIN32 ${MAIN_SRC_FILES})

juce_add_gui_app(EIM PRODUCT_NAME "Echo In Mirror")
target_sources(EIM PRIVATE ${SRC_FILES})
set_property(TARGET EIM PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set_property(TARGET EIMMain PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
# juce_add_gui_app(EIM PRODUCT_NAME "Echo In Mirror")

target_compile_definitions(EIM
    PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:EIM,JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:EIM,JUCE_VERSION>")

# If the target needs extra binary assets, they can be added here. The first argument is the name of
# a new static library target that will include all the binary resources. There is an optional
# `NAMESPACE` argument that can specify the namespace of the generated binary data class. Finally,
# the SOURCES argument should be followed by a list of source files that should be built into the
# static library. These source files can be of any kind (wav data, images, fonts, icons etc.).
# Conversion to binary-data will happen when the target is built.

# juce_add_binary_data(ConsoleAppData SOURCES ...)

# `target_link_libraries` links libraries and JUCE modules to other libraries or executables. Here,
# we're linking our executable target to the `juce::juce_core` module. Inter-module dependencies are
# resolved automatically. If you'd generated a binary data target above, you would need to link to
# it here too. This is a standard CMake command.

target_link_libraries(EIM
    PRIVATE
        juce::juce_gui_extra
        juce::juce_audio_utils
    PUBLIC
        cefdll_wrapper
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)

add_windows_manifest(EIM "Echo In Mirror.exe")
