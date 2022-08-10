#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ncnn" for configuration "Debug"
set_property(TARGET ncnn APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(ncnn PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libncnnd.so.1.0.20220810"
  IMPORTED_SONAME_DEBUG "libncnnd.so.1"
  )

list(APPEND _IMPORT_CHECK_TARGETS ncnn )
list(APPEND _IMPORT_CHECK_FILES_FOR_ncnn "${_IMPORT_PREFIX}/lib/libncnnd.so.1.0.20220810" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
