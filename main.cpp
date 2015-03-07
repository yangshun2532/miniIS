#include "cv.h"
#include "highgui.h"
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/nonfree/features2d.hpp>
#include "opencv2/core/core.hpp"

#define OBJECT_PATH "G:\\BaiduYunDownload\\contest_data\\contest_data\\clothes\\clothes_source\\clothes_250001.jpg"
#define CLOTH_DIR "G:\\BaiduYunDownload\\contest_data\\contest_data\\clothes\\clothes_image\\" //ͼ�������ļ���
#define CLOTH_AMOUNT 150000    //���ļ���
#define CLOTH_FIRST_NUMBER 100001  //��һ���ļ����
#define THRESHOLD 400

unsigned int goodMatch[150000]={0};
using namespace cv;

int mySurf(Mat *);
int main()
{
    int i;
    char clothPath[120]=CLOTH_DIR;
    unsigned int best=0;
    int ans=0;

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
        int currentNumber=CLOTH_FIRST_NUMBER+i-1;   //�õ���ǰ�ļ����
        sprintf(clothPath+strlen(CLOTH_DIR),"clothes_%d.jpg",currentNumber);  //�õ���ǰ�ļ�Ŀ¼
        Mat img=imread(clothPath,CV_LOAD_IMAGE_GRAYSCALE);//IplImage* img = cvLoadImage(clothPath, 1);
        if(img.data==NULL)
            return -1; //����Ϳ�������
        std::vector<KeyPoint> keypoints;
        detector.detect(img,keypoints);

        //to compare
        Mat descriptors_2;
        extractor.compute(img,keypoints,descriptors_2);

        if(descriptors_2.empty()) //����һ�������㶼û���ǲ��ܽ���flanƥ���
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
        goodMatch[i]=good_matches.size();
        if(good_matches.size()>best)
        {
            best=good_matches.size();
            ans=i;
        }
        //printf("%d\n������ƥ�������%d\n���ƥ���ǵ� %d ��ͼƬ��%d��\n",i,good_matches.size(),ans,best);

        //draw the good matches
        /*Mat img_matches;
        drawMatches(objectImg,objectKeypoints,img,keypoints,good_matches,img_matches,
                    Scalar::all(-1),Scalar::all(-1),vector<char>(),DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
        imshow("Good Matches",img_matches);
        waitKey(0);*/
    }
    //��goodmatch��Ϣд���ļ�
    FILE* fp=fopen("G:\\goodmatch.txt","a+");
    if(fp==NULL)
        return -1;
    for(i=1;i<=CLOTH_AMOUNT;i++)
    {
        fprintf(fp,"%u\n",goodMatch[i]);
    }
    fclose(fp);
    //��ans��Ϣд���ļ�
    FILE* fp_1=fopen("G:\\ans.txt","a+");
    if(fp==NULL)
        return -1;
    printf("The best match is NO:%d\n",ans);
    fclose(fp_1);

    return 0;
}


int i(Mat* img)
{
      //-- Step 1: Detect the keypoints using SURF Detector
      int minHessian = THRESHOLD;
      SurfFeatureDetector detector( minHessian );
      std::vector<KeyPoint> keypoints;
      detector.detect(*img, keypoints);

      //-- Draw keypoints
      Mat img_keypoints;
      drawKeypoints(*img, keypoints, img_keypoints, Scalar::all(-1), DrawMatchesFlags::DEFAULT );

      //-- Show detected (drawn) keypoints
      imshow("Keypoints", img_keypoints);

      waitKey(0);
      return 0;
}
