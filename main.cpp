#include "cv.h"
#include "highgui.h"
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/nonfree/features2d.hpp>

#define CLOTH_DIR "G:\\BaiduYunDownload\\contest_data\\contest_data\\clothes\\clothes_source\\" //图像集所在文件夹
#define CLOTH_AMOUNT 100000    //总文件数
#define CLOTH_FIRST_NUMBER 250001  //第一个文件编号
#define THRESHOLD 400

using namespace cv;

int mySurf(Mat *);
int main()
{
    int i;
    char clothPath[120]=CLOTH_DIR;
    for(i=0;i<=CLOTH_AMOUNT;i++)
    {
        int currentNumber=CLOTH_FIRST_NUMBER+i;   //得到当前文件编号
        sprintf(clothPath+strlen(CLOTH_DIR),"clothes_%d.jpg",currentNumber);  //得到当前文件目录
        Mat img=imread(clothPath,CV_LOAD_IMAGE_GRAYSCALE);//IplImage* img = cvLoadImage(clothPath, 1);
        if(img.data==NULL)
            return -1; //读完就可以跳出
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
