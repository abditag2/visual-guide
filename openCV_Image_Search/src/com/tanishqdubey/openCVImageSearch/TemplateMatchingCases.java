package com.tanishqdubey.openCVImageSearch;

import org.opencv.core.*;
import org.opencv.highgui.Highgui;
import org.opencv.imgproc.Imgproc;

/**
 * Created by Tanishq Dubey on 2/23/2015.
 */
public class TemplateMatchingCases {
    int match_method;
    String match_Append;

    public void run(String inFileName, String matchFileName, String outFileName){
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

        for (int x=0; x < 6; x++){
            switch (x){
                case 0:
                    match_method = Imgproc.TM_CCOEFF;
                    match_Append = "TM_CCOEFF.jpg";
                    break;
                case 1:
                    match_method = Imgproc.TM_SQDIFF;
                    match_Append = "TM_SQDIFF.jpg";
                    break;
                case 2:
                    match_method = Imgproc.TM_SQDIFF_NORMED;
                    match_Append = "TM_SQDIFF_NORMED.jpg";
                    break;
                case 3:
                    match_method = Imgproc.TM_CCOEFF_NORMED;
                    match_Append = "TM_CCOEFF_NORMED.jpg";
                    break;
                case 4:
                    match_method = Imgproc.TM_CCORR;
                    match_Append = "TM_CCORR.jpg";
                    break;
                case 5:
                    match_method = Imgproc.TM_CCORR_NORMED;
                    match_Append = "TM_CCOEFF_NORMED.jpg";
                    break;
                default:
                    System.out.println("FINISHED OR ERROR!!!");

            }
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
            image = Highgui.imread(inFileName);
            Core.rectangle(image, matchLocation, new Point(matchLocation.x + dst.cols(), matchLocation.y + dst.rows()), new Scalar(225,0,0));
            System.out.println("Writing: " + outFileName+match_Append);
            Highgui.imwrite(outFileName+match_Append, image);
        }


    }
}
