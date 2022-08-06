cmake_minimum_required(VERSION 3.1.0)

# 设置项目名称
set(PRO_NAME video_algorithm_ncnn_qt)

set(DCMAKE_BUILD_TYPE Release)

project(${PRO_NAME})
# list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
# 在相应的构建目录中查找头文件
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# 设置CMake在需要时自动运行moc
set(CMAKE_AUTOMOC ON)

# 从Qt设计师文件列表中创建代码
set(CMAKE_AUTOUIC ON)

# 设置Qt的环境变量
# list(APPEND CMAKE_PREFIX_PATH "~/Qt5.9.0/5.9/gcc_64/lib/cmake")
# set(Qt5Multimedia_DIR  "~/Qt5.9.0/5.9/gcc_64/lib/cmake/Qt5Multimedia")
# set(Qt5MultimediaWidgets_DIR  "~/Qt5.9.0/5.9/gcc_64/lib/cmake/Qt5MultimediaWidgets")

# 搜索当前目录下的源文件
aux_source_directory(./src DIR_SRCS)
aux_source_directory(./ui DIR_UIS)
# 寻找Qt5的库   

add_subdirectory(ncnn)
add_subdirectory(examples)
find_package(Qt5 COMPONENTS Widgets Core   REQUIRED)
find_package(OpenCV  REQUIRED)


# include(ui2header)
# ui2header(DIR_SRCS ${DIR_UIS})
# message(${DIR_SRCS})


include_directories(
        ${OpenCV_INCLUDE_DIRS}
        ${examples_INCLUDE_DIRS}
        )


# 设置可执行文件
add_executable(${PRO_NAME} ${DIR_SRCS} ${DIR_UIS})

# 链接Qt5的库
target_link_libraries(${PRO_NAME} PUBLIC ${OpenCV_LIBS} Qt5::Widgets yolov5s_ ncnn  yolact_ unet_)
#Qt5::Core Qt5::Multimedia Qt5::MultimediaWidgets
#Multimedia MultimediaWidgets