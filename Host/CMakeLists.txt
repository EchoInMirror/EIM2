file(GLOB SRC_FILES "./*.cpp" "./*.h")
add_executable(EIMRender ${SRC_FILES})

target_link_libraries(EIMRender cefdll_wrapper)
set_property(TARGET EIMRender PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
