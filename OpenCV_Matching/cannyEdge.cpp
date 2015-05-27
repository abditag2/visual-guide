/*
 *  @author: Tanishq Dubey
 *
 *
 *
*/


#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>

using namespace cv;

Mat src, src_gray;
Mat dst, detected_edges;

int edgeThreshold = 10;
int lowThreshold;
int const max_lowThreshold = 900;
int ratio = 3;
int kernel_size = 3;

char* window_name = "Edge Detection Mapping";

int main(int argc, char** argv){
    src = imread(argv[1]);
    if( !src.data){
        printf("Image has no data (Bad Image?), exiting with E: -1.\n");
    }

    if( argc!= 4 ){
        printf("Syntax Error!\n");
        printf("Usage: cannyEdge <ImagePath> <Threshold> <ImageSaveLocation> \n");
    }

    dst.create(src.size(), src.type());
    cvtColor( src, src_gray, CV_BGR2GRAY );

    namedWindow( window_name, CV_WINDOW_NORMAL );
    int threshLowArg;
    threshLowArg = atoi(argv[2]);
    printf("Detecting Edges with threshold of: %d \n", *&threshLowArg);
    
    printf("Beginning Edge Detection!\n");
    int t0 = time(NULL);
    blur( src_gray, detected_edges, Size(3,3) );
    Canny( detected_edges, detected_edges, threshLowArg, threshLowArg*ratio, kernel_size);
    dst = Scalar::all(0);
    src.copyTo(dst, detected_edges);
    int t1 = time(NULL);
    printf("Edge Detection Completed in %d seconds\n", t1-t0);
    imwrite(argv[3], dst);
    //imshow(window_name, dst);

    //waitKey(0);

    return 0;
}
