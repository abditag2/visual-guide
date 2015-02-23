package com.tanishqdubey.openCVImageSearch;

import org.opencv.core.Core;
import org.opencv.core.CvType;
import org.opencv.core.Mat;

/**
 * Created by Tanishq Dubey on 2/22/2015.
 */
public class OCVTest {

    public static void TestOCVInstall(){
        System.loadLibrary( Core.NATIVE_LIBRARY_NAME);
        Mat mat = Mat.eye( 3, 3, CvType.CV_8UC1);
        System.out.println("Mat = " + mat.dump());
    }
}
