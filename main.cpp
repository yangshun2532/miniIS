#include "cv.h"
#include "highgui.h"
#define CLOTH_DIR "G:\\BaiduYunDownload\\contest_data\\contest_data\\clothes\\clothes_source\\" //图像集所在文件夹
#define CLOTH_AMOUNT 100000    //总文件数
#define CLOTH_FIRST_NUMBER 250001  //第一个文件编号
int main()
{
    int i;
    char clothPath[120]=CLOTH_DIR;
    for(i=0;i<=CLOTH_AMOUNT;i++)
    {
        int currentNumber=CLOTH_FIRST_NUMBER+i;   //得到当前文件编号
        sprintf(clothPath+strlen(CLOTH_DIR),"clothes_%d.jpg",currentNumber);  //得到当前文件目录
        IplImage* img = cvLoadImage(clothPath, 1);
        if(img==NULL)
            return -1; //读完就可以跳出
        cvNamedWindow( "Example1", 0 );
        cvShowImage("Example1", img);
        cvWaitKey(0);
        cvReleaseImage( &img );
        cvDestroyWindow( "Example1" );
    }
    return 0;
}
