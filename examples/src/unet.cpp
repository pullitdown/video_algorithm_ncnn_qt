#include"unet.h"




void mask_emplace(cv::Mat& input1,cv::Mat& mask,cv::Mat & background)
{
    if (mask.channels() != 1)
	{
        std::cout<<"mask_filter mask mat mush be single channel"<<std::endl;
		return ;
	}
    for (int i = 0; i < mask.rows; ++i)
	{
		uchar *in = mask.ptr<uchar>(i);
		
		for (int j = 0; j < mask.cols; ++j)
		{
            if(in[j]==1)
            {
                
                cv::Vec3b& out = input1.at<cv::Vec3b>(i, j);
                cv::Vec3b& bg  = background.at<cv::Vec3b>(i, j);
                out[0]=bg[0],out[1]=bg[1],out[2]=bg[2];
            }
		}
	}
}

void mask_filter(cv::Mat& input1,cv::Mat& mask,int middle_blur_kernel_size)
{
	cv::Mat input=input1.clone();
	if (mask.channels() != 1)
	{
        std::cout<<"mask_filter mask mat mush be single channel"<<std::endl;
		return ;
	}
    if(middle_blur_kernel_size%2==0)
    {
        std::cout<<"middle_blur_kernel_size mush be Odd number"<<std::endl;
		return ;
    }
	
	// 蒙版处理
    size_t half_middle_blur_kernel_size=middle_blur_kernel_size/2;
	
	for (int i = half_middle_blur_kernel_size; i < mask.rows-half_middle_blur_kernel_size; ++i)
	{
		uchar *in = mask.ptr<uchar>(i);
		
		for (int j = half_middle_blur_kernel_size; j < mask.cols-half_middle_blur_kernel_size; ++j)
		{
            if(in[j]==1)
            {
                
                cv::Vec3b& out = input1.at<cv::Vec3b>(i, j);
                out[0]=0,out[1]=0,out[2]=0;
                for(size_t y=i-half_middle_blur_kernel_size;y<i+half_middle_blur_kernel_size;y++)
                {
                    for(size_t x=j-half_middle_blur_kernel_size;x<j+half_middle_blur_kernel_size;x++)
                    {
                        
                        out[0]+=static_cast<uchar>((input.at<cv::Vec3b>(y, x)[0])/9);
                        out[1]+=static_cast<uchar>((input.at<cv::Vec3b>(y, x)[1])/9);
                        out[2]+=static_cast<uchar>((input.at<cv::Vec3b>(y, x)[2])/9);
                    }
                    
                }
            }
			
		}
	}
	
}

int detect_unet(const ncnn::Net& unet,cv::Mat& bgr,cv::Mat& background_img,float threshold,bool isbackground){
    const int newW=480, newH=320;

    int img_w = bgr.cols;
    int img_h = bgr.rows;

    ncnn::Mat in = ncnn::Mat::from_pixels_resize(bgr.data, ncnn::Mat::PIXEL_BGR2RGB, img_w, img_h, newW, newH);

    const float mean_vals[3] = {123.68f, 116.78f, 103.94f};
    const float norm_vals[3] = {1.0 / 58.40f, 1.0 / 57.12f, 1.0 / 57.38f};
    in.substract_mean_normalize(mean_vals, norm_vals);
    ncnn::Extractor ex = unet.create_extractor();
    ex.input("in0", in);
    clock_t start,end;
    start = clock();
    ncnn::Mat bottom_top_blob;
    ex.extract("out0", bottom_top_blob);
    end = clock();   //结束时间
    cv::Mat a(in.h, in.w, CV_8UC1);
    int w = bottom_top_blob.w;
    int h = bottom_top_blob.h;
    int channels = bottom_top_blob.c;
    int size = w * h;
    int k=static_cast<int>(-log((1/threshold)-1));
    #pragma omp parallel for num_threads(6)
    for (int q = 0; q < channels; q++)
    {
        float* ptr = bottom_top_blob.channel(q);

        for (int i = 0; i < size; i++)
        {
            float v = ptr[i];
            v = std::min(v, 88.3762626647949f);
            v = std::max(v, -88.3762626647949f);
            ptr[i] = v>k?!isbackground:isbackground;
        }
    }
    cv::resize(bgr,bgr,cv::Size(480,320), (0, 0), (0, 0), 3);
    bottom_top_blob.to_pixels(a.data, ncnn::Mat::PIXEL_GRAY);
    // cv::Mat background,person;
    // // background=bgr.mul(a);
    // std::cout<<a.size()<<" "<< bgr.size()<<a.type()<<a.type()<<std::endl;
    // bitwise_and(a, bgr, background);
    // bitwise_xor(a, bgr, person);
    // cv::imshow("background", background);
    // cv::waitKey(0);
    // //cv::imshow("person", person);
    // //cv::waitKey(0);
    mask_emplace(bgr,a,background_img);
    std::cout<<" time = "<<double(end-start)/CLOCKS_PER_SEC<<"s"<<std::endl;
    // cv::imshow("image", bgr);
    
    // cv::waitKey(0);
    return 0;
}

