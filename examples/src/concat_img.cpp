#include<opencv2/opencv.hpp>
#include<iostream>
#include <string>
#include<vector>
#include<stack>
using namespace cv;
using namespace std;
vector<Mat> imageVector;

void multipleImage(vector<Mat> imgVector, Mat& dst, int imgCols)
{
    const int MAX_PIXEL = 300;
    int imgNum = imgVector.size();
    //选择图片最大的一边 将最大的边按比例变为300像素
    Size imgOriSize = imgVector[0].size();
    int imgMaxPixel = max(imgOriSize.height, imgOriSize.width);
    //获取最大像素变为MAX_PIXEL的比例因子
    double prop = MAX_PIXEL / (double)imgMaxPixel;
    Size imgStdSize(imgOriSize.width * prop, imgOriSize.height * prop); //窗口显示的标准图像的Size

    Mat imgStd; //标准图片
    Point2i location(0, 0); //坐标点(从0,0开始)
    //构建窗口大小 通道与imageVector[0]的通道一样
    Mat imgWindow(imgStdSize.height * ((imgNum - 1) / imgCols + 1), imgStdSize.width * imgCols, imgVector[0].type());
    for (int i = 0; i < imgNum; i++)
    {
        location.x = (i % imgCols) * imgStdSize.width;
        location.y = (i / imgCols) * imgStdSize.height;
        resize(imgVector[i], imgStd, imgStdSize, 0,0, INTER_LINEAR); //设置为标准大小
        imgStd.copyTo(imgWindow(Rect(location, imgStdSize)));
    }
    dst = imgWindow;
}

int fl(float aa,int isx)
{
    int a = aa;
    if (a < 0)
    {
        return  -a;
    }
    if (isx == 1)
     {
        if (a < imageVector[0].size().width) {
            return  0;
        }
        else {
            return a- imageVector[0].size().width;
        }
      }
    else {
        if (a < imageVector[0].size().height)
            return  0;
        return a - imageVector[0].size().height;
    }
    
    
}
void generate_mask(Mat& image, Mat& mask)
{
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            if (image.at<Vec3b>(i, j)[0] || image.at<Vec3b>(i, j)[1] || image.at<Vec3b>(i, j)[2]) {
                mask.at<Vec3b>(i, j) = Vec3b(0.5,0.5,0.5);
             

            }
            else {
                mask.at<Vec3b>(i, j) = Vec3b(1, 1, 1);
            }
        }
    }
    
}

