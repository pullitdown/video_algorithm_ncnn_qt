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
#ifndef UNT_H
#define UNT_H
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




int detect_unet(const ncnn::Net& unet,cv::Mat& bgr,cv::Mat& background_img,float threshold,bool isbackground);
void mask_filter(cv::Mat& input, cv::Mat& mask, int n);
#endif