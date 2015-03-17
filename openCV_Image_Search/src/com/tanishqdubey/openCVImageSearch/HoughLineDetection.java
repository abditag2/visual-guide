package com.tanishqdubey.openCVImageSearch;


import org.opencv.core.Mat;
import org.opencv.highgui.Highgui;
import org.opencv.imgproc.Imgproc;
import processing.core.PConstants;

import java.util.ArrayList;

/**
 * Created by Tanishq Dubey on 3/17/2015.
 */
public class HoughLineDetection {

    ArrayList<Line> lines;
    public void HoughLine(String inImageName, String outImageName){
        System.out.println("Starting Hough Line Method on: " + inImageName);
        Mat inImage = Highgui.imread(inImageName);
        Imgproc.Canny(inImage, inImage, 10, 200);

        lines = findLines(100, 30 ,20, inImage);


    }

    public static ArrayList<Line> findLines(int threshold, double minLineLength, double maxLineLength, Mat currentMat){
        ArrayList<Line> result = new ArrayList<Line>();

        Mat lineMat = new Mat();
        Imgproc.HoughLines(currentMat, lineMat, 1, PConstants.PI/180.0,threshold, minLineLength, maxLineLength);
        for(int i = 0; i< lineMat.width(); i++){

        }
        return result;
    }
}
