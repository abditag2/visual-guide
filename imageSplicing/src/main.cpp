#include "splice.h"
#include <iostream>
#include "png.h"

int main()
{
    PNG inImg;
    inImg.readFromFile("test.png");

    Splice test(inImg);
    test.saveToDisk("Super");
    spliceRange_t x, y;
    x.begin = 200;
    x.end = 300;
    y.begin = 0;
    y.end = 989;
    PNG imgout;

    imgout = test.getImage(string("Super"), x, y).image;
    imgout.writeToFile("test1.png");

    Splice test2("Super");
    imgout = test.getImage(string("Super"), x, y).image;
    imgout.writeToFile("test2.png");

    Splice test3(test2);
    imgout = test.getImage(string("Super"), x, y).image;
    imgout.writeToFile("test3.png");



    return 0;

}
