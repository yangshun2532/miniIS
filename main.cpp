#include "cv.h"
#include "highgui.h"
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/nonfree/features2d.hpp>

#define CLOTH_DIR "G:\\BaiduYunDownload\\contest_data\\contest_data\\clothes\\clothes_source\\" //ͼ�������ļ���
#define CLOTH_AMOUNT 100000    //���ļ���
#define CLOTH_FIRST_NUMBER 250001  //��һ���ļ����
#define THRESHOLD 400

using namespace cv;

int mySurf(Mat *);
int main()
{
    int i;
    char clothPath[120]=CLOTH_DIR;
    for(i=0;i<=CLOTH_AMOUNT;i++)
    {
        int currentNumber=CLOTH_FIRST_NUMBER+i;   //�õ���ǰ�ļ����
        sprintf(clothPath+strlen(CLOTH_DIR),"clothes_%d.jpg",currentNumber);  //�õ���ǰ�ļ�Ŀ¼
        Mat img=imread(clothPath,CV_LOAD_IMAGE_GRAYSCALE);//IplImage* img = cvLoadImage(clothPath, 1);
        if(img.data==NULL)
            return -1; //����Ϳ�������
        mySurf(&img);
        cvWaitKey(0);
    }
    return 0;
}


int mySurf(Mat* img)
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
