cmake_minimum_required(VERSION 3.1.0)

# 设置项目名称
set(PRO_NAME video_algorithm_ncnn_qt)

project(${PRO_NAME})

# 在相应的构建目录中查找头文件
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# 设置CMake在需要时自动运行moc
set(CMAKE_AUTOMOC ON)

# 从Qt设计师文件列表中创建代码
set(CMAKE_AUTOUIC ON)

# 设置Qt的环境变量
#list(APPEND CMAKE_PREFIX_PATH /home/azmddy/Qt/5.12.0/gcc_64)

# 搜索当前目录下的源文件
aux_source_directory(./src DIR_SRCS)

# 寻找Qt5的库
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# 设置可执行文件
add_executable(${PRO_NAME} ${DIR_SRCS})

# 链接Qt5的库
target_link_libraries(${PRO_NAME} Qt5::Widgets)

add_subdirectory(ncnn)