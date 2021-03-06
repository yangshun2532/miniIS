#include "cv.h"
#include "highgui.h"
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/nonfree/features2d.hpp>
#include "opencv2/core/core.hpp"
#include "algorithm"

#define OBJECT_PATH "G:\\BaiduYunDownload\\contest_data\\contest_data\\clothes\\clothes_source\\clothes_250001.jpg"
#define CLOTH_DIR "G:\\BaiduYunDownload\\contest_data\\contest_data\\clothes\\clothes_image\\" //图像集所在文件夹
#define CLOTH_AMOUNT 150000    //总文件数
#define CLOTH_FIRST_NUMBER 100001  //第一个文件编号
#define THRESHOLD 600

int i;
unsigned int best=0;

using namespace cv;
using namespace std;


struct Ans
{
    int score;
    int Num;
}ans;

bool tmp(struct Ans a,struct Ans b)
{
    return a.score>b.score;
}

struct Ans goodMatch[150001];
int mySurf(Mat *);
int main()
{
    char clothPath[120]=CLOTH_DIR;
    memset(goodMatch,0,sizeof(struct Ans)*CLOTH_AMOUNT);
    Mat objectImg=imread(OBJECT_PATH,CV_LOAD_IMAGE_GRAYSCALE);
    int minHessian = THRESHOLD;
    std::vector<KeyPoint> objectKeypoints;
    SurfFeatureDetector detector(minHessian);
    detector.detect(objectImg,objectKeypoints);
     SurfDescriptorExtractor extractor;
     Mat descriptors_1;
     extractor.compute(objectImg,objectKeypoints,descriptors_1);

    for(i=1;i<=CLOTH_AMOUNT;i++)
    {
        int currentNumber=CLOTH_FIRST_NUMBER+i-1;   //得到当前文件编号
        sprintf(clothPath+strlen(CLOTH_DIR),"clothes_%d.jpg",currentNumber);  //得到当前文件目录
        Mat img=imread(clothPath,CV_LOAD_IMAGE_GRAYSCALE);//IplImage* img = cvLoadImage(clothPath, 1);
        if(img.data==NULL)
            return -1; //读完就可以跳出
        std::vector<KeyPoint> keypoints;
        detector.detect(img,keypoints);

        //to compare
        Mat descriptors_2;
        extractor.compute(img,keypoints,descriptors_2);

        if(descriptors_2.empty()) //若果一个特征点都没有是不能进行flan匹配的
            continue;

        FlannBasedMatcher matcher;
        std::vector<DMatch>matches;
        matcher.match(descriptors_1,descriptors_2,matches);

        double max_dist=0;
        double min_dist=100;

        int j;
        for(j=0;j<descriptors_1.rows;j++)
        {
            double dist=matches[j].distance;
            if(dist<min_dist)min_dist=dist;
            if(dist>max_dist)max_dist=dist;
        }

        std::vector<DMatch>good_matches;
        for(j=0;j<descriptors_1.rows;j++)
        {
            if(matches[j].distance<2*min_dist)
            {
                good_matches.push_back(matches[j]);
            }
        }
        goodMatch[i].score=good_matches.size();
        goodMatch[i].Num=i;
        if(good_matches.size()>best)
        {
            best=good_matches.size();
        }
        //printf("%d\n特征点匹配个数：%d\n最佳匹配是第 %d 张图片（%d）\n",i,good_matches.size(),ans,best);

        //draw the good matches
        /*Mat img_matches;
        drawMatches(objectImg,objectKeypoints,img,keypoints,good_matches,img_matches,
                    Scalar::all(-1),Scalar::all(-1),vector<char>(),DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
        imshow("Good Matches",img_matches);
        waitKey(0);*/
        printf("%d\n",i);
    }

    sort(goodMatch+1,goodMatch+150000,tmp);
    //将goodmatch信息写入文件
    FILE* fp=fopen("G:\\goodmatch.txt","a+");
    if(fp==NULL)
        return -1;
    for(i=1;i<=CLOTH_AMOUNT;i++)
    {
        fprintf(fp,"%d\t%d\n",goodMatch[i].Num,goodMatch[i].score);
    }
    fclose(fp);
    return 0;
}



