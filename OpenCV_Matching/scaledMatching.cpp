#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>

using namespace std;
using namespace cv;

Mat templateSrc, fullSrc;
Mat resized, dst;
bool printVerbose = false;
double resizeRatio;

double maxCurrentCorrelationFactor = 0;
double minCurrentCorrelationFactor = 0;
Point minCurrentLocation;
Point maxCurrentLocation;

double maxAllCorrelationFactor = 0;
double minAllCorrelationFactor = 0;
Point minAllLocation;
Point maxAllLocation;

double finalRatio;


int main(int argc, char** argv)
{
    //If wrong number of arguments, throw error
    if(argc != 4)
    {
        printf("Syntax Error! Usage: scaledMatching <templateFile> <fullFile> <imageSaveLocation> <-v verbose flag");
        return -1;
    }

    templateSrc = imread(argv[1]);
    fullSrc = imread(argv[2]);
    
    //Used to print verbose output
    if(argv[4] == "-v")
    {
        printVerbose = true;
    }
    
    //Used to record runtime
    int t0 = time(NULL);

    //Scaled Matching
    for (double i = 1.0; i > .2; i = i - .1)
    {
    	resize(fullSrc, resized, Size(),i,i, CV_INTER_AREA);
    	resizeRatio = fullSrc.rows / resized.rows;
    	if(printVerbose){
            printf("Resize Ratio: %d %d %f \n", fullSrc.rows, resized.rows, resizeRatio );
        }
        //Check to make sure template is not bigger than scaled
    	if(resized.rows < templateSrc.rows || resized.cols < templateSrc.cols)
    	{
    		break;
    	}
        
    	matchTemplate(resized, templateSrc, dst, CV_TM_CCOEFF_NORMED);
    	minMaxLoc(dst, &minCurrentCorrelationFactor, &maxCurrentCorrelationFactor, &minCurrentLocation, &maxCurrentLocation );
        if(printVerbose){
            printf("Current Currelation Factor; %f\n", maxCurrentCorrelationFactor);
        }

    	if (maxCurrentCorrelationFactor > maxAllCorrelationFactor){
    		if(printVerbose){
                printf("NEW MAX CORRELATION FACTOR FOUND: %f \n", maxCurrentCorrelationFactor);
            }
            maxAllCorrelationFactor = maxCurrentCorrelationFactor;
    		maxAllLocation = maxCurrentLocation;
    		finalRatio = resizeRatio;
    	}
    }
    
    //Get runtime end
    int t1 = time(NULL);
    printf("Edge Detection Completed in %d seconds\n", t1-t0);
   //Draw rectangle
    rectangle(fullSrc, Point(maxAllLocation.x*finalRatio, maxAllLocation.y * finalRatio), Point((maxAllLocation.x*finalRatio)+templateSrc.cols, (maxAllLocation.y * finalRatio) + templateSrc.rows), Scalar(255,0,225), 5, 8, 0 );

    //Write Image
    imwrite(argv[3], fullSrc);
    return 0;
}
