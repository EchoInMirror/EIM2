file(GLOB SRC_FILES "./*.cpp" "./*.h")
add_executable(EIMMain ${SRC_FILES})

target_link_libraries(EIMMain cefdll_wrapper)
set_property(TARGET EIMMain PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
