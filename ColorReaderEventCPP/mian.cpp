#include <astra/astra.hpp>
#include <cstdio>
#include <iostream>
#include "key_handler.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include"astra_cap.h"

int main()
{
    astra::astra_capture ll;
    ll.my_astra_init();
    uchar * date=ll.my_astra_update();
    for(int i=0;i<100;i++)
    std::cout<<(int)date[i]<<std::endl;
    
    
    ll.my_astra_terminate();
    return 0;

}