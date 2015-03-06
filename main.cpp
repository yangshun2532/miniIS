#include "cv.h"
#include "highgui.h"
#define CLOTH_DIR "G:\\BaiduYunDownload\\contest_data\\contest_data\\clothes\\clothes_source\\" //ͼ�������ļ���
#define CLOTH_AMOUNT 100000    //���ļ���
#define CLOTH_FIRST_NUMBER 250001  //��һ���ļ����
int main()
{
    int i;
    char clothPath[120]=CLOTH_DIR;
    for(i=0;i<=CLOTH_AMOUNT;i++)
    {
        int currentNumber=CLOTH_FIRST_NUMBER+i;   //�õ���ǰ�ļ����
        sprintf(clothPath+strlen(CLOTH_DIR),"clothes_%d.jpg",currentNumber);  //�õ���ǰ�ļ�Ŀ¼
        IplImage* img = cvLoadImage(clothPath, 1);
        if(img==NULL)
            return -1; //����Ϳ�������
        cvNamedWindow( "Example1", 0 );
        cvShowImage("Example1", img);
        cvWaitKey(0);
        cvReleaseImage( &img );
        cvDestroyWindow( "Example1" );
    }
    return 0;
}
