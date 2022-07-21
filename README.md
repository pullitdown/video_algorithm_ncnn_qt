# video_algorithm_ncnn_qt
Multiple video algorithms accelerated with ncnn, interface implemented with qt

The functions provided are as follows
1.yolov5 dected face 
2.the mask of background
3.Video stabilization
4.Beauty Camera





commod list
git clone git@github.com:pullitdown/video_algorithm_ncnn_qt.git --recurse-submodules
cd video_algorithm_ncnn_qt 


cd ncnn
mkdir build && cd build
cmake ..
make -j$(nproc)

cd ..
uic ./ui/main_widget.ui ./src/main_widget.h

mkdir build && cd build
cmake ..
make -j$(nproc)