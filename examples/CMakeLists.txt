project(examples)


add_library(yolov5s_ SHARED src/yolov5_pnnx.cpp)
target_include_directories(yolov5s_ PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(yolov5s_ PRIVATE ncnn)





find_package(OpenCV REQUIRED)
include_directories(${PROJECT_SOURCE_DIR}/include 
    ${OpenCV_INCLUDE_DIRS}
)
add_executable(yolo src/yolov5_pnnx_1.cpp)
target_link_libraries(yolo PUBLIC ncnn ${OpenCV_LIBS})