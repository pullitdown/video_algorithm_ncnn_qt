// This file is part of the Orbbec Astra SDK [https://orbbec3d.com]
// Copyright (c) 2015-2017 Orbbec 3D
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Be excellent to each other.

#ifndef ASTRA_CAP
#define ASTRA_CAP
#include <astra/astra.hpp>
#include <cstdio>
#include <iostream>
#include "key_handler.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace astra{
    class SampleFrameListener : public astra::FrameListener
{
private:
    using buffer_ptr = std::unique_ptr<astra::RgbPixel []>;
    buffer_ptr buffer_;
    unsigned int lastWidth_;
    unsigned int lastHeight_;
    uchar data[3*640*480];

public:
    friend class astra_capture;
    virtual void on_frame_ready(astra::StreamReader& reader,
                                astra::Frame& frame) override
    {
        const astra::ColorFrame colorFrame = frame.get<astra::ColorFrame>();

        if (colorFrame.is_valid())
        {
            print_color(colorFrame);
        }
    }

    void print_color(const astra::ColorFrame& colorFrame)
    {
        if (colorFrame.is_valid())
        {
            int width = colorFrame.width();
            int height = colorFrame.height();
            int frameIndex = colorFrame.frame_index();

            if (width != lastWidth_ || height != lastHeight_){
                buffer_ = buffer_ptr(new astra::RgbPixel[colorFrame.length()]);
                lastWidth_ = width;
                lastHeight_ = height;
            }
            colorFrame.copy_to(buffer_.get());
            draw_opencv();
            std::cout<<"dd"<<std::endl;
        }
    }

     uchar* draw_opencv()
    {
        size_t remian = lastHeight_ * lastWidth_;
        #define SATURATE_CAST_UCHAR(X) (unsigned char)::std::min(::std::max((int)(X), 0), 255);
        uchar * ptr=this->data;
        #pragma omp parallel for num_threads(6)
        for(size_t y=0;y<remian;y++)
        {
            ptr[0]=SATURATE_CAST_UCHAR(buffer_[y].r);
            ptr[1]=SATURATE_CAST_UCHAR(buffer_[y].g);
            ptr[2]=SATURATE_CAST_UCHAR(buffer_[y].b);
            ptr+=3;   
        }
        #undef SATURATE_CAST_UCHAR
        return this->data;
    }
};


class astra_capture{
private:
    astra::StreamSet streamSet;
    astra::StreamReader reader;
    SampleFrameListener listener;// listen a frame
    uchar * dd;
public:
    void my_astra_init();
    uchar* my_astra_update();
    void my_astra_terminate();
    
    
};


}
#endif