#include "canny.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "common.h"

static cv::Mat canny_frame, cdst, timg_gray, timg_grad;
static int lowThreshold           = 0;
static int const max_lowThreshold = 100;

int kernel_size = 3;
int edgeThresh  = 1;
int ratio       = 3;

static IplImage* frame;
extern int width;
extern int height;

extern CvCapture* capture;

void CannyThreshold( int, void* )
{
   //Mat mat_frame(frame);
   cv::Mat mat_frame( cv::cvarrToMat( frame ) );

   cv::cvtColor( mat_frame, timg_gray, CV_RGB2GRAY );

   /// Reduce noise with a kernel 3x3
   cv::blur( timg_gray, canny_frame, cv::Size( 3, 3 ) );

   /// Canny detector
   cv::Canny( canny_frame, canny_frame, lowThreshold, lowThreshold * ratio, kernel_size );

   /// Using Canny's output as a mask, we display our result
   timg_grad = cv::Scalar::all( 0 );

   mat_frame.copyTo( timg_grad, canny_frame );

   pthread_mutex_lock( &windowLock );
   cv::imshow( window_name[ 0 ], timg_grad );
   pthread_mutex_unlock( &windowLock );
}

void* executeCanny( void* args )
{
   int dev = 0;
   if ( NULL != args )
   {
      int dev = *( (int*)args );
   }
   //CvCapture* capture;

   cv::namedWindow( window_name[ 0 ], CV_WINDOW_AUTOSIZE );
   // Create a Trackbar for user to enter threshold
   cv::createTrackbar( "Min Threshold:", window_name[ 0 ], &lowThreshold, max_lowThreshold, CannyThreshold );

   //capture = (CvCapture*)cvCreateCameraCapture( dev );
   //cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_WIDTH, width );
   //cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_HEIGHT, height );

   while ( 1 )
   {
      pthread_mutex_lock( &captureLock );
      frame = cvQueryFrame( capture );
      pthread_mutex_unlock( &captureLock );
      if ( !frame )
         break;

      CannyThreshold( 0, 0 );

      char q = cvWaitKey( 33 );
      if ( q == 'q' )
      {
         printf( "got quit\n" );
         break;
      }
   }

   return NULL;
}
