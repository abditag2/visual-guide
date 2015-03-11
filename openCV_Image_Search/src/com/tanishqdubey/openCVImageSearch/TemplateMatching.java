package com.tanishqdubey.openCVImageSearch;

import org.opencv.core.*;
import org.opencv.highgui.Highgui;
import org.opencv.imgproc.Imgproc;

/**
 * Created by Tanishq Dubey on 2/22/2015.
 */
public class TemplateMatching {

    public void run(String inFileName, String matchFileName, String outFileName, int match_method){
        System.out.println("\nStart Template Match...");

        Mat image = Highgui.imread(inFileName);
        Mat template = Highgui.imread(matchFileName);

        Size size = new Size(682, 512);
        Mat dst = new Mat();
        Imgproc.resize(template, dst, size);

        int result_cols = image.cols() - dst.cols() + 1;
        int result_rows = image.rows() - dst.rows() + 1;
        System.out.println("Image Search Rows: " + result_rows);
        System.out.println("Image Search Columns: "+ result_cols);

        Mat result = new Mat(result_rows, result_cols, CvType.CV_32FC1);
        System.out.println(result);

        Imgproc.matchTemplate(image, dst, result, match_method);
        Core.normalize(result, result, 0, 1, Core.NORM_MINMAX, -1, new Mat());


        Core.MinMaxLocResult minMaxLocResult = Core.minMaxLoc(result);

        Point matchLocation;
        if(match_method == Imgproc.TM_SQDIFF || match_method == Imgproc.TM_SQDIFF_NORMED){
            matchLocation = minMaxLocResult.minLoc;
            System.out.println("USING MATCH METHOD: " + match_method);
        } else {
            matchLocation = minMaxLocResult.maxLoc;
            System.out.println("USING MATCH METHOD: " + match_method);
        }

        Core.rectangle(image, matchLocation, new Point(matchLocation.x + dst.cols(), matchLocation.y + dst.rows()), new Scalar(225,255,0));

        System.out.println("Writing: " + outFileName);
        Highgui.imwrite(outFileName, image);
    }
}
