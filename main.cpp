/**
 * Author: Flores, Facundo Gabriel
 * email: flores.facundogabriel@gmail.com
 * Description: Hands-on for Jornadas de Software Libre at UNSA - 2013.
 * 		The program uses a simple grayscale algorithm for image
 * 		processing.
 */

#define __CL_ENABLE_EXCEPTIONS
#if defined(__APPLE__) || defined(__MACOSX)
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif


#include <iostream>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#include "reference.hpp"

//  Load an image using the OpenCV library and create an OpenCL
//  image out of it
cl::Image2D LoadImage(cl::Context context, char *fileName, int &width, int &height)
{
    cv::Mat image = cv::imread(fileName, CV_LOAD_IMAGE_COLOR);
    cv::Mat imageRGBA;
    
    width = image.rows;
    height = image.cols;
    
    cv::cvtColor(image, imageRGBA, CV_BGR2RGBA);
    char *buffer = reinterpret_cast<char *>(imageRGBA.data);
    
    cl::Image2D clImage(context,
                            CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                            cl::ImageFormat(CL_RGBA, CL_UNORM_INT8),
                            width,
                            height,
                            0,
                            buffer);
    return clImage;
}

// Save the image using the OpenCV library
bool SaveImage(char *fileName, char *buffer, int width, int height)
{
    cv::Mat image(cv::Size(width, height), CV_8UC4, buffer, cv::Mat::AUTO_STEP);
    cv::imwrite(fileName, image);
}

// Run the algorithm usign the CPU
void RunSerialAlgorithm(char *fileNamein)
{
    cv::Mat imageIN = cv::imread(fileNamein);
    reference_calculation(imageIN);
    cv::imwrite("serial.bmp", imageIN);    
}

int main(int argc, char **argv) {
    
    RunSerialAlgorithm(argv[1]);

    try{
	std::vector<cl::Platform> platformList;
    
	//Pick platform
	cl::Platform::get(&platformList);
	
	//Pick first platform
	cl_context_properties cpros[] = 
	    {
		CL_CONTEXT_PLATFORM,
		(cl_context_properties)(platformList[0])(),
		0
	    };
    
	    
	// YOU HAVE TO COMPLETE THE FOLLOWING
	// PLEASE FILL WITH THE CORRECT DEVICE
	cl::Context context(..., cpros);
	
	//Set of devices attached to the context
	std::vector<cl::Device> devices = context.getInfo<CL_CONTEXT_DEVICES>();
	
	//Create comman-queue
	cl::CommandQueue queue(context, devices[0], 0);
	
	
	//Load input image to the host and to the GPU
	int width, height;
	cl::Image2D imageInput;
	imageInput = LoadImage(context, argv[1], width, height);
	
	
	//Create output image object
	cl::Image2D imageOutput(context,
				CL_MEM_WRITE_ONLY,
				cl::ImageFormat(CL_RGBA, CL_UNORM_INT8),
				width,
				height,
				0,
				NULL);
	
	
	//Create sampler
	cl::Sampler sampler(context, CL_FALSE, CL_ADDRESS_CLAMP_TO_EDGE,
			    CL_FILTER_NEAREST);
	
	//Read and compile the kernel
	// YOU HAVE TO COMPLETE THE FOLLOWING
	std::ifstream programFile(...);
	
	std::string programString(std::istreambuf_iterator<char>(programFile), 
				    (std::istreambuf_iterator<char>()));
	cl::Program::Sources source(1, std::make_pair(programString.c_str(),
				    programString.length() + 1));
	cl::Program program(context, source);
	program.build(devices);
	
	//Set kernel
	// YOU HAVE TO COMPLETE THE FOLLOWING
	cl::Kernel kernel(program, ...);
	
	kernel.setArg(0,...);
	kernel.setArg(1,...);
	kernel.setArg(2,...);
	kernel.setArg(3,...);
	kernel.setArg(4,...);
	
	//Send kernel to GPU
	// YOU HAVE TO COMPLETE THE FOLLOWING
	queue.enqueueNDRangeKernel(...);
	
	char *buffer = new char[width * height * 4];
	cl::size_t<3> origin;
	origin[0] = 0; origin[1] = 0, origin[2] = 0;
	cl::size_t<3> region;
	region[0] = width; region[1] = height; region[2] = 1;
	
	//Read the image from GPU
	// YOU HAVE TO COMPLETE THE FOLLOWING
	queue.enqueueReadImage(...);
	
	//Save the read image
	SaveImage(argv[2], buffer, width, height);
	
	delete [] buffer;   
    }
    catch(cl::Error err){
	
	std::cerr << "ERROR: " << err.what() << "( " << err.err()
		    << " )" << std::endl;
	return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
