// Tencent is pleased to support the open source community by making ncnn available.
//
// Copyright (C) 2020 THL A29 Limited, a Tencent company. All rights reserved.
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

#ifndef YOLACT_H
#define YOLACT_H
#include <net.h>

#if defined(USE_NCNN_SIMPLEOCV)
#include <simpleocv.h>
#else
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#endif
#include <iostream>
#include <vector>

#include <time.h>
struct Object_yolact
{
    cv::Rect_<float> rect;
    int label;
    float prob;
    std::vector<float> maskdata;
    cv::Mat mask;
};

float intersection_area(const Object_yolact& a, const Object_yolact& b);
void qsort_descent_inplace(std::vector<Object_yolact>& objects);

void nms_sorted_bboxes(const std::vector<Object_yolact>& faceobjects, std::vector<int>& picked, float nms_threshold, bool agnostic = false);

void qsort_descent_inplace(std::vector<Object_yolact>& objects, int left, int right);

void draw_objects(cv::Mat& image, const std::vector<Object_yolact>& objects);
int detect_yolact(const ncnn::Net& yolact,cv::Mat& bgr, std::vector<Object_yolact>& objects);


// int main(int argc, char** argv)
// {
    

//     const char* imagepath = "/home/stepf/world/img/1.jpg";

//     cv::Mat m = cv::imread(imagepath, 1);
//     if (m.empty())
//     {
//         fprintf(stderr, "cv::imread %s failed\n", imagepath);
//         return -1;
//     }
//     ncnn::Net yolact;

//     yolact.opt.use_vulkan_compute = true;
//     if (yolact.load_param("/home/stepf/world/video_algorithm_ncnn_qt/param/yolact.param"))
//         exit(-1);
//     if (yolact.load_model("/home/stepf/world/video_algorithm_ncnn_qt/param/yolact.bin"))
//         exit(-1);
//     std::vector<Object_yolact> objects;
//     detect_yolact(yolact,m, objects);

//     draw_objects(m, objects);

//     return 0;
// }
#endif