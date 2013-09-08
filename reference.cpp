/**
 * Author: Flores, Facundo Gabriel
 * email: flores.facundogabriel@gmail.com
 * Description: Hands-on for Jornadas de Software Libre at UNSA - 2013.
 * 		The program uses a simple grayscale algorithm for image
 * 		processing.
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#include "reference.hpp"

void reference_calculation(cv::Mat &imageInput)
{
    for(int i = 0; i < imageInput.rows; i++)
    {
	for(int j = 0; j < imageInput.cols; j++)
	{
	    
	    uchar x = imageInput.at<cv::Vec3b>(j,i)[0];
	    uchar y = imageInput.at<cv::Vec3b>(j,i)[1];
	    uchar z = imageInput.at<cv::Vec3b>(j,i)[2];
	    
	    uchar g = (x+y+z)/3;
	    
	    imageInput.at<cv::Vec3b>(j,i)[0] = g;
	    imageInput.at<cv::Vec3b>(j,i)[1] = g;
	    imageInput.at<cv::Vec3b>(j,i)[2] = g;
	 }
    }
}