# visual-guide

##For the Spring 2015 PURE Research Project under Fardin Abdi

Whenever you upload a file or folder guys, just add a quick description of it here

##edgeDetect.m
 - Matlab function that takes in filename and applies a filter that detects the image and outputs the filtered image

###Uses

edgeDetect(filepath, type, threshold, direction)

0 - canny method, optional threshold and direction<br/>
1 - sobel method, optional threshold and direction<br/>
2 - prewitt method, optional threshold<br/>
3 - roberts method, optional threshold<br/>
4 - laplacian of the gaussian, optional threshold and sigma<br/>
 
##openCV_Image_Search
 - An IntelliJ Project using openCV to find a small image in a larger image given a template.

##Splice class
- Class that handles splitting up a large image into smaller parts on the harddrive using a quadTree structure.  Saves the image inside a folder with NW/SW/NE/SE folders
- Allows the user to create a picture by specifying an x and y range.
- Read .h file for function definitions

##OpenCV_Matching
 - C++ Implementation of template matching
 - USAGE:
    - cannyEdge.cpp: cannyEdge ImagePath Threshold ImageSaveLocation
    - scaledMatching.cpp: scaledMatching templateFile fullFile imageSaveLocation -v verbose flag
