
add_library(host_includes INTERFACE)
target_include_directories(host_includes INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
if(NOT MSVC)
    target_compile_options(host_includes INTERFACE -Wno-pragma-pack)
endif()
