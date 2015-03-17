package com.tanishqdubey.openCVImageSearch;

import org.opencv.core.Core;
import org.opencv.imgproc.Imgproc;

public class Main {

    public static void main(String[] args) {

        //OCVTest.TestOCVInstall(); //Test to see if OpenCV is installed correctly

        System.loadLibrary(Core.NATIVE_LIBRARY_NAME);

        /*Runs once, generates one image*/
        //new TemplateMatching().run("TestImages/fullImage.jpg", "TestImages/templateImage.jpg", "TestImages/resultImage.jpg", Imgproc.TM_CCOEFF);


        /*Runs once, generates multiple images based on different matching filters */
        //new TemplateMatchingCases().run("TestImages/fullImage.jpg", "TestImages/templateImage.jpg", "TestImages/resultImage");

        /*Runs once, uses edge detected images to locate*/
        EdgeDetectionCanny.EdgeCanny("TestImages/fullImage.jpg","TestImages/fullImageEdge.jpg");
        EdgeDetectionCanny.EdgeCanny("TestImages/templateImage.jpg","TestImages/templateImageEdge.jpg");
        new TemplateMatching().run("TestImages/fullImageEdge.jpg", "TestImages/templateImageEdge.jpg", "TestImages/resultImageEdge.jpg", Imgproc.TM_CCOEFF);

    }
}