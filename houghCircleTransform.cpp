#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

/** @function main */
int main(int argc, char** argv)
{
  Mat src, src_gray, thres;

  /// Read the image
  src = imread( "Untitled.png" );

  if( !src.data )
    { return -1; }

  /// Convert it to gray
  cvtColor( src, src_gray, CV_BGR2GRAY );

  /// Reduce the noise so we avoid false circle detection
  //GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );
  //adaptiveThreshold(src_gray, thres, 150, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 5, 0);
  //threshold(src_gray, thres, 50, 255, CV_THRESH_OTSU);
  //Canny(src_gray, src_gray, 1, 90);

  vector<Vec3f> circles;

  /// Apply the Hough Transform to find the circles
  HoughCircles( src_gray, circles, CV_HOUGH_GRADIENT, 1, 30.0, 30, 20, 1, 30 ); //( src_gray, circles, CV_HOUGH_GRADIENT, 1, 30.0, 30, 30, 1, 30 );

  /// Draw the circles detected
  for( size_t i = 0; i < circles.size(); i++ )
  {
      Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
      int radius = cvRound(circles[i][2]);
      // circle center
      circle( src, center, 3, Scalar(0,255,0), -1, 8, 0 );
      // circle outline
      circle( src, center, radius, Scalar(0,0,255), 3, 8, 0 );
  }
  printf("%d", circles.size());
  imwrite("circles2.jpg", src);
  /// Show your results
  namedWindow( "Hough Circle Transform Demo", 0 );
  imshow( "Hough Circle Transform Demo", src );

  waitKey(0);
  return 0;
}

