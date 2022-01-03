add_definitions(-DJUCE_PLUGINHOST_VST3)

add_subdirectory(JUCE)

file(GLOB SRC_FILES "./*.cpp" "./*.h")
juce_add_gui_app(EIMHost PRODUCT_NAME)
target_sources(EIMHost PRIVATE ${SRC_FILES})

set_property(TARGET EIMHost PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

target_compile_definitions(EIMHost
    PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:EIMHost,JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:EIMHost,JUCE_VERSION>")

target_link_libraries(EIMHost
    PRIVATE
        juce::juce_gui_extra
        juce::juce_audio_utils
    PUBLIC
        cefdll_wrapper
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)

add_custom_command(TARGET EIMHost POST_BUILD
    COMMENT "EIMHost: Copying files"
    COMMAND ${CMAKE_COMMAND} -E
        make_directory ${CEF_CMAKE_OUTPUT_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/Host/EIMHost_artefacts/$<CONFIG>/EIMHost.exe
        ${CMAKE_BINARY_DIR}/Host/EIMHost_artefacts/$<CONFIG>/EIMHost.pdb
        ${CEF_CMAKE_OUTPUT_DIR}/$<CONFIG>
)