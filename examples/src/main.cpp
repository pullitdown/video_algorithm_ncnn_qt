// Tencent is pleased to support the open source community by making ncnn available.
//
// Copyright (C) 2022 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.


#include "unet.h"
#include "yolov5_pnnx.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <vector>

#include <time.h>



int yolov5s_test()
{
    std::string path="/home/stepf/world/video_algorithm_ncnn_qt/param/";
    ncnn::Net yolov5;

    //yolov5.opt.use_vulkan_compute = true;
    yolov5.opt.use_bf16_storage = true;

    // original pretrained model from https://github.com/ultralytics/yolov5
    // the ncnn model https://github.com/nihui/ncnn-assets/tree/master/models
    
    if (yolov5.load_param(&(path+"yolov5s.ncnn.param")[0]))
        exit(-1);
    if (yolov5.load_model(&(path+"yolov5s.ncnn.bin")[0]))
        exit(-1);

    const char* imagepath = "/home/stepf/world/img/1.jpg";

    cv::Mat m = cv::imread(imagepath, 1);
    if (m.empty())
    {
        fprintf(stderr, "cv::imread %s failed\n", imagepath);
        return -1;
    }

    std::vector<Object_yolov5s> objects;
    
    
    detect_yolov5(yolov5,m, objects);
    
    draw_objects(m, objects);

    cv::imshow("dd",m);
    cv::waitKey(0);
    return 0;
}

int show_unet()
{
    std::string path="/home/stepf/world/video_algorithm_ncnn_qt/param/";
    ncnn::Net unet;

    // original pretrained model from https://github.com/ultralytics/yolov5
    // the ncnn model https://github.com/nihui/ncnn-assets/tree/master/models
    
    if (unet.load_param(&(path+"unet.ncnn.param")[0]))
        exit(-1);
    if (unet.load_model(&(path+"unet.ncnn.bin")[0]))
        exit(-1);
    const char* imagepath1 = "/home/stepf/world/img/3.jpg";
    const char* imagepath2 = "/home/stepf/world/img/R.png";
    cv::Mat bgr = cv::imread(imagepath1, 1);
    cv::Mat bkg= cv::imread(imagepath2, 1);
    detect_unet(unet,bgr,bkg,0.3,1);
    return 0;
}


int main(int argc, char** argv)
{
    if(argc<2)
    {
        std::cout<<"use commod like :\n test [yolo|unet]"<<std::endl;
        exit(0);
    }
    std::vector<std::string> test_name{"yolo","unet","yolact"};
    int idx;
    for(int i=0;i<test_name.size();i++)
    {
        if(test_name[i]==argv[1])
        {
            idx=i;
            break;
        }
    }
    switch (idx)
    {
    case 0:
        yolov5s_test();
        break;
    case 1:
        show_unet();
        break;
    default:
        break;
    }
    return 0;
}
