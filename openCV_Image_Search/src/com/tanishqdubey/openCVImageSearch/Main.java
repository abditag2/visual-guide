package com.tanishqdubey.openCVImageSearch;

import org.opencv.core.Core;
import org.opencv.imgproc.Imgproc;

public class Main {

    public static void main(String[] args) {

        //OCVTest.TestOCVInstall(); //Test to see if OpenCV is installed correctly

        System.loadLibrary(Core.NATIVE_LIBRARY_NAME);

        new TemplateMatching().run("TestImages/fullImage.png", "TestImages/templateImage.png", "TestImages/resultImage.png", Imgproc.TM_CCOEFF);
    }
}
