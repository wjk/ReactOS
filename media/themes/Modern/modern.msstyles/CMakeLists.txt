file(GLOB_RECURSE modern_rc_deps ${CMAKE_CURRENT_BINARY_DIR}/bitmaps/* ${CMAKE_CURRENT_BINARY_DIR}/lang/* ${CMAKE_CURRENT_BINARY_DIR}/textfiles/*)
add_rc_deps(modern.rc ${modern_rc_deps})

list(APPEND TEXTFILES
    textfiles/Light/ExtraLargeLight.INI
    textfiles/Light/LargeFontsLight.INI
    textfiles/Light/RegularLight.INI
    textfiles/Dark/ExtraLargeDark.INI
    textfiles/Dark/LargeFontsDark.INI
    textfiles/Dark/RegularDark.INI)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/textfiles)
foreach(_file ${TEXTFILES})
    get_filename_component(_file_name ${_file} NAME_WE)
    get_filename_component(_subdir ${_file} DIRECTORY)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${_subdir})
    set(_converted_file ${CMAKE_CURRENT_BINARY_DIR}/${_subdir}/${_file_name}_utf16.INI)
    utf16le_convert(${CMAKE_CURRENT_SOURCE_DIR}/${_file} ${_converted_file})
    list(APPEND _converted_files ${_converted_file})
endforeach()

set_source_files_properties(modern.rc PROPERTIES OBJECT_DEPENDS "${_converted_files}")
add_library(modern.msstyles MODULE modern.rc)
set_module_type(modern.msstyles module)
set_target_properties(modern.msstyles PROPERTIES SUFFIX "")
add_cd_file(TARGET modern.msstyles DESTINATION reactos/Resources/Themes/Modern FOR all)
