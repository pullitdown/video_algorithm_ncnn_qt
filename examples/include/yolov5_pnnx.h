#ifndef YOLOV_PNNX_H
#define YOLOV_PNNX_H
#include <layer.h>
#include <net.h>

#if defined(USE_NCNN_SIMPLEOCV)
#include "simpleocv.h"
#else
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#endif
#include <float.h>
#include <stdio.h>
#include <vector>
#include <iostream>

struct Object_yolov5s
{
    cv::Rect_<float> rect;
    int label;
    float prob;
};

float intersection_area(const Object_yolov5s& a, const Object_yolov5s& b);
void qsort_descent_inplace(std::vector<Object_yolov5s>& faceobjects, int left, int right);
void qsort_descent_inplace(std::vector<Object_yolov5s>& faceobjects);
void nms_sorted_bboxes(const std::vector<Object_yolov5s>& faceobjects, std::vector<int>& picked, float nms_threshold, bool agnostic );
float sigmoid(float x);
void generate_proposals(const ncnn::Mat& anchors, int stride, const ncnn::Mat& in_pad, const ncnn::Mat& feat_blob, float prob_threshold, std::vector<Object_yolov5s>& objects);
void draw_objects(cv::Mat& image, const std::vector<Object_yolov5s>& objects);

int detect_yolov5(const ncnn::Net& yolov5, const cv::Mat bgr, std::vector<Object_yolov5s>& objects);

#endif