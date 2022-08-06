project(examples)



find_package(OpenCV REQUIRED)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include 
    ${OpenCV_INCLUDE_DIRS}
)

add_library(yolov5s_ SHARED src/yolov5_pnnx.cpp)
target_include_directories(yolov5s_ PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(yolov5s_ PRIVATE ncnn ${OpenCV_LIBS})



add_library(yolact_  SHARED  src/yolact.cpp)
target_include_directories(yolact_ PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(yolact_ PRIVATE ncnn ${OpenCV_LIBS})

add_library(unet_  SHARED  src/unet.cpp)
target_include_directories(unet_ PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(unet_ PRIVATE ncnn ${OpenCV_LIBS})


aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src DIR_SRCS)
add_executable(test src/main.cpp src/unet.cpp src/yolov5_pnnx.cpp)

target_include_directories(test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include )
target_link_libraries(test PRIVATE ncnn ${OpenCV_LIBS})