int main() {

	String path1 = "C:\\Users\\stepf\\Desktop\\4.jpg", path2 = "C:\\Users\\stepf\\Desktop\\5.jpg", path3 = "C:\\Users\\stepf\\Desktop\\6.jpg";
	Mat k1 = imread(path1), k2 = imread(path2), k3 = imread(path3);
    
    Mat merge;
    imageVector.push_back(k1);
    imageVector.push_back(k2);
    imageVector.push_back(k3);
   
    multipleImage(imageVector,merge,3);
    imshow("df",merge);
    imwrite("C:/Users/stepf/Desktop/merge.jpg",merge);
    waitKey(0);
    
    cout << imageVector[0].size() << endl;
    Ptr<ORB> orb = ORB::create();//创建指针orb,而orb是一个特征描述算法,可以返回特征点
    vector<KeyPoint> keyPoints_1;
    Mat descriptors_1;
    vector<KeyPoint> keyPoints_2;//设置当前关键点
    Mat descriptors_2;//当前描述矩阵
    orb->detectAndCompute(imageVector[0], Mat(), keyPoints_1, descriptors_1);
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming");
    vector<DMatch> matches;//dmatch
    vector<Point2f> allpoint;//存储所有的边缘点
    vector<Mat>allH;
    vector<int> num;
    vector<Point2f> allQT;
    float botton=0, right=0, top=10000, left = 10000;
    for (int i = 1; i < imageVector.size(); i++)
    {
        orb->detectAndCompute(imageVector[i], Mat(), keyPoints_2, descriptors_2);
        if (keyPoints_2.size() >= 10)
        {
            matcher->match(descriptors_1, descriptors_2, matches);//匹配描述矩阵
            double max_dist = 0; double min_dist = 100;//设置距离上下限
            for (int i = 0; i < descriptors_1.rows; i++)//行数
            {
                double dist = matches[i].distance;
                if (dist < min_dist) min_dist = dist;
                if (dist > max_dist) max_dist = dist;
            }//获得最大距离
            std::vector< DMatch > good_matches;//声明匹配的转载器

            vector<Point2f> train_p, query_p;

            for (int i = 0; i < descriptors_1.rows; i++)//遍历行数次
            {
                if (matches[i].distance < 0.5 * max_dist)//如果匹配小于最大距离的1/2
                {
                    good_matches.push_back(matches[i]);//记录这个匹配

                    int query_i = matches[i].queryIdx;
                    int train_i = matches[i].trainIdx;
                    KeyPoint query_kp = keyPoints_1[query_i];//
                    KeyPoint train_kp = keyPoints_2[train_i];
                    train_p.push_back(train_kp.pt);//记录原始图像位置
                    query_p.push_back(query_kp.pt);//记录当前图像位置
                }
            }
            num.push_back(train_p.size());
            allQT.insert(allQT.end(),train_p.begin(), train_p.end());
            allQT.insert(allQT.end(), query_p.begin(), query_p.end());

            if (train_p.size() >= 4 && train_p.size() >= (int)(0.1 * descriptors_1.rows))///当有十分之一的特征点得到时
            {

                Mat H = findHomography( train_p,query_p, RANSAC, 20);//找到十个最大的匹配坐标,然后计算两个平面的转换矩阵
                allH.push_back(H);
                //cout << H << endl;
                std::vector<Point2f> obj_corners(4);//初始化
                obj_corners[0] = cv::Point(0, 0);
                obj_corners[1] = cv::Point(imageVector[i].cols, 0);//特征图片的宽
                obj_corners[2] = cv::Point(imageVector[i].cols, imageVector[i].rows);//特征图片的高
                obj_corners[3] = cv::Point(0, imageVector[i].rows);//特征图片的高
                std::vector<Point2f> scene_corners(4);//初始化

                perspectiveTransform(obj_corners, scene_corners, H);//将目标图像投影到当前的图片坐标sence_corners是目标图片在现在一帧的坐标
                allpoint.insert(allpoint.end(), scene_corners.begin(),scene_corners.end());
                for (int k = 0; k< 4; k++)
                {
                    int ll = scene_corners[k].x, rr = scene_corners[k].y;
                    if (ll < top)
                        top = ll;
                    if (ll > botton)
                        botton = ll;
                    if (rr < left)
                        left = rr;
                    if (rr > right)
                        right = rr;
                    
                    cout<<scene_corners[k] << endl;
                }
            }
        }
        

    }//for
    Mat goal;
    copyMakeBorder(k1, goal, fl(left, 0), fl(right, 0), fl(top, 1), fl(botton, 1),  BORDER_CONSTANT, cv::Scalar(0, 0, 0));
    cout << left << " " << fl(top, 1) << " " << right << " " << fl(botton, 1) << " " << top << " " << fl(left, 0) << " " << botton << " " << fl(right, 0) << endl;
    allH.clear();
    int count = 0;
    int idx = 0;
    auto it = allQT.begin();
    while ( it != allQT.end())
    {

        if (idx < num.size())
        {
            count = num[idx];
            vector<Point2f> train_p, query_p;
            for (int k = 0; k < count; k++)
            {
                
                
                train_p.push_back(*it);
                it++;
            }
            for (int k = 0; k < count; k++)
            {
                it->x = it->x + fl(top, 1);
                it->y = it->y + fl(left, 0);
                query_p.push_back(*it);
                it++;
            }
            Mat H = findHomography(train_p, query_p, RANSAC, 20);//找到十个最大的匹配坐标,然后计算两个平面的转换矩阵
            allH.push_back(H);
            idx++;
        }
        
     }
     
    

    
    
    

    vector<Mat>allGoal;
    allGoal.push_back(goal.clone());
   // imshow("show",goal);
    imwrite("C:\\Users\\stepf\\Desktop\\goal.jpg", goal);

    cout <<left<< " " << fl(top, 1) << " " << right << " " << fl(botton, 1) << " " << top << " " << fl(left, 0) << " " << botton << " " << fl(right, 0) << endl;
    //waitKey(0);
    for (int i = 0; i < 2; i++)
    {
        Mat dst;
        warpPerspective(imageVector[i + 1], goal, allH[i], goal.size(), INTER_LINEAR, BORDER_CONSTANT);
       
        
        if(i==0)
        imwrite("C:\\Users\\stepf\\Desktop\\dst1.jpg", goal);
        else
        {
            imwrite("C:\\Users\\stepf\\Desktop\\dst2.jpg", goal);
        }
        cout << goal.size() << endl;
        allGoal.push_back(goal.clone());
        //imshow("11",dst);
        //waitKey(0);
    }
    Mat on;
    Mat mask;
    
    bitwise_xor(allGoal[1], allGoal[0], mask);
    
    for (int i = 1; i < 3; i++)
    {
        generate_mask(allGoal[i], mask);
        multiply(mask, allGoal[0], allGoal[0]);

        add(allGoal[i], allGoal[0], allGoal[0]);

        //multiply(allGoal[0], mask, allGoal[0]);
        //bitwise_xor(allGoal[0], allGoal[i], allGoal[0]);
    }
    imwrite("C:\\Users\\stepf\\Desktop\\fin.jpg", allGoal[0]);
	return 0;
}
