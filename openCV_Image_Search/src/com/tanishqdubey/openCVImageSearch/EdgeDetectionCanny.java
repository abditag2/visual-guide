package com.tanishqdubey.openCVImageSearch;

import org.opencv.core.Mat;
import org.opencv.core.Size;
import org.opencv.highgui.Highgui;
import org.opencv.imgproc.Imgproc;

/**
 * Created by Tanishq Dubey on 3/17/2015.
 */
public class EdgeDetectionCanny {

    public static void EdgeCanny(String inFileName, String outFileName){
        System.out.println("Starting Edge Detection");
        Mat inImage = Highgui.imread(inFileName);

        Imgproc.Canny(inImage, inImage, 10, 400);
        Highgui.imwrite(outFileName, inImage);
    }

}
