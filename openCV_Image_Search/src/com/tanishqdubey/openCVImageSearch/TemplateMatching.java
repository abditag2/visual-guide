package com.tanishqdubey.openCVImageSearch;

import org.opencv.core.*;
import org.opencv.highgui.Highgui;
import org.opencv.imgproc.Imgproc;

/**
 * Created by Tanishq Dubey on 2/22/2015.
 */
public class TemplateMatching {

    public void run(String inFileName, String matchFileName, String outFileName, int match_method){
        System.out.print("\nStart Template Match...");

        Mat image = Highgui.imread(inFileName);
        Mat template = Highgui.imread(matchFileName);

        int result_cols = image.cols() - template.cols() + 1;
        int result_rows = image.rows() - template.rows() + 1;

        Mat result = new Mat(result_rows, result_cols, CvType.CV_32FC1);

        Imgproc.matchTemplate(image, template, result, match_method);
        Core.normalize(result, result, 0, 1, Core.NORM_MINMAX, -1, new Mat());

        Core.MinMaxLocResult minMaxLocResult = Core.minMaxLoc(result);

        Point matchLocation;
        if(match_method == Imgproc.TM_SQDIFF || match_method == Imgproc.TM_SQDIFF_NORMED){
            matchLocation = minMaxLocResult.minLoc;
        } else {
            matchLocation = minMaxLocResult.maxLoc;
        }

        Core.rectangle(image, matchLocation, new Point(matchLocation.x + template.cols(), matchLocation.y + template.rows()), new Scalar(225,0,0));

        System.out.println("Writing: " + outFileName);
        Highgui.imwrite(outFileName, image);
    }
}
