# Install script for directory: /home/stepf/world/video_algorithm_ncnn_qt/ncnn/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libncnnd.so.1.0.20220810"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libncnnd.so.1"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/stepf/world/video_algorithm_ncnn_qt/build/ncnn/src/libncnnd.so.1.0.20220810"
    "/home/stepf/world/video_algorithm_ncnn_qt/build/ncnn/src/libncnnd.so.1"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libncnnd.so.1.0.20220810"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libncnnd.so.1"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libncnnd.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libncnnd.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libncnnd.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/stepf/world/video_algorithm_ncnn_qt/build/ncnn/src/libncnnd.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libncnnd.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libncnnd.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libncnnd.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ncnn" TYPE FILE FILES
    "/home/stepf/world/video_algorithm_ncnn_qt/ncnn/src/allocator.h"
    "/home/stepf/world/video_algorithm_ncnn_qt/ncnn/src/benchmark.h"
    "/home/stepf/world/video_algorithm_ncnn_qt/ncnn/src/blob.h"
    "/home/stepf/world/video_algorithm_ncnn_qt/ncnn/src/c_api.h"
    "/home/stepf/world/video_algorithm_ncnn_qt/ncnn/src/command.h"
    "/home/stepf/world/video_algorithm_ncnn_qt/ncnn/src/cpu.h"
    "/home/stepf/world/video_algorithm_ncnn_qt/ncnn/src/datareader.h"
    "/home/stepf/world/video_algorithm_ncnn_qt/ncnn/src/gpu.h"
    "/home/stepf/world/video_algorithm_ncnn_qt/ncnn/src/layer.h"
    "/home/stepf/world/video_algorithm_ncnn_qt/ncnn/src/layer_shader_type.h"
    "/home/stepf/world/video_algorithm_ncnn_qt/ncnn/src/layer_type.h"
    "/home/stepf/world/video_algorithm_ncnn_qt/ncnn/src/mat.h"
    "/home/stepf/world/video_algorithm_ncnn_qt/ncnn/src/modelbin.h"
    "/home/stepf/world/video_algorithm_ncnn_qt/ncnn/src/net.h"
    "/home/stepf/world/video_algorithm_ncnn_qt/ncnn/src/option.h"
    "/home/stepf/world/video_algorithm_ncnn_qt/ncnn/src/paramdict.h"
    "/home/stepf/world/video_algorithm_ncnn_qt/ncnn/src/pipeline.h"
    "/home/stepf/world/video_algorithm_ncnn_qt/ncnn/src/pipelinecache.h"
    "/home/stepf/world/video_algorithm_ncnn_qt/ncnn/src/simpleocv.h"
    "/home/stepf/world/video_algorithm_ncnn_qt/ncnn/src/simpleomp.h"
    "/home/stepf/world/video_algorithm_ncnn_qt/ncnn/src/simplestl.h"
    "/home/stepf/world/video_algorithm_ncnn_qt/ncnn/src/vulkan_header_fix.h"
    "/home/stepf/world/video_algorithm_ncnn_qt/build/ncnn/src/ncnn_export.h"
    "/home/stepf/world/video_algorithm_ncnn_qt/build/ncnn/src/layer_shader_type_enum.h"
    "/home/stepf/world/video_algorithm_ncnn_qt/build/ncnn/src/layer_type_enum.h"
    "/home/stepf/world/video_algorithm_ncnn_qt/build/ncnn/src/platform.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/ncnn/ncnn.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/ncnn/ncnn.cmake"
         "/home/stepf/world/video_algorithm_ncnn_qt/build/ncnn/src/CMakeFiles/Export/lib/cmake/ncnn/ncnn.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/ncnn/ncnn-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/ncnn/ncnn.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/ncnn" TYPE FILE FILES "/home/stepf/world/video_algorithm_ncnn_qt/build/ncnn/src/CMakeFiles/Export/lib/cmake/ncnn/ncnn.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/ncnn" TYPE FILE FILES "/home/stepf/world/video_algorithm_ncnn_qt/build/ncnn/src/CMakeFiles/Export/lib/cmake/ncnn/ncnn-debug.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/ncnn" TYPE FILE FILES "/home/stepf/world/video_algorithm_ncnn_qt/build/ncnn/src/ncnnConfig.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/stepf/world/video_algorithm_ncnn_qt/build/ncnn/src/ncnn.pc")
endif()

