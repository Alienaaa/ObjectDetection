
#include <cv.h>
#include <highgui.h>
#include <stdio.h>

int main( int argc, char** argv )
{
     IplImage* image; 

 	 image = cvLoadImage( "D:/test.jpg" );
//   if( !image ) return -1;
//	 IplImage* rgb=cvCreateImage(cvGetSize(image), 8, 3);
     IplImage* hsv=cvCreateImage(cvGetSize(image), 8, 3);
	 IplImage* hue=cvCreateImage(cvGetSize(image), 8, 1); 
	 IplImage* t_hue=cvCreateImage(cvGetSize(image), 8, 1); 

	 if(!image) return -1;

	 cvCvtColor(image, hsv, CV_BGR2HSV);
	 cvSplit( hsv, hue, 0, 0, 0 ); 

	 cvShowImage("HUE",hue);
     cvThreshold(hue,t_hue, 100, 255.0,CV_THRESH_BINARY);
///
	 CvMemStorage *stor = 0;
	 stor =cvCreateMemStorage(0); 
	 CvSeq * contour = 0;
	 contour = cvCreateSeq(CV_SEQ_ELTYPE_POINT, sizeof(CvSeq), sizeof(CvPoint), stor); 

	 cvFindContours(t_hue,stor,&contour, sizeof(CvContour), CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE , cvPoint(0,0)  ); 
     for (CvSeq* external = contour; external; external = external->h_next)
	 {
		 float contour_area_tmp = fabs(cvContourArea( external, CV_WHOLE_SEQ )); 
		 if(contour_area_tmp <= 1000)
		 {
		 //remove current small contour
			 cvDrawContours(t_hue,external,cvScalar(0),cvScalar(0),0,CV_FILLED,8,cvPoint(0,0));
			 continue;
 
		 }
		 else
		 {
		 //cvZero(pContourImg);
			 //½«ÂÖÀª»­³ö    
			 cvDrawContours(t_hue, external, cvScalar(255),cvScalar(255),0,CV_FILLED, 8, cvPoint(0,0));
 
         }

	 }



	     cvThreshold(hue,hue, 100, 255.0,CV_THRESH_BINARY);

///	

     cvNamedWindow( "test", 1 );
	// cvNamedWindow( "HUE", 1);
	// cvNamedWindow( "ÂÖÀª", 1);
	 cvNamedWindow("È¥Ôë",1);

     cvShowImage("test", image );
	// cvShowImage("HUE", hue );
	// cvShowImage("ÂÖÀª", t_hue );
	 cvShowImage("È¥Ôë",t_hue);

     cvWaitKey();

     cvDestroyWindow("test");
   //  cvDestroyWindow("HUE");
	// cvDestroyWindow("ÂÖÀª");
	 cvDestroyWindow("È¥Ôë");
     cvReleaseImage(&image);
     cvReleaseImage(&hue);
	 cvReleaseImage(&t_hue);


     return 0; 


}

